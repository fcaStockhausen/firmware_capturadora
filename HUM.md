# HUM — Investigación del tono de 60 Hz en el audio (interno al chip)

> Sesión 29/10 noche. Síntoma: con video streameando, un tono puro
> ~60 Hz + armónicos (120/180) + subarmónico ~30 Hz aparece EN LOS
> DATOS capturados (digital, pre-playback). +7 dB sobre el nivel
> audio-only. Medido desde scalapp (`SCALAPP_REC`, FFT 0.09 Hz res).
> Mitigación actual: `scalapp --notch-hum` (quirúrgico, Q=25).

## 1. Caracterización medida (entrada 1920x1080 @ 120 Hz, USB3)

| Modo UVC | Tono ~60 Hz | Rumor 26-30 Hz | RMS total |
|---|---|---|---|
| 1080p60 | **−29.2 dBFS** | −52 dBFS | −33.2 |
| 720p60 | **−39.7 dBFS** | −47 dBFS | −37.8 |
| (sin UVC) | −68 dBFS (no existe) | −52 dBFS | −40.9 |

Conclusiones firmes:

1. **El tono es binario con el stream UVC** (sin cliente de video no
   hay tono; el receptor HDMI sigue corriendo → no es el RX).
2. **La amplitud escala con el tamaño/procesamiento de salida**
   (1080p vs 720p = +10.5 dB ≈ proporcional a píxeles).
3. **La frecuencia es la cadencia del UVC de SALIDA (~60 Hz), no la
   del input (120 Hz)** — el acople sigue a la paquetización/proceso
   por frame de salida, no al trabajo del RX en tiempo real.
4. El rumor 26-30 Hz es piso CONSTANTE del chip (independiente de
   carga) — fenómeno separado, quieto a −52 dBFS.

Modelo de trabajo: **corriente dinámica del bloque scaler/memoria/
USB3 (ráfagas por frame de salida) acoplándose a un tramo del path
de audio** (rail/tierra en el die). Un tono SINE puro en samples =
voltaje analógico sumado antes de la digitalización → el path de
audio tiene un tramo analógico interno (DAC→ADC loop o referencia
del ADC). Firmware probablemente NO puede eliminarlo; solo
reducirlo (cambiar timing de ráfagas — profundo) o notch digital.

## 2. Descubrimiento lateral CRÍTICO: la entrada está a 120 Hz

`[22B8]=1920x1080 [22BE:BF]=12001` → el source corre 1080p120, y con
el formatguard v3 pausado (scalapp activo) el capturador quedó en
estado **diezmado** (`f606/f660=960`, `f65c=0x08`, verificado con
`ms2131_fix120 status`). El video que entrega scalapp en esa
condición es 960 estirado a 1920 (blando).

**CORRECCIÓN (post-veredicto del usuario)**: el apply durante stream a
120Hz de entrada **NO funcionó**: la imagen se distorsionó (exactamente
el modo de fallo documentado en RE.md: f65c=0x10 contra la batería
f620-f651 de medio ancho a 120Hz puro = ruido/estirado) y el path de
audio quedó wedeado (silencio digital; revert de registros NO lo
revivió — requiere replug). La verificación de "0 INPUT GAPs" midió
el transporte, no la imagen ni el audio: error metodológico.

**Sobre validado del fix120 apply**: SOLO en eventos hot-switch (la
era de validación del daemon). A 120Hz de entrada de pie, el
medio-ancho es política POR MURO FÍSICO (entrada full-width a 120Hz =
zona prohibida, BITACORA 27/10). El diseño "v4 aplica el fix al
arranque del cliente" queda ANULADO.

**Recomendación para monitoreo nítido**: fuente a 1080p60 — a 60Hz de
entrada el chip entrega 1920 full-width natural ("60Hz: perfecto sin
nada", RE.md).

## 3. Caza de registros del bloque de audio (diff XDATA idle vs stream)

Dump 0x2200-0x2300, 0xf600-0xf700, 0xf700-0xf800, 0xf800-0xf900:

- `0xf7xx`: **idéntico** idle vs stream — bloque muerto o no usado.
- `0xf8xx`: **31 registros 0→nonzero al streamear** — es el bloque
  de config del payload UVC (contiene la geometría 1920x1080 en
  f822:25 y f824). VIDEO, no audio.
- `0x22xx`: cambios conocidos (formato, estado).
- `0xf6xx`: scaler (mapa conocido).
- **No apareció ningún bloque de registros de audio** en los rangos
  escaneados. El UAC probablemente vive en silicio dedicado (o en
  rangos no escaneados: 0x2xxx-0x21xx, 0x23xx-0xefff, 0xf9xx+).

## 4. Comunidad

- MS2109 (hermano USB2): parche comunitario del descriptor UAC
  (mono/96k → stereo/48k) — el lado audio ES parcheable por
  firmware en la familia (A-Dunstan/ms2109_stereo_patch).
- BertoldVdb/ms-tools: herramental de registros para MS210x —
  revisar su mapa por registros de audio/ganancia aplicables al
  2131.
- eevblog teardown MS2131: pendiente de revisar.

## 5. Pendientes / casuística siguiente

- [ ] **Resolver el silencio actual**: el path de audio entrega
  ceros con video vivo (¿source muteado o wedge por la tormenta de
  dumps HID?). Replug = cura histórica.
- [ ] Medir hum con captura 960 vs 1920 (mismo output 1080p60) —
  el experimento quedó a medias por el silencio. Separa carga de
  captura vs paquetización.
- [ ] Barrido de rangos XDATA no escaneados buscando regs de audio
  (por regiones, con cuidado de no wedgear — esta sesión sugiere
  que ~1500 reads seguidos pueden ser demasiado).
- [ ] Revisar ms-tools (BertoldVdb) por mapa de audio MS210x.
- [ ] Si el mecanismo es rail/analógico (lo más probable): las
  opciones son notch host-side (ya hecho) o parche de timing de
  ráfagas (deep RE, no garantizado).

## 6. Archivos de la sesión

- `/tmp/hum_1080p60.f32`, `/tmp/hum_720p60.f32`, `/tmp/hum_aonly.f32`
  — caracterización por modo
- `/tmp/xd_{idle,str}_{22xx,f6xx,f7xx,f8xx}.bin` — diffs XDATA
- `/tmp/hum_fix.f32` — experimento fix120 (salió silencio, ver §5)
