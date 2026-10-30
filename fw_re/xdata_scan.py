#!/usr/bin/env python3
"""Escaneo de accesos XDATA en el code space del MS2131.
Patrones: MOV DPTR,#imm16 (90 hi lo) + MOVX @DPTR,A (f0) => escritura
          MOV DPTR,#imm16 (90 hi lo) + MOVX A,@DPTR (e0) => lectura
          SDCC a veces usa MOV DPL,#imm (75 82 lo) + MOV DPH,#imm (75 83 hi)
Ventana: DPTR-load .. MOVX con <=12 bytes intermedios (sin otro load DPTR).
"""
import sys

code = open('fw_re/code_original.bin','rb').read()

def scan(targets):
    """targets: {addr16: nombre} — imprime sitios de acceso"""
    hits = {name: [] for name in targets.values()}
    n = len(code)
    for i in range(n - 3):
        # patron A: 90 hi lo
        if code[i] == 0x90:
            hi, lo = code[i+1], code[i+2]
            addr = (hi << 8) | lo
            if addr not in targets: continue
            # buscar MOVX en ventana
            for j in range(i+3, min(i+16, n)):
                if code[j] == 0xF0:
                    hits[targets[addr]].append((i, 'W', j-i))
                    break
                if code[j] == 0xE0:
                    hits[targets[addr]].append((i, 'R', j-i))
                    break
                if code[j] == 0x90 or (code[j] == 0x75 and code[j+1] in (0x82, 0x83)):
                    break  # otro load de DPTR — abortar
        # patron B: 75 82 lo ... 75 83 hi (o al reves) — raro, lo cubrimos con DPL then DPH
        if code[i] == 0x75 and code[i+1] == 0x82:
            lo = code[i+2]
            # DPH en ventana
            for j in range(i+3, min(i+10, n-3)):
                if code[j] == 0x75 and code[j+1] == 0x83:
                    hi = code[j+2]
                    addr = (hi << 8) | lo
                    if addr not in targets: break
                    for k in range(j+3, min(j+14, n)):
                        if code[k] == 0xF0:
                            hits[targets[addr]].append((i, 'W', k-i)); break
                        if code[k] == 0xE0:
                            hits[targets[addr]].append((i, 'R', k-i)); break
                        if code[k] in (0x90,) or (code[k] == 0x75 and code[k+1] in (0x82,0x83)):
                            break
                    break
    return hits

targets = {
    0xF120: 'F120 (wrapper lee "hact")',
    0xF121: 'F121',
    0x22E4: '22E4 (gate wrapper: refresh?)',
    0x22E5: '22E5',
    0x268C: '268C (wrapper compara "fmt")',
    0x1AE2: '1AE2 (descriptor f604/ancho IN)',
    0x1AEA: '1AEA (descriptor f606/ancho captura)',
    0x1AE6: '1AE6 (hactive clamp)',
    0x1AAD: '1AAD (pclk medido)',
    0x1AB1: '1AB1 (clase pclk)',
    0x22B8: '22B8 (struct timing RX)',
    0x22DE: '22DE (hactive RX)',
    0xF606: 'F606 (ancho captura scaler)',
    0xF60E: 'F60E (wrapper escribe aqui!)',
    0xF65C: 'F65C (rescale H)',
}

for name in sorted(set(targets.values())):
    pass

hits = scan(targets)
for name, sites in sorted(hits.items()):
    if sites:
        print(f"\n== {name}: {len(sites)} accesos ==")
        for off, rw, gap in sites[:20]:
            print(f"  0x{off:04X} {rw} (movx a +{gap})")
    else:
        print(f"\n== {name}: SIN ACCESOS DIRECTOS (indirecto via helpers) ==")
