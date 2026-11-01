## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler receives a specific validation result for zero/single counts, invalid intervals, and requests beyond the configured output limit before geometry is allocated.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G013 — Zero-count handling:** Count zero is rejected without creating output.
- [ ] **G014 — Single-count handling:** Count one creates one placement at the layout origin.
- [ ] **G015 — Positive interval validation:** A zero interval is rejected before placement.
- [ ] **G016 — Output limit validation:** A request exceeding the explicitly configured output limit is rejected before allocation.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
