# BITÁCORA — firmware_capturadora

> Registro cronológico de sesiones. El estado actual y el uso diario están en
> `README.md`; la documentación técnica de RE en `fw_re/RE.md`.

---

## 2026-10-13 — Diagnóstico inicial, EDID, tabla de timings, fix en vivo

- Problema: entrada 1080p120 → captura "agrandada/distorsionada"; 60 Hz bien.
- Causa demostrada: la tabla de timings del firmware no tiene 1080p120; el
  clasificador cae al preset 4K30 (mismo pclk) que aplica diezmación ÷2
  pensada para 3840→1920. Scaler captura 960 y estira a 1920.
- Experimentos EDID (quitar VIC 62/63/64) y tabla (entry 1080p120): no
  cambian nada — el ÷2 se decide en código contra el pclk MEDIDO.
- **Solución operativa**: LaunchAgent `cl.fcaraneda.ms2131fix120` (daemon
  smartguard) corrige en caliente (f606/f618/f660=1920 + f65c=0x10,
  stop→start). Validado en producción (Discord, capturas locales).

## 2026-10-13 noche — Bricks v4/v5/v6/v7 y su causa raíz

- Code caves consecutivos (v4/v5/v6/v7/testB) tumbaban el chip.
- Causa raíz hallada: dos `AJMP 0xBF5B` (desde 0xC267 y 0xC26E) entran al
  MEDIO del bloque 0xBF01 (colas compartidas del compilador). Modificar
  bytes en 0xBF56-0xBF5D = ejecución de basura = chip muerto pre-USB.
- Recovery probado: sin HDMI el USB enumera + catcher que flashea apenas
  aparece + replug.
- Diseño "correcto" de la época: wrapper en 0xF3D9 vía hook del único
  caller (0x5856) — `backup/MS2131_native_wrapper.bin` (nunca flasheado).
- Brick testB final del día → abre la vía de rescate por ROM.

## 2026-10-15/17 — Rescate por ROM, RE completo, jmp120

- Brick testB → descubrimiento de la **interfaz #4 oculta en USB3** que
  responde a control transfers crudos `wIndex=4` → `tools/rom_flash`
  (setup SPI, erase chip, write por páginas, verify). Rescate documentado
  en `RESCATE_ROM.md`.
- RE completo del firmware (radare2 `-a 8051`): cadena de config
  0x569E-0x5860, clamp min(entrada, formato) en 0x5707, ÷2 del clasificador
  en 0x356F.
- **Fix nativo jmp120**: 1 byte (código 0x3569, flash 0x3599: `50→80`,
  jnc→jmp) — salta la halving del hot-switch. Verificado triple.

## 2026-10-17 tarde-noche — Cacería del transitorio 960: el mapa real

- Meta: eliminar el residuo 960 latchado en f606 tras eventos de modo sin
  stream (el síntoma Discord/Deck).
- **Revolución metodológica**: la métrica H/V sobre contenido arbitrario
  miente (ruido puntúa alto, juego real bajo). La "degradación progresiva"
  1.297→0.255 de la noche era contenido. Medición válida = patrón de
  calibración 1:1 (Firefox F11 — el visor de imágenes del Deck escalaba
  1.78× horizontal y contaminó media noche) + mapeo geométrico + veredicto
  visual del usuario.
- **Mapa real de registros** (dump 256B 60 vs 120 + RE):
  - f604/f606/f60e/f60c ← walk 0xBC02 (structA @1AE2)
  - **f660/f661 = el ancho REAL de captura** (+f662/f663 alto) ← applier
    0xBF01 (structB @1AEA)
  - f618 y f65c = **readbacks de hardware, sin escritor en el firmware**
  - Pares **LITTLE-ENDIAN** (f606=lo, f607=hi)
  - 0xBC02 **no retorna** (tail `ljmp 0xD374` en 0xBC61) — el código tras
    su lcall es muerto
  - structA es buffer compartido con el chat I2C del receptor: el walk lee
    veneno a mitad de su propia lectura (por eso cada evento latcheaba
    basura distinta: 960, 720, 50, 2853)
- Genealogía de parches de la noche (en `backup/`, scripts
  `analysis/patch_*.py`):
  - v3 reclean ([22DE] como fuente): insuficiente (el formato transita
    fallback)
  - v4 applier (fuente [1AE2]): la carrera está en el walk, no antes
  - v6/v7/v8 postfix/tailhook: f606 era el registro equivocado
  - v9/v10/v11 applier2/3: corrigió el boot-default (f660=1920) pero
    **descubrió el bug de endianness** (escribía LE 0x8007=32775)
  - v12 noclass: flag 0x20.1 es flag GENERAL (15 setters) — en vano,
    revertido
- **La política de 120Hz** (causa raíz definitiva): pclk≥200MHz → preset de
  MEDIO ANCHO distribuido en la batería f620-f651 + f65c=0x08. Deliberada
  de MacroSilicon (banda USB3: YUYV 1080p120=497MB/s). No vive en un
  registro: forzar f660 solo = estirado 2×; forzar f65c solo = ruido puro
  (ambos verificados por el usuario con patrón).
