## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can retain Sources while assigning a compatible guide, resolve ambiguous mixed preselection, reject invalid targets with a reason, and replace a source without losing target identities. This is verifiable selection behavior in the active tool.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G081 — Separate target pick set:** Pick a target after Sources is assigned; the source identities remain unchanged.
- [ ] **G082 — Ambiguous-role handling:** Preselect a source candidate and a curve that could also be a source; the tool requests explicit roles rather than guessing from pick order.
- [ ] **G083 — Explicit mixed preselection:** Assign roles in a mixed preselection; both resulting sets match the designated identities.
- [ ] **G084 — Invalid-target explanation:** Pick one unsupported target in the active stage; a specific reason appears and no output is committed.
- [ ] **G085 — Edit source selection:** Replace Sources after targets were assigned; the target identities remain unchanged.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Keep LINE_READY passing and rerun applicable shared source/output/variation/lifecycle cases for this layout.
