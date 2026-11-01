## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can choose tangent alignment, roll, and supported upright/nonplanar frame behavior, with independently checked orientation fixtures.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G096 — Tangent alignment:** At a smooth curved-path station, the fixture's forward axis matches the evaluated path tangent.
- [ ] **G097 — Roll control:** Apply 30 degrees of roll at the same station; orientation differs from G096 only by that roll around the tangent.
- [ ] **G098 — Upright path alignment:** On a compatible planar path, the declared up axis remains world-up.
- [ ] **G099 — Nonplanar path frame:** On a recorded nonplanar fixture, adjacent frames follow the reviewed transport rule without an unintended flip.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
