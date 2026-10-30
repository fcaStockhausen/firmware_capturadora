#!/usr/bin/env python3
"""flat1 — aplanado de stack por conversión tail-call (bug B).

Mecanismo (GUIA.md §20): SP=0x4B fijo, techo IRAM 0x7F = 52B. Las cadenas
ISR desbordan en sus caminos profundos (EXT1/TIMER1 +11B). Un sitio
`lcall X ; ret` al final de una funcion es semanticamente identico como
`ljmp X` — pero ahorra 2B de stack (el ret-addr del lcall nunca se apila).

Sitios convertidos (verificados: patron exacto `12 xx xx 22`, cero saltos
que aterricen en los 4 bytes reescritos — verificacion del 27/10):

  code 0x8758: lcall 0xCD55; ret   (sub_8680 -> cd55)  [cola compartida]
  code 0x9bd1: lcall 0x8837; ret   (sub_9bcd -> 8837)  [cola compartida]
  code 0xa898: lcall 0xD72D; ret   (sub_a78c -> d72d)
  code 0xdab7: lcall 0x4AEF; ret   (sub_da55 -> 4aef)  [cola compartida]
  code 0xe655: lcall 0x0016; ret   (sub_e63a -> 0016, trampolin -> 0xE279)
  code 0xe6d1: lcall 0xDA55; ret   (sub_e63a -> da55)  [cola compartida]

Ahorro por camino (max-live secuencial):
  TIMER1: 60B -> 52B EXACTO (4 sitios: e6d1, dab7, 8758, 9bd1)
  EXT1:   94B -> 86B (mismos 4 sitios; resto = walk de propiedades anidado,
          estatico y sobre-estimado por ramas)
  EXT0:   127B -> 119B estatico (idem)
Cada sitio ademas resta 2B a TODA ejecucion que lo cruce.

Base: backup/MS2131_jmp120.bin — TODO lo demas intacto (politica, formatos,
parche jmp120 @0x3569).
"""
import sys

SRC = sys.argv[1] if len(sys.argv) > 1 else 'backup/MS2131_jmp120.bin'
OUT = sys.argv[2] if len(sys.argv) > 2 else 'backup/MS2131_flat1.bin'
HEADER_LEN = 0x30
CODE_LEN = 0xF4C7

# code_addr -> target del lcall
SITIOS = {
    0x8758: 0xCD55,
    0x9bd1: 0x8837,
    0xa898: 0xD72D,
    0xdab7: 0x4AEF,
    0xe655: 0x0016,
    0xe6d1: 0xDA55,
}

fw = bytearray(open(SRC, 'rb').read())
assert len(fw) == HEADER_LEN + CODE_LEN + 4, f'tamaño inesperado: {len(fw)}'

for code_addr, target in SITIOS.items():
    off = code_addr + HEADER_LEN
    esperado = bytes([0x12, target >> 8, target & 0xFF, 0x22])
    actual = bytes(fw[off:off + 4])
    assert actual == esperado, \
        f'0x{code_addr:04x}: esperado {esperado.hex(" ")}, hay {actual.hex(" ")}'
    # lcall X (12 xx xx) ; ret (22)  ->  ljmp X (02 xx xx) ; nop (00)
    fw[off:off + 4] = bytes([0x02, target >> 8, target & 0xFF, 0x00])
    print(f'  0x{code_addr:04x} (flash 0x{off:04x}): lcall 0x{target:04X}; ret'
          f'  ->  ljmp 0x{target:04X}; nop')

# checksum de codigo (BE, suma del codigo)
cs_off = HEADER_LEN + CODE_LEN + 2
cs = sum(fw[HEADER_LEN:HEADER_LEN + CODE_LEN]) & 0xFFFF
fw[cs_off] = cs >> 8
fw[cs_off + 1] = cs & 0xFF

open(OUT, 'wb').write(fw)
print(f'checksum -> {cs:04X}, {len(fw)} bytes -> {OUT}')
