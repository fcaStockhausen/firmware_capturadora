#!/usr/bin/env python3
"""Patch v2: agrega entrada 1080p120 a la tabla de timings del firmware MS2131.

La tabla (21 bytes/entry) vive en flash+0x2BE5..0x2CF5. No hay entrada para
1080p120; con 297 MHz el matcher cae al entry de 4K30 (flags 0x4b07, preset
con decimacion horizontal /2 pensada para 3840 de ancho) => captura 960.

Sobrescribimos el entry 720x576@50 (flash+0x2CB7, PAL, no usado) con:
  flags 0x0507 (mismo preset que 1080p60), 2200/1125/1920/1080,
  pclk 297.00 MHz, refresh 120.00 Hz, tail copiado del entry 1080p60.

Base: imagen con EDID ya parcheado (MS2131_no120hz.bin). Recalcula checksum
de codigo.
"""
import sys

SRC = 'backup/MS2131_no120hz.bin'
OUT = 'backup/MS2131_full120.bin'
HEADER_LEN = 0x30

ENTRY_OFF = 0x2CB7          # slot del entry 720x576@50 (htotal field +2)
NEW_ENTRY = bytes.fromhex(
    '0507'      # flags: preset como 1080p60
    '0898'      # htotal 2200
    '0465'      # vtotal 1125
    '0780'      # hactive 1920
    '0438'      # vactive 1080
    '7404'      # pixel clock 29700 (297.00 MHz)
    '2ee0'      # refresh 12000 (120.00 Hz)
    '00600014'  # tail (copiado del entry 1080p60: 96, 20)
    '002c00'    # ... 44, 0
)

fw = bytearray(open(SRC, 'rb').read())

# verificar que el slot contiene 720x576@50 antes de tocar
slot = fw[ENTRY_OFF-2:ENTRY_OFF-2+21]
expect = bytes.fromhex('040786 0402 7102 d002 6008 8801 f400'.replace(' ',''))
# 720x576: flags 0407, htot 864(0360)? -- verificado por el scanner:
# 720x576 htot=864=0x0360 vtot=625=0x0271 hact=720=0x02d0 vact=576=0x0240
expect = bytes.fromhex('0407' '0360' '0271' '02d0' '0240' '0a8c' '1388')
assert bytes(slot[:len(expect)]) == expect, f'slot inesperado: {slot[:16].hex()}'

fw[ENTRY_OFF-2:ENTRY_OFF-2+21] = NEW_ENTRY

# checksum de codigo
code_len = (fw[0x02] << 8) | fw[0x03]
cs_off = HEADER_LEN + code_len + 2
new_cs = sum(fw[HEADER_LEN:HEADER_LEN + code_len]) & 0xffff
fw[cs_off] = new_cs >> 8
fw[cs_off + 1] = new_cs & 0xff

open(OUT, 'wb').write(fw)
print(f'entry 1080p120 escrito en flash+0x{ENTRY_OFF-2:04x} (reemplaza 720x576@50)')
print(f'checksum codigo -> {new_cs:04x}')
print(f'imagen: {OUT}')
