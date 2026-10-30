#!/usr/bin/env python3
"""Patch nativo v4: code cave + hook al final del bloque escritor f65b/f660.

Bloque 0xBF01 (epilogo compartido de config del scaler H):
  ... f65b:f65c (ratio Q12 via 0xB295), f65d:f65e, f660:f661 ...
  BF51: LCALL 0x9C73          ; A(lo):B(hi) = valor via descriptor
  BF54: MOV R6, 0xF0
  BF56: MOV DPTR,#0xF662
  BF59: MOVX @DPTR,A          ; f662 = A
  BF5A: MOV A,R6
  BF5B: INC DPTR
  BF5C: MOVX @DPTR,A          ; f663 = B
  BF5D: RET

Hook: 0xBF56..0xBF5D (8 bytes) -> LCALL CAVE + 5 NOPs.
Cave (8051 0xF4D0 = flash 0xF500, tras checksums, no altera code checksum):
  - reproduce f662=A, f663=B
  - si [0xF120:0xF121] (hactive RX) == [0x268C:0x268D] (ancho formato UVC):
      f606=f60E=f618=f660 = hactive ; f65c = 0x10 (bypass rescale H)
    (= replica del hot-fix validado: Laplaciano 3.0k -> 48k)
  - restaura A/B y RET

Casos: 1080p120 fix; 60Hz no-op; 720p(f120) fix; 4K30 skip (3840!=1920);
input<format (upscale) skip.
"""
SRC = 'backup/MS2131_2025-04-09_backup_2617_44fc.bin'
OUT = 'backup/MS2131_native_cave.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

HOOK = 0xBF56            # 8051
HOOK_FLASH = HOOK + 0x30 # 0xBF86
CAVE = 0xF4D0            # 8051
CAVE_FLASH = CAVE + 0x30 # 0xF500

hook_orig = bytes.fromhex('90f662f0eea3f022')  # mov dptr,#f662; movx; mov a,r6; inc; movx; ret
hook_new  = bytes([0x12, CAVE >> 8, CAVE & 0xff]) + b'\x00' * 5  # lcall cave + nops

cave = bytes.fromhex(
    '90f662'       # mov dptr,#0xf662
    'f0'           # movx @dptr,a      ; f662 = A
    'e5f0'         # mov a,0xf0        ; A = B
    'a3'           # inc dptr
    'f0'           # movx @dptr,a      ; f663 = B
    'c0e0'         # push acc
    'c0f0'         # push 0xf0         ; B
    '90f120'       # mov dptr,#0xf120
    'e0'           # movx a,@dptr      ; hactive lo
    'fc'           # mov r4,a
    'a3'           # inc dptr
    'e0'           # movx a,@dptr      ; hactive hi
    'fd'           # mov r5,a
    '90268c'       # mov dptr,#0x268c
    'e0'           # movx a,@dptr      ; format lo
    '6c'           # xrl a,r4
    '702b'         # jnz END
    'a3'           # inc dptr
    'e0'           # movx a,@dptr      ; format hi
    '6d'           # xrl a,r5
    '7026'         # jnz END
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
    'f0'           # movx @dptr,a
    'd0f0'         # pop 0xf0
    'd0e0'         # pop acc
    '22'           # ret
)
assert len(cave) == 0x4B, len(cave)

fw = bytearray(open(SRC, 'rb').read())
orig = bytes(fw[HOOK_FLASH:HOOK_FLASH + 8])
assert orig == hook_orig, f'hook site inesperado: {orig.hex()}'
assert len(fw) <= CAVE_FLASH, 'imagen invade la zona de la cue'

fw[HOOK_FLASH:HOOK_FLASH + 8] = hook_new
fw.extend(b'\xff' * (0x10000 - len(fw)))   # padding a 64K
fw[CAVE_FLASH:CAVE_FLASH + len(cave)] = cave

# checksum de codigo (el hook cae dentro; la cue esta fuera)
cs_off = HEADER_LEN + CODE_LEN + 2
new_cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = new_cs >> 8
fw[cs_off + 1] = new_cs & 0xff

open(OUT, 'wb').write(fw)
print(f'hook flash+0x{HOOK_FLASH:04x}: {hook_orig.hex()} -> {hook_new.hex()}')
print(f'cue  flash+0x{CAVE_FLASH:04x} ({len(cave)} bytes)')
print(f'checksum codigo -> {new_cs:04x}')
print(f'imagen: {OUT} ({len(fw)} bytes)')
