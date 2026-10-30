#!/usr/bin/env python3
"""Parchea el firmware MS2131 para eliminar 1080p100/119.88/120 del EDID.

Causa raíz: el EDID declara VIC 62/63/64 (1080p100/119.88/120) pero el
silicio procesa máx ~148.5 Mpix/s; con 1080p120 (297 MHz) el firmware
diezma horizontalmente ÷2 (1920→960) y estira a 1920 => imagen con la
mitad de resolución horizontal. Al quitar esos VIC, las fuentes ya no
ofrecen 120 Hz y el problema desaparece.

Estrategia de diferencia mínima: sustituir los bytes SVD 62/63/64 por
VIC seguros (16/31/32) manteniendo idéntico el largo de todos los
bloques CTA. Se recalculan: checksum CTA y checksum de código del flash.
"""
import sys

BACKUP = 'backup/MS2131_2025-04-09_backup_2617_44fc.bin'
OUT = 'backup/MS2131_no120hz.bin'
EDID_OFF = 0x5A
HEADER_LEN = 0x30
CHECKSUM_LEN = 4
REPLACE = {62: 16, 63: 32, 64: 31}  # 1080p100->1080p60, 119.88->1080p60, 120->1080p50

fw = bytearray(open(BACKUP, 'rb').read())
edid = fw[EDID_OFF:EDID_OFF + 128]
assert edid[:8] == bytes([0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0]), 'firma EDID no encontrada'
assert sum(edid) & 0xff == 0, 'checksum EDID base invalido'

ext_cnt = edid[126]
cta = fw[EDID_OFF + 128:EDID_OFF + 128 + 128]
assert cta[0] == 0x02, 'sin extension CTA-861'
replaced = []

i = 4
while i < cta[2]:  # data block collection termina en dtd_offset
    tag = cta[i] >> 5
    length = cta[i] & 0x1f
    if tag == 2:  # Video Data Block (SVDs)
        for j in range(i + 1, i + 1 + length):
            vic = cta[j] & 0x7f
            native = cta[j] & 0x80
            if vic in REPLACE:
                replaced.append((vic, REPLACE[vic]))
                cta[j] = REPLACE[vic] | native
    i += 1 + length

assert replaced, 'no se encontraron los VIC a reemplazar'

# checksum CTA (bloque de 128 bytes)
cta[127] = (256 - (sum(cta[:127]) & 0xff)) & 0xff
fw[EDID_OFF + 128:EDID_OFF + 256] = cta

# checksum de codigo del flash: suma16 de [0x30 .. 0x30+code_len)
code_len = (fw[0x02] << 8) | fw[0x03]
cs_off = HEADER_LEN + code_len + 2
old_cs = (fw[cs_off] << 8) | fw[cs_off + 1]
new_cs = sum(fw[HEADER_LEN:HEADER_LEN + code_len]) & 0xffff
fw[cs_off] = new_cs >> 8
fw[cs_off + 1] = new_cs & 0xff

# verificaciones
assert sum(fw[EDID_OFF:EDID_OFF+128]) & 0xff == 0
assert (fw[HEADER_LEN+code_len] << 8 | fw[HEADER_LEN+code_len+1]) == \
       (sum(b for k, b in enumerate(fw[:HEADER_LEN]) if not 0x0c <= k <= 0x0f) - fw[0] - fw[1]) & 0xffff

open(OUT, 'wb').write(fw)
print(f'VIC reemplazados: {replaced}')
print(f'checksum codigo: {old_cs:04x} -> {new_cs:04x}')
print(f'image parcheada: {OUT} ({len(fw)} bytes)')
