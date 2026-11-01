# Scatter

Python palette experiment for placing copies of picked objects on picked faces or objects. `fzMain()` creates a palette with Copies (1–200, default 20), Size variation (0–50%, default 25%), Set source, and Scatter controls.

## Use inside form·Z

Load `scatter.py` through form·Z's Python scripting interface and invoke `fzMain()`.

1. Pick source objects and press **Set source (picked objects)**.
2. Pick target objects or individual faces. A target object contributes all its faces; source objects are excluded from object targets.
3. Set the copy count and size variation, then press **Scatter (on picked objects/faces)**.

The copy count is total across the selected faces. Target faces are weighted by area; a source is chosen randomly for each copy. A variation of 25% gives a scale factor between 0.75 and 1.25. Sources are held in module state for that script session.

`scatter_log.txt` is written beside the script and is Git-ignored. It records source selection, scatter results, and exceptions. Use a disposable document for checks: Scatter adds copies to the current project.

## Standalone check

From the repository root:

```sh
python3 projects/scatter/scatter.py
```

The built-in check samples 2,000 points on a square and checks scale bounds. It uses only Python's standard library and prints `scatter self-check ok`. It does not require `formzPythonInterface`, and it does not validate host selection, edge traversal, object copying, or UI callbacks.

## Known limitations

- Fan triangulation assumes convex polygons. Concave faces and faces with holes are not supported correctly; only the outer loop is collected.
- Placement scales in local coordinates, then translates using the axis-aligned bounding box and face normal. It does not rotate a source to match the face normal or prevent overlapping copies.
- Geometry comes from the host's face and edge APIs. Degenerate target geometry can raise exceptions, which are logged.

The [historical API snapshot](../python-api-dump/reference/fz_api_dump.txt) records observed host members. Existing local logs record one run with 20 copies on five faces at 25% variation; that is historical evidence, not a comprehensive regression suite.
