#!/usr/bin/env python3
"""Parche quirurgico v2: desactivar SOLO la halving de ancho (÷2) en el
clasificador de modos.

Evidencia en vivo (2026-10-17 01:47):
  hot-switch 60->120 con stream abierto: f606 colapsa 1280 -> 640 (÷2 del
  ancho de formato; a 1080p seria 1920 -> 960). La diezmacion dispara en el
  EVENTO de cambio de modo con stream activo, no en el estado 120 Hz.

Codigo (0x3557-0x3582):
  0x3563: lcall 0x315f (dptr=&1AFB)   ; condicion
  0x3569: jnc 0x3595                  ; sin carry -> saltar halving   <- AQUI
  0x356F: clr c / rrc / rrc           ; [1AFB:1AFC] ÷= 2             <- EL ÷2
  0x357E+: ... escribe el valor via puntero

Patch: 0x3569: 50 2a (jnc +0x2a) -> 80 2a (jmp +0x2a)
  La halving nunca corre. El flujo cae siempre al camino 0x3595 (valor
  SIN dividir). El clamp con el formato UVC sigue acotando:
    4K30: f604=3840 (sampling completo, <=124Mpx/s ok), f606=min(3840,1920)=1920
    1080p120 hot-switch: f606 = formato (1920 o 1280) SIN dividir  <- FIX
"""
SRC = 'backup/MS2131_2025-04-09_backup_2617_44fc.bin'
OUT = 'backup/MS2131_jmp120.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7
PATCH = 0x3569
PATCH_FLASH = PATCH + 0x30

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4
assert fw[PATCH_FLASH] == 0x50, f'esperaba jnc (0x50), hay {fw[PATCH_FLASH]:02x}'
assert fw[PATCH_FLASH + 1] == 0x2a, 'offset rel inesperado'
fw[PATCH_FLASH] = 0x80   # jnc -> jmp (incondicional)

cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff

open(OUT, 'wb').write(fw)
print(f'patch: 0x{PATCH:04x} (flash 0x{PATCH_FLASH:04x}): 50 -> 80  (jnc->jmp, halving OFF)')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
