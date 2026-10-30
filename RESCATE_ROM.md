# Rescate MS2131 — bitácora completa de la sesión 2026-10-15/16

> **EPÍLOGO (17/10 01:55)**: el rescate terminó en fix nativo de 1 byte.
> Resumen completo de la cadena entera en `fw_re/RE.md` y el encabezado del
> `README.md`. Timeline de esta bitácora:
>
> 1. Puente CS↔VCC → modo ROM reproducible (sección de abajo)
> 2. ROM "sorda" en if#0 (probado exhaustivamente) → panorama desesperanzador
> 3. **Giro**: descriptor leak reveló config de 5 interfaces en USB3
> 4. Transfers crudos `wIndex=4` → protocolo de fábrica VIVO en if#4 oculta
> 5. Bug de framing (len big-endian `01 00`) → lectura byte-perfecta
> 6. `tools/rom_flash` → wrapper flasheado y verificado por la ROM
> 7. Wrapper: passthrough por bug de endianness + no-frames por overflow de
>    stack (4 pushes, margen <5) → postmortem en `fw_re/RE.md`
> 8. RE completo del firmware → ÷2 en 0x356F dispara en hot-switch con stream
> 9. **Parche final 1 byte** (`MS2131_jmp120.bin`): verificado por protocolo,
>    registro y análisis de columnas al píxel

## Estado de la tarjeta

Flash sigue con `MS2131_testB_identity.bin` (muerte de boot determinística, 0/25+ replugs
incluyendo 2 días de reposo). El chip NO está perdido: la flash es accesible físicamente.

## HAZLO ASÍ: entrar en modo ROM (VERIFICADO — reseteable a voluntad)

> Técnica dominada por el usuario (2026-10-16): la entrada a ROM es reproducible
> y rápida; ventanas estables de ~100 s, repetibles indefinidamente. El bypass
> HDMI al monitor FUNCIONA en modo ROM (el camino de vídeo va por hardware
> dedicado MS7126/27, independiente del 8051) — la tarjeta sigue siendo útil
> como passthrough mientras tanto.

1. Abrir carcasa. SPI = **U6, Puya P25Q40SH, SOP-8** (cuadrante sup-izq, entre HDMI OUT
   y MS2131). Pin 1 = pata inferior del lado IZQUIERDO (punto moldeado en esquina
   inferior-izquierda). Pin 8 (VCC) = pata inferior del lado DERECHO.
   **El puente CS(1)↔VCC(8) son las DOS patas del borde inferior, enfrentadas (~4-5 mm).**
