## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can save and reopen committed LINE output with its native geometry and existing material assignments. The accumulated LINE workflow passes before another layout is developed.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G066 — Committed output persistence:** Save and reopen the document; committed outputs retain their positions and native geometry.
- [ ] **G067 — Preserve material assignments:** Reopened outputs retain the source object/face material references.
- [ ] **G068 — No material creation:** Creating the array leaves the document's material count unchanged.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
- [ ] Rerun the accumulated visible LINE gates and record the passing commit as LINE_READY before ticket 17 starts.
