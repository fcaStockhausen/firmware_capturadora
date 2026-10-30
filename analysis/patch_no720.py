#!/usr/bin/env python3
"""Parche no720 — elimina 1280x720 del menú UVC de la capturadora.

PROBLEMA (25/10): Discord captura por defecto a 1280x720 (su cámara-default
en Electron, igual en Mac y Deck). El guard no puede ganarle a un consumidor
vivo sin guerras de renegociación que glitchean el audio.

SOLUCIÓN: si la capturadora NO ofrece 720p, el fallback de Discord toma
1080p60. Los frame descriptors UVC viven en flash: los dos de 720p
(MJPG@0x409, YUYV@0x5e8) se reescriben como 1920x1080 (8 bytes, mismas
longitudes, índices intactos). Sin efectos colaterales de longitud.

Base: jmp120 (original + 1 byte). Este parche es aditivo.
"""
SRC = 'backup/MS2131_jmp120.bin'
OUT = 'backup/MS2131_no720.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

PATCHES = [
    (0x0409, bytes.fromhex('0005d002'), bytes.fromhex('80073804'), 'MJPG frame 6: 1280x720 -> 1920x1080'),
    (0x05E8, bytes.fromhex('0005d002'), bytes.fromhex('80073804'), 'YUYV frame 6: 1280x720 -> 1920x1080'),
]

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4

for off, orig, new, desc in PATCHES:
    cur = bytes(fw[off:off + 4])
    assert cur == orig, f'0x{off:03x}: esperaba {orig.hex()}, hay {cur.hex()}'
    fw[off:off + 4] = new
    print(f'flash 0x{off:03x}: {orig.hex()} -> {new.hex()}  ({desc})')

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff
assert len(fw) == HEADER_LEN + CODE_LEN + 4

open(OUT, 'wb').write(fw)
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
