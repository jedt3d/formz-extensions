## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can choose fixed intervals within an extent or fit a generated count to an overall LINE length, with the expected endpoint/remainder behavior.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G017 — Line by interval within extent:** Extent 250 and interval 100 produces X=`0,100,200`, with the remainder left unused.
- [ ] **G018 — Line count fitted to length:** Count 4 across length 300 produces four placements including both endpoints.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
