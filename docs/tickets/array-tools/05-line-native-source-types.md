## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can choose smooth-solid, straight/curved NURBS, NURBS-surface, NURBS-faced-solid, and controlled-solid sources in the existing LINE workflow, with each type tested separately and preserved natively.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G025 — Smooth-solid source copy:** Copy a known smooth-solid fixture; its output retains the native smooth-solid representation.
- [ ] **G026 — Straight NURBS source copy:** Copy a geometrically straight NURBS source; the output retains its native NURBS representation rather than becoming a polygonal line.
- [ ] **G027 — Curved NURBS source copy:** Copy a recorded curved NURBS source; the output retains its native curve representation.
- [ ] **G028 — NURBS surface source copy:** Copy a known NURBS surface; the output retains its native surface representation.
- [ ] **G029 — NURBS-faced solid source copy:** Copy a recorded solid with NURBS faces; the output remains a solid with the recorded native surface representation.
- [ ] **G030 — Controlled-solid source copy:** Copy a parameterized solid; its copied parameter remains editable.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Mark each advertised source/guide case separately; unsupported or unrun cases are explained rather than silently converted to facets or marked supported.
