#!/usr/bin/env python3
"""patch_bisect — conversión tail-call de un SUBCONJUNTO de sitios flat1.

Bisect empirico del defecto de boot de flat1 (27/10: jmp120 boota, flat1
no, ambas flash-verificadas, sin agente). Uso:

    patch_bisect.py <out.bin> <code_addr>...     (direcciones de sitio)

Sitios disponibles (de patch_flat1.py):
  0x8758 0x9bd1 0xa898 0xdab7 0xe655 0xe6d1
"""
import sys

SRC = 'backup/MS2131_jmp120.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

SITIOS = {
    0x8758: 0xCD55,
    0x9bd1: 0x8837,
    0xa898: 0xD72D,
    0xdab7: 0x4AEF,
    0xe655: 0x0016,
    0xe6d1: 0xDA55,
}

out = sys.argv[1]
sel = [int(a, 16) for a in sys.argv[2:]]
for a in sel:
    assert a in SITIOS, f'sitio desconocido: {hex(a)}'

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4

for code_addr in sel:
    target = SITIOS[code_addr]
    off = code_addr + HEADER_LEN
    esperado = bytes([0x12, target >> 8, target & 0xFF, 0x22])
    actual = bytes(fw[off:off + 4])
    assert actual == esperado, \
        f'0x{code_addr:04x}: esperado {esperado.hex(" ")}, hay {actual.hex(" ")}'
    fw[off:off + 4] = bytes([0x02, target >> 8, target & 0xFF, 0x00])
    print(f'  0x{code_addr:04x}: lcall 0x{target:04X}; ret -> ljmp 0x{target:04X}; nop')

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xFFFF
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xFF

open(out, 'wb').write(fw)
print(f'checksum -> {cs:04X}, {len(fw)} bytes -> {out}')
