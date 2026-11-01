## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can set a seed and position variation in units or a defined percentage through LINE Tool Options and obtain repeatable native scene placements.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G037 — Repeatable seed:** Identical seed, element identities, and settings produce identical sampled channel values.
- [ ] **G038 — Change seed:** Two recorded distinct seeds produce their respective reproducible, different fixture values.
- [ ] **G039 — Position variation in units:** X jitter limited to ±10 mm stays within that bound relative to nominal anchors.
- [ ] **G040 — Position variation in percent:** A 100 mm reference pitch with ±10% jitter produces the same bound as G039.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
