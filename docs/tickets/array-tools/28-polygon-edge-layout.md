## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can choose whole-perimeter or per-edge placement, selected edges, shared-corner deduplication, and explicit outgoing-edge corner orientation through the shared Array workflow.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G102 — Whole-perimeter polygon spacing:** On a 100 mm square, interval 75 produces perimeter distances `0,75,150,225,300,375`, continuing across corners.
- [ ] **G103 — Per-edge polygon spacing:** On the same square, restart interval 75 on each edge; resulting positions match the declared per-edge rule.
- [ ] **G104 — Shared-corner deduplication:** With both ends of adjacent edges included, a shared topological corner produces exactly one placement.
- [ ] **G105 — Polygon-corner orientation:** With outgoing-edge orientation selected at a square corner, the forward axis follows the outgoing edge.
- [ ] **G106 — Selected-edge scope:** Designate two edges of a polygon; no placements are generated on unselected edges.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
