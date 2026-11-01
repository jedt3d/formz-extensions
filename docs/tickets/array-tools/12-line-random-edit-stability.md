## Parent

https://github.com/jedt3d/formz-extensions/issues/2

## What to build

A modeler can disable variation to recover the deterministic layout, preserve intervals within an extent, change one channel independently, and increase LINE count without rerolling existing placements.

The primary test boundary is the visible Array workflow through native scene output. Keep the gates below in order: each accepted gate supplies the next baseline, even within this ticket. This ticket does not replace that requirement with one large implementation step.

## Acceptance criteria

- [ ] **G049 — Zero-variation equivalence:** All variation ranges set to zero reproduce the deterministic placement fixture exactly.
- [ ] **G050 — Randomized extent remainder:** Fixed-extent interval mode stops before crossing its boundary and preserves sampled intervals rather than silently rescaling them.
- [ ] **G051 — Random channel independence:** Change only size variation; sampled position-jitter values stay unchanged.
- [ ] **G052 — Stable LINE count increase:** Increase LINE count by one; the existing placement identities retain their sampled random-channel values.
- [ ] Record the tested source/guide fixture choices, actual native types, units/tolerance, settings/seed, expected/observed results, and relevant prior regression results.
- [ ] Demonstrate the delivered behavior in form·Z; a build or disconnected mathematical helper alone does not satisfy acceptance.
