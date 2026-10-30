#!/bin/zsh
# Experimento MS2131: snapshot del estado interno + frames + fps
# Uso: ./snapshot.sh <nombre>   (ej: ./snapshot.sh 1080p60)
set -e
NAME=$1
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
DIR="$ROOT/analysis/snap_${NAME}"
mkdir -p "$DIR"
echo "== snapshot: $NAME =="

"$ROOT/tools/ms213x_xdata" dump f000 f7ff "$DIR/xdata_fpage.bin"

python3 - "$DIR" << 'EOF'
import time, sys, cv2, numpy as np
outdir = sys.argv[1]
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
cap.set(cv2.CAP_PROP_FPS, 60)
ts, f = [], None
t_end = time.monotonic() + 4
while time.monotonic() < t_end:
    ret, f = cap.read()
    if ret:
        ts.append(time.monotonic())
if len(ts) > 2:
    d = np.diff(ts)
    print(f'frames={len(ts)} fps_medio={len(ts)/d.sum():.2f} delta_medio={d.mean()*1000:.1f}ms delta_p90={np.percentile(d,90)*1000:.1f}ms')
if f is not None:
    print(f'resolucion={f.shape[1]}x{f.shape[0]}')
for i in range(10):
    ret, f = cap.read()
    if ret:
        cv2.imwrite(f'{outdir}/frame_{i:02d}.png', f)
cap.release()
print('frames guardados')
EOF
echo "== listo: $DIR =="
