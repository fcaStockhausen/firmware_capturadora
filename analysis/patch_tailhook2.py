#!/usr/bin/env python3
"""Parche quirurgico v8 "tailhook2": postfix de f660 (el registro real).

Descubrimientos acumulados (2026-10-17, sesion de caza):
  * f606/f618 son secundarios: el ANCHO REAL de captura vive en f660/f661
    (par con altura f662/f663). Evidence: todos los demas registros correctos
    + f660=960 => H/V 0.49-0.64 (blur). El fix120 historico escribe
    f606+f618+f660 — el que cura es f660.
  * f660=960 es el DEFAULT DE BOOT del scaler: sin negociacion que lo fije,
    queda en 960 (el sintoma Deck+Discord reproducido en Mac).
  * El tail 0xBC61 (ljmp 0xD374) pasa r4/r5 cargados (0xBC5E/F) a la cola
    0xD374 — que es la que configura f660. La cueva v7 clobberaba A/r6/r7/
    dptr => la cola recibia basura => f660 nunca se actualizaba.

v8: cueva con save/restore COMPLETO (ACC, r6, r7, DPL, DPH), postfix
f660/f661 <- ancho de entrada [22B8:B9] (siempre correcto, inmune al chat
I2C), restore, y reanudar la cola original 0xD374 intacta.

Layout cueva 0x356B (39B sobre el bloque muerto del jmp120):
  c0e0 c006 c007 c082 c083          push ACC,6,7,DPL,DPH
  9022b8 e0fe a3e0ff                r6r7 = [22B8:B9] (w entrada)
  90f660 eef0 a3eff0                f660/f661 = w
  d083 d082 d007 d006 d0e0          pop DPH,DPL,7,6,ACC
  02d374                            ljmp 0xD374 (cola original)
tail 0xBC61: ljmp 0x356B (de v7, sin cambios)
"""
SRC = 'backup/MS2131_tailhook.bin'
OUT = 'backup/MS2131_tailhook2.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

CAVE = 0x356B

CAVE_V7 = bytes.fromhex(
    '9022b8' + 'e0fe' + 'a3e0ff' +
    '90f606' + 'eef0' + 'a3eff0' +
    '9022ba' + 'e0fe' + 'a3e0ff' +
    '90f60e' + 'eef0' + 'a3eff0' +
    '02d374'
)
CAVE_V8 = bytes.fromhex(
    'c0e0' + 'c006' + 'c007' + 'c082' + 'c083' +           # saves
    '9022b8' + 'e0fe' + 'a3e0ff' +                        # r6r7 = w entrada
    '90f660' + 'eef0' + 'a3eff0' +                        # f660/f661 = w
    'd083' + 'd082' + 'd007' + 'd006' + 'd0e0' +          # restores
    '02d374'                                               # cola original
)
assert len(CAVE_V8) == 39, f'cueva {len(CAVE_V8)}B'
assert len(CAVE_V7) == 35

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4
cc = CAVE + HEADER_LEN
assert bytes(fw[cc:cc + 35]) == CAVE_V7, 'cueva no es v7'

fw[cc:cc + 35] = b'\x00' * 35
fw[cc:cc + 39] = CAVE_V8

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff

open(OUT, 'wb').write(fw)
print(f'cueva 0x{CAVE:04x}: save/postfix-f660/restore ({len(CAVE_V8)}B)')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
