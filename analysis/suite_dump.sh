#!/bin/bash
# suite_dump.sh — volcado completo del scaler + metrica H/V en un solo paso
# Uso: suite_dump.sh <nombre>   (guarda analysis/suite_<nombre>.txt + mide H/V)
X=tools/ms213x_xdata
NAME="$1"
T=/private/var/folders/6l/cd74g2tj2zzgqn2mymf5qzdh0000gn/T/opencode
OUT="analysis/suite_${NAME}.txt"
{
echo "=== SUITE $NAME ($(date +%H:%M:%S)) ==="
echo "refresh=$($X read 0x22BE 2>/dev/null) $($X read 0x22BF 2>/dev/null)  entrada=$($X read 0x22B8 2>/dev/null)$($X read 0x22B9 2>/dev/null)x$($X read 0x22BA 2>/dev/null)$($X read 0x22BB 2>/dev/null)  formato=$($X read 0x22DE 2>/dev/null)$($X read 0x22DF 2>/dev/null)"
for R in F600 F604 F606 F60C F60E F618 F61A F620 F622 F624 F65B F65C F65D F660 F662 F6B4 F6C0 F6C1 F6C2 F6C3; do
  L=$($X read 0x$R 2>/dev/null | awk '{print $NF}')
  H=$($X read 0x$(printf 'F%03X' $((0x$R + 1))) 2>/dev/null | awk '{print $NF}')
  printf "%s=%s%s " "$R" "${L#0x}" "${H#0x}"
done
echo ""
} | tee "$OUT"
ffmpeg -hide_banner -loglevel error -f avfoundation -framerate 30 -video_size 1920x1080 -i "0" -frames:v 1 -y "$T/suite_${NAME}.png" 2>/dev/null
[ ! -f "$T/suite_${NAME}.png" ] && ffmpeg -hide_banner -loglevel error -f avfoundation -framerate 30 -video_size 1920x1080 -probesize 50M -i "0" -frames:v 1 -y "$T/suite_${NAME}.png" 2>/dev/null
python3 -c "
from PIL import Image
import numpy as np
img = np.asarray(Image.open('$T/suite_${NAME}.png').convert('L'), dtype=float)
gy = np.abs(np.diff(img, axis=0)).mean(); gx = np.abs(np.diff(img, axis=1)).mean()
print(f'H/V ({NAME}): {gx/gy:.3f}')
" 2>/dev/null || echo "H/V: captura fallo"