- **Veredicto del usuario con patrón**: 60Hz perfecto 1:1 (H/V=1.604);
  120Hz con la receta histórica = nítida, aprobada. La evidencia "nítida"
  de la semana pasada (veredicto_120fix.png) también estaba diezmada
  (gx 8.8 vs 26.8 del original) — la métrica de entonces no lo veía.
- Estado final: jmp120 puro + daemon (receta automática aprobada). Parches
  revertidos, quedan en backup/ como genealogía.

## 2026-10-18 madrugada — Incidente ROM espontáneo + rescate limpio

- La capturadora amaneció caída a su ROM de fábrica (534d:2130, "USB
  Video") SIN corrupción de flash (magic 3c c3 válido — crash del chip,
  no brick). Replug no revivió.
- `rom_flash backup/MS2131_jmp120.bin` por la if#4: VERIFY OK a la primera
  + replug → boot normal. Estado verificado: 1080p120, suite 1920/0x10,
  smartguard corriendo.
- Lección: si se repite, sospechar alimentación (probar puerto directo).

## 2026-10-18 tarde — El ciclo de caídas y el diagnóstico en curso

- Secuencia del día: escribí `f601=0x47` (experimento de descarte del diff
  60/120) → el chip murió minutos después → escalada: ROM espontánea →
  USB2 fallback (avfoundation sin video) → nodo sin interfaces
  (crash-on-HDMI) → detach total → solo ROM en puerto directo.
- **Crash-on-HDMI confirmado por el usuario**: sin HDMI el firmware vive;
  al conectar la Deck (1080p120) se cuelga la enumeración.
- Herramienta estandarizada creada: `tools/ms213x_estado.py` (detección por
  VID:PID, no por nombres — tres fallos de grep en un día enseñaron la
  lección). BUG del parser: `+-o` son DOS caracteres, no uno.
- Flash re-escrita 3× (jmp120) — siempre VERIFY OK.
- Hipótesis en prueba al cierre: crash-on-HDMI disparado por el procesado
  de la señal (camino de config) vs hardware marginal. Pendiente: flashear
  el ORIGINAL de fábrica como baseline (si el crash persiste con él, no es
  firmware; si desaparece, jmp120 está implicado).
- Nota del usuario: "la conectoré a USB3 y queda como USB" — el fallback
  USB2 se daba también en puerto directo.

## 2026-10-19 — Diagnóstico final del día: el daño es específico de 120Hz

- Pruebas con ORIGINAL de fábrica (cero parches): sin HDMI vivo; con HDMI
  a 1080p120 = crash (firmware descartado como causa).
- Con la Deck a **1080p60 + HDMI: el dispositivo VIVE** — el daño es
  específico del procesado de 120Hz (corriente/banda pico).
- Captura de recuperación a 60Hz tomada y mostrada al usuario.
- Estado del sistema: firmware jmp120 (verificado), suite aplicada, guard
  corriendo. La device es usable a 1080p60.
- Experimento pendiente (gratis): dejarla SIN energía toda la noche
  (USB+HDMI fuera) y retestear 120Hz mañana — los componentes marginales
  a veces se recuperan tras descarga completa.
- Asumido por el agente: la cascada de daño empezó con la escritura
  experimental de f601 (valor de modo-60 en estado-120). Lección: los
  registros con cero escritores de firmware son territorio prohibido.

## 2026-10-21 — RESUELTO: el descanso curó el hardware

- Dos días sin energía (lunes→miércoles) y el crash-on-120Hz desapareció.
- La device revivió completa: boot firme, **HID de vuelta** (muerto desde
  el incidente f601 del 18/10), sobrevive 1080p120 estable.
- Guard re-activado (nota: el LaunchAgent había quedado descargado desde el
  bootout del 18/10 — re-bootstrapeado; carga solo en el próximo login).
- Estado final: **receta completa operativa** (jmp120 + smartguard,
  960→1920 corregido al vuelo). Tratamiento para futuros episodios:
  descanso prolongado sin energía.

## 2026-10-22 — La distorsión clasificada + el mapa hsdaoh + experimento transparente

**Clasificación del defecto (descripción del usuario, imágenes 4-5):** franjas
horizontales que se repiten/desplazan/mezclan, estilo macrobloques rotos =
**tearing por saturación de line-buffers** — el scaler mezcla cuadros
consecutivos en franjas. NO es geometría ni escalado: es el bus interno del
camino de ENTRADA sin margen para 1920@120 (497 MB/s) cuando la política de
fábrica lo limita a 960 (248 MB/s).

**Fuente externa de conocimiento integrada — hsdaoh (steve-m):** registros
encontrados por try-and-error que redefinen el mapa:
- f65c = reescalado H (0x10=off) · **f65e = reescalado V** (nunca lo tocamos)
- **f600 bit7 (0x80) = interpolación de croma** — bit0=run; escribimos 0x81
  por primera vez hoy
- f6b0 = sharpening · f6be/f6bf = procesado luma/croma (0x11=off)
- f039/f030 = forzado RGB/YCbCr de entrada
- Confirmación upstream: hsdaoh re-inicializa periódicamente porque "the
  firmware is resetting the registers" (la guerra, documentada afuera)

