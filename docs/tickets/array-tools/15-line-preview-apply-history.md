## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can revise a LINE preview without accumulating output, handle a deleted source, cancel temporary geometry, and Apply the complete array as one undoable/redoable operation.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G061 — Preview replacement:** Change one parameter twice; only the latest preview output remains, without accumulated copies.
- [ ] **G062 — Source deletion during preview:** Delete the active source; Apply is unavailable and unrelated objects remain intact.
- [ ] **G063 — Preview cancellation:** Cancel a previewed multi-element array; no temporary output remains in the document.
- [ ] **G064 — Multi-element commit Undo:** Apply the preview; one Undo removes the complete generated array.
- [ ] **G065 — Multi-element Redo:** One Redo restores the complete array removed by G064's Undo.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
