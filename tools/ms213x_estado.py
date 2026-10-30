#!/usr/bin/env python3
"""ms213x_estado — deteccion estandarizada de la capturadora MS2131.

Busca por VID:PID (estable) en TODAS sus personas:
  firmware USB3 : 345f:2131  ("USB3 Video")
  firmware USB2 : 345f:2131  ("USB2 Video")
  ROM de fabrica: 534d:2130  ("USB Video")

Reporta: persona, velocidad, puerto, topologia (directo/hub), AVFoundation,
HID y registros basicos. Una sola llamada = diagnostico completo.
"""
import re
import subprocess
import sys

VID_FW, PID_FW = 0x345F, 0x2131
VID_ROM, PID_ROM = 0x534D, 0x2130

def ioreg_usb():
    r = subprocess.run(['ioreg', '-p', 'IOUSB', '-w', '0', '-l'],
                       capture_output=True, text=True, timeout=15)
    return r.stdout.splitlines()

def parse_devices(lines):
    """Extrae cada nodo USB con su profundidad, nombre, VID/PID y velocidad."""
    devs = []
    cur = None
    for ln in lines:
        m = re.search(r'([| +\-]*)\+-o ([^@]+)@([0-9a-f]+)', ln)
        if m:
            depth = m.group(1).count('|') + (len(m.group(1)) - m.group(1).count('|')) // 4
            cur = {'name': m.group(2).strip(), 'port': m.group(3),
                   'depth': depth, 'vid': None, 'pid': None, 'speed': None}
            devs.append(cur)
            continue
        if cur is not None:
            mv = re.search(r'"idVendor" = (\d+)', ln)
            mp = re.search(r'"idProduct" = (\d+)', ln)
            ms = re.search(r'"USB Speed" = (\d+)', ln)
            if mv: cur['vid'] = int(mv.group(1))
            if mp: cur['pid'] = int(mp.group(1))
            if ms: cur['speed'] = int(ms.group(1))
    return devs

def main():
    lines = ioreg_usb()
    devs = parse_devices(lines)
    found = []
    for d in devs:
        if (d['vid'], d['pid']) in ((VID_FW, PID_FW), (VID_ROM, PID_ROM)):
            kind = 'ROM (bootloader fabrica)' if d['vid'] == VID_ROM else 'FIRMWARE'
            found.append((d, kind))
        # hubs en el camino (para topologia)
    hubs = [d['name'] for d in devs if 'hub' in d['name'].lower()]

    if not found:
        print('ESTADO: NO ENUMERADA (ni firmware ni ROM)')
        return 1

    for d, kind in found:
        speed = {480: 'USB2 (480 Mbps)', 5000: 'USB3 (5 Gbps)'}.get(d['speed'], f"? ({d['speed']})")
        topo = 'DIRECTA al controlador' if d['depth'] <= 1 else f'via {d["depth"]-1} nivel(es) de hub'
        print(f'ESTADO : {kind}')
        print(f'  nombre     : {d["name"]}')
        print(f'  VID:PID    : {d["vid"]:04x}:{d["pid"]:04x}')
        print(f'  velocidad  : {speed}')
        print(f'  puerto     : @{d["port"]} ({topo})')

    # AVFoundation
    r = subprocess.run(['ffmpeg', '-hide_banner', '-f', 'avfoundation',
                        '-list_devices', 'true', '-i', ''],
                       capture_output=True, text=True, timeout=15)
    av = [l.strip() for l in (r.stderr or '').splitlines() if 'USB' in l and 'Video' in l]
    print(f'AVFoundation: {"OK -> " + av[0] if av else "NO visible"}')

    # HID (solo persona firmware)
    if found[0][1] == 'FIRMWARE':
        r = subprocess.run(['tools/ms213x_xdata', 'read', '0x22BE'],
                           capture_output=True, text=True, timeout=10, cwd='.')
        if 'not found' in (r.stdout + r.stderr).lower():
            print('HID         : NO accesible')
        else:
            print(f'HID         : OK ({r.stdout.strip()})')
    else:
        print('HID         : N/A (modo ROM — usar tools/rom_flash)')
    return 0

if __name__ == '__main__':
    sys.exit(main())
