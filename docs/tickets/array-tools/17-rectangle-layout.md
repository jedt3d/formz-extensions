## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can create a two-axis Rectangle grid, enter its extents, and switch between LINE and Rectangle while retaining applicable shared settings and each layout's own values.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G069 — Rectangle layout:** A `2 × 3` grid with pitches 100 and 200 produces exactly the six expected XY anchors.
- [ ] **G070 — Rectangle extent entry:** A `2 × 3` grid fitted across extents 100 and 400 matches G069's anchors.
- [ ] **G071 — Layout switching retains shared settings:** Change layout and return; source identities and shared randomization values remain unchanged.
- [ ] **G072 — Remember layout values:** Switch layouts and back; the original layout's placement values are restored.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
