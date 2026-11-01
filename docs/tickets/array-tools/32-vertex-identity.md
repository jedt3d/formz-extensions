## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler gets one output per unique topological identity: repeated references are deduplicated, distinct coincident vertices remain distinct, and display refinement does not change the count.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G115 — Repeated vertex references:** Supply the same topological vertex through adjacent selections; it produces one placement.
- [ ] **G116 — Distinct coincident vertices:** Two distinct vertex identities at the same coordinate produce two placements under the proposed identity policy.
- [ ] **G117 — Display-resolution independence:** Change only the target's display refinement; the topological-vertex placement count remains unchanged.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