**Hipótesis de la casuística (vigorizante):** el fix histórico era PARCIAL
(5 registros de un suite de ~35). Sin f65e y sin el bit de croma, el
pipeline queda incoherente al forzar 1920@120. La semana pasada el margen
del chip absorbía la incoherencia; post-cascada del f601 ya no.

**Experimento transparente (22:5x):** secuencia completa hsdaoh + anchos
(f65c/f65e=0x10, f6b0=0, f6be/f6bf=0x11, f600=0x81, f606/f618/f660=1920)
con stream vivo. Resultado numérico: tearing SOLO en el frame de transición
(t=3s, 14 filas); t=8/14/19s = 0 filas de tear. Config sostenida sin
revertirse. Veredicto visual del usuario: pendiente al cierre de esta
entrada.

**Estado del sistema al cierre de esta entrada:** firmware jmp120
(verificado byte a byte desde flash), guard apagado, config transparente
completa montada, entrada 1080p120 de la Deck.

**Veredicto del experimento transparente (usuario): "misma distorsión".**
Con la secuencia COMPLETA y coherente de hsdaoh + anchos 1920 el tearing
persiste idéntico → el espacio de configuración queda agotado con conclusión:
**el camino de entrada del chip ya no tiene margen para 1920 ancho @120Hz**
(497 MB/s). No es incoherencia de suite ni ruta de escalado: es capacidad
de hardware de ESTA unidad, degradada tras la cascada del f601 (18/10).

Estado devuelto a la config natural estable (960/f65c=f65e=0x08, f6b0=0):
imagen estable y geométricamente correcta, suave en horizontal.

**Cierre del mapa de estados de esta unidad:**
- 1080p60: nativo perfecto (única resolución full-width que queda)
- 1080p120 natural: estable, medio ancho (960) — uso actual
- 1080p120 forzado 1920: tearing por saturación — TODAS las variantes de
  config probadas (fix parcial, fix completo hsdaoh, transparente, con/sin
  stop, con/sin guard)

## 2026-10-22 (3) — TOOLCHAIN RE COMPLETO + DECOMPILACIÓN MASIVA

**Petición del usuario**: usar REA (github.com/rea-tools/rea) para el RE,
entender el firmware perfectamente y reconstruirlo todo en una guía.

Instalado y conectado:
- REA 6.7.0 (MCP en opencode + skill reverse-engineer-anything +
  GHIDRA_INSTALL_DIR) — vivo tras restart de sesión
- Ghidra 12.1.4 nativo macOS/ARM (brew — el zip oficial NO trae nativos mac:
  "os/mac_arm_64/decompile does not exist"; el bottle de brew sí)
- JDK 21 (openjdk@21) en ~/tools + PATH

**La decompilación masiva funcionó en dos pasos clave:**
1. El análisis automático de Ghidra NO encuentra funciones en 8051 crudo →
   se siembran las 1242 entradas del call-graph (targets de lcall/acall
   extraídos del disasm) con disassemble()+createFunction()
2. Re-proceso CON análisis (cuerpos completos) + DecompileAll.java

**RESULTADO: 1034 funciones decompiladas a C** en fw_re/decomp/
(f_CODE:xxxx.c + INDEX.txt) — 5.1MB de pseudocódigo. Verificado contra el
RE manual (sub_bc02 = el walk, coincide perfecto).

Siguiente: la guía completa del firmware (GUIA.md) construida desde el
pseudocódigo + todo el conocimiento runtime acumulado.

## 2026-10-22 (4) — Superficie vendor decodificada completa + mode-lock descubierto

- Los 4 overrides de sub_4454 identificados: [0x1FD4/6]=VID/PID rename (¡el
  mecanismo de ms213x-rename!), [0x1FE0]=**lista de modos**, [0x1FF0]=segunda
  lista (38B, pendiente).
- Mecanismo exacto (raw disasm): en cada init de modo, loop copia
  [0x1073+i]→[0x240A+i] (22B default) — el override cambia la fuente a
  [0x1FE1+i] (nuestra data por HID).
- **La lista son VIC codes** (55/53/42/66/20/105/100/101/111...): el
  control nativo de qué modos la capturadora ofrece/acepta.
- Experimento plantado: [0x1FE0]=1, [0x1FE1]=0x10 (VIC 16=1080p60) —
  mode-lock a 1080p60. Disparador pendiente: evento de modo HDMI (ciclo de
  resolución en la Deck — NO replug: el override es RAM).
- PENDIENTES anotados: (1) disparar y verificar el mode-lock; (2) decodificar
  la segunda lista 0x109f/0x10df (38B — ¿DTDs?); (3) probar si la lista
  custom incluye el timing completo o solo VICs (¿se puede definir un
  1080p120 custom full-width?); (4) REA MCP quedó con paths absolutos y
  ghidra OK — pero raw 8051 no lo abre (limitación); usar decomp/ + Ghidra
  directo; (5) el inyector espera IDs de 1 byte pero la lista default usa
  2 bytes por entrada (VIC + 00) — validar formato con el experimento.

