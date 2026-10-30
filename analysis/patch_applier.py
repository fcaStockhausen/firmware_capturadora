#!/usr/bin/env python3
"""Parche quirurgico v9 "applier": f660/f662 leen la geometria de ENTRADA.

Modelo final completo (2026-10-17):
  * El ANCHO REAL de captura = f660/f661 (par con f662/f663 = altura).
    Escritor UNICO: 0xBF4A dentro de 0xBF01 (aplicador del struct B,
    llamado desde 0x5856 y otros).
  * struct B ([1AEA:AB]) queda estacionado en 960 en eventos de modo 120Hz
    sin stream (clamp con el w2 transitorio del chat I2C) -> 0xBF01 lo
    propaga a f660 -> blur. f606/f618 eran señuelos.
  * f660=960 es ademas el default de boot del scaler (sintoma Deck+Discord).

v9: dentro de 0xBF01, reemplazar las lecturas de campo (lcall 0x0EC5 /
lcall 0x9C73 que alimentan A/r6 desde el struct) por cargas desde la
geometria de entrada [22B8:BB] (siempre correcta). El write original queda
INTACTO — solo cambia su fuente. Lectura y escritura a microsegundos, dentro
del aplicador: sin carrera, aplica en todos los callers de 0xBF01.

Layout:
  cueva 0x356B (20B, dos entradas — sobre el bloque muerto del jmp120):
    entry1 0x356B: r6=[22B9], A=[22B8]  (w)  ret     -> f660/f661
    entry2 0x3575: r6=[22BB], A=[22BA]  (h)  ret     -> f662/f663
  0xBF45: 12 0e c5 ae f0  ->  12 35 6b 00 00
  0xBF51: 12 9c 73 ae f0  ->  12 35 75 00 00
  0xBC61: revert tailhook ->  02 d3 74 (original)

Acumula: original + jmp120 (0x3569) + applier(v9).
"""
SRC = 'backup/MS2131_tailhook2.bin'
OUT = 'backup/MS2131_applier.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

CAVE1 = 0x356B
CAVE2 = 0x3575
TAIL  = 0xBC61
P1    = 0xBF45
P2    = 0xBF51

CAVE_CODE = bytes.fromhex(
    # entry1: r6=[22B9] (lo), A=[22B8] (hi) — para f660/f661
    '9022b9' + 'e0fe' +          # dptr=22B9; A=[22B9]; r6=A
    '9022b8' + 'e0' +            # dptr=22B8; A=[22B8]
    '22' +                        # ret
    # entry2 (0x3575): r6=[22BB] (lo), A=[22BA] (hi) — para f662/f663
    '9022bb' + 'e0fe' +
    '9022ba' + 'e0' +
    '22'
)
assert len(CAVE_CODE) == 20
assert CAVE1 + 10 == CAVE2

P1_ORIG = bytes.fromhex('120ec5aef0')
P1_NEW  = bytes.fromhex('12356b0000')
P2_ORIG = bytes.fromhex('129c73aef0')
P2_NEW  = bytes.fromhex('1235750000')
TAIL_V8 = bytes.fromhex('02356b')
TAIL_ORIG = bytes.fromhex('02d374')

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4

cp1, cp2, ct, cc = P1 + HEADER_LEN, P2 + HEADER_LEN, TAIL + HEADER_LEN, CAVE1 + HEADER_LEN
assert bytes(fw[cp1:cp1+5]) == P1_ORIG, f'P1: {bytes(fw[cp1:cp1+5]).hex()}'
assert bytes(fw[cp2:cp2+5]) == P2_ORIG, f'P2: {bytes(fw[cp2:cp2+5]).hex()}'
assert bytes(fw[ct:ct+3]) == TAIL_V8, 'tail no es v8'

fw[cp1:cp1+5] = P1_NEW
fw[cp2:cp2+5] = P2_NEW
fw[ct:ct+3] = TAIL_ORIG                  # revertir tailhook
fw[cc:cc+42] = b'\x00' * 42              # limpiar cueva vieja (39B + margen)
fw[cc:cc+20] = CAVE_CODE

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff

open(OUT, 'wb').write(fw)
print(f'0xBF45: {P1_ORIG.hex()} -> {P1_NEW.hex()} (lcall entry1 f660)')
print(f'0xBF51: {P2_ORIG.hex()} -> {P2_NEW.hex()} (lcall entry2 f662)')
print(f'0xBC61: tailhook revertido a original')
print(f'cueva 0x{CAVE1:04X}/0x{CAVE2:04X}: cargas w/h de entrada ({len(CAVE_CODE)}B)')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
