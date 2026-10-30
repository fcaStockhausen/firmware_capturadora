#!/usr/bin/env python3
"""Test C / v8: WRAPPER en el caller de 0xBF01 (no toca el bloque original).

Causa raiz de TODOS los bricks anteriores: dos AJMP (0xC267, 0xC26E) entran
a 0xBF5B (medio del bloque 0xBF01, cola compartida del compilador). Cualquier
modificacion de bytes dentro de 0xBF56-0xBF5D rompe esas entradas.

Solucion: el bloque 0xBF01 tiene UN unico caller (mode_57c0 @ 0x5856:
`LCALL 0xBF01`). Se reemplaza ese LCALL (3 bytes) por `LCALL WRAPPER`.
El wrapper ejecuta el bloque original INTACTO y luego aplica el fix
condicionado, preservando A/B/R4/R5 para la continuacion del caller
(que hace `f620 = R4 & R5 | ...`).

Wrapper en 0xF3D9 (run de 108 ceros dentro de la region de codigo,
imagen sigue en 62715 bytes, sin padding 64K).
"""
SRC = 'backup/MS2131_2025-04-09_backup_2617_44fc.bin'
OUT = 'backup/MS2131_native_wrapper.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

HOOK = 0x5856
HOOK_FLASH = HOOK + 0x30
WRAP = 0xF3D9
WRAP_FLASH = WRAP + 0x30

fw = bytearray(open(SRC, 'rb').read())
assert bytes(fw[HOOK_FLASH:HOOK_FLASH + 3]) == bytes([0x12, 0xbf, 0x01])
assert all(b == 0 for b in fw[WRAP_FLASH:WRAP_FLASH + 108])

# --- ensamblar wrapper con offsets calculados ---
parts = []
pos = WRAP

def emit(hexstr, note=''):
    global pos
    b = bytes.fromhex(hexstr)
    parts.append((pos, b, note))
    pos += len(b)

def placeholder_jmp(opcode_hex, note):
    """emite salto condicional de 2 bytes con offset placeholder; devuelve pos"""
    global pos
    parts.append((pos, bytes.fromhex(opcode_hex + '00'), note + ' [placeholder]'))
    p = pos
    pos += 2
    return p

emit('12bf01', 'lcall 0xbf01 (bloque original intacto)')
emit('c0e0', 'push acc')
emit('c0f0', 'push B')
emit('c004', 'push R4')
emit('c005', 'push R5')
emit('9022e4', 'dptr=0x22e4')
emit('e0', 'a=[22e4] lo')
emit('6470', 'xrl a,#0x70')
j1 = placeholder_jmp('70', 'jnz POP_END (stream gate lo)')
emit('a3', 'inc dptr')
emit('e0', 'a=[22e5] hi')
emit('6417', 'xrl a,#0x17')
j2 = placeholder_jmp('70', 'jnz POP_END (stream gate hi)')
emit('90f120', 'dptr=0xf120')
emit('e0', 'a=hact lo')
emit('ff', 'r7=a')
emit('a3', 'inc')
emit('e0', 'a=hact hi')
emit('fe', 'r6=a')
emit('ee', 'a=r6')
emit('c3', 'clr c')
emit('9402', 'subb a,#2')
j3 = placeholder_jmp('40', 'jc POP_END (guard lo)')
emit('ee', 'a=r6')
emit('c3', 'clr c')
emit('9408', 'subb a,#8')
j4 = placeholder_jmp('50', 'jnc POP_END (guard hi)')
emit('90268c', 'dptr=0x268c')
emit('e0', 'a=fmt lo')
emit('6f', 'xrl a,r7')
j5 = placeholder_jmp('70', 'jnz POP_END (fmt lo)')
emit('a3', 'inc')
emit('e0', 'a=fmt hi')
emit('6e', 'xrl a,r6')
j6 = placeholder_jmp('70', 'jnz POP_END (fmt hi)')
emit('90f606', 'dptr=f606')
emit('eff0a3eef0', 'write16 r7:r6')
emit('90f60e', 'dptr=f60e')
emit('eff0a3eef0', 'write16')
emit('90f618', 'dptr=f618')
emit('eff0a3eef0', 'write16')
emit('90f660', 'dptr=f660')
emit('eff0a3eef0', 'write16')
emit('90f65c', 'dptr=f65c')
emit('7410', 'a=0x10')
emit('f0', 'f65c=0x10 bypass')
pop_end = pos
emit('d005', 'pop R5')
emit('d004', 'pop R4')
emit('d0f0', 'pop B')
emit('d0e0', 'pop acc')
emit('22', 'ret')

# parchear offsets: target POP_END
blob = bytearray()
for p, b, note in parts:
    if p in (j1, j2, j3, j4, j5, j6):
        off = pop_end - (p + 2)
        assert 0 <= off <= 0x7f, f'offset fuera de rango: {off:#x}'
        b = bytes([b[0], off])
    blob += b

assert len(blob) <= 108, len(blob)
print(f'wrapper: {len(blob)} bytes @ 0x{WRAP:04x}, POP_END=0x{pop_end:04x}')

fw[HOOK_FLASH:HOOK_FLASH + 3] = bytes([0x12, WRAP >> 8, WRAP & 0xff])
fw[WRAP_FLASH:WRAP_FLASH + len(blob)] = blob

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff

open(OUT, 'wb').write(fw)
print(f'hook 0x{HOOK:04x}: 12bf01 -> 12{WRAP:04x}')
print(f'checksum -> {cs:04x}, imagen {len(fw)} bytes: {OUT}')