## 2026-10-23 — Segunda lista decodificada: strings de audio

- 0x109F/0x10DF = "USB3/USB2 Digital Audio" (UTF-16) — el override [0x1FF0]
  es rename de audio, NO timings.
- Superficie vendor CERRADA: VID/PID + nombre audio + lista VICs. Sin DTDs
  custom → full-width@120 inalcanzable por esta vía.
- Pendiente vigente: disparar el mode-lock plantado ([1FE0]=1, VIC 16) con
  un ciclo de resolución de la Deck y verificar la renegotiación.

## 2026-10-23 (2) — Bateria decodificada: la ventana NO se reduce a 120

- Formato: {f622=htotal, f624=vtotal, grupos f62e/30/32/34 = hstart/hactive/
  vstart/vactive} — ventana con overscan 2016x1100 para 1080p.
- **IDENTICA a 60-perfecto y 120-diezmo** → la diezmacion es 100% del motor
  de escalado, no del sampler. Reescribe el modelo del "limite de banda de
  entrada".
- f620 bit0 = 1@60 / 0@120 — candidato sin probar (el experimento inaugural
  corrio en estado contaminado 720p — rehacer en estado limpio).
- Escritor universal 0xE279 = field-update decodificado.

## 2026-10-24 — CIERRE DEL MODELO COMPLETO: el pipeline es trajectorial

**El experimento f620-bit0 cerró el caso**: el bit se revierte solo (readback
puro como f601/f65c — tercera trampa del readback descartada). Y el intento
en estado limpio reveló el principio final:

1. **El estado bueno NO son valores de registro — es la TRAYECTORIA del
   pipeline**: boot natural @1080p120 = BIEN (verificado por el usuario dos
   veces); cualquier ciclo stop→write→start (guard, fixes) lo degrada y
   NO se restaura escribiendo los valores "naturales" de vuelta.
2. **Forzado full a 120 en el estado más limpio posible = distorsión** —
   límite real del motor de escalado. Caso definitivamente cerrado.
3. **El drop de formato a 720p (Discord) = feo** — y su cura segura es SOLO
   `setformat` (pasa por el camino de negociación del firmware, no toca
   registros del scaler).

**RECETA FINAL VALIDADA**: jmp120 + boot natural + setformat ante drops de
formato. Guard de registros: PROHIBIDO en esta unidad (degrada trajectorial).

## 2026-10-24 (2) — formatguard v2: la automatización segura, funcionando

- v1 colgada: AVFoundation (setformat --status) bloquea desde launchd →
  sample del proceso = select/poll eterno. v2: detección HID pura.
- Bug propio cazado: [22B8]/[22DE] = byte ALTO (BE) — el v2 inicial nunca
  matcheaba por endianness invertido.
- **Validado en vivo**: drop real de Discord detectado (21:36:02) y
  corregido por setformat en ~2s, scaler natural intacto (f65c=0x08).
- Sistema FINAL: jmp120 + natural + cl.fcaraneda.ms2131formatguard.
  El fix120d viejo: retirado (degrada trajectorialmente).

## 2026-10-27 — El experimento no720: conclusión y reversión

- **Bug B (crash a ROM mid-stream) resuelto por identificación**: empezó
  EXACTAMENTE tras flashear no720v2. Mecanismo: sin 720p en el menú, Discord
  streamea 1080p60 MJPG full-width = carga máxima sostenida → el firmware
  cae a ROM (el muro de banda del streaming sostenido — coherente con todo
  el mapa: la política 720p existía por esto).
- **Revertido a jmp120** (estado estable histórico: 720p stream = ~110MB/s).
- El no720 queda como genealogía documentada: resuelve el menú pero expone
  el techo físico. La unidad NO sostiene 1080p60 en stream.
- Bug A (audio dual-cliente scalapp+Discord, SIN caída del device) sigue
  pendiente por la vía del delay/resiliencia en scalapp.
- El BlackHole/virtual-out quedó implementado en scalapp (opcional, si
  algún día se quiere la arquitectura de lector único).

**Refinamiento del modelo (observación del usuario, 27/10):** el muro no es
la tasa de SALIDA sino la ENTRADA full-width a 120Hz: 1080p60-input +
stream 1080p60 = estable TODO EL DIA; 1080p120-input + salida diezmada =
estable; 1080p120-input + conversion full-width a 1080p60 (lo que el no720
provocaba) = crash. "El 1080x120 convertido a 1080x60" no se sostiene —
el procesamiento de entrada a 497MB/s es la carga prohibida (la razon de
ser de la politica de medio-ancho). Reversion a jmp120 confirmada.

## 2026-10-27 (2) — MANUAL COMPLETO consolidado + verificaciones del caza-crash

- GUIA.md reescrita como manual completo (5 partes, 21 secciones): integra
  todo lo que vivía solo en BITACORA (muro de entrada modelo final, modelo
  trajectorial, doctrina, ecosistema formatguard, historial de daño,
  bugs A/B) + lo nuevo de hoy.
