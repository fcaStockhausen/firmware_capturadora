#!/usr/bin/env python3
"""Genera patron de calibracion 1920x1080 para caracterizar la distorsion
de la MS2131. Geometria conocida => medir escala H/V, crop y perdida de
resolucion es trivial desde los frames capturados."""
import numpy as np
from PIL import Image, ImageDraw

W, H = 1920, 1080
img = np.zeros((H, W), dtype=np.uint8)

# --- 1) grilla gruesa cada 120 px (lineas de 2px) + fina cada 30 px (1px) ---
img[:, ::30] = 60          # fina
img[::30, :] = 60
img[:, ::120] = 255        # gruesa
img[::120, :] = 255
img[:, 1::120] = 255       # doble linea gruesa => origen inequivoco
img[1::120, :] = 255

# --- 2) reglas codificadas: en el borde superior, bloques que codifican
#        la posicion en binario (permite detectar crop exacto) ---
for i, x in enumerate(range(0, W, 120)):
    v = i
    for b in range(6):
        if v & (1 << b):
            img[8 + 12*b: 8 + 12*b + 8, x+4: x+10] = 255
for i, y in enumerate(range(0, H, 120)):
    v = i
    for b in range(6):
        if v & (1 << b):
            img[y+4: y+10, 8 + 12*b: 8 + 12*b + 8] = 255

# --- 3) bandas multiburst: periodos 16,8,4,2,1 px en franjas verticales ---
#        region central-superior, filas 150..420
y0, y1 = 150, 420
for cx, per in [(200, 16), (500, 8), (800, 4), (1100, 2), (1400, 1)]:
    wband = 200 if per < 16 else 240
    xs = np.arange(wband)
    stripe = ((xs // max(1, per // 2)) % 2) * 255
    img[y0:y1, cx:cx+wband] = stripe[None, :]

# --- 4) multiburst vertical: mismas frecuencias, franjas horizontales ---
#        columnas izq, region x 120..500
x0, x1 = 120, 500
for cy, per in [(560, 16), (650, 8), (740, 4), (830, 2), (920, 1)]:
    ys = np.arange(64)
    stripe = ((ys // max(1, per // 2)) % 2) * 255
    img[cy:cy+64, x0:x1] = stripe[:, None]

# --- 5) cruces diagonales para detectar shear/keystone ---
yy, xx = np.mgrid[0:H, 0:W]
for off in range(0, W + H, 240):
    m = ((xx - yy == off) | (xx - yy == off + 1) |
         (xx + yy == W - off) | (xx + yy == W - off - 1))
    img[m] = np.maximum(img[m], 180)

# --- 6) mira central ---
cy, cx = H // 2, W // 2
img[cy-40:cy+40, cx:cx+2] = 255
img[cy:cy+2, cx-40:cx+40] = 255
r = 60, 120, 180
for rr in r:
    yy, xx = np.mgrid[cy-200:cy+200, cx-200:cx+200]
    m = (xx-cx)**2 + (yy-cy)**2
    img[cy-200:cy+200, cx-200:cx+200][np.abs(np.sqrt(m) - rr) < 1] = 255

out = Image.fromarray(img)
out.save('patron_calibracion_1920x1080.png')
print('patron generado: patron_calibracion_1920x1080.png')
