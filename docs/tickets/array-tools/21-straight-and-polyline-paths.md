## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can select a straight line/edge, polygonal polyline, or geometrically straight NURBS guide and generate native placements at verified physical-distance stations for each distinct guide type.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G086 — Straight selected-path input:** Use a selected 300 mm straight line/edge as the path; three stations at distances 0, 150, and 300 match the numeric LINE reference.
- [ ] **G087 — Polyline path distance:** Sample the fixture `(0,0,0) → (100,0,0) → (100,200,0)` at distances `0,150,300`; anchors match the analytically expected positions.
- [ ] **G088 — Straight NURBS path input:** Use a 300 mm geometrically straight NURBS path; measured stations match the same straight-path reference.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
- [ ] Mark each advertised source/guide case separately; unsupported or unrun cases are explained rather than silently converted to facets or marked supported.
