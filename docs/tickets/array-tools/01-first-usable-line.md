## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can activate Array with pre-picked sources or select them afterward, enter a simple count/pitch LINE, create ordinary copies, and undo/redo or cancel the operation. The tool and native scene operation work together; this is not a shell-only or math-only ticket.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G001 — Register the Array tool:** Launch the built plugin in form·Z and confirm exactly one new Array tool is registered.
- [ ] **G002 — Incomplete LINE input:** Apply stays disabled while the LINE source or required placement input is incomplete.
- [ ] **G003 — Source-only pre-picking:** Select the source before activating Array; Sources contains that object without a redundant selection step.
- [ ] **G004 — Source post-picking:** Activate Array with an empty selection and pick the source; Sources matches G003's source set.
- [ ] **G005 — Native source-pick completion:** The verified host source-pick completion gesture advances to LINE placement exactly once.
- [ ] **G006 — Source-picking cancellation:** Cancel while collecting LINE sources; the original document geometry is unchanged.
- [ ] **G007 — Native facetted-object copy:** Duplicate one known facetted fixture; exactly one native facetted copy appears.
- [ ] **G008 — Translation:** Place that copy's anchor at `(100, 0, 0)`; its measured anchor matches the target.
- [ ] **G009 — Undo the operation:** One Undo restores the pre-operation object set.
- [ ] **G010 — Redo the operation:** One Redo restores the same generated copy at the same location.
- [ ] **G011 — Cancel an unfinished operation:** Cancel after temporary creation; the document returns to its original object set.
- [ ] **G012 — Line by count and pitch:** Count 4, start `(0,0,0)`, pitch 100 along X produces anchors at X=`0,100,200,300`.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
