#!/usr/bin/env python3
"""Patch nativo v7: v6 + preservacion de A/B (2 pushes, presupuesto v4-probado).

Evidencia experimental acumulada en el hook 0xBF56 (bloque compartido):
- v4: push/pop A,B + clobber R4/R5 -> boot OK sin senal (ese caller no usa
  R4/R5), muerto CON senal (mode_57c0 hace f620 = R4 & R5 -> 0).
- v5: push/pop A,B,PSW,R4,R5 (5 pushes) -> muerto siempre: stack overflow.
- v6: sin stack, sin R4/R5, pero clobber A/B -> muerto incluso sin senal:
  ese caller necesita A/B al retorno.

v7 = v6 + push/pop de ACC y B (exactamente 2 bytes, como v4) y nada mas.
Gate: [0x22E4:E5]==0x1770 (stream activo) && hactive hi en [2..7]
      && [0x268C:8D]==hactive.
"""
SRC = 'backup/MS2131_2025-04-09_backup_2617_44fc.bin'
OUT = 'backup/MS2131_native_cave7.bin'
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
    'c0e0'         # push acc
    'c0f0'         # push 0xf0         ; B
    # gate stream activo: [0x22E4:E5] == 0x1770
    '9022e4'       # mov dptr,#0x22e4
    'e0'           # movx a,@dptr
    '6470'         # xrl a,#0x70       ; lo
    '704c'         # jnz POP           ; -> F530
    'a3'           # inc dptr
    'e0'           # movx a,@dptr
    '6417'         # xrl a,#0x17       ; hi
    '7046'         # jnz POP
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
    '4038'         # jc POP
    'ee'           # mov a,r6
    'c3'           # clr c
    '9408'         # subb a,#0x08
    '5032'         # jnc POP
    # formato == hactive ?
    '90268c'       # mov dptr,#0x268c
    'e0'           # movx a,@dptr
    '6f'           # xrl a,r7
    '702b'         # jnz POP
    'a3'           # inc dptr
    'e0'           # movx a,@dptr
    '6e'           # xrl a,r6
    '7026'         # jnz POP
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
    # POP = 0xF530:
    'd0f0'         # pop 0xf0          ; B
    'd0e0'         # pop acc           ; A
    '22'           # ret
)
assert len(cave) == 0x65, len(cave)

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
print(f'cue v7 flash+0x{CAVE_FLASH:04x} ({len(cave)} bytes, push/pop A/B + gates)')
print(f'checksum codigo -> {new_cs:04x}')
print(f'imagen: {OUT} ({len(fw)} bytes)')
