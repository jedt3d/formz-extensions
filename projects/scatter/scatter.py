try:
	import formzPythonInterface as fz
except ImportError:		# lets the geometry self-check at the bottom run outside formZ
	fz = None

import math, os, random, traceback

# Scatter: copies of the source objects placed at random points on the picked faces,
# each with a random size variation.
#   1. pick one or more objects, press "Set source"
#   2. pick the target objects (all their faces) or individual faces, press "Scatter"

LOG = os.path.join(os.path.dirname(os.path.abspath(__file__)), "scatter_log.txt")
sources = []


def scale_factor(variation):
	"""variation is 0.0-0.5 (the slider's 0-50%). Returns the size multiplier for one copy.

	This is the creative knob of the tool. Default: symmetric, so 30% gives 0.7x to 1.3x.
	Alternatives: grow only (1.0 + random.uniform(0, variation)), or
	random.triangular(1 - variation, 1 + variation) to keep most copies near original size.
	"""
	return 1.0 + random.uniform(-variation, variation)


def random_point(poly):
	"""Uniform random point inside a polygon given as [(x, y, z), ...] in loop order."""
	# ponytail: fan triangulation, correct for convex faces only; ear-clip if concave faces matter
	a = poly[0]
	tris = [(a, poly[i], poly[i + 1]) for i in range(1, len(poly) - 1)]
	weights = [tri_area(*t) for t in tris]
	a, b, c = random.choices(tris, weights)[0]
	s, t = math.sqrt(random.random()), random.random()
	return tuple(a[k] * (1 - s) + b[k] * s * (1 - t) + c[k] * s * t for k in range(3))


def tri_area(a, b, c):
	u = [b[k] - a[k] for k in range(3)]
	v = [c[k] - a[k] for k in range(3)]
	n = (u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0])
	return 0.5 * math.sqrt(sum(x * x for x in n))


def face_polygon(face):
	"""Outer loop of a face as a list of (x, y, z)."""
	poly = []
	edge = face.loop().edge()
	while edge and len(poly) < 10000:
		p = edge.vertex1().xyz()
		poly.append((p.x, p.y, p.z))
		edge = edge.next()
	return poly


def place(obj, point, normal, factor):
	"""Scale obj, then move it so its bounding box rests on point, on the normal's side."""
	obj.scaleLocal([factor, factor, factor])
	lo, hi = obj.extents()
	lo, hi = (lo.x, lo.y, lo.z), (hi.x, hi.y, hi.z)
	n = (normal.x, normal.y, normal.z)
	# the bounding box point that touches the face: its center pushed back along the normal
	reach = sum(abs(n[k]) * (hi[k] - lo[k]) / 2.0 for k in range(3))
	anchor = [(lo[k] + hi[k]) / 2.0 - n[k] * reach for k in range(3)]
	obj.move([point[k] - anchor[k] for k in range(3)])


def log(text):
	with open(LOG, "a") as f:
		f.write(text + "\n")


def setSource(panel, message):
	global sources
	if message == 0:
		sources = [e for e in fz.pickList() if e.__class__.__name__ != "face"]
		log("source: %d object(s)" % len(sources))
		return 1
	return 0


def scatter(panel, message):
	if message != 0:
		return 0
	try:
		count = int(panel.getValue(1))
		variation = float(panel.getValue(2)) / 100.0
		# picked faces are used as they are; a picked object contributes all of its faces
		faces = []
		picked = fz.pickList()
		for e in picked:
			if e.__class__.__name__ == "face":
				faces.append(e)
			elif e not in sources:
				faces.extend(e.faceList())
		if not sources or not faces:
			log("nothing done: %d source object(s), %d target face(s), picked: %s"
				% (len(sources), len(faces), [e.__class__.__name__ for e in picked]))
			return 1
		polys = [(f, face_polygon(f)) for f in faces]
		polys = [(f, p) for f, p in polys if len(p) >= 3]
		areas = [f.area() for f, p in polys]
		for i in range(count):
			face, poly = random.choices(polys, areas)[0]
			copy = random.choice(sources).copy()
			place(copy, random_point(poly), face.normal(), scale_factor(variation))
		log("scattered %d copies on %d face(s), variation %.0f%%" % (count, len(polys), variation * 100))
	except Exception:
		log(traceback.format_exc())
	return 1


def fzMain():
	panel = fz.uiPanel("Scatter")
	panel.slider(1, "Copies", 20, 1, 200)
	panel.slider(2, "Size variation %", 25, 0, 50)
	panel.button(3, "Set source (picked objects)", "setSource")
	panel.button(4, "Scatter (on picked objects/faces)", "scatter")
	panel.presentPalette()


if __name__ == "__main__":
	square = [(0, 0, 5), (10, 0, 5), (10, 10, 5), (0, 10, 5)]
	for _ in range(2000):
		x, y, z = random_point(square)
		assert 0 <= x <= 10 and 0 <= y <= 10 and abs(z - 5) < 1e-9
		assert 0.5 <= scale_factor(0.5) <= 1.5
	assert scale_factor(0.0) == 1.0
	print("scatter self-check ok")
