## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can create full-circle or arc arrays with numeric/graphic input, angular spacing, radial orientation, and seeded angular interval variation through the shared tool.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G075 — Full-circle radial layout:** Four placements at radius 100 produce four quarter-turn positions with no seam duplicate.
- [ ] **G076 — Partial radial arc:** Three placements from 0 to 90 degrees produce anchors at 0, 45, and 90 degrees.
- [ ] **G077 — Radial angular interval:** An arc from 0 to 100 degrees with step 30 produces 0, 30, 60, and 90 degrees.
- [ ] **G078 — Graphic radial definition:** Graphic center/radius input reproduces the numeric radial fixture.
- [ ] **G079 — Radial orientation:** With radial-facing alignment selected, each fixture's declared forward axis points toward the center.
- [ ] **G080 — Radial angular interval variation:** Nominal 30 degree step with ±10% variation produces successive angular steps in `[27,33]` degrees within the selected arc.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
