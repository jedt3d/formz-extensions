## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can define a LINE graphically in its own frame, choose a source anchor, replace sources, repeat a multi-object assembly, and request the declared simple clear-gap behavior through the same working tool.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G019 — Graphic line definition:** Define the same line using graphic input; generated anchors match G012's numeric fixture.
- [ ] **G020 — Tilted LINE frame:** Define a LINE along world Y; its local forward axis follows world Y rather than world X.
- [ ] **G021 — Explicit source anchor:** Select an offset source anchor; that anchor, rather than its bounding-box center, lands on the first layout point.
- [ ] **G022 — Replace LINE source selection:** Replace Sources in the working LINE tool; previously entered placement values remain unchanged.
- [ ] **G023 — Multiple-object source assembly:** Repeat a two-object assembly once; the two objects retain their relative transform in the generated assembly.
- [ ] **G024 — Numeric clear gap:** Unrotated 100 mm-wide parts with a 25 mm bounding-extent gap produce 125 mm anchor intervals.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