- **Verificado en disasm antes de documentar**: (1) los ljmp de los
  vectores EXT0/TIMER0/EXT1/TIMER1 aterrizan EXACTAMENTE donde empiezan
  los prólogos de pushes (d595/c5ed/b44d/624f) — la medición de stack del
  camino ISR es válida (solo TIMER1 tiene 4B de pushes bajo el landing);
  (2) main = 0x4F20 (llamado al final del boot a4eb); (3) la cadena EXT0
  pasa por el trampoline 0x0016 → escritor universal 0xE279: el ISR USB
  escribe registros del scaler en su camino profundo.
- Next steps vigentes: abrir 0x3438 (25B), handlers pesados, re-validar
  baseline jmp120 post-reversión, bug A en scalapp.

## 2026-10-27 (3) — CAZA DEL CRASH: mecanismo del bug B cerrado (estático)

- **SP nunca se reubica**: único `mov SP,#imm` del firmware = boot @0xA4F1.
  Presupuesto 52B fijo. Push con SP=0x7F envuelve a IRAM 0x00 → pisa los
  BANCOS DE REGISTROS = corrupción instantánea → hang → ROM.
- **Medición refinada (max-live secuencial, push/pop neteado)** en vez de
  conteo total de pushes: TIMER0=52B y MAIN=52B EXACTOS (diseño al byte);
  EXT0=55B (+3), EXT1=63B (+11), TIMER1=63B (+11). Las ramas profundas no
  corren siempre — la carga del streaming las dispara = el overflow.
- **0x3438 INOCENTE**: 25B era conteo de ramas; max-live real 5B. Falso
  positivo de la primera pasada. Su caller único: sub_63C9 = máquina de
  estados del receptor HDMI (estados [268B], countdown [2002], escribe
  f6xx y f0xx); 4f20→1b67→63c9→3438 = solo 11B.
- **Cola compartida** d953→cd0b→a32a→be45→c4ec→... presente en las 4 ISRs
  y en el main = el blanco ideal de aplanado (frames grandes: 9a8b:4,
  a89c:6).
- GUIA.md §20/§21 actualizados con el modelo cerrado y el plan de aplanado
  + verificación dinámica (centinela SP en handlers).

## 2026-10-27 (4) — flat1: el aplanado de stack construido y flasheado

- **DP corregido** (bug: guard del seen disparaba en la raíz) → caminos
  estáticos reales: EXT0=127B, EXT1=94B, TIMER1=60B, TIMER0=26B. El
  camino del EXT1 pasa por el motor de propiedades COMPLETO desde la
  interrupción (7116→0016→0121→0502→070e→2402→...) — la reconfig del RX
  desde ISR = justo lo que la carga full-width dispara. Estático
  sobre-estima (si corriera siempre, crashearía en segundos) pero marca
  la maquinaria compartida.
- **Conversión tail-call** (lcall X; ret → ljmp X): semánticamente
  idéntica, ahorra 2B de stack por sitio. 6 sitios encontrados,
  verificados (patrón exacto 12 xx xx 22 + cero saltos que aterricen en
  los 4 bytes): 8758→cd55, 9bd1→8837, a898→d72d, dab7→4aef, e655→0016,
  e6d1→da55.
- **TIMER1 queda en 52B EXACTO** (60−8). EXT1: 94→86 estático.
- `analysis/patch_flat1.py` → `backup/MS2131_flat1.bin` (base jmp120 +
  6 conversiones, checksum recalculado).
- **Tercera caída a ROM espontánea del día** (pre-flasheo, sin stream
  aparente) → flat1 flasheado por rom_flash directo (rescate+patch en un
  paso). VERIFY OK. Pendiente: replug + test de estabilidad.

## 2026-10-27 (5) — cierre del día: episodio de no-arranque (hardware)

- Tras flashear flat1: replug → ROM. **A/B con jmp120 (known-good de
  semanas): TAMBIÉN ROM** → flat1 absuelto, no es el parche.
- **Sin HDMI y tras replug: tampoco arranca** → crash-on-BOOT, más profundo
  que el crash-on-HDMI del 18/10. Flash triple-verificada (VERIFY OK dos
  veces hoy, bytes exactos).
- Progresión del día: 3 caídas espontáneas a ROM → degradación hasta
  no-arranque de NINGÚN firmware = calco de la semana 18-21/10 (que
  terminó igual y se curó con 48h sin energía).
- Vigilancia de 1.5h (ioreg): el dispositivo nunca se desconectó — el
  test de descarga completa (USB+HDMI fuera 30s → solo USB) quedó PENDIENTE
  de ejecutar.
- **Prescripción**: (a) test de descarga completa; (b) si no revive,
  descanso prolongado sin energía. Al despertar: flash flat1 + test de
  estabilidad. Todo listo en backup/ y documentado en GUIA §20/§21.

## 2026-10-27 (6) — GIRO FORENSE: la flash estaba TRUNCADA, no era "no-arranque"

- Nueva herramienta `tools/rom_readloop` (lectura SPI en loop desde ROM):
  10 pasadas completas (245 paginas c/u) = **0 bit-flips**. La mask ROM lee
  la flash sin errores en el estado actual. SFRs en ROM: SP=00 ACC=00
  (coherente con firmware que nunca corrio).
