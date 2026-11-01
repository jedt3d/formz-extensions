## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can rotate and scale supported controlled sources while retaining their parameters, and receives a specific rejection for verified unsupported nonuniform transformations before controls are lost.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G031 — Controlled-object rotation:** Rotate that copied fixture by 30 degrees; its parameter controls remain available.
- [ ] **G032 — Controlled-object uniform scale:** Apply scale `1.25` to the copied fixture; its parameter controls remain available.
- [ ] **G033 — Unsupported transform detection:** Request nonuniform scaling of a verified unsupported controlled type; creation is rejected with a specific reason before controls are lost.
- [ ] **G034 — Supported parametric nonuniform scale:** A verified capable controlled fixture retains controls under the requested independent-axis scale.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Mark each advertised source/guide case separately; unsupported or unrun cases are explained rather than silently converted to facets or marked supported.
