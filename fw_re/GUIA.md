# GUÍA DEL FIRMWARE MS2131 — Manual completo de reconstrucción

> Documento maestro de referencia. Fuentes: ingeniería inversa manual
> (radare2), decompilación masiva Ghidra (`fw_re/decomp/`, 1034 funciones en
> C), observación en vivo (HID/registros), el conocimiento comunitario de
> hsdaoh, y los experimentos controlados de octubre 2026. Cada sección cita
> su evidencia.
>
> **Estado del sistema vigente**: firmware `jmp120` + boot natural +
> `setformat` ante drops + formatguard v2 (LaunchAgent
> `cl.fcaraneda.ms2131formatguard`). Guard de registros: PROHIBIDO.

## Índice

```
PARTE I — LA MÁQUINA
  1. Identidad y arquitectura
  2. Mapa de memoria
  3. Boot decodificado (0xA4EB)
  4. Vectores de interrupción

PARTE II — EL PIPELINE DE VIDEO
  5. Inventario de funciones
  6. Flujos principales
  7. El scaler — mapa completo de registros (f6xx)
  8. Inventario de registros f000-f7ff (instruction-level)
  9. La batería decodificada — la ventana de muestreo
  10. La política de 120 Hz
  11. El muro de la unidad (modelo final, 27/10)
  12. El modelo trajectorial (principio rector)

PARTE III — SUPERFICIE EXTERNA
  13. Protocolo HID
  14. Superficie de configuración del fabricante
  15. Parches — genealogía completa

PARTE IV — OPERACIÓN Y ECOSISTEMA
  16. Recetas operativas y doctrina
  17. Ecosistema de herramientas
  18. Historial de daño y límites de esta unidad

PARTE V — ESTADO ACTUAL Y CAZA DEL CRASH
  19. Los dos bugs abiertos (A y B)
  20. Análisis de stack (la caza del crash, 27/10)
  21. Próximos pasos
```

---

# PARTE I — LA MÁQUINA

## 1. Identidad y arquitectura

| Campo | Valor |
|---|---|
| Chip | MacroSilicon MS2131 (USB 3.0 HDMI capture) |
| USB firmware | VID:PID `345f:2131` ("USB3 Video" / USB2 fallback "USB2 Video") |
| ROM fábrica | VID:PID `534d:2130` ("USB Video") — mask ROM inmortal, if#4 oculta en USB3 habla el protocolo de flasheo |
| CPU | 8051 (SDCC-compiled) — 16-bit BE en Ghidra (`8051:BE:16:default`) |
| Flash | SPI, imagen de 62715 bytes: header 0x30 + código 0xF4C7 + checksum 2B (BE, suma del código) |
| Firmware base | 2025-04-09 (backup íntegro en `backup/MS2131_2025-04-09_backup_2617_44fc.bin`) |

Direcciones: **addr de código = offset en flash − 0x30**. El desensamblado
referenciado usa direcciones de código.

## 2. Mapa de memoria

### 2.1 XDATA (RAM externa del 8051)

| Rango | Contenido | Evidencia |
|---|---|---|
| `0x0000-0x00FF` | Flags/scratch de propósito general (SDCC reusa: 0x20.1 = flag de sistema con 15 setters; 0x30/0x31/0x32 = índices de modo/fps; 0xE4 = scratch) | escaneos de escritores |
| `0x1000-0x12FF` | Buffers de comandos/protocolo (USB strings en 0x1042+; matcher ptrs 0x12A9/0x12CE) | dumps |
| `0x1A6x-0x1AFF` | **Work-struct del pipeline**: [1AAD]=pclk/10kHz, [1AAF] geometría, [1AB1]=clase, [1ABB-1ABF] cómputos de la batería, [1AA9] puntero, [1AE0-1AEB] struct A (w1,h1,w2,h2 @1AE2), [1AEA-1AEB] struct B w, [1AEE-1AF0] puntero de walk (scratch), [1AF1-1AF3] puntero auxiliar, [1AFB] variable del ÷2 original | RE manual + forense en vivo |
| `0x1Bxx-0x1BEx` | Zona matcher (1B13, 1B25-1B38, 1B4x, 1B7x, 1BBx-1BEx: campos intermedios del emparejador de tabla) | disasm zona 0x5Bxx-0x5Fxx |
| `0x1C0x-0x1C6x` | Zona relojes/gobernanza ([1C0C], [1C10]-[1C15]: comparaciones de ancho de banda tras ÷2^r0) | disasm 0x9477 |
| `0x1FD4-0x1FE0` | Overrides vendor (leídos por sub_4454 — si ≠ 0xFF, pisan la detección) — ver §14 | **decomp sub_4454** |
| `0x22B8-0x22E1` | **Estado de entrada HDMI**: [22B8:B9]=ancho BE, [22BA:BB]=alto BE, [22BC:BD]=pclk×10kHz, [22BE:BF]=refresh×100 BE, [22DC:DD]=scratch, [22DE:DF]=formato activo w BE, [22E0:E1]=formato h BE | lecturas en vivo |
| `0xF0xx` | **Receptor HDMI** (entrada): f039/f030=forzado RGB/YCbCr, f062/f063=EDID RAM switch, f005, f007, f06c | hsdaoh + decomp |
| `0xF6xx` | **Scaler** (ver §7) | toda la investigación |

