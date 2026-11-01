## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler receives a clear response when switching to an incompatible layout or deleting an active path target; targets are not silently reassigned and stale preview output is invalidated.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G100 — Layout switching revalidates targets:** Switch to an incompatible layout; invalid targets are explained without silently reassigning their roles.
- [ ] **G101 — Target deletion during preview:** Delete the active target; the preview is invalidated with a missing-target reason.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