- El golden de la flash NO era jmp120: contenia el prefijo EXACTO
  (0 diffs en 34.5KB) de `MS2131_native_wrapper.bin` (experimento del 13/10,
  "nunca flasheado" hasta ahora), truncado en la pagina 135 (0x8700) con
  mar de FF hasta el final → checksum en flash = ffff → **la ROM
  correctamente se nego a arrancar**.
- Timing: el vigilante vio al dispositivo desaparecer 18:20:28 (7s) —
  calza con un rom_flash (imagen vieja via historial/tab-complete) muerto
  a mitad de escritura (~2min erase+write, murio ~60% dentro).
- **Reflash jmp120 completo: 245/245 paginas + VERIFY OK** — la escritura
  NO murio en pag 135 esta vez → la flash esta sana; lo anterior fue la
  unidad cayendose (o desplugue) a mitad de write.
- CORRECCION al relato: el "no-arranca-nada" de esta tarde tenia causa
  conocida (flash truncada). El A/B de la manana (jmp120 verificado en
  flash que no bootea) sigue en pie como evidencia de episodio marginal,
  PERO hay que re-testear: si jmp120 arranca en este replug, el episodio
  fue transitorio y la unidad esta viva.

## 2026-10-27 (7) — EL SABOTEADOR: LaunchAgent ms2131watcher (caso cerrado)

- **Causa raiz de TODOS los episodios de hoy (y probablemente parte de la
  semana 18-21/10)**: LaunchAgent `cl.fcaraneda.ms2131watcher` (plist del
  16/10 22:28, noche de rescates) corriendo `tools/ms213x_watchpid2`.
- Mecanismo (confesado en /tmp/ms2131_watch2.log, 112 CARRERA GANADA):
  poll cada 20ms; cuando ve 345f:* (firmware) hace
  `execl(ms213x_flash -w MS2131_native_wrapper.bin -n)` — **erase+write
  de native_wrapper sobre la flash mientras el firmware corre**.
- Clave tecnica que lo hizo invisible: **el firmware ejecuta desde RAM**
  (la ROM copia la imagen al arrancar) → el flasheo en caliente NO mata
  la sesion → todo "funciona" hasta el proximo reboot, que encuentra
  native_wrapper (o truncado si el write fue interrumpido → checksum
  ffff → la ROM se niega a bootear → "no arranca NINGUN firmware").
- Reinterpretacion del dia: las "3 caidas espontaneas", la flash
  truncada en pag 135 (write interrumpido 18:20), los "no-arranca
  pese a VERIFY OK" (el agente re-truncaba DESPUES de cada verify),
  el wedge 18:39:58 (erase contra el USB re-enumerando) = TODO el agente.
  La entrada (6) queda corregida: no fue un comando manual viejo.
- **Neutralizado**: `launchctl bootout` + pkill + plist movido a
  `~/Library/LaunchAgents/disabled/` (reversible). Barrida: sin cron,
  sin otros agentes ms2131 (solo formatguard, legitimo).
- Dato del wedge: la mask ROM si puede no enumerar (powered, D+/D-
  mudos) tras un erase en mala fase — antes la creiamos inmortal.
- Secuencia de recuperacion: ROM readloop estable (0 flips) → reflash
  jmp120 (VERIFY OK) → boot limpio 18:43:49 en @00200000 (el OTRO
  controlador; @01200000 vio todo el desastre) → agente muerto →
  **flash flat1 via ms213x_flash CON verify: Done.**
- Pendiente inmediato: replug → boot flat1 → test estabilidad >=30 min.
  Es el PRIMER test limpio de flat1 — todos los anteriores fueron
  envenenados por el agente.

## 2026-10-27 (8) — BISECT de flat1: culpable e6d1; flat2 (5 sitios) revela INTERACCION

- Bisect empirico (flash+verify+replug por ronda, agente muerto, sin ruido):
  - bisectA {8758,9bd1,a898}: BOOTA (2s), estable 3min   → inocentes
  - bisectB {e655} (trampoline 0016): BOOTA               → inocente
  - bisectC {dab7}: BOOTA                                 → inocente
  - **e6d1->da55 culpable POR ELIMINACION** (flat1=6 sitios no bootea)
- flat2 = 5 sitios (sin e6d1, checksum 4432): bootea 2 veces pero
  **muere sola a los 8s y 82s** con WEDGE (dropout total del bus, ni ROM).
  → interaccion: individualmente inocentes, los 5 juntos toxicos.
- Mecanismo NO identificado: sin refs de tabla a los sitios (busqueda BE
  de e6d1..e6d4 en el binario = limpia), callees sin push/pop/mov SP.
  Hipotesis pendiente: codigo SP-relativo, o dependencia de profundidad
  de stack como marca/scratch. Requiere experimento controlado.
- El WEDGE en si es flash-independiente (18:39:58 con jmp120 verificado)
  = episodio marginal real del USB de la unidad (la parte SI hardware).
- **Decision**: entregable de hoy = bisectA (TIMER1 56B, EXT1 88B,
  EXT0 121B; mejora estricta vs jmp120 en todos los caminos).
  Siguiente nivel de aplanado queda en cola hasta entender la interaccion.
