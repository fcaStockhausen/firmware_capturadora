# CASUÍSTICA — Gaps de audio isócrono durante streaming de video

> Objetivo: entender de dónde provienen los INPUT GAPs de audio
> (~100-220ms) que aparecen cuando la MS2131 streamea video, para
> volver a un colchón de 50ms en scalapp sin blips.
>
> Escrito el 2026-10-29 tras la sesión de A/B (ver BITACORA).
> Firmware de la unidad: **flat3** (jmp120 + {8758,9bd1,dab7,e655}).

## 1. Síntoma medido (scalapp, instrumentado)

Scalapp loguea con timestamp `t=` (desde arranque) y `@HH:MM:SS`
(reloj de pared) tres eventos: `INPUT GAP` (stall del callback de
entrada), `UNDERRUN` (silencio insertado) y trayectoria de cola cada
5s. Datos acumulados:

- Gaps de **99-216ms**, cada 25-170s, **solo con video streameando**.
- El bloque de entrada NUNCA cambia de tamaño (Fixed(256) estable) →
  no es renegociación de la interfaz de audio.
- La cola no explota al recuperar el gap → **los samples nunca
  llegaron**: el device/driver los dropeó (no fue bloqueo nuestro).
- Audio-only (misma engine, sin video): **0 gaps en 3min**.
- 1080p60 (250MB/s) y 720p60 (110MB/s): **mismo ritmo de gaps** →
  no es ancho de banda USB.

## 2. El hallazgo del 29/10: el formatguard está involucrado

A/B controlado, mismo día, misma señal, 3 minutos por rama:

| formatguard | setformat disparados | INPUT GAPs |
|---|---|---|
| **OFF** (`launchctl bootout`) | 0 | **0** |
| **ON** (restaurado) | 0 | **2** (101ms, 104ms) |

La rama ON tuvo gaps **sin que el guard disparara ni un setformat**
→ el imputado es el **polling HID cada 2s** (`ms213x_xdata read
22de/22df` via subprocess), no el fix.

Además, correlación gruesa histórica: la peor corrida de gaps
(201/207/203/209ms cada ~25s, 16:38-16:46) coincide con la **tormenta
de 27 setformat** del guard (16:42:34→16:48:02, `/tmp/ms2131_formatguard.log`)
— el device se caía a 1280 cada ~10s y cada arreglo glitcheaba todo.

## 3. Hipótesis (re-rankeadas tras el A/B)

- **H1 — El polling xdata del formatguard interfiere con el isoch.**
  El firmware es un núcleo chico atendiendo USB control + isoch +
  HDMI; cada control transfer (o cada OPEN del dispositivo por el
  subprocess) puede pausar el servicing isoch. La mayoría de los
  polls pasan (<15ms), algunos aterrizan mal → gap ~100ms.
  Estado: **imputado principal, A/B positivo**.
  Sub-preguntas: ¿el open/close del subprocess o el read en sí?
  ¿depende de la cadencia?
- **H2 — Cada setformat agrega un gap grande (~200ms).**
  Reconfiguración completa del pipeline. Estado: correlacionado en
  la tormenta 16:42-16:48. (Consecuencia de H1 si los drops a 1280
  también son autoinfligidos — ver E6.)
- **H3 — Residuo propio del firmware flat3/jmp120.**
  Con guard OFF hubo 0 gaps en 3min, pero 3min no descarta eventos
  raros. El soak del flat3 documentó "3 dropoffs de 2s
  autorecuperados" — fenómeno distinto (2s ≠ 100ms) que conviene
  mantener separado.
- **H4 — Block size del audio.** Implausible (gap ≠ múltiplo de
  bloque; el bloque no cambia). Descartable barato.
- **H5 — Fuente HDMI.** Los gaps sobreviven cambios de resolución de
  captura pero no se probó cambiar la fuente. Baja prioridad.
- **H6 — Scheduling USB por ancho de banda.** DESCARTADO (720p60 =
  1080p60).

## 4. Casuística propuesta (experimentos)

Ordenados por costo. Cada uno dice qué hipótesis mata.

| ID | Experimento | Discrimina | Cómo |
|---|---|---|---|
| E1 | Guard OFF + polls manuales: `while true; do ms213x_xdata read 22de; sleep 2; done` desde terminal durante stream | separa "xdata read en sí" de "subprocess/open del guard" | Si los gaps reaparecen → el read/control-transfer es el veneno (H1 read). Si no → el open repetido del dispositivo o el contexto launchd |
| E2 | Igual con cadencia 10s y 30s | dosis-respuesta de H1 | gaps ∝ frecuencia de polls → H1 confirmada con mecanismo |
| E3 | Guard OFF + monitoreo del formato por AVFoundation (`ms2131_setformat --status` desde terminal, sin HID) | observa sin tocar HID | gaps = 0 → el camino HID es el problema, AVFoundation no |
| E4 | Guard OFF, stream 15-20min (soak corto de audio) | H3 (residuo) | algún gap raro → existe fuente adicional al guard; 0 gaps → el guard era TODO |
| E5 | Guard ON + instrumentar cada poll en el guard (log timestamp + duración de cada xdata read) | correlación fina H1 | el gap cae pegado a un read lento → mecanismo directo |
| E6 | Guard OFF + vigilar [22DE] solo por AVFoundation durante 15min | ¿los drops a 1280 son autoinfligidos por el polling? | si el formato se mantien 1920 sin guard → el guard CAUSA lo que vigila (rediseñar el guard) |
| E7 | `--block-size 512/1024` en scalapp con guard OFF | H4 | irrelevante si E4 da 0 gaps |
| E8 | Cambiar la fuente HDMI (otra consola/PC o resolución de entrada) con guard OFF | H5 | idem |
| E9 | **Parche de firmware**: si E1/E5 confirman el control-transfer como veneno, hacer que el handler xdata no deschedule el isoch (o mover el poll a una ventana segura) | raíz | tenemos flasher, genealogía de parches y mapa de registros — es el camino "de verdad" |
| E10 | Long-run: guard rediseñado (poll por AVFoundation o cadencia ≥30s) + colchón 50ms fijo en scalapp, 1h de uso real | meta final | 0 blips a 50ms = objetivo cumplido |