### 2.2 IRAM (directa)

Scratch SDCC multiuso. Conocidos: 0x30/0x31/0x32 (índices), 0x4B (SP de
boot), 0xC8/0xC9, 0xE4. Los flags bit-addressables de 0x20/0x21 son
compartidos por subsistemas (0x20.1, 0x20.3 = clase alta marcada).
**El stack vive entre SP=0x4B y 0x7F — ver §20 para el presupuesto.**

## 3. Boot decodificado (0xA4EB)

El vector RESET (`ljmp 0xA4EB`) ejecuta (verificado en decomp
`f_CODE:a4eb.c` + disasm):

```
RESET → 0xA4EB:
  1. Limpia la IRAM completa (0x7F → 0x00, loop descendente)
  2. SP = 0x4B                       ← el presupuesto de stack nace acá
  3. Descomprime tablas de init (RLE) desde CODE:0x2AA3:
     - copia bloques a XDATA/IRAM
     - modos AND/OR con máscara contra tabla @0xA51E (set/clear de bits)
  4. main = FUN_CODE_4f20()          ← el programa principal
```

Al boot el scaler queda en default de fábrica con entrada 1080p:
f660/f661 LE = 0x8007 (no es un ancho válido — valor basura de reset),
f65c=0x00. Un evento real de config (formato/modo) lo pone coherente.

## 4. Vectores de interrupción

| Vector | Addr | Handler | Fuente probable |
|---|---|---|---|
| RESET | 0x0000 | `ljmp 0xA4EB` | arranque (§3) |
| Ext. 0 | 0x0003 | `ljmp 0xD595` | **USB** (transacciones/eventos) |
| Timer 0 | 0x000B | `ljmp 0xC5ED` | timer del sistema |
| Ext. 1 | 0x0013 | `ljmp 0xB44D` | evento externo (¿RX HDMI?) |
| Timer 1 | 0x001B | `ljmp 0x624F` | timer |
| Serie | 0x0023 | dispatch en el propio vector | UART/spi |

**Verificado 27/10**: los `ljmp` de EXT0/TIMER0/EXT1/TIMER1 aterrizan
EXACTAMENTE donde empieza el prólogo de pushes del ISR (ver §20.2) — la
medición de stack por función es válida para el camino de interrupción.

