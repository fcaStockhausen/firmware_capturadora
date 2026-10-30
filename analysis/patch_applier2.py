#!/usr/bin/env python3
"""Parche quirurgico v10 "applier2": f606 Y f660 <- ancho de entrada.

Sobre v9: el boot limpio dio f660=1920/f662=1080 (default 960 muerto) pero
H/V=0.773 — el walk (0xBC02) sigue envenenando f606=960 y el suite incoherente
mantiene el blur. El fix120 historico escribe f606+f618+f660 — coherencia
de suite.

v10: una sola cueva (36B) que escribe f606/f607 Y f660/f661 desde [22B8:BB]
(ancho de entrada), dejando {A=hi, r6=lo} para el write original de f660 que
sigue intacto. 0xBF51 revierte a original (f662/flujos naturales — el dano
es solo horizontal). Orden garantizado: 0xBC02 (walk, junk) corre ANTES de
0xBF01 (applier) en la cadena (0x583F < 0x5856) — last write wins.

Layout cueva 0x356B (36B):
  r6=hi, r7=lo <- [22B8:B9]
  f606/f607  = r6r7
  f660/f661  = r6r7
  A=hi (ee), swap r6<->r7 (cf ce) → A=hi, r6=lo
  ret
0xBF45: 12 35 6b 00 00   (igual que v9)
0xBF51: ORIGINAL (129c73aef0) — revertido de v9
0xBC61: ORIGINAL — ya revertido en v9
"""
SRC = 'backup/MS2131_applier.bin'
OUT = 'backup/MS2131_applier2.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

CAVE = 0x356B
P2   = 0xBF51

CAVE_V9 = bytes.fromhex(
    '9022b9' + 'e0fe' + '9022b8' + 'e0' + '22' +
    '9022bb' + 'e0fe' + '9022ba' + 'e0' + '22'
)
CAVE_V10 = bytes.fromhex(
    '9022b8' + 'e0fe' + 'a3e0' + 'ff' +       # r6=[22B8] hi, r7=[22B9] lo
    '90f606' + 'eef0' + 'a3' + 'eff0' +       # f606=hi, f607=lo
    '90f660' + 'eef0' + 'a3' + 'eff0' +       # f660=hi, f661=lo
    'ee' + 'cf' + 'ce' +                       # A=r6(hi); xch r7; xch r6 → A=hi, r6=lo
    '22'
)
assert len(CAVE_V10) == 28, f'cueva {len(CAVE_V10)}B'

P2_V9  = bytes.fromhex('1235750000')
P2_ORIG = bytes.fromhex('129c73aef0')

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4
cc, cp2 = CAVE + HEADER_LEN, P2 + HEADER_LEN
assert bytes(fw[cc:cc+20]) == CAVE_V9, 'cueva no es v9'
assert bytes(fw[cp2:cp2+5]) == P2_V9, 'P2 no es v9'

fw[cc:cc+42] = b'\x00' * 42
fw[cc:cc+len(CAVE_V10)] = CAVE_V10
fw[cp2:cp2+5] = P2_ORIG

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff

assert len(fw) == HEADER_LEN + CODE_LEN + 4, f'tamano corrupto: {len(fw)}'

open(OUT, 'wb').write(fw)
print(f'cueva 0x{CAVE:04X}: f606+f660 <- entrada, preserva {chr(123)}A,r6{chr(125)} ({len(CAVE_V10)}B)')
print(f'0xBF51: revertido a original (f662 natural)')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
