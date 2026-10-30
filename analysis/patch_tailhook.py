#!/usr/bin/env python3
"""Parche quirurgico v7 "tailhook": intercepcion del tail-jump del latch.

Descubrimiento clave (2026-10-17): 0xBC02 (el propagador unico de f604/f60c/
f606/f60e) NO retorna — termina en `ljmp 0xD374` (0xBC61). El codigo tras el
lcall (0x5842+) era codigo muerto. Por eso el postfix v6 en 0x5842 nunca corrio.

v7: redirigir el tail-jump a la cueva (bloque muerto del jmp120), que
corrige f606/f60e desde la geometria de entrada [22B8:BB] (siempre correcta,
inmune al chat I2C que envenena el struct) y reanuda la cola original.

Layout:
  0xBC61: 02 35 6b            ljmp cueva    (era: 02 d3 74)
  cueva 0x356B (36B):
    r6r7 = [22B8:B9] (w entrada) -> f606/f607
    r6r7 = [22BA:BB] (h entrada) -> f60e/f60f
    02 d3 74                    ljmp 0xD374 (reanudar cola original)
  0x582B/0x5842: restaurados a original (el segundo era muerto de todos modos).

Acumula: original + jmp120 (0x3569) + tailhook(v7).
"""
SRC = 'backup/MS2131_postfix.bin'
OUT = 'backup/MS2131_tailhook.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

CAVE = 0x356B
TAIL = 0xBC61
WIN2 = 0x5842

CAVE_CUR = bytes.fromhex(
    '9022b8' + 'e0fe' + 'a3e0ff' +
    '90f606' + 'eef0' + 'a3eff0' +
    '9022ba' + 'e0fe' + 'a3e0ff' +
    '90f60e' + 'eef0' + 'a3eff0' +
    '22'
)
CAVE_NEW = bytes.fromhex(
    '9022b8' + 'e0fe' + 'a3e0ff' +
    '90f606' + 'eef0' + 'a3eff0' +
    '9022ba' + 'e0fe' + 'a3e0ff' +
    '90f60e' + 'eef0' + 'a3eff0' +
    '02d374'                       # ljmp 0xD374 — reanudar la cola original
)
WIN2_CUR  = bytes.fromhex('12356b' + '00' * 11)
WIN2_ORIG = bytes.fromhex('901af17401f0a3741af0a374e6f0')
TAIL_ORIG = bytes.fromhex('02d374')

assert len(CAVE_NEW) == 35, f'cueva {len(CAVE_NEW)}B'
assert len(WIN2_ORIG) == 14

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4

cc, ct, cw = CAVE + HEADER_LEN, TAIL + HEADER_LEN, WIN2 + HEADER_LEN
assert bytes(fw[cc:cc + 33]) == CAVE_CUR, 'cueva no es v6'
assert bytes(fw[cw:cw + 14]) == WIN2_CUR, 'ventana2 no es v6'
assert bytes(fw[ct:ct + 3]) == TAIL_ORIG, 'tail no es ljmp d374'

fw[cc:cc + 33] = b'\x00' * 33          # limpiar cueva vieja
fw[cc:cc + 35] = CAVE_NEW
fw[cw:cw + 14] = WIN2_ORIG             # restaurar original (muerto igual)
fw[ct:ct + 3] = bytes.fromhex('02356b')  # ljmp -> cueva

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff

open(OUT, 'wb').write(fw)
print(f'tail 0x{TAIL:04x}: ljmp 0xD374 -> ljmp 0x{CAVE:04X} (cueva)')
print(f'cueva 0x{CAVE:04x}: postfix f606/f60e <- entrada + ljmp 0xD374 ({len(CAVE_NEW)}B)')
print(f'ventana2 0x{WIN2:04x}: restaurada')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
