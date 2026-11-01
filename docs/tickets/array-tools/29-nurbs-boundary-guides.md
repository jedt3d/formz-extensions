## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can select straight and curved NURBS surface/object boundary edges as guides, with separate distance/representation evidence rather than display-facet placement.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G107 — Straight NURBS boundary edge:** Use a recorded straight boundary edge of a NURBS surface/object; stations match its measured native length.
- [ ] **G108 — Curved NURBS boundary edge:** Use a recorded curved boundary edge of a NURBS surface/object; placements follow its native curve rather than display facets.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
- [ ] Mark each advertised source/guide case separately; unsupported or unrun cases are explained rather than silently converted to facets or marked supported.
