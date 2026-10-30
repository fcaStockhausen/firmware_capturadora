#!/usr/bin/env python3
"""Parche definitivo 1-byte: [1AE2] := [22DE] (hactive real del RX).

Cadena demostrada por RE (ver sesion 2026-10-16):
  0x56BB: mov dptr,#0x22b8  ; 90 22 b8  — lee geometria "captura" (preset, con ÷2 a 120Hz)
  0x56C2: [1AE2] := [22B8]              — copia 16-bit
  0x56E0: [1AE6] := [22DE]              — hactive REAL del RX
  0x5707: clamp [1AEA] = min([1AE2],[1AE6]) -> f606 via 0xBC02

El byte 0x56BD (flash 0x56ED) cambia b8 -> de: la fuente pasa de [22B8]
(preset diezmado) a [22DE] (hactive real). Resultado a 1080p120: f606=1920.

Efectos por modo:
  1080p60/50/30, 720p, 480p: SIN CAMBIO ([22B8]==[22DE] en esos modos)
  1080p100/120: f606 = 1920 (antes 960) — FIX NATIVO
  4K30: f604/f606 = 3840 full (antes 1920 diezmado) — REGRESION aceptada

Ademas: restaurar el hook del wrapper (0x5856 -> LCALL 0xBF01 original)
y limpiar la cue de 0xF3D9 — firmware 100% original salvo 1 byte.
"""
import sys

SRC = sys.argv[1] if len(sys.argv) > 1 else 'backup/MS2131_native_wrapper.bin'
OUT = sys.argv[2] if len(sys.argv) > 2 else 'backup/MS2131_1byte120.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

HOOK = 0x5856
HOOK_FLASH = HOOK + 0x30
WRAP = 0xF3D9
WRAP_FLASH = WRAP + 0x30
PATCH = 0x56BD          # byte bajo del imm16 de 'mov dptr,#0x22b8' en 0x56BB
PATCH_FLASH = PATCH + 0x30

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4

# 1) restaurar hook original
fw[HOOK_FLASH:HOOK_FLASH + 3] = bytes([0x12, 0xbf, 0x01])

# 2) limpiar la cue del wrapper (todo el run de 108 bytes a 0)
fw[WRAP_FLASH:WRAP_FLASH + 108] = bytes(108)

# 3) EL parche: b8 -> de
assert fw[PATCH_FLASH - 2] == 0x90, 'no es mov dptr'
assert fw[PATCH_FLASH - 1] == 0x22
assert fw[PATCH_FLASH] == 0xb8, f'byte inesperado: {fw[PATCH_FLASH]:02x}'
fw[PATCH_FLASH] = 0xde

# 4) checksum de codigo
cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xffff
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xff

open(OUT, 'wb').write(fw)
print(f'hook restaurado: 0x{HOOK:04x} -> 12bf01')
print(f'cue 0x{WRAP:04x} limpiada (108 bytes)')
print(f'patch 1-byte: 0x{PATCH:04x} (flash 0x{PATCH_FLASH:04x}): b8 -> de  ([1AE2] := [22DE])')
print(f'checksum -> {cs:04x}, {len(fw)} bytes -> {OUT}')
