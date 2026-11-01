## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can vary LINE repetition size uniformly or independently by axis on supported sources using explicit percentage or numeric ranges.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G041 — Uniform size variation in percent:** ±10% size variation produces uniform scale factors in `[0.9,1.1]`.
- [ ] **G042 — Numeric size range:** A numeric uniform scale range `[0.8,1.2]` stays within those bounds.
- [ ] **G043 — Independent-axis size variation:** On a supported fixture, independent XYZ ranges affect only their assigned axes.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
