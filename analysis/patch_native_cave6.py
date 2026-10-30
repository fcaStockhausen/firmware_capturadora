#!/usr/bin/env python3
"""Patch nativo v6: cue zero-stack + gate de stream activo.

Lecciones v4 (clobber R4/R5 -> f620 = R4&R5 = 0 -> hang) y v5 (5 pushes
-> stack overflow -> hang incluso sin HDMI): el bloque hookeado corre en
TODA config, incluida la de boot. El fix solo tiene efecto (y solo es
seguro) cuando hay stream abierto.

Gate empirico verificado: [0x22E4:0x22E5] = 0x1770 (6000) <==> stream
activo (UVC commit 60fps); 0x07D0 (2000) en reposo/cierre.

Cue v6 (zero stack, usa solo A/R6/R7/DPTR/flags):
  1. f662=A, f663=B (comportamiento original del hook)
  2. si [0x22E4:E5] != 0x1770 -> ret (boot/idle: nunca dispara)
  3. hactive=[0xF120:21] -> r7(lo):r6(hi); guard hi en [2..7]
  4. si [0x268C:8D] != hactive -> ret (4K30 y upscale intactos)
  5. f606=f60E=f618=f660=hactive ; f65c=0x10 (bypass rescale H)
"""
SRC = 'backup/MS2131_2025-04-09_backup_2617_44fc.bin'
OUT = 'backup/MS2131_native_cave6.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

HOOK_FLASH = 0xBF56 + 0x30
CAVE = 0xF4D0
CAVE_FLASH = CAVE + 0x30

hook_orig = bytes.fromhex('90f662f0eea3f022')
hook_new  = bytes([0x12, CAVE >> 8, CAVE & 0xff]) + b'\x00' * 5

cave = bytes.fromhex(
    '90f662'       # mov dptr,#0xf662
    'f0'           # movx @dptr,a      ; f662 = A
    'e5f0'         # mov a,0xf0        ; A = B
    'a3'           # inc dptr
    'f0'           # movx @dptr,a      ; f663 = B
    # gate stream activo: [0x22E4:E5] == 0x1770
    '9022e4'       # mov dptr,#0x22e4
    'e0'           # movx a,@dptr
    '6470'         # xrl a,#0x70       ; lo
    '704c'         # jnz SKIP          ; -> F52C
    'a3'           # inc dptr
    'e0'           # movx a,@dptr
    '6417'         # xrl a,#0x17       ; hi
    '7046'         # jnz SKIP
    # hactive -> r7(lo):r6(hi)
    '90f120'       # mov dptr,#0xf120
    'e0'           # movx a,@dptr
    'ff'           # mov r7,a
    'a3'           # inc dptr
    'e0'           # movx a,@dptr
    'fe'           # mov r6,a
    # guard hi en [2..7]
    'ee'           # mov a,r6
    'c3'           # clr c
    '9402'         # subb a,#0x02
    '4038'         # jc SKIP
    'ee'           # mov a,r6
    'c3'           # clr c
    '9408'         # subb a,#0x08
    '5032'         # jnc SKIP
    # formato == hactive ?
    '90268c'       # mov dptr,#0x268c
    'e0'           # movx a,@dptr
    '6f'           # xrl a,r7
    '702b'         # jnz SKIP
    'a3'           # inc dptr
    'e0'           # movx a,@dptr
    '6e'           # xrl a,r6
    '7026'         # jnz SKIP
    # fix
    '90f606'       # mov dptr,#0xf606
    'eff0a3eef0'   # write16 r7:r6
    '90f60e'       # mov dptr,#0xf60e
    'eff0a3eef0'
    '90f618'       # mov dptr,#0xf618
    'eff0a3eef0'
    '90f660'       # mov dptr,#0xf660
    'eff0a3eef0'
    '90f65c'       # mov dptr,#0xf65c
    '7410'         # mov a,#0x10
    'f0'           # movx @dptr,a
    # SKIP = 0xF52C:
    '22'           # ret
)
assert len(cave) == 0x5D, len(cave)

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
print(f'cue v6 flash+0x{CAVE_FLASH:04x} ({len(cave)} bytes, zero-stack, gate stream)')
print(f'checksum codigo -> {new_cs:04x}')
print(f'imagen: {OUT} ({len(fw)} bytes)')
