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
