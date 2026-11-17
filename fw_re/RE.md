# RE MS2131 — Ingeniería inversa del firmware (sesión 2026-10-16/17)

Fuente: `backup/MS2131_2025-04-09_backup_2617_44fc.bin` (original del fabricante)
Code space: `fw_re/code_original.bin` = flash[0x30 : 0x30+0xF4C7] · **addr código = addr flash − 0x30**
Herramientas: radare2 (`-a 8051 -b 8`), `fw_re/xdata_scan.py` (escáner de accesos XDATA),
`tools/ms213x_xdata` en vivo (firmware corriendo, HID if#4).

## Mapa XDATA relevante (verificado en vivo)

| Dirección | Significado | Notas |
|---|---|---|
| `0x22B8:BB` | geometría de ENTRADA (preset): ancho×alto | 1920×1080 a 60 y 120 estable; el ÷2 aparece solo en el evento hot-switch |
| `0x22BE:BF` | refresh de entrada ×100 (BIG-endian) | 5999=59.99Hz, 0x2edd=119.97Hz |
| `0x22DE:E1` | formato UVC ACTIVO: ancho×alto | cambia con Discord/setformat; 1280×720 si Discord baja a 720p |
| `0x22E4:E5` | framerate del formato ×100 (BIG-endian) | 6000 = 60.00 (¡no es "stream activo"!) |
| `0x1AE2:1AE4` | puntero SDCC 3 bytes {type,hi,lo} — campo ancho-IN del struct de config | |
| `0x1AEA` | campo ancho-CAPTURA del struct → acaba en f606 | |
| `0x1AF1:1AF3` | puntero activo del struct (se apunta a sí mismo/1AEA) | |
| `0x1AFB:1AFC` | ancho "en proceso" — **la víctima del ÷2** | |
| `0xF600` | scaler run (0x01) | |
| `0xF604/f605` | ancho de muestreo (LE 16) | sigue [1AE2] |
| `0xF606/f607` | ancho de captura (LE 16) | 80 07=1920 bueno · c0 03=960 diezmado · 00 05=1280 formato 720p |
| `0xF618/f619` | largo de línea del input | no sigue al formato |
| `0xF65C` | rescale H: 0x10=off, 0x08=diezmado | |
| `0xF60C/F60E` | alturas (38 04 = 1080) | |

## Cadena de configuración de modo (0x569E–0x5860)

```
0x56BB: [1AE2] := [22B8]   (copia 16-bit de geometría entrada → campo ancho-IN)
0x56D1: [1AE4] := [22BA]   (altura)
0x56E0: [1AE6] := [22DE]   (formato UVC → campo para el clamp)
0x5707–0x5723: CLAMP:  [1AEA] = min([1AE2], [1AE6])     ← ancho captura
0x572B–0x5733: 2ª escritura condicional de [1AEA] vía [0x268C]
0x573B+: clamp vertical análogo ([1AE8]/[1AE4] → [1AEC])
0x57C0–0x581F: detector: hactive==1920×1080 && [22BE:BF]≥4900 → [1AEA]=5 (clase)
0x5820: r4r5=0x1770(6000), r6r7=0x0bb8(3000) → helper 0xE33F
0x582B: [1AF1..F3] = ptr a 0x1AEA
0x5839: r3r2r1 = ptr a 0x1AE2
0x583F: LCALL 0xBC02  → escritor: f604 ← [1AE2]; f606/f618/f660 ← [1AEA]
0x5856: LCALL 0xBF01  → bloque ratios f65b+ (el hook del wrapper estuvo aquí)
```

**El clamp `min(entrada, formato)` es el correcto diseño** — el bug nunca estuvo aquí.

## El clasificador con la diezmación ÷2 (zona 0x3438–0x38xx)

```
0x3546–0x3552: gate del bloque: compara [1AF6:1AF7] vs [1AF9:1AFA] → ljmp 0x3601 si no
0x3557: r3r2r1 = puntero en [1AE2]
0x355D: helper 0x313F sobre [1AF8]
0x3563: helper 0x315F sobre [1AFB]  → condición (carry)
0x3569: jnc 0x3595                  ← ★ EL PARCHE (50→80: jnc→jmp)
0x356B–0x357D: [1AFB:1AFC] ÷= 2     ← clr c / rrc / rrc (16-bit ÷2, ÚNICO en la zona)
0x357E: recarga puntero, propaga el valor dividido
0x3595+: camino sin-dividir (carga ptr y continúa)
Segundo RRC en 0x9474 (zona pclk→clase [1AAD]→[1AB1]) — clasificación, no geometría.
```

## Causa raíz del bug 1080p120 (DEMOSTRADA en vivo, 17/10 01:47)

**La diezmación NO es una propiedad del modo 120 Hz.** Dispara en el
**evento de cambio de modo con stream activo**:

```
protocolo: 60Hz → abrir Discord → hot-switch a 120Hz
original:   f606: 1280 → 640   (= formato ÷2; a 1080p sería 1920→960)
parcheado:  f606: 1280 (estable) — la halving no corre
```

Arranque limpio a 120 sin stream: el original TAMBIÉN entrega 1920. Por eso
el bug era intermitente según la secuencia del usuario.

## El parche final

**`backup/MS2131_jmp120.bin`** = original + 1 byte:
`0x3569 (flash 0x3599): 50 → 80` — `jnc`→`jmp` — el ÷2 jamás se ejecuta.

- 1080p60/50/30, 720p, 480p: sin cambio (la halving no aplicaba o el resultado coincide)
- 1080p100/120 hot-switch: f606 = formato sin dividir ← **el fix**
- 4K30: f604=3840 (muestreo completo ≈115 Mpx/s, cabe), f606=min(3840, formato)=1920 — mismo resultado que antes (acotado por formato), probablemente con mejor downscale

Verificación triple: repetición del protocolo (f606 estable), registro en streaming
(f606=1920 @120Hz formato 1080p), y análisis de columnas duplicadas al píxel:
33.7% (nuestro) vs 79.5% (roto) vs 52.8% (referencia fix vivo).

## Postmortem del wrapper (por qué falló — lecciones)

`backup/MS2131_native_wrapper.bin` (hook en 0x5856 + cue 0xF3D9):

1. **Bug de endianness en el gate**: comparaba `[0x22E4]^0x70 && [0x22E5]^0x17`
   (6000 little-endian) pero el struct guarda BIG-endian → gate jamás verdadero →
   el wrapper era un passthrough puro (por eso f60e nunca se corrompió).
2. **Overflow de stack**: 4 pushes (acc/B/R4/R5) a la profundidad del caller
   0x5856. La lección v5: margen <5 bytes ahí. 4 pushes = desborde silencioso
   de IDATA → pipeline de entrega UVC muerto con TODOS los registros perfectos
   (f620 preservado OK — el daño fue colateral al stack).
3. Además escribía hactive en f60e (registro de ALTURA) — bug latente que el
   gate roto nunca dejó manifestar.

**Regla de oro extra**: cualquier hook a esa profundidad de llamada = 0 pushes.
Si se necesita preservar estado, usar registros muertos o XDATA scratch.

## Parche fallido documentado: `analysis/patch_1byte120.py`

`0x56BD: b8→de` ([1AE2] := [22DE] formato en vez de [22B8] entrada):
provoca estiramiento horizontal cuando formato < entrada (f604 sigue al formato
→ ventana de muestreo 1280 de una línea de 1920 → "se ve ancho"). Reproducido
y revertido. El objetivo correcto era el ÷2, no la fuente del clamp.

## Emergencia: flashear con la tarjeta muerta (ROM if#4)

Si el firmware no arranca (brick) y no hay ventana de replug:

1. Tarjeta en puerto USB3 DIRECTO (no hub — el ROM sirve 5 interfaces solo en SS)
2. Puente CS(pin1)↔VCC(pin8) del SPI U6 (Puya P25Q40SH, SOP-8, patas del borde
   inferior) DURANTE la conexión; quitar a los 2-3 s
3. Enumera `534d:2130` "USB Video" (ROM mode persistente)
4. `tools/rom_flash <imagen.bin>` — habla a la **interfaz 4** vía control
   transfers crudos EP0 (`wIndex=4`, SET/GET_REPORT, framing 8 bytes {cmd,...},
   longitudes big-endian 0x0100=256). macOS no instancia la if#4: por eso el
   flasher normal falla ("Could not open device" / setup_spi) y por esto funciona
   el nuestro.
5. Replug sin puente

La mask ROM del MS2131 **no tiene loader HID accesible por la interfaz 0**
(STALL a todo: probeado feature/output/vendor, IDs 0–3/0x10/0x11, len 8–9/255,
vendor OUT 0x00–0xFF). Toda la superficie EP0 está mapeada en `tools/rom_probe*.c`.

---

# Sesión 17/10 tarde-noche: el mapa real del scaler (cacería del transitorio)

## Metodología (la revolución de esta sesión)

**La métrica H/V sobre contenido arbitrario NO SIRVE**: los frames de ruido
(garbage de negociaciones fallidas) puntúan ALTO (ruido = gradiente alto) y
el juego real puntúa BAJO (agua/cielo = gradiente suave). Toda la progresión
"degradación 1.297→0.255" de esta noche era contenido, no hardware.

**La única medición válida**: el patrón de calibración en pantalla 1:1
(Firefox F11 en la fuente — el visor de imágenes del Deck escalaba 1.78×
horizontal y contaminó mediciones) + mapeo geométrico de features + veredicto
visual del usuario. Con eso: 60Hz H/V=1.604 geometría 1:1 exacta (verificado
por el usuario), 120Hz estirado 2× (verificado por el usuario).

## El mapa real de registros del scaler (validado con dump 256B 60 vs 120)

| Registro | Contenido | Escritor firmware |
|---|---|---|
| f600 | run/stop scaler | 0xEDxx helpers |
| f604/f605 | ancho sampling (LE) | walk 0xBC16 (único) |
| f606/f607 | ancho #2 (LE) | walk 0xBC2B (único) |
| f60C/f60D | altura #1 | walk 0xBC1E |
| f60E/f60F | altura #2 | walk 0xBC33 |
| f618 | **STATUS readback** (sin escritor fw) | hardware |
| f620-f651 | batería de config del scaler | 0x42D0-0x4450 (llamada solo desde 0x50D4) |
| f65B/f65D/f660/f662 | suite structB: f660/f661=ANCHO REAL, f662/f663=alto | applier 0xBF01 |
| f65C | **STATUS readback del modo** (0x00 boot/0x08 medio/0x10 completo) | hardware |
| f6C0-f6C3 | relojes (idénticos 60/120 — no son el switch) | zona 0xC2xx/0xD3xx |

**Pares LITTLE-ENDIAN** (f606=lo, f607=hi; el fix120 escribe 0x80/0x07=1920).

## Hallazgos estructurales

1. **0xBC02 (walk structA) NO RETORNA**: termina en `ljmp 0xD374` (0xBC61).
   Todo código tras su lcall (0x5842+) es muerto.
2. **0xBF01 (walk structB) SÍ retorna** (ret en 0xBF5D).
3. **structA (0x1AE2) es buffer compartido con el chat I2C del receptor**:
   el walk puede leer veneno EN MEDIO de su propia lectura (por eso cada
   evento latcheaba basura distinta: 960, 720, 50, 2853).
4. **f660/f661 = el ancho REAL de captura** (f606/f618 señuelos).
5. **f660=960 es default de boot** del hardware con 1080p input.
6. **f65C y f618 = readbacks de hardware** — escribirlos solos = ruido
   (verificado: f65c 0x08→0x10 a 120Hz puro = pantalla de ruido).

## La política de 120Hz (la causa raíz definitiva)

1080p120 (pclk 297MHz ≥ 200MHz) → preset de MEDIO ANCHO distribuido en la
batería f620-f651 + f65c=0x08. Es política deliberada de MacroSilicon
(banda: YUYV 1080p120 = 497MB/s, límite USB3). NO es un registro único:
- forzar f660=1920 solo → estirado 2× (v11: verificado por el usuario)
- forzar f65c=0x10 solo → ruido (verificado por el usuario)
- flag 0x20.1 = flag GENERAL del sistema (15 setters) — NO es el bit de
  política (el intento noclass fue en vano y se revirtió)

## El estado que funciona (verificado por el usuario, receta histórica)

**jmp120 puro + daemon fix120d (LaunchAgent) + setformat + fix120 apply**
=> 1080p120 nítida (el usuario la aprobó). El smartguard corrige en caliente
(960→1920 en f606/f618/f660 + f65c=0x10, stop→start) cada pocos segundos.

60Hz: perfecto sin nada (geometría 1:1, H/V=1.604 sobre patrón).

## Firmwares de backup (backup/)

- MS2131_jmp120.bin — **EN USO** (jmp120 puro, la base de la receta)
- MS2131_applier3(b).bin — jmp120 + hook applier (coherencia de boot; sin
  efecto dañino pero innecesario con el daemon)
- MS2131_noclass.bin — NO USAR (flag general parcheado = en vano)
- MS2131_tailhook(2).bin — NO USAR (hooks en la cola con registros equivocados)
- Los demás: historia de la noche

## Herramientas nuevas

- tools/ms213x_trap.c — watcher rápido multi-ventana (¡cuidado: el polling
  agresivo puede wedgear la tarjeta durante cambios de modo!)
- tools/ms213x_forense.c — espera el latch y vuelca el estado
- analysis/suite_dump.sh — volcado completo + H/V
- analysis/patch_*.py — la genealogía completa de parches (reclean→applier)

## Para la próxima sesión (si se quiere matar la política en firmware)

El camino: RE de la batería (0x42D0+, caller 0x50D4) y de dónde salen sus
valores (work-struct) para encontrar el parámetro de medio ancho. El flag
0x20.1 NO es el camino. La alternativa realista: el daemon ya lo hace
perfecto en caliente.

---

# Path de AUDIO — investigación del thump ~1Hz (sesión 2026-11-14)

## Contexto (medición en scalapp, ver ROADMAP scalapp)
Con video streameando aparecen tonos inyectados EN LAS MUESTRAS de audio:
- Sesión 29/10: tono 60.06Hz (+armónicos).
- Sesión 14/11 (1080p60 nativo): PAR 59.5490 / 60.4505Hz batiendo a
  0.9015Hz (el "tum tum" audible), + familia 29.770/30.236Hz.
- Audio-only: LIMPIO (0 tones) → el origen es el dominio de video.
- Las frecuencias SE MUDAN entre configuraciones (siempre alrededor
  del refresco) → bandas laterales tipo FM de un reloj esclavizado.

## Descriptores UAC (flash del backup 2617_44fc)
- 2 sets de descriptores @ flash 0x6e9 y 0xc73 (modos USB2/USB3).
- Interface AC #2, AS #3 alt1.
- AS FORMAT TYPE I: **2ch / 16-bit / 48000Hz exactos** (tSamFreq 0xBB80).
- **EP 0x82**, isocrono DATA, wMaxPacket 192, `bSynchAddress=0x00`,
  **SIN endpoint de feedback** → el device promete audio SOF-locked
  pero NO hay mecanismo explícito: si su reloj de muestreo deriva de
  otro dominio, el host no resamplea y el ruido queda EN BANDA.

## Candidatos XDATA del reloj/config de audio (MAPA_REGISTROS.txt)
Bloques con cara de PLL/divisor (escrituras de pares 16-bit +
constantas, gated por estado de modo):
- `0xF102/F103` ← site 0x69c9: guard `r7==5`; escribe par, const 0xF0
  vía helper 0x6e64; sigue con F108/F109 ← par r7:r6. Lee estado 0x1A74.
- `0xF146/F147` ← site 0x6a21: guard `[0x1A72]^4==0`; **const 0xF4**
  (¿divisor?) + par r6.
- `0xF12A` ← site 0x4d8d: valor compuesto de nibbles de r2/r3
  (decode de dígitos?); también F122/F123 a cero. Lee estado 0x1A78.
Los helpers 0x6e64/0x6da7/0x6e2d (¿wait-ready de PLL?) sin analizar.

## Hipótesis de CAUSA (a verificar en silicio)
El divisor/reloj maestro de audio (f10x/f14x) se deriva del dominio
de video (PLL/pixel) y/o se RETUNEA dinámicamente según el modo → el
ripple del timing de video (decimación, hot-switch, buffering de
línea) fase-modula el reloj de muestreo → bandas laterales alrededor
de refresco/2 y refresco = los pares medidos. Sin feedback EP, el
host no puede corregirlo → tonos en banda.

## Resultados en vivo (17/11 — device prestado, ffmpeg como cliente video-only)
- Sanidad: 0x22BE:BF=0x2EE1 (120.01Hz entrada ✓), 22DE=1920 con stream ✓.
- **Divisores ESTÁTICOS**: f102:f103=0x00F0 (240), f142:f143=0x00F4 (244),
  f106:f107=0xC000, f108:f109=0xC0F8, f146:f147=0x0004 — IDÉNTICOS en
  idle / streaming-60fps / post-stop. **El retuning dinámico de estos
  registros está DESCARTADO** (12s @10Hz, 0 cambios).
- f138/f139/f17c/f17e/f17f TOGGLEAN SIEMPRE (idle incluido, ~8Hz de
  cambios) → contadores free-running, no config video-gated.
- Diff bloque f100-f180 entre stream 60fps y "30fps": solo esos mismos
  contadores (sin confirmar que el 30fps enganchara: 22E4 sigue 6000).
- **Constraint nuevo**: los pares medidos son SIMÉTRICOS alrededor de
  30.000/60.000 EXACTOS (media del par 60.4505+59.5490)/2 = 59.99975)
  → bandas laterales de un proceso coherente a 60.000 exacto, con
  modulación ~0.45/0.23Hz. Un divisor de 24MHz daría 60.000 limpio
  (24e6/400000 = 60.000); el 59.94 HDMI NO es el portador.

