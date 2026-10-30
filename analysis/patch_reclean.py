#!/usr/bin/env python3
"""Parche quirurgico v3 "reclean": eliminar el residuo 960 en eventos de modo
(120Hz, sin stream) re-limpiando w2 desde el formato justo antes del latch.

Evidencia (2026-10-17, sesion de caza del transitorio):
  * f606 tiene UN solo escritor en la existencia: 0xBC02, llamado UNA sola
    vez (0x583F) con el struct A en 0x1AE2. f606 <- [1AE6:47].
  * En eventos de modo 120Hz sin stream, [1AE6] recibe un transitorio 960
    (readback I2C del receptor durante su re-lock a pclk alto; no hay ÷2
    computado en el firmware: cero inmediatos 960, tablas alineadas, un solo
    RRC-pair ya parcheado en 0x3569).
  * El struct A termina CORRECTO (w2=1920) pero el latch ya comio el 960 y
    nadie re-propaga (forense: structB [1AEA]=960 estacionado, structA limpio).
  * [22DE:DF] (formato activo) queda CORRECTO en el estado residuo.

Patch: antes del latch, re-hacer la copia canonica w2 <- formato usando el
helper EXACTO que ya usa el firmware (0x3A00: copia [dptr],[dptr+1] ->
[1AE6],[1AE7]; mismo patron de llamada que 0x944B/0xB77D):

  0x582B: 90 22 de   mov dptr,#0x22DE
  0x582E: 12 3a 00   lcall 0x3A00      ; [1AE6:47] <- [22DE:DF] (limpio)
  0x5831-0x5838: 8x NOP                (liberado de stores de [1AF1-3])

Las stores de [1AF1-3] que se sacrifican son bookkeeping redundante en esa
ventana: 0xBC02 usa su propia area [1AEE-1AF0], y 0x5842 re-establece
[1AF1-3] antes de 0xBF01. Ningun lector de [1AF1] corre en la ventana.

Registro-clobbers de 0x3A00 (A, r5, dptr): inocuos, 0x5839 setea r1-r3
frescos y 0xBC02 setea su propio dptr.

Semantica preservada: w2 = formato (720p -> 1280, 640 -> 640). NO fuerza 1920.
"""
SRC = 'backup/MS2131_jmp120.bin'
OUT = 'backup/MS2131_reclean.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

PATCH = 0x582B                 # direccion de CODIGO
PATCH_FLASH = PATCH + 0x30     # 0x585B en flash

ORIG = bytes.fromhex('901af174 01 f0 a3 741a f0 a3 74ea f0'.replace(' ', ''))
NEW  = bytes.fromhex('9022de123a00' + '00' * 8)

assert len(ORIG) == 14 and len(NEW) == 14

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4, f'tamano inesperado {len(fw)}'
cur = bytes(fw[PATCH_FLASH:PATCH_FLASH + 14])
assert cur == ORIG, f'bytes inesperados en flash 0x{PATCH_FLASH:04x}: {cur.hex()}'

fw[PATCH_FLASH:PATCH_FLASH + 14] = NEW

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff

open(OUT, 'wb').write(fw)
print(f'reclean: code 0x{PATCH:04x} (flash 0x{PATCH_FLASH:04x}):')
print(f'  -  {ORIG.hex()}')
print(f'  +  {NEW.hex()}')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
