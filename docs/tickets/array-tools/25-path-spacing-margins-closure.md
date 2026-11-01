## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can use physical path intervals, start/end margins, and a closed-path distribution without a duplicate seam placement.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G092 — Path by fixed interval:** On a 250 mm path with interval 100, placement distances are `0,100,200`.
- [ ] **G093 — Start margin:** Add a 20 mm start margin to the fixed-interval fixture; the first distance becomes 20 mm from the path start.
- [ ] **G094 — End margin:** Add an end margin to the fixture; no anchor crosses the reduced usable endpoint.
- [ ] **G095 — Closed-path seam:** Place eight items around a closed curve; there are eight unique placements and no duplicate at closure.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
