"""Write batch 1 masters (Shapes + Draw flyouts) in the approved style.

Arc, circle and ellipse geometry, point positions and digit positions are
measured from formZ's own 48 px icons, so each new icon overlays its original.
Every digit is checked against lines and dots and pushed clear if it touches.
usage: python3 gen_batch1.py <masters dir>
"""
import math
import os
import sys

OUT = sys.argv[1]
N, Y, W, A, L = '#1F3550', '#F2C200', '#FFFFFF', '#E0362C', '#DCEBF7'
HELP, HANDLE = '#7FA3C8', '#6E8FB5'
ST = f'stroke="{N}" stroke-linejoin="round" stroke-linecap="round"'
FONT = 12.5                       # digit cap height ~9 units, as in formZ
DW, DH = 0.56 * FONT, 0.72 * FONT  # Helvetica Bold digit box
DOT_R, CLEAR = 3.4, 1.4            # dot radius; min gap between digit and ink


def svg(body):
    return f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 48 48" width="48" height="48">{body}</svg>'


def pt(x, y, c, r=DOT_R):
    return f'<circle cx="{x:.2f}" cy="{y:.2f}" r="{r}" fill="{c}" stroke="{N}" stroke-width="1.7"/>'


def line(x1, y1, x2, y2, c=N, w=2.4):
    return f'<line x1="{x1}" y1="{y1}" x2="{x2}" y2="{y2}" stroke="{c}" stroke-width="{w}" stroke-linecap="round"/>'


def on_circle(cx, cy, r, p):
    """Project a measured point onto the circle, returning (point, angle)."""
    a = math.atan2(p[1] - cy, p[0] - cx)
    return (cx + r * math.cos(a), cy + r * math.sin(a)), math.degrees(a)


def arc_path(cx, cy, r, a0, a1):
    """Clockwise (screen) arc from angle a0 to a1, degrees."""
    sweep = (a1 - a0) % 360
    x0, y0 = cx + r * math.cos(math.radians(a0)), cy + r * math.sin(math.radians(a0))
    x1, y1 = cx + r * math.cos(math.radians(a1)), cy + r * math.sin(math.radians(a1))
    return (f'<path d="M{x0:.2f} {y0:.2f} A{r} {r} 0 {1 if sweep > 180 else 0} 1 {x1:.2f} {y1:.2f}" '
            f'fill="none" {ST} stroke-width="2.6"/>')


def arc_samples(cx, cy, r, a0, a1):
    sweep = (a1 - a0) % 360
    return [(cx + r * math.cos(math.radians(a0 + sweep * k / 120)), cy + r * math.sin(math.radians(a0 + sweep * k / 120)))
            for k in range(121)]


def ellipse_samples(cx, cy, a, b, rot):
    t = math.radians(rot)
    return [(cx + a * math.cos(s) * math.cos(t) - b * math.sin(s) * math.sin(t),
             cy + a * math.cos(s) * math.sin(t) + b * math.sin(s) * math.cos(t))
            for s in (2 * math.pi * k / 200 for k in range(200))]


def label(text, cx, cy, ink, dots):
    """Digit centred near (cx, cy); nudged until clear of ink samples and dots."""
    def gap(x, y):
        x0, x1, y0, y1 = x - DW / 2, x + DW / 2, y - DH / 2, y + DH / 2
        def d(p, pad):
            dx = max(x0 - p[0], 0, p[0] - x1)
            dy = max(y0 - p[1], 0, p[1] - y1)
            return math.hypot(dx, dy) - pad
        return min([d(p, 1.3) for p in ink] + [d(p, DOT_R + 0.85) for p in dots])
    x, y = cx, cy
    if gap(x, y) < CLEAR:
        best = None
        for step in range(1, 41):  # spiral search, nearest clear spot wins
            r = 0.25 * step
            for k in range(16):
                a = 2 * math.pi * k / 16
                nx, ny = cx + r * math.cos(a), cy + r * math.sin(a)
                if 2 <= nx - DW / 2 and nx + DW / 2 <= 46 and 2 <= ny - DH / 2 and ny + DH / 2 <= 46 and gap(nx, ny) >= CLEAR:
                    best = (nx, ny)
                    break
            if best:
                break
        assert best, f'no clear spot for digit {text} near {cx},{cy}'
        x, y = best
    moved = math.hypot(x - cx, y - cy)
    if moved > 0.01:
        print(f'  digit {text}: moved {moved:.1f} units to clear the lines')
    return (f'<text x="{x:.2f}" y="{y + DH / 2:.2f}" font-family="Helvetica" font-weight="bold" '
            f'font-size="{FONT}" text-anchor="middle" fill="{N}">{text}</text>')


icons = {}

