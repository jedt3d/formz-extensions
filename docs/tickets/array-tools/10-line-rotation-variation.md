## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can vary LINE repetition rotation using degrees or a percentage of an explicit reference angle, and observe the intended native orientation changes.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G044 — Rotation variation in degrees:** Z-only variation in `[-15,15]` degrees produces no X/Y rotational variation.
- [ ] **G045 — Rotation variation in percent:** Base angle 30 degrees with ±50% delta gives a ±15 degree variation bound.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