2. Puentear 1↔8 con cable fino MIENTRAS se conecta el USB
3. Contar 2-3 s (la ROM arranca, no puede leer firmware → queda en ROM y enumera)
4. QUITAR el puente (la tarjeta SIGUE en modo ROM — persiste mientras no se repita boot)
5. Aparece como `534d:2130`, producto "USB Video", serial "20201228", 1 config,
   1 interfaz HID (if#0, clase 3.00), 1 EP IN, usage ff00:0001

⚠️ NO desconectar/reconectar sin puente: lee testB → boot → muerte determinística.

## Descubrimiento CRÍTICO: la ROM del MS2131 es SORDA

Probado de forma exhaustiva (ver tools/rom_probe*.c):

| Prueba | Resultado |
|---|---|
| hidapi feature reports, IDs 0x00/0x01, longitudes 2-66 | ❌ `IOHIDDeviceSetReport 0xE0005000` |
| libusb SET_REPORT directo EP0 (bypass capa HID macOS), tipo FEATURE (3) y OUTPUT (2), IDs 0-3,0x10,0x11, len 8/9 | ❌ STALL (LIBUSB_ERROR_PIPE) |
| GET_REPORT cualquier tipo/ID | devuelve SIEMPRE `06 00 ff 09 01 a1 01 15` (eco del descriptor HID — handler roto) |
| Vendor OUT (0x40) bRequest 0x00-0x3F, 8 bytes | ✅ ACK silencioso (r=8) — sin protocolo detrás |
| **Test marcador DEADBEEF** (probe7): vendor OUT marcado → GET buffer antes/después | **buffer idéntico — los vendor OUT aterrizan en NINGUNA parte** (ACK por defecto del stack, sin handler) |
| Vendor IN (0xC0) bRequest 0x00-0x3F | mismo eco del descriptor |
| claim if#0 para interrupt EP | ❌ LIBUSB_ERROR_ACCESS (driver HID macOS) |

**Nota sobre el "eco del descriptor":** no es un eco — es RAM sin inicializar
que el handler IN (tampoco existe de verdad) devuelve tal cual. Cambia entre
resets (`06 00 ff 09...` → `32 00 00 01...`) y NO reacciona a inyecciones.

**Conclusiones:**
- La mask ROM del MS2131 NO implementa el loader HID (a diferencia de la familia
  MS210x cuya ROM sí da acceso XDATA/EEPROM — ver BertoldVdb/ms-tools).
- El soporte "MS213x-ROM" de steve-m/ms213x_flash (534d:2130, hid_if=4) es teórico:
  esta ROM tiene 1 sola interfaz (if#0) y sin handlers. Además su ruta hidapi
  non-Windows usa el primer byte del comando como report ID (bug de framing).
- El descriptor HID declara UN feature report de 8 bytes SIN report ID
  (`0600ff0901a101150026ff001901290275089508b102c0`).

## Tool OEM reversado (MS21XX&91XXDownloadTool 1.7.0 BUILD 20221024)

Descargado del MEGA enlazado en Forest178/ms21xx-firmware-research (MS2130烧录软件.zip).
MFC nativo, usa HidD_SetFeature/GetFeature + SetupDi. El disasm (r2) del caller en
VA 0x409940 muestra el framing:

```
buffer = {0x00, 0xb6, 0x0b, 0x02, ...}  ; report ID 0x00 + comando XDATA-write
HidD_SetFeature(handle, buf, 9)          ; 9 bytes = ID + 8 payload
```

= MISMO protocolo que ms-tools (out[0]=0, out[1]=cmd, len 9). El tool OEM solo
habla con el firmware corriendo (345f:*). NO existe tool público para flashear
la ROM sorda del MS2131.

## Protocolo de flasheo del firmware (para cuando arranque) — CONFIRMADO por 3 fuentes

- ms-tools mshal (hal_flash.go), steve-m ms213x_flash, UltraSemi web tool y el OEM exe:
  - framing: feature report 9 bytes = reportID 0x00 + {cmd, args...} (8 bytes)
  - `b6 addr_hi addr_lo val` — XDATA write; `b5 ...` XDATA read
  - `c5 sfr` / `c6 sfr val` — SFR read/write (P2=0xa0, P3=0xb0)
  - setup SPI: XDATA f01f=00, P3: |=0x20 &=~0x1c, P2: |=0x1c, XDATA f01f=10
  - `f7 01 aaaaaa bbbb` read flash→buffer, `f7 00 ... offset` buffer→host (8 bytes)
  - `f8 01 aaaaaa bbbb` setup write, `f8 00 + 6 bytes` buffer fill (256/page)
  - `fe` — erase completa
- UltraSemi web (UsbVideoDownloadTool.DTzpyuM8.js): prueban report ID 0 primero
  y 1 de fallback (probeFeatureReport); respuesta puede venir con o sin byte de ID.

## ÚNICA VÍA RESTANTE para escribir la flash

~~Acceso físico al SPI con un controlador externo~~ **OBSOLETO (misma noche)**:
descubrimos que la ROM en USB3 sirve internamente 5 interfaces — incluida la
**interfaz HID 4 de fábrica** — que macOS no instancia pero que responde a
control transfers crudos con `wIndex=4`. `tools/rom_flash` flashea por ahí.
Ver "Emergencia" en `fw_re/RE.md`.

## Vigía permanente (LaunchAgent)

`~/Library/LaunchAgents/cl.fcaraneda.ms2131watcher.plist` — corre desde el login
(KeepAlive, sobrevive reinicios). Comportamiento: `345f:*` → flashea wrapper
automáticamente (carrera ganada); `534d:2130` → solo log con timestamp.
Log: `/tmp/ms2131_watch2.log`. Desactivar:
`launchctl bootout gui/$(id -u)/cl.fcaraneda.ms2131watcher`

## Herramientas creadas esta sesión

- `tools/ms213x_watchpid2(.c)` — vigía: 345f:* → flashea wrapper; 534d:2130 → log.
  Compilar: `cc -O2 -I/opt/homebrew/include -L/opt/homebrew/lib -o ms213x_watchpid2 ms213x_watchpid2.c -lusb-1.0`
  Supervisor: `nohup sh -c 'while true; do <ruta>/ms213x_watchpid2 2>&1; sleep 1; done' >> /tmp/ms2131_watch2.log 2>&1 &`
  (ojo: nombres de proceso >15 chars se truncan — `pgrep -x` falla, usar `ps axo comm`)
- `tools/rom_probe.c` … `rom_probe6.c` — sondas del protocolo ROM (evidencia)
- Fotos de placa: IMG_6324/6326.heic (Downloads, 13/10) — U6 identificado por vision agent
