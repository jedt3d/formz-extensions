import formzPythonInterface as fz
import os, sys

# Writes everything the formZ Python module exposes to fz_api_dump.txt beside this script,
# so later scripts are written against the real API instead of guesses.

def dump(out, title, thing):
	out.write("\n=== %s  (%s)\n" % (title, type(thing).__name__))
	for name in dir(thing):
		if name.startswith("__"):
			continue
		try:
			doc = getattr(thing, name).__doc__
		except Exception as e:
			doc = "<error: %s>" % e
		out.write("  %-28s %s\n" % (name, (doc or "").strip().replace("\n", " | ")))

def fzMain():
	path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "fz_api_dump.txt")
	out = open(path, "w")
	out.write("python %s\n" % sys.version)
	dump(out, "module fz", fz)
	dump(out, "xyz", fz.xyz(1.0, 2.0, 3.0))

	obj = fz.cube([0.0, 0.0, 0.0], [10.0, 10.0, 10.0])
	dump(out, "object", obj)
	try:
		face = obj.face(0)
		dump(out, "face", face)
		for attr in ("loop", "normal", "centerOfGravity", "area"):
			try:
				val = getattr(face, attr)()
				out.write("\nface.%s() -> %r\n" % (attr, val))
				if attr == "loop":
					dump(out, "loop", val)
			except Exception as e:
				out.write("\nface.%s() failed: %s\n" % (attr, e))
		for attr in ("vertexList", "faceList", "extents", "boundingBox"):
			try:
				val = getattr(obj, attr)()
				out.write("\nobj.%s() -> %r\n" % (attr, val))
				if attr == "vertexList" and len(val):
					dump(out, "vertex", val[0])
			except Exception as e:
				out.write("\nobj.%s() failed: %s\n" % (attr, e))
	except Exception as e:
		out.write("\nface probing failed: %s\n" % e)
	out.close()
