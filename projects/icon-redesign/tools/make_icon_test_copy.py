"""Build "formZ icon-test.app" beside the installed formZ.app.

Every 48 x 48 px Cic_<id>.ENU.bmp / .Dark.ENU.bmp is replaced by a 96 x 96 px
copy (each pixel doubled) with a 1 px magenta frame and a 6 x 6 px magenta
corner mark. Inside formZ this shows, in one look:
  - icon unchanged          -> the file was not loaded from Icons/
  - icon twice as large     -> formZ sizes icons from the bitmap
  - same size, hairline frame -> formZ scales to the button; 2x art works on Retina
The installed app is only read. Standard library only.
"""
import os
import struct
import subprocess
import sys

APP_DIR = sys.argv[1] if len(sys.argv) > 1 else "/Applications/formZ 10/formZ 10.0 pro"
SRC = os.path.join(APP_DIR, "formZ.app")
DST = os.path.join(APP_DIR, "formZ icon-test.app")
ICONS = os.path.join(DST, "Contents", "Resources", "Icons")
MARK = (255, 0, 255, 255)  # RGBA


def read_bmp(path):
    d = open(path, "rb").read()
    off, = struct.unpack_from("<I", d, 10)
    hsize, w, h, _, bpp, comp = struct.unpack_from("<IiiHHI", d, 14)
    if hsize != 40 or bpp != 32 or comp != 0:
        return None
    rows = []
    for r in range(abs(h)):
        start = off + r * w * 4
        rows.append([tuple(d[start + i * 4:start + i * 4 + 4]) for i in range(w)])  # BGRA
    if h > 0:
        rows.reverse()  # stored bottom-up; keep top-down in memory
    return w, abs(h), rows


def write_bmp(path, w, h, rows):
    body = b"".join(bytes(c for px in row for c in px) for row in reversed(rows))
    header = struct.pack("<2sIHHI", b"BM", 54 + len(body), 0, 0, 54)
    info = struct.pack("<IiiHHIIiiII", 40, w, h, 1, 32, 0, len(body), 2835, 2835, 0, 0)
    open(path, "wb").write(header + info + body)


def marked_double(rows):
    out = [[px for px in row for _ in (0, 1)] for row in rows for _ in (0, 1)]
    n = len(out)
    b, g, r, a = MARK[2], MARK[1], MARK[0], MARK[3]
    for y in range(n):
        for x in range(n):
            if x in (0, n - 1) or y in (0, n - 1) or (x < 6 and y < 6):
                out[y][x] = (b, g, r, a)
    return out


if not os.path.isdir(os.path.join(SRC, "Contents", "Resources", "Icons")):
    sys.exit(f"missing {SRC}")
if os.path.exists(DST):
    sys.exit(f"{DST} already exists; remove it first")

subprocess.run(["ditto", SRC, DST], check=True)
changed = skipped = 0
for name in sorted(os.listdir(ICONS)):
    if not (name.startswith("Cic_") and name.endswith(".ENU.bmp")):
        continue
    path = os.path.join(ICONS, name)
    bmp = read_bmp(path)
    if not bmp or bmp[:2] != (48, 48):
        skipped += 1
        continue
    write_bmp(path, 96, 96, marked_double(bmp[2]))
    changed += 1
print(f"built {DST}: {changed} icons doubled and marked, {skipped} left as is")
