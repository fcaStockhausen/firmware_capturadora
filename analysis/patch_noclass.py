#!/usr/bin/env python3
"""Parche v12 "noclass": el detector de pclk-alto nunca dispara.

Circuito completo establecido (2026-10-17, con veredicto visual del usuario):
  60Hz:  f65c=0x10, muestreo ancho completo, geometria 1:1, H/V=1.604 = PERFECTO
  120Hz: f65c=0x08, muestreo a medio ancho => mitad izquierda estirada 2x
  (escribir f65c=0x10 solo a 120 => RUIDO: el modo necesita su config completa)

La decision: 0x93C6 computa [1AAD]=pclk y compara >= 0x4E20 (200MHz):
  0x93D4: jc 0x93D9  (si pclk bajo -> flag 0x20.1 = 0)
  0x93D6: setb c     (si alto...)
  0x93DA: mov 0x20.1, C
El flag 0x20.1 => clase alta => preset de medio ancho para la bateria f620-f651.

Patch: 0x93D4: 40 03 (jc +3) -> 80 03 (sjmp +3)  [mismo truco que jmp120]
  El flag nunca se enciende => el firmware configura SIEMPRE el preset de
  ancho completo (el de 60Hz) aun con entrada 1080p120.

Caveat documentado: YUYV 1080p120 full = 497MB/s (limite USB3). Si el host
no banca el caudal, habra frames dropeados — pero la geometria sera 1:1.

Acumula: original + jmp120 + applier3(v11) + noclass(v12).
"""
SRC = 'backup/MS2131_applier3.bin'
OUT = 'backup/MS2131_noclass.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

P = 0x93D4

ORIG = bytes.fromhex('4003')
NEW  = bytes.fromhex('8003')

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4
cp = P + HEADER_LEN
assert bytes(fw[cp:cp+2]) == ORIG, f'inesperado: {bytes(fw[cp:cp+2]).hex()}'

fw[cp:cp+2] = NEW

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff
assert len(fw) == HEADER_LEN + CODE_LEN + 4

open(OUT, 'wb').write(fw)
print(f'0x{P:04X}: 40 03 (jc) -> 80 03 (sjmp) — flag 0x20.1 nunca setea')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
