#!/usr/bin/env python3
"""Parche quirurgico v6 "postfix": correccion post-latch de f606/f60e.

Causa raiz final (2026-10-17, tras v3/v4):
  El struct A (0x1AE2) es BUFFER COMPARTIDO con el chat I2C del receptor.
  El walk del latch (0xBC02 lee campo a campo via helpers) puede pillar el
  veneno EN MEDIO de su propia lectura — por eso cada evento latchea basura
  distinta (960, 720, 50, 2853...). Limpiar ANTES del latch (v3/v4) no sirve:
  la carrera es durante el walk. f604/f60c (campos +0/+2) siempre salieron
  bien — el chat solo ensucia [1AE6]+ (w2/h2).

Fix: escribir f606/f60e DIRECTO desde la geometria de entrada [22B8:BB]
(siempre correcta) INMEDIATAMENTE DESPUES de que el latch retorna (0x5842).
Los registros no son buffer del chat — sin carrera.

Layout:
  cueva 0x356B (33B sobre el bloque muerto del jmp120):
    r6r7 = [22B8:BB] (w)      -> f606/f607
    r6r7 = [22BA:BB] (h)      -> f60e/f60f
  ventana 0x5842 (3B + 11 NOP — era la store [1AF1-3] para 0xBF01, redundante:
    0xBF01 recibe su puntero en r1-r3 en 0x5850):
    12 35 6b   lcall cueva
  ventana 0x582B: RESTAURADA a las stores originales de [1AF1-3].

Acumula: original + jmp120 (0x3569) + postfix(v6).
Semantica: en cada corrida del chain, f606/f60e reflejan la entrada
(comportamiento sano original a 60Hz). Formatos UVC menores (720p): el
scaler se autogestiona (captura 720p funciono incluso con f606=50).
"""
SRC = 'backup/MS2131_reclean2.bin'
OUT = 'backup/MS2131_postfix.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

CAVE = 0x356B
WIN1 = 0x582B
WIN2 = 0x5842

WIN1_ORIG = bytes.fromhex('901af17401f0a3741af0a374eaf0')          # stores [1AF1-3]={01,1a,ea}
WIN1_CUR  = bytes.fromhex('9022b8123a009022ba12356b0000')          # contenido v4
WIN1_NEW  = WIN1_ORIG                                              # restaurar

CAVE_CUR = bytes.fromhex('e0fda3e0901ae8cdf0a3edf022')             # helper v4
CAVE_NEW = bytes.fromhex(
    '9022b8' + 'e0fe' + 'a3e0ff' +        # dptr=22B8; r6=[22B8], r7=[22B9] (w)
    '90f606' + 'eef0' + 'a3eff0' +        # f606=r6, f607=r7
    '9022ba' + 'e0fe' + 'a3e0ff' +        # dptr=22BA; r6=[22BA], r7=[22BB] (h)
    '90f60e' + 'eef0' + 'a3eff0' +        # f60e=r6, f60f=r7
    '22'                                   # ret
)
WIN2_ORIG = bytes.fromhex('901af17401f0a3741af0a374e6f0')          # stores [1AF1-3]={01,1a,e6}
WIN2_NEW  = bytes.fromhex('12356b' + '00' * 11)                     # lcall cueva + NOPs

assert len(CAVE_NEW) == 33, f'cueva {len(CAVE_NEW)}B'
assert len(WIN1_NEW) == 14 and len(WIN2_NEW) == 14

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4

c1, c2, c3 = WIN1 + HEADER_LEN, WIN2 + HEADER_LEN, CAVE + HEADER_LEN
assert bytes(fw[c1:c1 + 14]) == WIN1_CUR, 'ventana1 no es v4'
assert bytes(fw[c3:c3 + 13]) == CAVE_CUR, 'cueva no es v4'
assert bytes(fw[c2:c2 + 14]) == WIN2_ORIG, 'ventana2 inesperada'

fw[c1:c1 + 14] = WIN1_NEW
fw[c3:c3 + len(CAVE_NEW)] = CAVE_NEW
fw[c2:c2 + 14] = WIN2_NEW

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff

open(OUT, 'wb').write(fw)
print(f'cueva 0x{CAVE:04x}: post-fixer f606/f60e <- entrada ({len(CAVE_NEW)}B)')
print(f'ventana1 0x{WIN1:04x}: restaurada a original')
print(f'ventana2 0x{WIN2:04x}: {WIN2_NEW.hex()}')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