# --- Pilot 2D icons, retraced from formZ (measured dot centres and strokes) ----
icons[3025] = (f'<rect x="6.4" y="6.6" width="35.1" height="34.3" fill="{L}" {ST} stroke-width="2.2"/>'
               + pt(6.4, 6.6, Y) + pt(41.5, 40.9, A))
HEX_R, HEX_A0 = 20.0, -29  # pointy top; red vertex measured at (41.6, 14.4)
hexv = [(24 + HEX_R * math.cos(math.radians(HEX_A0 + 60 * k - 60)), 24 + HEX_R * math.sin(math.radians(HEX_A0 + 60 * k - 60)))
        for k in range(6)]
icons[3142] = (f'<path d="M{" L".join(f"{x:.2f} {y:.2f}" for x, y in hexv)} Z" fill="{L}" {ST} stroke-width="2.2"/>'
               + line(24, 24, *(round(v, 2) for v in hexv[1]), HELP, 1.8) + pt(24, 24, Y) + pt(*hexv[1], A))
c1_red, _ = on_circle(23.9, 23.7, 19.95, (41.6, 14.4))
icons[3038] = (f'<circle cx="23.9" cy="23.7" r="19.95" fill="{L}" {ST} stroke-width="2.2"/>'
               + line(23.9, 23.7, round(c1_red[0], 2), round(c1_red[1], 2), HELP, 1.8)
               + pt(23.9, 23.7, Y) + pt(*c1_red, A))
vline = [(5.9, 43.3), (41.6, 43.1), (42.3, 21.9), (24.0, 4.6), (5.7, 22.4)]
icons[3033] = (f'<polyline points="{" ".join(f"{x},{y}" for x, y in vline)}" fill="none" {ST} stroke-width="2.5"/>'
               + ''.join(pt(x, y, W) for x, y in vline[1:-1]) + pt(*vline[0], Y) + pt(*vline[-1], A))

# --- Shapes -----------------------------------------------------------------
icons[3152] = (f'<path d="M6 20 L33 6 L43 26 L17 40 Z" fill="{L}" {ST} stroke-width="2.2"/>'
               + pt(6, 20, Y) + pt(17, 40, W) + pt(43, 26, A))
icons[3039] = (f'<circle cx="24" cy="24" r="18" fill="{L}" {ST} stroke-width="2.2"/>'
               + line(9.26, 34.32, 38.74, 13.68, HELP, 1.8) + pt(9.26, 34.32, Y) + pt(38.74, 13.68, A))

C3 = (23.8, 23.8, 19.9)  # Circle 3: measured circle
(p1, _), (p2, _), (p3, _) = (on_circle(*C3, q) for q in [(6.4, 13.9), (38.5, 10.5), (32.5, 40.9)])
ink = arc_samples(*C3, 0, 359.9)
dots = [p1, p2, p3]
print('3040')
icons[3040] = (f'<circle cx="{C3[0]}" cy="{C3[1]}" r="{C3[2]}" fill="{L}" {ST} stroke-width="2.2"/>'
               + pt(*p1, Y) + pt(*p2, W) + pt(*p3, A)
               + label(1, 12, 20, ink, dots) + label(2, 30.5, 14.5, ink, dots) + label(3, 27, 33, ink, dots))

# Ellipse: centre at the white point, yellow on the major vertex, red on the minor vertex.
EC, EA, EB, ER = (24.6, 22.9), 25.8, 13.0, -45
ell = ellipse_samples(*EC, EA, EB, ER)
t = math.radians(ER)
major_lo = (EC[0] - EA * math.cos(t), EC[1] - EA * math.sin(t))   # lower left
major_hi = (EC[0] + EA * math.cos(t), EC[1] + EA * math.sin(t))   # upper right
minor_up = (EC[0] + EB * math.sin(t), EC[1] - EB * math.cos(t))   # upper left
ELL = (f'<ellipse cx="{EC[0]}" cy="{EC[1]}" rx="{EA}" ry="{EB}" transform="rotate({ER} {EC[0]} {EC[1]})" '
       f'fill="{L}" {ST} stroke-width="2.2"/>')
d1 = [major_lo, EC, minor_up]
print('3041')
icons[3041] = (ELL + pt(*major_lo, Y) + pt(*EC, W) + pt(*minor_up, A)
               + label(1, 13, 34, ell, d1) + label(2, 33, 18, ell, d1) + label(3, 7, 7, ell, d1))
d2 = [major_lo, major_hi, minor_up]
print('3042')
icons[3042] = (ELL + pt(*major_lo, Y) + pt(*major_hi, W) + pt(*minor_up, A)
               + label(1, 13, 34, ell, d2) + label(2, 34, 12, ell, d2) + label(3, 7, 7, ell, d2))

