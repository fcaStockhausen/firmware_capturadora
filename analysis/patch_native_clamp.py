#!/usr/bin/env python3
"""Patch nativo v3: fuerza ancho de captura = hactive en el clamp 0x5711-0x5723.

Cadena demostrada: f606 = [0x1AEA] = min([0x1AE2], hactive[0x1AE6]) y a 120Hz
[0x1AE2]=960 al momento de la config => captura diezmada /2.

El clamp (8051):
  5711: DPTR=0x1AE2
  5714: LCALL 0x31FD          ; R4:R5 = [0x1AE2]
  5717: CLR C / SUBB A,R7 / MOV A,R4 / SUBB A,R6
  571B: JNC 0x5723            ; [0x1AE2] >= hactive -> conservar hactive
  571D: R6=R4 / R7=R5         ; sino usar [0x1AE2]
  5723: [0x1AEA] = R6:R7

Parche: JNC (0x50) -> SJMP (0x80) => SIEMPRE conserva hactive.
El override posterior (0x5733: si [0x268C]=format_w < width -> width=[0x1AE2])
sigue activo y capa el 4K30 (hactive 3840 -> [0x1AE2]=1920).

Flash offset = 8051 addr + 0x30 = 0x574B.
"""
SRC = 'backup/MS2131_2025-04-09_backup_2617_44fc.bin'
OUT = 'backup/MS2131_native_clamp.bin'
HEADER_LEN = 0x30
OFF = 0x571B + 0x30   # 0x574B

fw = bytearray(open(SRC, 'rb').read())
assert fw[OFF] == 0x50, f'byte inesperado en flash+0x{OFF:04x}: {fw[OFF]:02x} (esperaba 0x50=JNC)'
fw[OFF] = 0x80

code_len = (fw[0x02] << 8) | fw[0x03]
cs_off = HEADER_LEN + code_len + 2
new_cs = sum(fw[HEADER_LEN:HEADER_LEN + code_len]) & 0xffff
fw[cs_off] = new_cs >> 8
fw[cs_off + 1] = new_cs & 0xff

open(OUT, 'wb').write(fw)
print(f'flash+0x{OFF:04x}: 0x50 -> 0x80 (JNC -> SJMP 0x5723)')
print(f'checksum codigo -> {new_cs:04x}')
print(f'imagen: {OUT}')
