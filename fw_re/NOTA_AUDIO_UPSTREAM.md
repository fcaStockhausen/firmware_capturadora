# NOTA: camino UPSTREAM para el acople video→audio (17/11, post-investigación)

> Estado: el thump está MITIGADO host-side (notch adaptativo en scalapp,
> commit 1588755 — mide el par y re-afina en caliente). Este documento
> es el mapa de lo que existe PARA ARREGLARLO DEL LADO DEL CHIP, con
> riesgo rankeado. Nada de acá debería ejecutarse sin leer
> RESCATE_ROM.md primero (precedente: un experimento tiró el bus;
> replug revivió; flash JAMÁS tocado por esta línea de trabajo).

## Qué sabemos del mecanismo (resumen de RE.md)
- Tones inyectados EN LAS MUESTRAS, portador en múltiplos de la tasa
  UVC (2×f_uvc), par batiendo ~0.7-1Hz, SOLO con video streameando.
- UAC sin EP de feedback → el host no corrige → queda en banda.
- La config del bloque de audio (f100-f12a) se computa desde
  constantes de tasa de video (f124:f125=120, f126:f127=60); escribir
  f127 mató la entrega al instante (acople ESTRUCTURAL).
- Divisores estáticos en runtime (falsificado el re-tuning dinámico).

## Qué sabe la comunidad (recursos verificados 17/11)
- **ultrasemier/ms213x_community + FOSDEM docs**: `audio_route_t` en
  FLASH 0x00FB80 (ROM 0xFB50) — sample_rate (0=48k, 1=96k),
  i2s_in_mode (slave/master), mix3_mode (fuente del mixer: HDMI RX /
  I2S1 / I2S2 / combinaciones), i2s1_mode, usb_out_mute, lk621_en
  (configura chip de reloj externo LK621 @I2C 0x26/0x20 — SOLO en el
  diseño de referencia con codec; nuestro stick NO lo tiene).
- **HIDCMD documentado** (FOSDEM): SFR/IDATA/XDATA RD/WR (B5/B6/C5/C6)
  y FLASH RD/WR (F7/F8) por HID — el audio_route_t es editable sin
  abrir el chip.
- **BertoldVdb/ms-tools**: librería Go + CLI para el HID de fábrica
  (XDATA/EEPROM/FLASH, call-a-función, patching runtime). Issue #14:
  MS2131 parpadea leyendo RAM (fragilidad conocida del HID con
  streaming activo — coincide con nuestro formatguard).
- **steve-m/hsdaoh**: los que más saben del isócrono USB del MS2130/31
  (lo usan como SDR de 100+ MB/s). hsdaoh_test MIDE estabilidad del
  reloj de salida. Registraron el modo "transparente" de video
  (f039/f6b0/f6be/f65c/f65e/f6bf/f600 — solapa con nuestro mapa).
  PUNTO DE CONTACTO para preguntar por el clocking del isoc de AUDIO.
- **Reseña bilibili (2022)**: "USB3 干扰…obs里面音频会有噪音" — el
  ruido de audio con USB3 es defecto CONOCIDO de la familia; lo
  atribuyen a interferencia de blindaje. Nadie publica fix del chip.
- **amnemonic/MacroSilicon**: mapa XDATA MS2109 (UserConfig 0xCBD0) —
  referencia para buscar el equivalente MS2131.

## Rutas upstream, rankeadas por (valor / riesgo)
1. **audio_route_t.sample_rate = 96k** (1 byte de flash, campo
   DOCUMENTADO para customización): cambia toda la cadena de divisores
   de audio. Podría (a) mover el acople, (b) matarlo si la cadena 96k
   deriva de otro dominio, (c) no cambiar nada. Riesgo BAJO (región de
   user-config, no código; toolkit listo; backups múltiples) pero no
   cero (historial de brick). 96k UAC: los hosts lo soportan.
   → Experimento de 15 minutos CON AUTORIZACIÓN del dueño del card.
2. **Preguntarle a la comunidad** (issue en steve-m/hsdaoh o
   BertoldVdb/ms-tools): "audio isochronous clocking on MS2131 —
   tones at 2×UVC rate injected in samples, anyone mapped the audio
   clock domain?" — costo cero, posible atajo si alguien ya lo tiene.
3. **RE profundo del f10x/f12x** (derivación de divisores desde
   0x4d0c + helpers 0x6da4/0x6e40/0x6e64/0x6e75): encontrar de dónde
   sale el reloj fuente y si hay un bit de selección cristal-vs-video.
   Sin documentación pública = semanas. Requiere tarjeta de sacrificio
   para probar valores.
4. **Parche de firmware reescribiendo la derivación**: solo después de
   (3). Precedente de parche de 1 byte existe (jmp120), pero este no
   es de 1 byte.
5. **lk621_en / ruteo I2S**: muerto para nuestro stick (no tiene el
   hardware del diseño de referencia).

## Falsado (no repetir)
- Retuning dinámico de divisores en runtime: NO (12s @10Hz, 0 cambios).
- f127 (constante "60") como knob: escribirlo mata la entrega (y un
  restore equivocado tiró el bus del USB — revivió con replug).
- Notches fijos: el par VAGUEA ±0.15Hz entre sesiones y ±0.05 dentro
  (por eso el adaptativo host-side).

## Decisión operativa vigente
Mitigación host-side (notch adaptativo scalapp) = estado de producción.
Upstream = las rutas 1-2 de arriba, pendientes de decisión del dueño.

## Resultado de la ruta 1 (17/11 noche): INAPLICABLE — con evidencia
- Lectura completa de flash (ms213x_flash -r): 62,715 bytes = header
  (0x30) + código (0xF4C7) — la imagen NO incluye la zona de user-data
  0xF830+ donde vive audio_route_t según FOSDEM.
- Escaneo de código: CERO referencias a 0xFB80/0xFB50 como datos (los
  `mov dptr,#0xF8xx/0xFBxx` son registros XDATA, no lecturas de
  user-config). Este build UltraSemi (bcdDevice 31.00) no implementa
  la estructura del build de referencia.
- XDATA 0xC800-0xD000 muerto (todo 00/FF) — sin copia runtime de la
  config (el layout 0xCBD0 del MS2109 no aplica).
- El descriptor UAC ofrece SOLO 48000Hz (tSamFreq único, 0xBB80) — el
  host no puede negociar 96k aunque el chip tuviera el modo.
- Dato curioso para el futuro: f12a=249 → 24e6/249 = 96,385Hz ≈ 2×48k
  +0.4% (¿divisor de MCLK 2×fs?). Y el dispatcher de audio tiene modos
  4/5/7 por IRAM 0x16 — si alguno fuera 96k, habría que ofrecerlo en
  el descriptor para que el host lo pida.

## Ruta 1-bis (pendiente de autorización EXPLÍCITA — otra clase de riesgo)
Parchear los DESCRIPTORES en flash (datos, no código): tSamFreq
48000→96000 (80 BB 00 → 80 77 01 @ ~0x728/0xcb2) + wMaxPacketSize
192→384 (C0 00 → 80 01). Especulativo: ¿el firmware tiene path de
config para 96k (¿modo 7?) o ignorará el pedido? Fallo → restaurar
backup (tooling listo). NO ejecutar sin autorización.
