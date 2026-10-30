#!/usr/bin/env python3
"""Parche no720 v2 — la tabla de modos (fuente runtime del menú UVC).

v1 parcheó los descriptores estáticos (0x409/0x5e8) pero el 720p siguió en
el menú: el firmware CONSTRUYE los descriptores en runtime desde la tabla
de modos (filas A/B/C/D). v2 parchea las 4 entradas 1280x720 de la tabla
(0500 02d0 BE) -> 1920x1080 (0780 0438). El timing de 720p (0x2c7c) queda
huérfano sin referencia (inofensivo).
"""
SRC = 'backup/MS2131_no720.bin'
OUT = 'backup/MS2131_no720v2.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

TABLE_HITS = [0x178, 0x1A8, 0x1D4, 0x200]   # entradas 1280x720 (BE) en filas A-D
ORIG = bytes.fromhex('050002d0')
NEW = bytes.fromhex('07800438')

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4

for off in TABLE_HITS:
    cur = bytes(fw[off:off + 4])
    assert cur == ORIG, f'0x{off:03x}: esperaba {ORIG.hex()}, hay {cur.hex()}'
    fw[off:off + 4] = NEW
    print(f'flash 0x{off:03x}: {ORIG.hex()} -> {NEW.hex()}  (tabla: 1280x720 -> 1920x1080)')

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff
assert len(fw) == HEADER_LEN + CODE_LEN + 4

open(OUT, 'wb').write(fw)
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
