"""Write an HTML contact sheet: formZ's original icon beside the new one,
with icon number, name and group, for review. Standard library only.

usage: python3 contact_sheet.py <formZ Icons dir> <built Icons dir> <manifest.csv> <out.html>

Both columns are drawn at the same size on formZ's light grey button colour,
at 2x (Retina) and 1x. The page embeds formZ's original artwork: keep it
local (build/ is ignored), do not publish it.
"""
import base64
import csv
import html
import os
import struct
import sys
import zlib

src_dir, built_dir, manifest, out = sys.argv[1:5]


def read_bmp(path):
    d = open(path, 'rb').read()
    off, = struct.unpack_from('<I', d, 10)
    w, h = struct.unpack_from('<ii', d, 18)
    bpp, = struct.unpack_from('<H', d, 28)
    step = bpp // 8
    pad = (4 - (w * step) % 4) % 4 if step == 3 else 0
    rows = []
    for r in range(abs(h)):
        start = off + r * (w * step + pad)
        row = bytearray()
        for x in range(w):
            b, g, rr = d[start + x * step:start + x * step + 3]
            a = d[start + x * step + 3] if step == 4 else 255
            row += bytes((rr, g, b, a))
        rows.append(bytes(row))
    if h > 0:
        rows.reverse()
    return w, abs(h), rows


def png_uri(w, h, rows):
    def chunk(tag, data):
        return struct.pack('>I', len(data)) + tag + data + struct.pack('>I', zlib.crc32(tag + data))
    raw = b''.join(b'\x00' + r for r in rows)
    png = (b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 6, 0, 0, 0))
           + chunk(b'IDAT', zlib.compress(raw, 9)) + chunk(b'IEND', b''))
    return 'data:image/png;base64,' + base64.b64encode(png).decode()


def img(path, size):
    if not os.path.exists(path):
        return '<div class="missing">not built</div>'
    w, h, rows = read_bmp(path)
    return f'<img src="{png_uri(w, h, rows)}" width="{size}" height="{size}" alt="">'


entries = list(csv.DictReader(open(manifest)))
cards = []
for e in entries:
    name = f'Cic_{e["id"]}.ENU.bmp'
    old, new = os.path.join(src_dir, name), os.path.join(built_dir, name)
    cards.append(
        f'<figure><div class="pair"><div><span>formZ now</span>{img(old, 96)}</div>'
        f'<div><span>new 2&times;</span>{img(new, 96)}</div>'
        f'<div class="small"><span>new 1&times;</span>{img(new, 48)}</div>'
        f'<div><span>overlay</span><div class="ov">{img(old, 96)}{img(new, 96)}</div></div></div>'
        f'<figcaption><b>{html.escape(e["id"])}</b> {html.escape(e["name"])}'
        f'<small>{html.escape(e["group"])} &middot; batch {html.escape(e["batch"])}</small></figcaption></figure>')

built = sum(os.path.exists(os.path.join(built_dir, f'Cic_{e["id"]}.ENU.bmp')) for e in entries)
total = sum(1 for f in os.listdir(src_dir) if f.startswith('Cic_') and f.endswith('.ENU.bmp') and '.Dark.' not in f)
page = f'''<!doctype html><meta charset="utf-8"><title>formZ icon contact sheet</title>
<style>
body{{font:13px -apple-system,Helvetica,sans-serif;margin:16px;background:#f4f5f7;color:#1f3550}}
h1{{font-size:18px;margin:0 0 4px}} p{{margin:0 0 14px;color:#555}}
main{{display:grid;grid-template-columns:repeat(auto-fill,minmax(420px,1fr));gap:10px}}
figure{{margin:0;background:#fff;border:1px solid #dde;border-radius:6px;padding:8px}}
.pair{{display:flex;gap:6px;align-items:flex-end}}
.pair div{{background:#d9d9d9;border-radius:4px;padding:4px;text-align:center}}
.pair span{{display:block;font-size:10px;color:#555;margin-bottom:2px}}
img{{display:block;margin:auto;image-rendering:auto}}
.ov{{position:relative;width:96px;height:96px}} .ov img{{position:absolute;inset:0}} .ov img+img{{opacity:.5}}
.missing{{width:96px;height:96px;display:grid;place-items:center;color:#a00;font-size:11px}}
figcaption{{margin-top:6px}} figcaption small{{display:block;color:#777}}
</style>
<h1>formZ icon contact sheet</h1>
<p>{built} of {len(entries)} listed icons built &middot; {total} light-mode icons in formZ in total</p>
<main>{"".join(cards)}</main>'''
open(out, 'w').write(page)
print(f'wrote {out}: {len(entries)} icons, {built} built')