# --- Draw: lines and curves ---------------------------------------------------
icons[3269] = line(8, 40, 40, 8) + pt(8, 40, Y) + pt(40, 8, A)
icons[3376] = (f'<path d="M7 41 C10 8 26 2 34 24" fill="none" {ST} stroke-width="2.6"/>'
               + line(30, 5, 41, 41, HELP, 1.8) + pt(30, 5, HANDLE, 2.8) + pt(41, 41, HANDLE, 2.8)
               + pt(7, 41, Y) + pt(34.7, 23.3, A))
icons[3258] = (f'<path d="M7 42 C9 22 15 12 21 14 C28 16 31 34 38 32 C43 30 43 16 43 7" fill="none" {ST} stroke-width="2.6"/>'
               + pt(7, 42, Y) + pt(21, 14, W) + pt(38, 32, W) + pt(43, 7, A))
icons[3257] = (f'<polyline points="7,7 42,7 7,41 42,41" fill="none" stroke="{HELP}" stroke-width="1.6" stroke-linejoin="round"/>'
               + f'<path d="M7 7 C30 7 36 10 24 24 C12 38 18 41 42 41" fill="none" {ST} stroke-width="2.6"/>'
               + pt(42, 7, HANDLE, 2.8) + pt(7, 41, HANDLE, 2.8) + pt(24, 24, W) + pt(7, 7, Y) + pt(42, 41, A))
stream = [(7, 7), (24, 6), (39, 11), (41, 23), (25, 26), (9, 30), (12, 41), (28, 37), (42, 42)]
icons[3034] = (f'<polyline points="{" ".join(f"{x},{y}" for x, y in stream)}" fill="none" {ST} stroke-width="2.4"/>'
               + ''.join(pt(x, y, W, 2.8) for x, y in stream[1:-1]) + pt(*stream[0], Y) + pt(*stream[-1], A))


# --- Draw: arcs (measured from formZ) -----------------------------------------
def arc_icon(circle, left, right, marks, digits, extra=''):
    """circle=(cx,cy,r); left/right: measured arc end points (arc runs clockwise
    from left over the top to right); marks: [(point or 'L'/'R'/'T', colour)];
    digits: [(text, x, y)] at formZ's measured digit centres."""
    (lp, la), (rp, ra) = on_circle(*circle, left), on_circle(*circle, right)
    ink = arc_samples(*circle, la, ra)
    where = {'L': lp, 'R': rp, 'T': (circle[0], circle[1] - circle[2])}
    snapped = [(where.get(p, p), c) for p, c in marks]
    dots = [p for p, _ in snapped]
    return (arc_path(*circle, la, ra) + extra + ''.join(pt(*p, c) for p, c in snapped)
            + ''.join(label(t, x, y, ink, dots) for t, x, y in digits))


ARC = (24.0, 25.1, 19.9)
LEFT, RIGHT = (9.0, 38.2), (39.0, 38.2)
CENTRE = (23.8, 24.2)
for i, marks, digits, extra in [
    (3037, [(CENTRE, Y), ('R', W), ('L', A)], [(1, 23.5, 13.5), (2, 30.5, 36.5), (3, 17.5, 38.5)], ''),
    (3036, [('L', Y), (CENTRE, W), ('R', A)], [(1, 11.5, 27.5), (2, 24, 15), (3, 35.5, 27)], ''),
    (3035, [('R', Y), (CENTRE, W), ('L', A)], [(1, 31, 38), (2, 24, 14), (3, 17.5, 38.5)],
     f'<path d="M14.5 17 Q11 20.5 11.3 26" fill="none" stroke="{A}" stroke-width="2.2" stroke-linecap="round"/>'
     f'<path d="M8.3 24.2 L11.4 30.4 L14.4 24.4 Z" fill="{A}"/>'),
    (3131, [('L', Y), ('T', W), ('R', A)], [(1, 31, 38), (2, 23.8, 16), (3, 17.5, 38)], ''),
]:
    print(i)
    icons[i] = arc_icon(ARC, LEFT, RIGHT, marks, digits, extra)
print(3174)
icons[3174] = arc_icon((24.0, 24.6, 19.7), LEFT, (39.2, 37.8), [('L', Y), ('R', W), ('T', A)],
                       [(1, 17, 38), (2, 30.5, 37.5), (3, 24, 15.5)])
print(3245)
icons[3245] = arc_icon((26.2, 26.0, 22.0), (9.1, 40.0), (41.0, 10.0), [('L', Y), ('R', W), ((25.4, 25.4), A)],
                       [(1, 16.5, 38.5), (2, 41, 20), (3, 32, 35)])

for i, body in sorted(icons.items()):
    open(os.path.join(OUT, f'Cic_{i}.svg'), 'w').write(svg(body))
print(f'wrote {len(icons)} masters')
