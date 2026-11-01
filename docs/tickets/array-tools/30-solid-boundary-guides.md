## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can select straight and curved solid boundary edges as guides, while preserving native edge evaluation and the source representation.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G109 — Straight solid boundary edge:** Select a recorded straight edge of a solid; equal-distance placements match the analytic line reference.
- [ ] **G110 — Smooth-solid curved edge:** Use a verified curved solid boundary edge; placements follow the native curve rather than display facets.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
- [ ] Mark each advertised source/guide case separately; unsupported or unrun cases are explained rather than silently converted to facets or marked supported.