## Hipótesis vigente (post-falsificación)
La inyección no es config-de-registro dinámica: es que el ENTREGADOR
de muestras al EP 0x82 (bomba isoc) se pacinga contra un proceso de
60.000Hz exacto (¿SOF-driven? ¿timer del diezmado 120→60?) cuyo
timing real tiene jitter/wow de ~0.75% modulando a 0.23-0.45Hz, o DOS
pumps de ~60Hz con rates distintos. Hay que leer el código de la
bomba del EP — próximo milestone RE.

## Próximos pasos (en orden)
1. **Atribución por captura (sin HID, scalapp solo):** con la fuente
   SONANDO: (a) UVC 60fps nativo, (b) UVC 30fps (--30), (c) fuente a
   1080p60. audio_diag sobre SCALAPP_REC dice si el par se mueve con
   la tasa UVC o con la de entrada.
2. **Bomba del EP 0x82**: los FIFOs de EP se escriben por DPTR indirecto
   (invisible al scan directo) → RE del ISR USB (int vectors 8051) y
   del handler del EP2 IN. Preguntar: ¿contra qué reloj se pacinga?
3. Helper 0x6e64/0x6da7/0x6e2d (¿PLL wait-ready?) y semántica de los
   divisores 240/244 (¿dos canales? ¿I2S L/R?).
