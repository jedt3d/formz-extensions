## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can add a third grid axis with independent pitch or extent while reusing accepted source selection, output, variation, and lifecycle behavior.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G073 — 3D grid layout:** Extending G069 to two Z layers at pitch 300 produces exactly twelve expected anchors.
- [ ] **G074 — Volume extent entry:** A `2 × 3 × 2` grid fitted across extents 100, 400, and 300 matches G073's anchors.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
