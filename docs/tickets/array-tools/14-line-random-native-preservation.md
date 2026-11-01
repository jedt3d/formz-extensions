## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can apply the supported random transforms to controlled, smooth-solid, NURBS-curve, and NURBS-surface LINE sources, with separate runtime evidence that representations and supported controls survive.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G057 — Controlled-source random size:** A verified controlled fixture retains its parameters under the supported random uniform-size range.
- [ ] **G058 — Smooth-source random transform:** A smooth-solid fixture retains its representation under the supported LINE random-transform fixture.
- [ ] **G059 — NURBS-curve random transform:** A NURBS curve retains its representation under the same supported transform fixture.
- [ ] **G060 — NURBS-surface random transform:** A NURBS surface retains its representation under the same supported transform fixture.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Mark each advertised source/guide case separately; unsupported or unrun cases are explained rather than silently converted to facets or marked supported.
