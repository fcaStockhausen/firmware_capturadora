#!/usr/bin/env python3
"""Patch nativo v5: cue corregida (preserva R4/R5/PSW + guard de ancho).

Causa raiz del brick v4 confirmada en el decompilado de mode_57c0:
tras LCALL 0xBF01, el caller hace:
    f620 = R4 & R5 | f620 & 0xFE
La cue v4 dejo R4=0x80 R5=0x07 (hactive) -> R4&R5=0x00 -> f620 pierde bit0
(enable del scaler) -> chip colgado antes del USB.

v5: misma ubicacion (hook 0xBF56, cue 8051 0xF4D0 = flash 0xF500) pero:
  - reproduce f662/f663 (comportamiento original)
  - PUSH ACC, B, PSW, R4, R5 / POP al final (orden inverso)
  - guard: hactive_hi en [0x02..0x07] (ancho 256..2047: 640/1280/1920)
  - solo si hactive == formato ([0xF120:21] == [0x268C:8D]):
      f606=f60E=f618=f660=hactive ; f65c=0x10
"""
SRC = 'backup/MS2131_2025-04-09_backup_2617_44fc.bin'
OUT = 'backup/MS2131_native_cave5.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

HOOK_FLASH = 0xBF56 + 0x30   # 0xBF86
CAVE = 0xF4D0
CAVE_FLASH = CAVE + 0x30     # 0xF500

hook_orig = bytes.fromhex('90f662f0eea3f022')
hook_new  = bytes([0x12, CAVE >> 8, CAVE & 0xff]) + b'\x00' * 5

cave = bytes.fromhex(
    '90f662'       # mov dptr,#0xf662
    'f0'           # movx @dptr,a      ; f662 = A
    'e5f0'         # mov a,0xf0        ; A = B
    'a3'           # inc dptr
    'f0'           # movx @dptr,a      ; f663 = B
    'c0e0'         # push acc
    'c0f0'         # push 0xf0         ; B
    'c0d0'         # push psw
    'c004'         # push 0x04         ; R4 banco actual
    'c005'         # push 0x05         ; R5
    '90f120'       # mov dptr,#0xf120
    'e0'           # movx a,@dptr      ; hactive lo
    'fc'           # mov r4,a
    'a3'           # inc dptr
    'e0'           # movx a,@dptr      ; hactive hi
    'fd'           # mov r5,a
    'ed'           # mov a,r5
    'c3'           # clr c
    '9402'         # subb a,#0x02      ; C=1 si hi < 2
    '4038'         # jc SKIP           ; -> F528
    'ed'           # mov a,r5
    'c3'           # clr c
    '9408'         # subb a,#0x08      ; C=0 si hi >= 8
    '5032'         # jnc SKIP          ; -> F528
    '90268c'       # mov dptr,#0x268c
    'e0'           # movx a,@dptr      ; format lo
    '6c'           # xrl a,r4
    '702b'         # jnz SKIP          ; -> F528
    'a3'           # inc dptr
    'e0'           # movx a,@dptr      ; format hi
    '6d'           # xrl a,r5
    '7026'         # jnz SKIP          ; -> F528
    '90f606'       # mov dptr,#0xf606
    'ecf0a3edf0'   # write16 r4:r5
    '90f60e'       # mov dptr,#0xf60e
    'ecf0a3edf0'
    '90f618'       # mov dptr,#0xf618
    'ecf0a3edf0'
    '90f660'       # mov dptr,#0xf660
    'ecf0a3edf0'
    '90f65c'       # mov dptr,#0xf65c
    '7410'         # mov a,#0x10
    'f0'           # movx @dptr,a      ; bypass rescale H
    # SKIP = 0xF528:
    'd005'         # pop 0x05
    'd004'         # pop 0x04
    'd0d0'         # pop psw
    'd0f0'         # pop 0xf0
    'd0e0'         # pop acc
    '22'           # ret
)
assert len(cave) == 0x63, len(cave)

fw = bytearray(open(SRC, 'rb').read())
assert bytes(fw[HOOK_FLASH:HOOK_FLASH + 8]) == hook_orig, 'hook site inesperado'
fw[HOOK_FLASH:HOOK_FLASH + 8] = hook_new
fw.extend(b'\xff' * (0x10000 - len(fw)))
fw[CAVE_FLASH:CAVE_FLASH + len(cave)] = cave

cs_off = HEADER_LEN + CODE_LEN + 2
new_cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = new_cs >> 8
fw[cs_off + 1] = new_cs & 0xff

open(OUT, 'wb').write(fw)
print(f'hook flash+0x{HOOK_FLASH:04x}: {hook_orig.hex()} -> {hook_new.hex()}')
print(f'cue v5 flash+0x{CAVE_FLASH:04x} ({len(cave)} bytes, con push/pop R4/R5/PSW + guard)')
print(f'checksum codigo -> {new_cs:04x}')
print(f'imagen: {OUT} ({len(fw)} bytes)')