4. FIX: parche de firmware (pacing contra cristal) o notches host-side
   (ya operativos en scalapp).

## ATRIBUCIÓN CONCLUIDA (17/11, capturas A/B con contenido)
- A (UVC 60fps nativo): portador **119.998Hz** (2× tasa UVC), bandas
  ±0.06-0.08Hz.
- B (UVC 30fps nativo): portadores **60.004 y 30.001Hz** (2× y 1× tasa
  UVC), bandas ±0.046Hz.
- El portador SIGUE a la tasa de frames UVC — NO al HDMI de entrada
  (si fuera 59.94/119.88 no se movería con --30).
- **CAUSA (dominio)**: la bomba isócrona de VIDEO UVC perturba la
  entrega de muestras del isoc de AUDIO (arbitración interna del
  USB del chip: cada frame de video en ráfaga roba ciclos al isoc de
  audio → micro-saltos de fase periódicos a f_uvc y armónicos →
  tonos en banda; sin EP de feedback, el host no puede corregir).
  La envolvente lenta ("tum tum" 0.5-1Hz) = nivel de buffer ciclando.
- Varianza entre sesiones: 14/11 dio par 59.55/60.45 (bandas ±0.45Hz);
  hoy bandas ±0.05Hz — la modulación depende de carga/contenido.
- Los notches de scalapp ya cubren 60/120; para 30fps nativo el
  portador 30Hz es casi subsónico y el 60 sigue cubierto.

## Estado
- [x] Descriptores UAC parseados
- [x] Bloques candidatos identificados (f10x/f14x/f12a)
- [x] Watch en vivo: divisores estáticos, contadores libres
- [x] Falsificado: retuning dinámico de divisores
- [x] Atribución de tonos por capturas A/B → dominio UVC
- [ ] Bomba EP 0x82 localizada (el detalle fino del mecanismo)
- [x] Causa atribuida al dominio (bomba de video UVC vs isoc audio)
