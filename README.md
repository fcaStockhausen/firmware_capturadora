# firmware_capturadora — MS2131 1080p120

Ingeniería inversa y fixes para la capturadora **MacroSilicon MS2131**
(USB 0x345F:0x2131, USB3, HDMI in → UVC out).

## Estado actual

- **Firmware en la tarjeta**: `flat3` (jmp120 + {8758,9bd1,dab7,e655})
  — el de régimen validado en el soak del 27/10.
- **Receta operativa** (automática, aprobada por el usuario): el
  LaunchAgent `cl.fcaraneda.ms2131formatguard` corre el guard v3
  desde el login — vigila drops de formato a 720p y los corrige,
  con pausa HID cuando scalapp streamea (ver Uso diario).
- Estado real medido (con patrón de calibración y veredicto visual):
  1080p60 **perfecto 1:1**; 1080p120 **nítida con receta** (el hardware
  muestrea a medio ancho por política de MacroSilicon — ver abajo).
- Comportamiento HID↔isoch documentado el 29/10: `CASUISTICA.md`
  (todo acceso HID con el stream abierto glitchea el audio).

## Uso diario

Nada manual: al prender la Mac, el LaunchAgent arranca el daemon
(`tools/ms2131_formatguard.py` **v3**), que:

1. Si hay un cliente streameando (scalapp, vía pgrep): **pausa HID
   total** — no toca el dispositivo (todo acceso HID mientras streamea
   glitchea el audio isócrono; ver `CASUISTICA.md`). El formato lo
   renegocia el cliente al abrir.
2. Sin clientes: vigila [22DE:DF] por HID puro y corrige drops a 720p
   con `setformat` (watchdog + backoff anti-guerra).

Log: `/tmp/ms2131_formatguard.log`. Desactivar:
`launchctl bootout gui/$(id -u)/cl.fcaraneda.ms2131formatguard`

## Lo que se sabe del hardware (resumen)

Documentación técnica completa en `fw_re/RE.md` y bitácora en `BITACORA.md`.

- **La diezmación a 1080p120 es política deliberada de MacroSilicon**:
  pclk ≥ 200 MHz → el scaler se configura a medio ancho (batería
  f620-f651 + modo f65c=0x08). YUYV 1080p120 completo = 497 MB/s (límite
  USB3). No vive en un registro único: forzar f660 solo = imagen estirada
  2×; forzar f65c solo = ruido.
- **Mapa de registros** (todos los pares son LITTLE-ENDIAN):
  - `f600` run/stop · `f604/f606/f60e/f60c` ← walk 0xBC02 (structA @1AE2)
  - `f660/f661` = **el ancho real de captura**; `f662/f663` = alto
  - `f618`, `f65c` = readbacks de hardware (sin escritor en el firmware)
  - 0xBC02 no retorna (tail `ljmp 0xD374`); structA es buffer compartido
    con el chat I2C del receptor
- **Rescate de bricks**: la mask ROM (534d:2130, "USB Video") es accesible
  por la interfaz #4 oculta de USB3 → `tools/rom_flash <imagen.bin>`
  (erase chip + write + verify). La ROM es inmortal: si no enumera, es
  energía o chip muerto, no firmware.

## Estructura

```
tools/    ms213x_flash, ms213x_xdata, rom_flash, ms2131_fix120(d),
          ms2131_setformat, ms2131_smartguard.py, ms213x_estado.py
fw_re/    RE.md (referencia técnica RE), code_original.bin, xdata_scan.py
analysis/ patch_*.py (genealogía de parches), suite_dump.sh, patron_*.png
backup/   todos los firmwares (original 2025-04-09 + genealogía jmp120)
BITACORA.md  registro cronológico de sesiones
RESCATE_ROM.md  procedimiento de rescate por interfaz oculta
```

## Flashear

```
tools/ms213x_flash backup/MS2131_jmp120.bin     # vía normal (firmware vivo)
tools/rom_flash  backup/MS2131_jmp120.bin       # rescate (modo ROM)
```
Tras flashear: replug del USB. Volver a fábrica:
`tools/ms213x_flash backup/MS2131_2025-04-09_backup_2617_44fc.bin`

## Referencias

- https://github.com/steve-m/ms213x_flash — flasher MS2130/S/31/S
- https://github.com/steve-m/hsdaoh — registros del scaler (f65c/f6b0/etc.)
- https://github.com/BertoldVdb/ms-tools — investigación MS210x/2130
- https://github.com/Starainrt/ms213x-rename — EDID en flash