- Archivos: analysis/patch_bisect.py (parcheador por subconjunto),
  backup/MS2131_bisectA|B|C.bin, backup/MS2131_flat2.bin.

## 2026-10-27 (9) — CIERRE: fase marginal activa; prescripcion descanso

- Soak de bisectA (21:08:06): la unidad murio SOLA a los 51s (21:08:57,
  wedge). Discord no pudo iniciar transmision porque el dispositivo ya
  estaba muerto.
- Progresion de wedges esta noche: 21:00:17 (flat2, 8s), 21:03:25
  (flat2, 82s), 21:08:57 (bisectA, 51s) — tres firmwares distintos,
  muertes sin actividad externa (formatguard sin disparar: su log no
  registra nada en la ventana; ultimas setformat 18:49/19:11).
- Conclusion: **fase marginal ACTIVA de la unidad** (patron semana 18-21/10:
  degradacion progresiva en horas). El bisect de flat1 sigue siendo valido
  (se hizo con boot rounds estables de 3-4 min); lo que ya no se puede
  confiablemente esta noche es un soak.
- Nota metodologica: `timeout` no existe en el zsh de macOS — los
  "frame grabs colgados" de esta noche nunca corrieron (command not found
  filtrado por grep). Corregir con `-t` de ffmpeg a futuro.
- **Prescripcion**: USB + HDMI fuera, descanso (overnight minimo; 48h fue
  la cura historica). En flash queda bisectA verificado (booteable).
- Al despertar: replug → boot bisectA → soak 30min idle + 30min stream.
  Si aguanta → bisectA = firmware de regimen. Cola: §21 actualizada
  (interaccion flat2, e6d1, centinela SP, bug A, RE de bajo riesgo).

## 2026-10-27 (10) — MECANISMO CERRADO: dos minas de aterrizaje; flat3

- Scanner de aterrizajes CORREGIDO (bug: primer hex del operando en vez
  del target — el mismo vicio del chequeo original de flat1):
  - **e6d1**: cjne e6ce aterriza en el ret -> convertido cae al
    mov dptr,#0x1193 = re-loop del dispatch al boot (rompe boot) ✓
  - **a898**: 5 saltos frios (a823,a82b,a887,a88c,a895) al ret ->
    convertido caen en lcall 0xbb3c = caos -> WEDGE del bus
- Correlacion empirica: 5/5 muertes espontaneas con a898 convertido
  (bisectA x3: 51s/102s idle; flat2 x2: 8s/82s); 4/4 boots sin a898
  sobrevivieron (jmp120 95min; bisectB/C a replug manual). La "tormenta
  marginal" era autoinfligida.
- **flat3 = jmp120 + {8758,9bd1,dab7,e655}** (checksum 4464): flasheado
  21:33, boot 21:34:02, checkpoint 2min41s superado. Soak en curso.

## 2026-10-27 (11) — CIERRE FINAL de la noche (post-data del usuario)

- El "wedge nº4" de las 22:09 fue el USUARIO desconectando la unidad —
  NO un fallo. **Soak de flat3 = APROBADO**: 35m32s de vida continua,
  ~20 min con stream de Discord, 3 dropoffs de 2s AUTORECUPERADOS (el
  fenomeno historico conocido), cero wedges, cero muertes. Final manual.
- **flat3 queda como firmware de regimen validado** (TIMER1 54B, mejor
  que jmp120 en todos los caminos, sin minas de aterrizaje).
- scalapp: implementados --delay-ms (colchon) + --stall-ms (watchdog
  con rebuild en main thread) para el bug A. Pendiente de test en vivo.
- La unidad quedo desconectada por decision del usuario (descanso).

## 2026-10-29 — scalapp: audio resuelto; arquitectura Discord→ventana

- La unidad revivio tras ~2 dias de descanso (la cura historica, otra
  vez) y booteo flat3 — el firmware de regimen validado en el soak.
- **Arquitectura nueva decidida por el usuario**: Discord transmite la
  VENTANA de scalapp (con su sonido propio via ScreenCaptureKit) en
  vez del dispositivo → la capturadora tiene UN solo cliente, la
  guerra de formatos muere, bug A muere arquitecturalmente. Sin
  dispositivos virtuales.
- Audio del modo --video arreglado en 3 pasos (commits c72250d..9202e65):
  1. tasa real del dispositivo (48k, port del fix 25/10)
  2. playback frame-exacto (el match bloque-a-bloque descartaba 3/4)
  3. motor con deriva compensada + bloques Fixed(256..1024) + target
  adaptativo ~30ms + watchdog con rebuild → **audio perfecto segun el
  usuario**, latencia ~50ms.
- Video queda pendiente: dice 60fps pero no lo es (el contador mide
  captura, no render). Analizado y anotado en scalapp/ROADMAP.md —
  objetivo del usuario: "direct output". El usuario sigue el en el
  repo por su cuenta.
## 2026-10-29 (2) — Gaps de audio en modo video: el formatguard es el imputado

