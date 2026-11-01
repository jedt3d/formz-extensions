"""Generate masters/Cic_3169.svg: a symmetric arrow, rotated to the cursor
angle, then extruded toward the bottom right. Standard library only.
usage: python3 pick_arrow.py > ../masters/Cic_3169.svg
"""
import math

N, TOP, SIDE_R, SIDE_D = '#1F3550', '#8EC3EE', '#2F6DB0', '#4F95D6'
ANGLE = -32          # degrees; negative turns the tip toward the upper left
DEPTH = (3.0, 2.6)   # extrusion offset in grid units
MARGIN = 3.5

# Half outline, tip first, mirrored about the vertical axis (tip points up).
half = [(0, -20), (11.5, 1.5), (4, -0.5), (4, 17)]
shape = half + [(-x, y) for x, y in reversed(half[1:])]

a = math.radians(ANGLE)
pts = [(x * math.cos(a) - y * math.sin(a), x * math.sin(a) + y * math.cos(a)) for x, y in shape]

# Fit arrow plus extrusion inside the 48-unit artboard, centred.
xs = [x for x, _ in pts] + [x + DEPTH[0] for x, _ in pts]
ys = [y for _, y in pts] + [y + DEPTH[1] for _, y in pts]
s = min((48 - 2 * MARGIN) / (max(xs) - min(xs)), (48 - 2 * MARGIN) / (max(ys) - min(ys)))
cx, cy = (max(xs) + min(xs)) / 2, (max(ys) + min(ys)) / 2
pts = [(24 + (x - cx) * s, 24 + (y - cy) * s) for x, y in pts]
o = (DEPTH[0] * s, DEPTH[1] * s)

area = sum(p[0] * q[1] - q[0] * p[1] for p, q in zip(pts, pts[1:] + pts[:1]))
sign = 1 if area > 0 else -1  # >0: clockwise on screen (y down)


def f(p):
    return f'{p[0]:.2f} {p[1]:.2f}'


sides = []
for p, q in zip(pts, pts[1:] + pts[:1]):
    nx, ny = sign * (q[1] - p[1]), -sign * (q[0] - p[0])  # outward normal
    if nx * o[0] + ny * o[1] > 0:  # edge faces the extrusion: visible side
        colour = SIDE_R if nx > ny else SIDE_D
        pp, qq = (p[0] + o[0], p[1] + o[1]), (q[0] + o[0], q[1] + o[1])
        sides.append(f'<path d="M{f(p)} L{f(q)} L{f(qq)} L{f(pp)} Z" fill="{colour}" stroke="{N}" stroke-width="1.4" stroke-linejoin="round"/>')

stroke = f'stroke="{N}" stroke-linejoin="round" stroke-linecap="round"'
back = 'M' + ' L'.join(f((x + o[0], y + o[1])) for x, y in pts) + ' Z'
top = 'M' + ' L'.join(f(p) for p in pts) + ' Z'
print('<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 48 48" width="48" height="48">'
      f'<path d="{back}" fill="{SIDE_R}" {stroke} stroke-width="2"/>'
      + ''.join(sides)
      + f'<path d="{top}" fill="{TOP}" {stroke} stroke-width="2"/></svg>')
