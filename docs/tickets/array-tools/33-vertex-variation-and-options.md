## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can add a vertex target without rerolling existing identities and apply optional position variation while retaining one-per-vertex output; Vertex options omit inapplicable gap/count controls.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G118 — Stable target addition:** Add one vertex target; existing identified targets retain their sampled values.
- [ ] **G119 — Vertex position variation:** With ±10 mm X jitter, each selected vertex still owns one output within its declared bound.
- [ ] **G120 — Layout-specific options:** Vertex layout has no editable gap or placement-count controls.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