- Scalapp (Fase 1 del ROADMAP: 1080p60 reales + latest-wins) dejó un
  residuo: blips de audio ~1/min. Instrumentación con timestamps
  (t= + @HH:MM:SS) en scalapp: INPUT GAPs de 99-216ms, solo con video
  streameando, mismo ritmo a 1080p60 y 720p60 (no es bandwidth),
  0 gaps en audio-only, bloque de entrada estable (no es
  renegociación). Los samples nunca llegan → drop del lado del device.
- **A/B del formatguard (3min por rama, mismo día/señal)**: guard OFF
  = **0 gaps**; guard ON (sin disparar ni un setformat) = 2 gaps.
  → el **polling HID cada 2s** (`ms213x_xdata read` via subprocess)
  es el imputado principal. La peor corrida histórica (gaps 200ms
  cada ~25s) coincide exacto con la tormenta de 27 setformat del
  16:42-16:48 — el device se caía a 1280 cada ~10s y cada arreglo
  glitchea todo.
- Mitigación mientras tanto (scalapp 6227293 + 937d15f): colchón
  adaptativo del playback (base 50ms, sube a gap+50 al observar gap,
  tope 350ms) + clamp de deriva asimétrico (-1% déficit profundo).
  A 150ms absorbe los gaps del guard sin underrun.
- **Escrita `CASUISTICA.md`**: matriz E1-E10 para aislar el mecanismo
  (read vs open, dosis-respuesta, observación por AVFoundation sin
  contaminar, parche de firmware como camino final) y validar si los
  drops a 1280 que el guard vigila son también autoinfligidos.
- El guard quedó restaurado (producción intacta). Meta del usuario:
  volver a 50ms de colchón → pasa por resolver H1.

## 2026-10-29 (3) — Guard v3: el fix del HID-vs-isoch (investigación completa)

- Runs A/B de la casuística ejecutados (misma tarde, 3 fases por
  corrida para control dentro-de-sujeto):
  - **Run A** (subprocess por poll, como v2): F1 base 0 gaps → F2
    (xdata read ×2 cada 2s, 122s) **1 gap de 105ms** → F3 0. El
    veneno es el acceso HID, no el contexto launchd.
  - **Run B** (watch residente, UN hid_open sostenido):
    **catastrófico** — stutter continuo 2min (gaps ~285/185ms
    alternos, ~3.5/s, underrun por callback, colchón al tope). Al
    cerrar, silencio inmediato. [22DE] estable en 1920 todo el
    window (sin drops de formato durante la agresión).
- Modelo final: el daño del HID sobre el isoch escala con la
  exposición — efímero = ~1 gap/min, sostenido = stutter continuo,
  ninguno = 0. Sostener la interfaz abierta es lo peor (el host la
  polea). Diseño "residente" DESCARTADO.
- **formatguard v3** (implementado in-place, v2 respaldado en
  tools/ms2131_formatguard_v2.py.bak): pgrep gratis cada ciclo; si
  scalapp corre → pausa HID total (0 gaps, el formato lo renegocia
  scalapp con modo exacto al abrir); sin clientes → vigilancia v2
  intacta. Transiciones logueadas.
- **Validado 18:07-18:11**: guard v3 ON + scalapp 245s → **0 gaps**,
  transiciones correctas. scalapp queda a colchón base 50ms (meta del
  usuario cumplida); el adaptativo queda como red de seguridad.
- Pendientes heredados (CASUISTICA.md §6): E6 (¿drops 1280
  autoinfligidos?) y E4 (soak largo). E9 (parche firmware) queda
  documentado como camino final si algún día se necesita HID en
  stream.

## 2026-10-29 (4) — HUM: caracterización interna + hallazgo 120Hz

- Escrita `HUM.md`: investigación del tono de 60 Hz en el audio
  (pide el usuario: causa interna al chip). Medido por modo: el tono
  solo existe con stream UVC, escala con el tamaño de salida
  (1080p −29.2 dBFS vs 720p −39.7) y su frecuencia es la cadencia de
  SALIDA (~60 Hz) — con input a 120 Hz. Modelo: corriente dinámica
  del bloque scaler/memoria/USB acoplada a un tramo analógico del
  path de audio. Mitigación host-side ya viva (scalapp --notch-hum,
  quirúrgico).
- **Diff XDATA idle vs stream** (4 rangos): f7xx muerto; f8xx =
  config del payload UVC (video); sin rastro de registros de audio
  en lo escaneado → UAC en silicio dedicado o rangos sin escanear.
- **HALLAZGO**: el source corre 1080p120 y con el guard v3 pausado
  el capturador quedó DIEZMADO (f606/f660=960) — scalapp entregaba
  video blando. Se probó `fix120 apply` con stream abierto: **FALLÓ**
  — imagen distorsionada (el modo documentado de RE.md: f65c=0x10 vs
  batería medio-ancho a 120Hz puro) + audio wedeado a silencio digital
  (revert no lo revive; replug pendiente). El apply solo es válido en
  hot-switch, NO a 120Hz de pie (muro físico de entrada, ver 27/10).
  Corregido HUM.md §2.
- El path de audio quedó entregando silencio digital (video vivo):
  wedge por el apply fuera de sobre. Cura: replug. Documentado en
  HUM.md §5.
