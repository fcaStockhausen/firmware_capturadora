#!/usr/bin/env python3
"""ms2131_formatguard v3 — v2 + pausa HID mientras hay clientes streameando.

Lección del 29/10 (ver CASUISTICA.md, runs A/B): toda presencia HID sobre
la MS2131 mientras streamea audio molesta al isoch —
  - open/close por poll (v2, cada 2s): ~1 INPUT GAP/min de ~100ms
  - interfaz mantenida abierta (watch residente): stutter CONTINUO
    (~3.5 gaps/s de 180-290ms) — descartado
  - sin HID: 0 gaps

v3: si hay un cliente de A/V corriendo (scalapp), el guard NO toca el
dispositivo (pausa HID): el streaming queda limpio y el formato lo
renegocia el propio cliente al abrir (scalapp pide modo exacto). Sin
clientes, vigilancia HID pura como v2 (detección [22DE:DF], fix via
setformat con watchdog, backoff anti-guerra).

v2 se mantenía en tools/ms2131_formatguard_v2.py.bak.
"""
import subprocess
import time
import os
import signal

DIR = os.path.dirname(os.path.abspath(__file__))
SETFMT = f"{DIR}/ms2131_setformat"
XDATA = f"{DIR}/ms213x_xdata"
COOLDOWN = 30
FIX_TIMEOUT = 15
# Clientes cuya presencia pausa el HID (el isoch del audio manda)
CLIENTES = ["scalapp"]

def log(msg):
    with open("/tmp/ms2131_formatguard.log", "a") as f:
        f.write(f"{time.strftime('%H:%M:%S')} {msg}\n")

def hid_read(addr):
    try:
        r = subprocess.run([XDATA, "read", f"{addr:04x}"], capture_output=True,
                           text=True, timeout=8).stdout
        return int(r.split("= ")[1].split()[0], 16)
    except Exception:
        return None

def cliente_activo():
    """True si algún cliente de la capturadora está streameando.
    pgrep no toca el dispositivo: gratis para el isoch."""
    for nombre in CLIENTES:
        if subprocess.run(["pgrep", "-x", nombre],
                          capture_output=True).returncode == 0:
            return True
    return False

def entrada_es_1080p():
    b8, b9 = hid_read(0x22B8), hid_read(0x22B9)
    if b8 is None or b9 is None:
        return False
    return (b8 << 8) | b9 == 1920   # [22B8]=hi, [22B9]=lo (BE)

def formato_fw():
    """Formato activo segun el firmware ([22DE:DF], BE: hi en 22DE)."""
    de, df = hid_read(0x22DE), hid_read(0x22DF)
    if de is None or df is None:
        return None
    return (de << 8) | df

def aplicar_fix_con_watchdog():
    """Corre setformat; si cuelga >FIX_TIMEOUT, lo mata y reporta."""
    try:
        p = subprocess.Popen([SETFMT], stdout=subprocess.DEVNULL,
                             stderr=subprocess.DEVNULL, start_new_session=True)
        try:
            p.wait(timeout=FIX_TIMEOUT)
            return p.returncode == 0
        except subprocess.TimeoutExpired:
            os.killpg(os.getpgid(p.pid), signal.SIGKILL)
            log("setformat colgado >15s — matado por watchdog")
            return False
    except Exception as e:
        log(f"error lanzando setformat: {e}")
        return False

log("formatguard v3 iniciado (pausa HID con clientes + watchdog)")
last_fix = 0.0
backoff_until = 0.0        # si Discord insiste, nos retiramos un rato
last_stable = 0.0
consecutive = 0
pausado = False
while True:
    if cliente_activo():
        if not pausado:
            log("cliente activo (scalapp) — pausa HID: no tocar el device")
            pausado = True
        time.sleep(5)
        continue
    if pausado:
        log("sin clientes — vigilancia HID reanudada")
        pausado = False
    fmt = formato_fw()
    now = time.time()
    # 1280 = drop a 720p. Solo actuar con entrada 1080p, pasado el cooldown
    # y NO estando en backoff (guerra con Discord = renegociaciones que
    # glitchean el audio — mejor ceder durante el streameo).
    if fmt == 1280 and now - last_fix > COOLDOWN and now > backoff_until:
        if entrada_es_1080p():
            log("drop detectado ([22DE]=1280, entrada 1080p) — setformat")
            if aplicar_fix_con_watchdog():
                last_fix = now
                # si el fix anterior fue hace <90s, Discord está insistiendo:
                # contar y entrar en backoff progresivo (2, 5, 10 min)
                if now - last_stable < 90:
                    consecutive += 1
                    wait = min(600, 120 * consecutive)
                    backoff_until = now + wait
                    log(f"Drop persistente x{consecutive} — retiro {wait}s (guerra evitada)")
                else:
                    consecutive = 0
            else:
                last_fix = now - COOLDOWN + 10  # reintento en 10s
    elif fmt == 1920:
        last_stable = now
    time.sleep(2)
