## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can pre-pick target vertices before choosing a source or explicitly designate an object's All Vertices scope and obtain one repetition per selected topological vertex.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G111 — Target-only pre-picking:** Preselect target vertices, then designate a source; the original target identities remain available.
- [ ] **G112 — Whole-object vertex targeting:** Designate an object as an All Vertices target; it is not reassigned as a source.
- [ ] **G113 — Selected-vertex layout:** Select five distinct target vertices; exactly five anchors are placed at those vertices.
- [ ] **G114 — All-vertices object scope:** Explicitly designate a box as an All Vertices target; eight topological vertices produce eight placements.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