## 5. Notas de método

- Los timestamps `@HH:MM:SS` de scalapp ya son hora LOCAL y
  directamente correlacionables con `/tmp/ms2131_formatguard.log`.
- IMPORTANTE: observar [22DE] con `ms213x_xdata` CONTAMINA el
  experimento (es el mismo mecanismo imputado). Para E6 usar
  AVFoundation.
- El guard quedó RESTAURADO y corriendo tras los tests (estado de
  producción intacto). Para repetir E1: 
  `launchctl bootout gui/$(id -u)/cl.fcaraneda.ms2131formatguard`
  y al terminar
  `launchctl bootstrap gui/$(id -u) ~/Library/LaunchAgents/cl.fcaraneda.ms2131formatguard.plist`.
- Mientras el guard siga ON, el colchón adaptativo de scalapp
  (~150ms) es la protección correcta. La meta de 50ms requiere
  resolver H1 (guard off / rediseñado / parcheado).

## 2b. Resultados de la investigación (misma tarde)

**Run A — subprocess por poll (como v2), desde terminal, 3 fases
dentro de la misma corrida:**

| Fase | Actividad | INPUT GAPs |
|---|---|---|
| F1 (70s) | nada | 0 |
| F2 (122s) | `xdata read` ×2 cada 2s (subprocess) | **1** (105ms) |
| F3 (40s) | nada | 0 |

→ El veneno se reproduce fuera de launchd: es el acceso HID, no el
contexto. ~1 open/s produce ~1 gap/min (la mayoría de los opens
pasan; alguno aterriza mal).

**Run B — `watch` residente (UN solo hid_open sostenido):**
catastrófico. 2 minutos de **stutter continuo**: gaps de ~285ms y
~185ms alternándose (~3.5/s), underruns en cada callback, colchón al
tope (350ms). Al cerrar el watch, silencio inmediato. [22DE] se
mantuvo 1920 todo el window (sin drops — solo la primera lectura
impresa).

**Modelo final del comportamiento HID↔isoch:**

| Diseño | Exposición HID | Daño |
|---|---|---|
| sin HID | 0 | 0 gaps |
| open/close efímero por poll (v2) | intermitente | ~1 gap/min |
| interfaz abierta sostenida (residente) | 100% del tiempo | stutter continuo |

El daño escala con la exposición; lo peor es SOSTENER la interfaz
(abierta, el host la polea). Conclusión de diseño: **el único acceso
HID inocuo mientras streamea es ninguno**.

## 2c. El fix: formatguard v3 (implementado y validado)

`tools/ms2131_formatguard.py` v3 (= v2 + pausa HID consciente de
clientes):

- `pgrep` (gratis, no toca el device) cada ciclo: si **scalapp** está
  corriendo → pausa HID total (el streaming queda a 0 gaps; el
  formato lo renegocia el propio scalapp al abrir con modo exacto).
- Sin clientes → vigilancia HID v2 intacta (detección [22DE:DF],
  setformat con watchdog, backoff anti-guerra).
- Transiciones logueadas ("pausa HID"/"vigilancia reanudada").

**Validado 18:07-18:11**: guard ON + scalapp 245s → **0 gaps**,
transiciones correctas en el log. El backup de v2 vive en
`tools/ms2131_formatguard_v2.py.bak`. El LaunchAgent no cambió (mismo
path).

Con v3, scalapp corre limpio a colchón base **50ms** (meta cumplida);
el colchón adaptativo queda como red de seguridad si algún día se
necesita tocar el HID con el stream abierto.

## 6. Estado

- [x] E0: matriz base (audio-only / 1080p60 / 720p60) — 29/10
- [x] A/B formatguard ON/OFF — 29/10 (OFF = 0 gaps)
- [x] E1: subprocess vs contexto — 29/10 (reproducido desde terminal:
      1 gap/122s de polls)
- [x] E5: residente (open sostenido) — 29/10 (stutter continuo,
      diseño descartado)
- [x] **Fix v3 implementado y validado** (pausa HID con clientes) —
      29/10, 18:07
- [ ] E6: ¿los drops a 1280 son autoinfligidos por el polling? —
      pendiente (observar [22DE] por AVFoundation con guard en pausa;
      hoy solo evidencia circunstancial: [22DE] estable 1920 durante
      todo el Run B con el stream activo)
- [ ] E4: soak largo audio+video con v3 (residuo de firmware) —
      pendiente
- [ ] E9: parche de firmware (handler xdata sin deschedulear isoch) —
      queda como el camino "de verdad" si algún día se necesita
      polling HID durante el stream
