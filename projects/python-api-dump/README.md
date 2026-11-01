# Python API dump

Inspect `formzPythonInterface` in the actual form·Z Python runtime before writing scripts against it. The probe records available members and docstrings for the module, an `xyz` value, a cube object, its first face, its loop, and a vertex. It also records representative calls such as `face.normal()`, `face.area()`, `obj.extents()`, and `obj.boundingBox()`.

## Run

Load `fz_api_dump.py` through form·Z's Python scripting interface and invoke `fzMain()`. The script imports the host module directly and cannot run under ordinary standalone Python.

The probe creates a cube from `[0, 0, 0]` to `[10, 10, 10]` and does not delete it. Run it in a disposable document. It overwrites `fz_api_dump.txt` beside the script; that fresh output is Git-ignored.

## Captured evidence

[`reference/fz_api_dump.txt`](reference/fz_api_dump.txt) preserves the original capture unchanged. It reports Python 3.13.7 but does not identify the form·Z application version. Object addresses are incidental. Many host docstrings repeat unrelated descriptions, so this capture establishes observed members and sample results rather than a complete API contract.

Keep new captures separate from this historical reference until deliberately reviewed. Record the form·Z version and capture context when updating the reference.

For a syntax-only check outside the host, from the repository root:

```sh
python3 -m py_compile projects/python-api-dump/fz_api_dump.py
```
