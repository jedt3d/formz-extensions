## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can use a declared randomization frame and combine supported size/rotation/position variation predictably; clear gaps follow varied sizes under the supported rule and invalid scale ranges are rejected.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G053 — Randomization coordinate frame:** In a 90-degree-rotated layout, local-X jitter follows world Y.
- [ ] **G054 — Transform composition:** Apply fixed scale, rotation, and jitter values together; the anchor/orientation matches an independently calculated transform.
- [ ] **G055 — Clear gap after size variation:** With supported unrotated parts, the measured clearance stays at the requested gap after the parts' sizes vary.
- [ ] **G056 — Invalid random scale range:** A scale range containing zero is rejected before generating output.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
