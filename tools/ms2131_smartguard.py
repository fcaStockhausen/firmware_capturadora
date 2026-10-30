#!/usr/bin/env python3
"""Guard inteligente MS2131:
- Lee el formato UVC activo (AVFoundation) y el estado del scaler (HID).
- Si la entrada es 1080p120 y el firmware diezmó el ancho (f606 = formato/2),
  lo restaura al ancho completo del formato EN CALIENTE (stop->config->start).
- No fuerza formatos (guerra con Discord) ni toca casos ambiguos.

Casos cubiertos: 1920x1080 (f606==960 -> 1920) y 1280x720 (f606==640 -> 1280).
Log: /tmp/ms2131_guard.log
"""
import subprocess, time, sys, os

DIR = os.path.dirname(os.path.abspath(__file__))
XDATA = f'{DIR}/ms213x_xdata'
SETFMT = f'{DIR}/ms2131_setformat'

def xdata(*args):
    return subprocess.run([XDATA, *args], capture_output=True, text=True).stdout

def read(addr):
    out = xdata('read', f'{addr:04x}')
    try:
        return int(out.split('= ')[1], 16)
    except (IndexError, ValueError):
        return None

def write(addr, val):
    xdata('write', f'{addr:04x}', f'0x{val:02x}')

def active_format():
    out = subprocess.run([SETFMT, '--status'], capture_output=True, text=True).stdout
    for w, h in [(1920,1080),(1280,720),(2560,1440),(1600,1200),(1360,768),
                 (1280,1024),(1280,960),(1024,768),(800,600),(720,576),
                 (720,480),(640,480)]:
        if f'{w}x{h}' in out:
            return w, h
    return None

def apply_fix(width):
    write(0xf600, 0x00)
    lo, hi = width & 0xff, width >> 8
    for base in (0xf606, 0xf618, 0xf660):
        write(base, lo); write(base+1, hi)
    write(0xf65c, 0x10)
    write(0xf600, 0x01)

# mapa formato -> (ancho diezmado, ancho completo)
CASES = {(1920,1080): (960, 1920), (1280,720): (640, 1280)}

def log(msg):
    with open('/tmp/ms2131_guard.log', 'a') as f:
        f.write(f'{time.strftime("%H:%M:%S")} {msg}\n')

log('smartguard iniciado')
fails = 0
last_fmt_force = 0
FORCE_COOLDOWN = 20  # s entre re-fuerzos de formato (no pelear en loop con apps)
while True:
    try:
        fmt = active_format()
        # REFUERZO ANTI-DISCORD: si la entrada es 1080p pero el formato activo
        # cayo a 720p (Discord lo baja al iniciar), re-forzar 1080p60.
        if fmt == (1280, 720) and time.time() - last_fmt_force > FORCE_COOLDOWN:
            w_in = read(0x22b8)
            w_in2 = read(0x22b9)
            if w_in == 0x07 and w_in2 == 0x80:  # entrada 1920
                subprocess.run([SETFMT], capture_output=True, timeout=10)
                last_fmt_force = time.time()
                log('entrada 1080p + formato 720p (Discord?) -> re-forzado 1080p')
        if fmt in CASES:
            decimated, full = CASES[fmt]
            f606 = read(0xf606)
            f607 = read(0xf607)
            if f606 is not None and f607 is not None:
                w = f606 | (f607 << 8)
                if w == decimated:
                    apply_fix(full)
                    log(f'fix {fmt[0]}x{fmt[1]}: {decimated}->{full}')
        fails = 0
    except Exception as e:
        fails += 1
        if fails > 10:
            log(f'error: {e}')
            fails = 0
    time.sleep(0.3)
