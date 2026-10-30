#!/usr/bin/env python3
"""Parche v11 "applier3": correccion CRITICA de endianness en la cueva.

BUG historico de v9/v10: los pares de registros del scaler son LITTLE-ENDIAN
(f606=lo, f607=hi — el fix120 escribe f606=0x80,f607=0x07 para 1920).
La cueva v9/v10 preparaba {A=hi, r6=lo} para el write original
([F660]=A, [F661]=r6) => escribia f660=0x07,f661=0x80 = LE 0x8007 = 32775.
Toda la progresion de blur raro de esta noche fue eso.

v11: r6=hi, r7=lo desde [22B8:BB]; escribir f606/f607 y f660/f661 en LE
(lo primero, hi despues); dejar A=r7=lo (r6 ya es hi) para el write original.
"""
SRC = 'backup/MS2131_applier2.bin'
OUT = 'backup/MS2131_applier3.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

CAVE = 0x356B

CAVE_V10 = bytes.fromhex(
    '9022b8' + 'e0fe' + 'a3e0' + 'ff' +
    '90f606' + 'eef0' + 'a3' + 'eff0' +
    '90f660' + 'eef0' + 'a3' + 'eff0' +
    'ee' + 'cf' + 'ce' + '22'
)
CAVE_V11 = bytes.fromhex(
    '9022b8' + 'e0fe' + 'a3e0' + 'ff' +    # r6=[22B8]=hi, r7=[22B9]=lo
    '90f606' + 'eff0' + 'a3' + 'eef0' +    # [F606]=r7(lo), [F607]=r6(hi)  <- LE!
    '90f660' + 'eff0' + 'a3' + 'eef0' +    # [F660]=r7(lo), [F661]=r6(hi)  <- LE!
    'ef' + '22'                             # A=r7=lo (r6 queda=hi), ret
)
assert len(CAVE_V11) == 26, f'cueva {len(CAVE_V11)}B'
assert len(CAVE_V10) == 28

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4
cc = CAVE + HEADER_LEN
assert bytes(fw[cc:cc+28]) == CAVE_V10, 'cueva no es v10'

fw[cc:cc+42] = b'\x00' * 42
fw[cc:cc+len(CAVE_V11)] = CAVE_V11

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff
assert len(fw) == HEADER_LEN + CODE_LEN + 4

open(OUT, 'wb').write(fw)
print(f'cueva 0x{CAVE:04X}: writes LE + {chr(123)}A=lo,r6=hi{chr(125)} ({len(CAVE_V11)}B)')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
