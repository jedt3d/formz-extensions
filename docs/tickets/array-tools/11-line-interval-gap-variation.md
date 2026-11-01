## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can randomize nominal LINE intervals or the supported clear-gap rule separately from position jitter, with explicit numeric or percentage bounds.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G046 — Interval variation in units:** Nominal pitch 100 mm with ±10 mm variation produces successive intervals in `[90,110]`.
- [ ] **G047 — Interval variation in percent:** Nominal pitch 100 mm with ±10% variation has the same bounds as G046.
- [ ] **G048 — Clear-gap variation:** On G024's supported fixture, gap variation of ±5 mm produces clear gaps in `[20,30]`.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