Los huecos entre vectores contienen trampolines diminutos (sembrados como
funciones en decomp/): `0x0006` (mov r7,#8; ljmp 0x7D18), `0x000E`
(setb P1.1/P1.0; ret — pins USB arriba), `0x0016` (clr a; mov r3,a;
**ljmp 0xE279** = llamada al escritor universal de registros con valores 0).
La cadena del ISR USB usa el trampoline 0x0016: **el USB escribe registros
f6xx desde contexto de interrupción** (ver cadena EXT0 en §20.1).

Cada handler es un punto de entrada crítico: si alguno crashea (puntero
loco, stack overflow), el 8051 se cuelga → el host resetea el USB → la mask
ROM queda sosteniendo el bus (= "caída a ROM", el síntoma del bug B §19).

---

# PARTE II — EL PIPELINE DE VIDEO

## 5. Inventario de funciones

1237-1242 funciones (sembradas del call-graph: targets de lcall/acall).
Pseudocódigo completo: `fw_re/decomp/f_CODE:XXXX.c` + `INDEX.txt`.

### 5.1 Zonas funcionales (por dirección de código)

| Zona | Subsistema | Funciones clave |
|---|---|---|
| `0x0000-0x07FF` | Vectores/reset + USB descriptors + tabla de modos | tabla de resoluciones @0x0130-0x01E7 (pares w,h BE: filas A/B 12 entradas, C/D 11) |
| `0x0E00-0x12FF` | Helpers SDCC (struct/property engine) | 0x0EC5 "avanzar y leer campo", 0x0EF0, 0x0F94, 0x0FC1, 0x104C, 0x1138, 0x1253 |
| `0x2Fxx-0x3Axx` | Librería de struct (getters/setters XDATA) | **0x3A00** = "copia 16-bit [dptr]→[1AE6:47]" (usado por 0x944B y 0xB77D) |
| `0x33xx` | Lectores de clase/propiedad | 0x33FB lee [0x00E4] |
| `0x35xx-0x37xx` | **Clasificador de modos** | 0x3569 = sitio del parche jmp120 (el ÷2 de [1AFB] del hot-switch); 0x3522 función del bloque |
| `0x42C0-0x4460` | **Batería del scaler** (f620-f651) | llamada solo desde 0x50D4; lee work-struct; **0x4454** lee overrides 0x1FD4-0x1FE0 (decomp) |
| `0x48xx-0x4Axx` | Selección de preset por clase | 0x48DD `cjne a,#5` — clase 5 (pclk alto) usa tabla base +0x5C; lee [22DE] vía 0x307C (tabla en código) |
| `0x4Dxx-0x50xx` | **Secuencia de init/arranque del scaler** | 0x50D4 llama la batería; retrasos 200/100 |
| `0x569E-0x5860` | **Cadena de config** (el "chain") | 0x56E0 copia [22DE]→[1AE6]; 0x5707 clamp min→struct B; 0x57EB-0x581F detector 1080p-alto-fps ([1AEA]=05); **0x583F lcall 0xBC02** (walk A, único f604/f606/f60c/f60e); **0x5856 lcall 0xBF01** (walk B); 0x5859/0x585C cola (lcall 0xEDE2 + ljmp 0xEDFD) |
| `0x5Axx-0x5Fxx` | Matcher de tabla de timings | escribe el struct vía helpers 0x3FBB/0x3FD6/0x4079/0x4117; 0x5D3E lcall 0x9D1D ([1AEA]:=r7) |
| `0x6Axx-0x6Cxx` | Gestión de índice de resolución | [0x1A73] índice; 0x66A4 defaults |
| `0x9300-0x9800` | **Detector pclk** + clase + chat I2C | 0x93C6: [1AAD]=pclk, flag 0x20.1 = (pclk≥20000); 0x9440-0x9476 clasificador+copias; 0x9477-0x9482 loop ÷2^r0 (gobernanza de banda, compara [1C15]); 0x98xx = chat I2C (surgeons [1AE6]=01/08/'R'/'r'/0x32) |
| `0x9Cxx-0x9Dxx` | Walk-helpers de struct B | 0x9C02/0x9C05/0x9C73/0x9BFD |
| `0xBC02` | **Walk struct A → f604/f60c/f606/f60e** (ver decomp!) | NO RETORNA: tail `ljmp 0xD374` @0xBC61. El código tras cualquier lcall suyo es muerto |
| `0xBF01` | **Walk struct B → f65B/f65D/f660/f662** | SÍ retorna. f660/f661 = el ANCHO REAL |
| `0xC2xx` | Escritores genéricos f6xx (r6=F6+r7=reg) | f65A/f6B4/f6BF, f6C0-f6C3 (relojes) |
| `0xD3xx` | Cola post-walk | 0xD374 continuación (se auto-inicializa: descarta A/r6/r7 de entrada) |
| `0xD6xx` | Helpers de puntero | 0xD6BE/0xD6C1 cargan ptr desde [1AF1]/[1AEE]; 0xD6CA escribe 16-bit |
| `0xED8x-0xEE01` | API de alto nivel de escritura | f600/f620 writers, resets |

### 5.2 La entrada de la cadena

- **sub_3D31 = entrada DIRECTA de la cadena con geometría explícita**: limpia
  el struct, setea [1AE2:44] con los params, dispara sub_0d92(...,0x15) +
  sub_0dd1(4,...) → la cadena completa corre.
- **sub_1FB8 = el puente matcher→cadena**: copia de propiedades
  ([0x1124]→[1ABB]), setea clase [1AE5]=1, [1AE6:47]={0x22,0xB3}, llama
  sub_3d31(0xc4,0x1a,1). Único caller: 0x2003 (dentro de sub_1fb8).
- **Escritor universal 0xE279(page, reg, mask=r5, val=r3)** = field-update
  (`reg = (reg & ~mask) | (val & mask)`). Thunk 0xEE2F incluido.

## 6. Flujos principales

### 6.1 Conexión HDMI / cambio de modo
RX detecta timing → [22B8-BF] se llena → clasificador (pclk → clase en
[1AB1]/[0xE4]) → matcher de tabla → struct A/B → cadena 0x569E → walk A
(0xBC02) + walk B (0xBF01) → suite del scaler. **A pclk≥200MHz (1080p120)
el preset de clase alta configura MEDIO ANCHO** (política de banda, §10).

### 6.2 Negociación de formato UVC (SET_CUR/COMMIT)
El handler escribe [22DE:21] (por tabla vía 0x307C desde 0x48xx según
clase/índice) → cadena → walk. Sin cambio de formato NO hay evento →
un "open pelido" no reconfigura nada (verificado).

### 6.3 Stream open/close
`f600` bit0 refleja el estado del consumidor (se pone en 1 SOLO cuando un
cliente UVC abre; escribirlo es un comando, su valor estable es estado).

## 7. El scaler — mapa completo de registros (f6xx)

Pares **LITTLE-ENDIAN** (reg=lo, reg+1=hi).

| Registro | Función | Escritor fw | Notas |
|---|---|---|---|
| f600 | bit0=run/stop (comando+estado), **bit7=0x80 interpolación de croma** (hsdaoh) | 0xEDxx | el fix120 solo escribía bit0 |
| f601 | STATUS (0x47@60 / 0x4b@120-medio / 0x53@120-full) | — ninguno (readback) | ⚠️ escribirlo crasheó el chip (18/10) |
| f604/f605 | ancho sampling | 0xBC16 (walk A) | |
| f606/f607 | ancho #2 | 0xBC2B (walk A) | histórico "el" registro — en realidad secundario |
| f60C/f60D | alto #1 | 0xBC1E | |
| f60E/f60F | alto #2 | 0xBC33 | |
| f618/f619 | STATUS/readback | — ninguno | valores observados: 1, 121, 960, 1920 |
| f620-f651 | **batería de config** (timing/geometry/?) | 0x42C0-0x4450 (solo caller 0x50D4) | parcialmente decodificada (§9); NO difieren 60 vs 120 en la ventana |
| f65B | ? | 0xBF24 (walk B) | |
| f65C | **modo declarado**: 0x00 boot / 0x08 medio-ancho / 0x10 full (hsdaoh: "H rescale off") | — ninguno directo (readback del modo) | escribirlo solo = RUIDO (necesita su config completa) |
| f65D | ? | 0xBF3F (walk B) | |
| f65E | **reescalado VERTICAL** (0x10=off) — hsdaoh | ? | nunca vigilado hasta 22/10 |
| f660/f661 | **ANCHO REAL DE CAPTURA** | 0xBF4A (walk B, directo) | el que cura el blur |
| f662/f663 | alto real | 0xBF56 (walk B) | |
| f6B0 | sharpening (0=off) — hsdaoh | ? | |
| f6BE/f6BF | procesado luma/croma (0x11=off) — hsdaoh | ? | |
| f6C0-f6C3 | relojes | 0xC2xx/0xD3xx/0xDExx | idénticos 60 vs 120 |

## 8. Inventario completo de registros f000-f7ff (23/10, instruction-level)

Mapa definitivo por instrucciones reales (no coincidencias de bytes):
`fw_re/MAPA_REGISTROS.txt` — 80 registros.

- **f0xx = frente HDMI**: ~23 status-readers + escritores concentrados:
  - **0x3EB2-0x3EF3: el configurador de ventana del RECEPTOR** — f032/f033,
    f034/f035, f036/f037 = posiciones/ventana de muestreo RX (compuestas
    de propiedades 0x11/0x0D vía sub_d404/d425) + f031|=0x80
  - f039 (input-format force, hsdaoh) escrito @0x3f98 (misma zona)
  - f00e = RW en la cola (0xd17c) — estado negociable
  - f0b0-f0b8 (0xc9xx) = ¿audio?
- **f1xx = config de subsistemas 0x69xx/0x6Axx/0x4Dxx** (sin mapear aún):
  f102/f106, f124/f127/f12a, f142/f146
- **f5xx**: f582/f58e leídos en 0x63xx; f5c2 escrito @0xce40
- f620 LECTOR @0x998f (¡el flag lo consulta la zona del chat I2C!)
- La batería confirma todos sus sitios de escritura (0x4334-0x444c)

## 9. La batería decodificada (23/10) — la ventana de muestreo

Formato del timing window (pares LE, idéntico en 3 grupos f62e/f63a/f646):

| Registro | Significado | @60Hz-perf | @120Hz-diez |
|---|---|---|---|
| f622/3 | HTOTAL | 2370 (custom Deck) | 2370 |
| f624/5 | VTOTAL | 1125 | 1125 |
| f62e | **HSTART** | 96 | 96 |
| f630 | **HACTIVE** (ventana con overscan) | **2016** | **2016** |
| f632 | VSTART | 20 | 20 |
| f634 | VACTIVE | 1100 | 1100 |
| f620 | flags | **0x0C01** | **0x0C00** ← bit0 difiere |

**Hallazgo central: la ventana de muestreo NO se reduce a 120Hz** — la
diezmación vive 100% en el motor de escalado (f65c/f606/f660). El sampler
entrega 2016-wide a 120 igual que a 60.

f620 bit0 (1@60 / 0@120) resultó ser **readback puro** — el experimento
24/10 lo descartó (tercera trampa del readback: se revierte solo).

## 10. La política de 120 Hz (la causa raíz de todo el proyecto)

```
pclk ≥ 200 MHz (1080p120/4K30) 
  → clase alta (flag/preset, NO un registro único)
  → batería f620-f651 + modo f65c=0x08 + anchos 960
  → captura a medio ancho, upscale bilinear → blur horizontal
```

- jmp120 (1 byte @0x3569) mata la instancia del ÷2 en el hot-switch — NO la
  política de estado estable.
- Forzar solo anchos (f606/f618/f660=1920) sin el resto → en esta unidad
  post-daño: **tearing por saturación** (franjas de cuadros mezclados =
  line-buffers del camino de entrada). En estado pre-daño funcionó una
  semana (la receta histórica).
- Forzar f65c solo = ruido. Flag 0x20.1 = flag general (15 setters), no es
  el interruptor.
- La razón de ser de la política: **el procesado full-width de una entrada
  a 120 Hz es la carga prohibida** — ver §11.

## 11. El muro de la unidad (modelo final, 27/10)

Refinamiento por observación del usuario (27/10): **el muro no es la tasa
de SALIDA, es la ENTRADA full-width a 120 Hz**. Definición del usuario:
*"lo que no sostiene es el 1080p120 convertido a 1080p60"*.

| Estado | Entrada HDMI | Procesado/salida | Resultado |
|---|---|---|---|
| 1080p60 nativo | 1080p60 (248 MB/s) | 1080p60 full-width | ✅ estable TODO EL DÍA |
| 120 natural (jmp120) | 1080p120 full | diezmado a 960, upscale | ✅ estable SEMANAS |
| 120 forzado por registros | 1080p120 full | 1920 full-width | ⚠️ tearing por saturación (22/10) |
| no720 (stream Discord) | 1080p120 full | conversión full-width a 1080p60 | 💀 **CRASH A ROM mid-stream** (27/10) |

El experimento no720 (§15) lo demostró: al quitar 720p del menú UVC,
Discord streamea 1080p60 MJPG full-width = el chip procesa la entrada a
120 Hz full-width (497 MB/s lado entrada) sostenido → el firmware cae a
ROM. **La política de medio-ancho de MacroSilicon existía por esto.**
Es el mismo muro visto desde: el tearing del f660 forzado (22/10), el
crash-on-HDMI del hardware dañado (18-19/10), y la caída mid-stream (27/10).

## 12. El modelo trajectorial (principio rector, 24/10)

El experimento f620-bit0 en estado limpio cerró el caso:

1. **El estado bueno NO son valores de registro — es la TRAYECTORIA del
   pipeline**: boot natural @1080p120 = BIEN (verificado dos veces);
   cualquier ciclo stop→write→start (guard, fixes) lo degrada y NO se
   restaura escribiendo los valores "naturales" de vuelta. Solo replug.
2. **Forzado full a 120 en el estado más limpio posible = distorsión** —
   límite real del motor de escalado. Caso cerrado.
3. **El drop de formato a 720p (Discord) = feo** — y su cura segura es
   SOLO `setformat` (pasa por el camino de negociación del firmware,
   no toca registros del scaler).
4. **Las tres trampas del readback**: f601, f65c, f620-bit0 — escribirlos
   no cambia el modo; f601 además crasheó el chip una vez (18/10).
   Los registros con cero escritores de firmware son territorio prohibido.

**RECETA FINAL VALIDADA**: jmp120 + boot natural + setformat ante drops de
formato. Guard de registros: PROHIBIDO en esta unidad (degrada
trajectorialmente).

---

# PARTE III — SUPERFICIE EXTERNA

## 13. Protocolo HID

Protocolo HID (interfaz 0): SET report id=cmd + 7 payload; GET report 0x01,
valor en byte 3. **La respuesta trae 4 bytes: [3..6] = addr..addr+3**
(lectura en bloque gratis — base de tools/ms213x_trap).

**Endianess en Mac (lección del formatguard v2, 24/10)**: los pares de
estado ([22B8], [22BE], [22DE]...) llegan con el byte ALTO primero (BE) —
el v2 inicial nunca matcheaba por leerlos LE.

## 14. Superficie de configuración del fabricante (22-23/10)

sub_4454 (dentro de la batería, caller 0x50D4) consume 4 overrides externos
en XDATA — **sin escritor en el firmware: diseñados para setearse por USB/HID**
(herramienta vendor). Todos viven 0xFF (dormidos) de fábrica:

| Override | Significado | Destino | Estado en vivo |
|---|---|---|---|
| [0x1FD4:5] | **VID override** (USB rename) | [0x1057:58]+[0x1069:6A] | activo con 0x345f real |
| [0x1FD6:7] | **PID override** (USB rename) | [0x1059:5A]+[0x106B:6C] | activo con 0x2131 real |
| [0x1FE0] | **contador de lista de modos** | inyecta N IDs en objeto [0x240A]+, flags [0x264B/C] | FF (lista default: 11 modos) |
| [0x1FE1..] | los IDs de modo (VIC codes, 1B c/u) | — | — |
| [0x1FF0] | rename de audio | strings 0x109F/0x10DF | FF |

- Mecanismo exacto (raw disasm): en cada init de modo, loop copia
  [0x1073+i]→[0x240A+i] (22B default) — el override cambia la fuente a
  [0x1FE1+i] (data nuestra por HID).
- Las listas 0x109F/0x10DF (38B) = **strings UTF-16**: "USB3 Digital Audio" /
  "USB2 Digital Audio". El disparador del consumo = **evento de modo HDMI**
  (NO formato, NO replug: el override vive en RAM y se pierde).
- La lista default viva: [0x240A]=0x16 (11 modos), entradas 0xFF (skeleton —
  el consumidor usa defaults). Los VICs default: 55/53/42/66/20/105/100/101/111...
- El dispatcher de objetos 0x3B65+ ([IRAM 0x0B]=propiedad → helpers
  0xA3D6-A44D) = la API de propiedades interna que usa esta configuración.

**Superficie vendor CERRADA**: VID/PID rename + nombre audio + **lista de
VICs (única funcional)**. NO hay inyección de timings/DTDs custom — el
mode-lock solo filtra VICs estándar. Implicación: el full-width 1080p120
no es alcanzable por la vía vendor-config. Pendiente: disparar y verificar
el mode-lock plantado ([1FE0]=1, VIC 16=1080p60).

## 15. Parches — genealogía completa

| Nombre | Bytes | Sitio | Efecto | Estado |
|---|---|---|---|---|
| jmp120 | 1 (50→80) | 0x3569 | mata ÷2 del hot-switch | **EN USO** (backup/MS2131_jmp120.bin) |
| full120/EDID | tabla | 0x2BE5+ | sin efecto (el ÷2 es por pclk medido) | histórico |
| native_wrapper/caves v4-v7 | varios | 0xBF56+, cue 0xF500 | bricks (AJMP 0xBF5B colas compartidas) | muertos — la lección de las colas |
| reclean v3 | 14B | 0x582B | latch leía fallback del formato | revertido |
| applier v9-v11 | 20-28B cueva | 0x356B+0xBF45 | f606/f660←entrada; **bug de endianness LE descubierto** (0x8007=32775) | revertido (sin daño, innecesario) |
| tailhook v7/v8 | cueva+ljmp | 0xBC61 | cola del walk; registros equivocados | revertido |
| noclass v12 | 1 (40→80) | 0x93D4 | matar flag 0x20.1 (era general) | revertido |
| **no720 / no720v2** | descriptores+tabla | UVC 0x409/0x5e8 + tabla 0x178/0x1a8/0x1d4/0x200 → 1920x1080 | saca 1280x720 del menú UVC → Discord streamea 1080p60 full-width → **CRASH A ROM** (§11) | revertido — el experimento que encontró el muro real |

---

# PARTE IV — OPERACIÓN Y ECOSISTEMA

## 16. Recetas operativas y doctrina

- **DOCTRINA (24/10, vigente)**: jmp120 + boot natural + `setformat` ante
  drops de formato. **PROHIBIDO escribir registros del scaler en caliente**
  (degrada trajectorialmente, §12). El "fix en caliente"
  (f600=0 → anchos 1920 → f65c=0x10 → f600=1) es **historical only** —
  degradaba el pipeline de esta unidad.
- Restaurar natural (si algo quedó raro): anchos 960 + f65c=f65e=0x08 —
  o mejor: **replug** (única restauración completa de trayectoria).
- Rescate brick/caída a ROM: si la ROM no enumera sola, puente
  CS(1)↔VCC(8) del SPI U6 → `tools/rom_flash <img>` (if#4, erase chip
  completo + write + verify). Probado ~6 veces, recovery de ~2 minutos.
  Detalle completo en `RESCATE_ROM.md`.
- Detección estandarizada: `tools/ms213x_estado.py` (por VID:PID, nunca por
  nombres — tres lecciones de grep pagadas).
- Episodios de caída espontánea (18-21/10): el tratamiento que curó el
  hardware fue **descanso prolongado sin energía** (48h USB+HDMI fuera).

## 17. Ecosistema de herramientas

| Herramienta | Rol |
|---|---|
| `tools/ms213x_estado.py` | detección por VID:PID (ROM=534d:2130, firmware=345f:2131) |
| `tools/ms2131_setformat` | negociación UVC de formato (el camino SEGURO de cure) |
| `tools/ms2131_formatguard.py` | guard v2: detección HID pura (byte ALTO BE), watchdog 15s, backoff progresivo anti-guerra con Discord |
| `cl.fcaraneda.ms2131formatguard` | LaunchAgent Mac del guard (activo) |
| `ms2131-formatguard.service` | systemd user en la Deck (instalado; la Deck ya no usa la capturadora) |
| `tools/ms213x_flash` | flasheo normal (libusb) |
| `tools/rom_flash` | flasheo por ROM if#4 (rescate) |
| `tools/ms213x_xdata` | lectura/escritura XDATA por HID |
| `tools/ms213x_trap`, `ms213x_forense`, `ms213x_watchpid` | forense en vivo (dump 4B por GET) |
| `fw_re/decomp/` | 1034 funciones decompiladas a C + INDEX.txt |

Nota Disciplina: Discord streamea la capturadora a **1280x720 por defecto**
(su cámara-default en Electron, igual en Mac y Deck); el formatguard lo
barre con backoff cuando Discord se va.

## 18. Historial de daño y límites de esta unidad

- **18/10**: escritura experimental de f601 (readback prohibido) → cascada:
  crash-on-HDMI a 1080p120, HID muerto. El daño es específico del
  procesado de 120Hz (a 1080p60 el dispositivo VIVE — probado con el
  ORIGINAL de fábrica).
- **19-21/10**: 48h sin energía → curación completa (boot firme, HID de
  vuelta, 120Hz estable de nuevo). Diagnóstico: componentes marginales
  que se recuperan tras descarga completa. **Corrección 27/10-noche**: el
  LaunchAgent saboteador (§18.1) existía desde el 16/10 22:28 — parte de
  esa semana pudo ser sabotaje en vez de (o sumado a) marginalidad.
- **Límites permanentes del post-daño**: el camino de entrada ya no tiene
  margen para full-width@120 (tearing) — y el experimento no720 mostró que
  la conversión full-width sostenida entrada-120→salida-60 tumba el
  firmware entero (ROM). Ninguna variante de config lo evade (§11).
- El WEDGE (dropout total del bus USB, ni ROM enumera; powered, D+/D−
  mudos) es flash-independiente: ocurrió con jmp120 verificado (18:39) y
  con flat2 (21:00, 21:03). Recuperación: replug (a veces con pausa).
  Esto ES marginalidad real de la unidad.
- Esta unidad es marginal: ante episodios raros, primero descartar
  sabotaje externo (§18.1), después descanso sin energía, después
  sospechar firmware.

### 18.1. EL SABOTEADOR (27/10-noche) — la gran corrección del relato

LaunchAgent `cl.fcaraneda.ms2131watcher` (plist del 16/10 22:28, noche de
rescates) corría `tools/ms213x_watchpid2`: poll cada 20ms, y al ver
cualquier firmware 345f:* hacía `execl(ms213x_flash -w MS2131_native_wrapper.bin -n)`.

- **112 CARRERA GANADA** en su log (`/tmp/ms2131_watch2.log`): cada
  arranque de firmware era flasheado con native_wrapper por la espalda.
- Clave que lo hizo invisible: **el firmware ejecuta desde RAM** (la mask
  ROM copia la imagen al boot) → el flasheo en caliente no mata la
  sesión → todo "funciona" hasta el próximo reboot, que encuentra
  native_wrapper (o truncado si el write se interrumpió → checksum
  ffff → la ROM se niega → "no arranca NINGÚN firmware").
- Explicó: las "3 caídas espontáneas" del 27/10, la flash truncada en
  pag 135 (write interrumpido), los "no-arranca pese a VERIFY OK"
  (re-truncaba DESPUÉS de cada verify de rom_flash).
- **Neutralizado**: `launchctl bootout` + pkill + plist movido a
  `~/Library/LaunchAgents/disabled/` (reversible). Barrida: sin cron, sin
  otros agentes ms2131 (solo formatguard, legítimo).
- Lección: `ms213x_watchpid2` fue un arnés de carrera del 16/10 que
  nadie apagó. Toda herramienta automática que toca la flash debe vivir
  con fecha de caducidad visible.

---

# PARTE V — ESTADO ACTUAL Y CAZA DEL CRASH

## 19. Los dos bugs abiertos (A y B) — separados por el usuario (27/10)

**"Son dos cosas distintas"** — la muerte del audio con doble cliente NO es
la caída del firmware:

| Bug | Síntoma | El dispositivo | Estado |
|---|---|---|---|
| **A: audio dual-cliente** | el monitoreo de scalapp muere cuando Discord también captura | **sigue vivo** | pendiente — plan: scalapp toma el audio y hace play con delay deliberado (colchón) para coexistir con el stream de Discord; falta resiliencia del stream de entrada (watchdog + `--delay-ms`) |
| **B: crash del firmware a ROM** | caída del dispositivo entero mid-stream | **muere → ROM** | disparador identificado (carga full-width entrada-120, §11); mecanismo interno en caza (§20) |

Contexto scalapp (proyecto aparte, `~/projects/utility_projects/scalapp`):
audio-only validado ("super bien"), fixes de deriva/electrocución/tasa
aplicados; `--virtual-out` (BlackHole) implementado y opcional — NO es el
plan del usuario (scalapp es SOLO para escuchar él; Discord captura la
capturadora directo).

## 20. Análisis de stack (la caza del crash, 27/10) — MECANISMO CERRADO

**Modelo verificado**: SP=0x4B al boot (§3) y **el firmware NUNCA lo reubica**
(el único `mov SP,#imm` del código entero está en el boot @0xA4F1 —
verificado por grep sobre el disasm completo). IRAM hasta 0x7F →
**presupuesto fijo: 52 bytes, siempre**. En 8051 el push con SP=0x7F
envuelve a 0x00 → **el desborde pisa primero los bancos de registros
(IRAM 0x00-0x1F) = corrupción instantánea** → el chip cuelga → el host
resetea → la ROM sostiene el bus ("caída a ROM" = bug B §19).

### 20.1 Medición max-live por cadena (secuencial push/pop neteado)

La primera pasada (27/10 mañana) contaba TODOS los pushes del cuerpo —
sobre-estimaba (pushes de ramas distintas no coexisten). La medición
refinada camina el cuerpo en orden de dirección con contador push/pop:

```
EXT0/USB  = 55B ⚠️ (+3 sobre el techo)
   d595:15 bad9:2 bd87:3 7489:2 e63a:2 e1ff:2 afe7:2 0016:2 0121:3
   2402:6 b590:2 d468:2 d1f6:2 d953:2 cd0b:2 a32a:2 be45:2 ead0:2
TIMER0    = 52B ✅ EXACTO (0 margen)
   c4ec:8 d1f6:2 9a8b:4 ecba:2 d953:2 cd0b:2 a32a:2 aa23:2 c126:2
   4aef:4 e38a:4 df0b:2 a89c:6 b225:2 e971:2 e987:2 e16c:2 0e44:2
EXT1      = 63B ⚠️ (+11)
   b3e0:15 d1f6:2 d953:2 cd0b:2 a32a:2 be45:2 c4ec:8 aa23:2 c126:2
   4aef:4 e38a:4 df0b:2 a89c:6 b225:2 e971:2 e987:2 e16c:2 0e44:2
TIMER1    = 63B ⚠️ (+11)
   60c3:12 ed2e:2 d953:2 cd0b:2 a32a:2 be45:2 c4ec:8 d1f6:2 9a8b:4
   c496:2 c126:2 4aef:4 e38a:4 df0b:2 a89c:6 ce7b:3 53e2:2 1253:2
MAIN      = 52B ✅ EXACTO (0 margen)
   4f20:2 eae4:2 d7d6:3 e63a:2 e1ff:2 afe7:2 0016:2 0121:3 2402:6
   b590:2 d468:2 d1f6:2 d953:2 cd0b:2 a32a:2 be45:2 c4ec:8 e4a9:2
   bea3:2 ee94:2
MAIN→3438 = 11B ✅ (4f20 → 1b67 → 63c9 → 3438)
```

(*) el vector aterriza a mitad del rango sembrado (c5ed/c4ec, b44d/b3e0,
624f/60c3): verificado que los prólogos de pushes empiezan EXACTAMENTE en
el landing (d595/c5ed/b44d/624f) — la medición es válida para el camino
de interrupción.

### 20.2 Lectura del resultado — el diseño al límite exacto

1. **TIMER0 y MAIN calzan EXACTO en 52B** — el compilador/firmware está
   diseñado (o ajustado por evolución) al byte exacto del presupuesto.
   Cualquier interrupción que llegue con el main en su punto más profundo
   desborda garantizado.
2. **EXT1 y TIMER1 desbordan por 11B en su camino más profundo**; EXT0 por
   3B. El firmware sobrevive porque las ramas profundas no se ejecutan
   siempre — **bajo carga (tormenta de interrupciones del streaming) las
   ramas profundas corren y el overflow llega**.
3. **0x3438 es INOCENTE**: sus "25B" eran pushes de ramas distintas
   (max-live real = 5B). El candidato de la primera pasada era un falso
   positivo por conteo total.
4. **La cola compartida** `d953 → cd0b → a32a → be45 → c4ec → ...`
   (motor de propiedades + helpers) aparece en TODAS las cadenas y en el
   main — es el punto común donde cortar frames libera presupuesto de
   todos los frentes a la vez.
5. **Dato clave**: la cadena EXT0 incluye el trampoline 0x0016 → escritor
   universal 0xE279 — el ISR del USB escribe registros del scaler en su
   camino más profundo. Bajo streameo full-width ese camino corre a
   máxima frecuencia (coherente con el disparador del bug B, §11).
6. sub_63C9 (caller único de 3438) = **máquina de estados de eventos del
   receptor HDMI** (estados en [268B], countdown [2002], llama escritores
   f6xx 0xE9xx-0xEE01 y `sub_c6eb(0xf0,0x22,...)` = escritura a f0xx RX).
   sub_1B67 = el dispatcher principal del loop de main.

Caveats: escaneo secuencial aún sobre-estima un poco (mezcla ramas); el
modelo es estático — la anidación (main profundo + ISR) multiplica el
exceso. La conclusión estructural no cambia.

### 20.3 flat1/flat2/bisect — post-mortem empírico (27/10-noche, REVISED 21:40)

Bisect limpio (agente muerto, flash verificada por ronda) + scanner de
aterrizajes corregido (bug: capturaba el primer hex del operando, no el
target — el chequeo original de flat1 tenia el mismo vicio):

| Sitio | Saltos que aterrizan en el sitio (+0..+3) | Veredicto |
|---|---|---|
| 0x8758 | 0 | VALIDO |
| 0x9bd1 | 0 | VALIDO |
| 0xa898 | **5** (jnz a823, a82b; jz a887; cjne a88c, a895 -> todos al ret a89b) | **MINA: wedge** |
| 0xdab7 | 0 | VALIDO |
| 0xe655 | 0 | VALIDO |
| 0xe6d1 | **1** (cjne e6ce -> ret e6d4) | **MINA: rompe boot** |

- **e6d1 (boot-breaker)**: el cjne del dispatch de estados XDATA
  0x1193-0x1195 salta al `ret` para saltarse el lcall; convertido, aterriza
  en el `nop` y cae al `mov dptr,#0x1193` siguiente = **re-loop infinito
  del dispatch** al boot -> ROM estacionado. Explica flat1 completo.
- **a898 (wedge-trigger)**: 5 paths frios aterrizan en el ret; convertido,
  caen en `lcall 0xbb3c` (la funcion siguiente) y ejecutan caos ->
  dropout del bus (wedge). Correlacion de la noche: **5/5 muertes
  espontaneas tenian a898 convertido; 4/4 boots sin a898 sobrevivieron**
  (jmp120 95 min; bisectB/C hasta replug manual). La "tormenta de wedges
  marginal" era la mina disparandose.
- **flat3 = jmp120 + {8758, 9bd1, dab7, e655}** (los 4 limpios):
  TIMER1 54B, EXT1 86B, EXT0 119B. Checksum 4464.
  Construccion: `analysis/patch_bisect.py backup/x.bin 8758 9bd1 dab7 e655`.
- Regla NUEVA para parches tail-call: escanear aterrizajes con target
  ULTIMO-operando (cjne/djne/jz/etc), sitio+0..+3, y mirar el codigo
  siguiente (+4..+8) para estimar dano de fall-through.
- Archivos: `backup/MS2131_bisectA|B|C.bin`, `flat2.bin`, `flat3.bin`,
  `analysis/patch_bisect.py`.


