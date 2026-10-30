#!/usr/bin/env python3
"""Parche quirurgico v4 "reclean2": fuente = geometria de ENTRADA [22B8:BB].

Historia del fix del residuo 960 (2026-10-17):
  v3 "reclean" ([22DE]-fuente): el latch dejo de comer el junk I2C de [1AE6],
  pero tomo el FALLBACK transitorio del formato (f606=720/f60e=480 en ciclos
  limpios). El formato mismo transita valores de re-init a mitad del baile.
  v4: la geometria de ENTRADA [22B8:BB] es correcta SIEMPRE (incluso a mitad
  del baile — es lo que reporta el receptor lockeado). El latch del evento de
  modo sin stream debe reflejar la entrada (= comportamiento sano original
  del firmware a 60Hz: f606=1920=input). El formato UVC aplica su propio
  chain+latch cuando se negocia de verdad.

Layout:
  cueva (bloque muerto desde jmp120, 0 saltos entrantes verificados):
    0x356B: e0 fd a3 e0 90 1a e8 cd f0 a3 ed f0 22
            helper "copia [dptr],[dptr+1] -> [1AE8],[1AE9]" (hermano del 0x3A00)
  ventana (antes del latch unico 0x583F):
    0x582B: 90 22 b8  mov dptr,#0x22B8      ; ancho entrada
    0x582E: 12 3a 00  lcall 0x3A00          ; [1AE6:47] <- [22B8:B9]
    0x5831: 90 22 ba  mov dptr,#0x22BA      ; alto entrada
    0x5834: 12 35 6b  lcall 0x356B (cueva)  ; [1AE8:49] <- [22BA:BB]
    0x5837: 00 00     padding

Sacrificados: las stores redundantes de [1AF1-3] (0x5842 re-establece antes
de 0xBF01; 0xBC02 usa [1AEE] propia) y el bloque muerto ÷2 (inalcanzable).

Stack: +2 bytes momentaneos ANTES del lcall 0xBC02 (helpers sin anidacion).
Caveat documentado: entrada 4K -> f606=3840 (mismo ancho de banda que
1080p120=249Mpx/s; sin usar por el usuario).

Acumula: original + jmp120 (0x3569) + reclean(v3, reemplazado por v4).
"""
SRC = 'backup/MS2131_reclean.bin'
OUT = 'backup/MS2131_reclean2.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

CAVE = 0x356B
WIN  = 0x582B

# bloque original 0x356B-0x3578 (el ÷2 muerto — para el assert)
CAVE_ORIG = bytes.fromhex('901afbe0c313fea3e013ff901afbee f0a3ef f0'.replace(' ', ''))
CAVE_NEW  = bytes.fromhex('e0fda3e0901ae8cdf0a3edf022')

WIN_ORIG = bytes.fromhex('9022de123a00' + '00' * 8)      # contenido reclean v3
WIN_NEW  = bytes.fromhex('9022b8123a009022ba12356b' + '0000')

assert len(CAVE_NEW) == 13, f'cueva {len(CAVE_NEW)}B'
assert len(WIN_ORIG) == 14 and len(WIN_NEW) == 14

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4

cf, wf = CAVE + HEADER_LEN, WIN + HEADER_LEN
cur_cave = bytes(fw[cf:cf + len(CAVE_ORIG)])
cur_win = bytes(fw[wf:wf + 14])
assert cur_win == WIN_ORIG, f'ventana inesperada: {cur_win.hex()}'
# el assert de cueva: verificar solo los primeros bytes del bloque muerto
assert cur_cave[:6] == bytes.fromhex('901afbe0c313'), f'cueva inesperada: {cur_cave.hex()}'

fw[cf:cf + len(CAVE_NEW)] = CAVE_NEW
fw[wf:wf + 14] = WIN_NEW

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff

open(OUT, 'wb').write(fw)
print(f'cueva 0x{CAVE:04x}: helper copy->[1AE8] ({len(CAVE_NEW)}B sobre el bloque muerto)')
print(f'ventana 0x{WIN:04x}: {WIN_NEW.hex()}')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
