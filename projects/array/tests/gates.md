# Ticket #3 gate evidence

Branch: `feature/array-ticket-3-line`. Planning baseline: merge of current `origin/main` and the approved `feature/array-tools-proposal` branch. No gate is accepted from a build result alone.

## G001 — Register the Array tool

Status: PASS — 2026-11-01, standard form·Z 10.0 Extensions Manager host check.

RED: standard `/Applications/formZ 10/formZ 10.0 pro/formZ.app`, form·Z 10.0, Extensions Manager, alphabetical A section: Animate tools followed by Augment Uploader; no Array row. Existing empty Untitled1 document, meter units. No source or guide, seed, placement, or geometry tolerance applies to registration.

Expected GREEN: exactly one enabled Array row (type Tool, vendor formZ-dev).

Observed GREEN: after installing the complete build/Array directory and relaunching form·Z, Extensions Manager displays exactly one checked Array row between Animate Turntable View and Augment Uploader: Type Tool, Kind Plugin, Version 0.1.0.0, Vendor formZ-dev. Captured in this session through the native UI screenshot. The existing empty document remains empty; no geometry code is present.

Build checks: shared/project build scripts pass sh -n; universal binary has x86_64 and arm64; codesign --verify succeeds. Binary SHA-256: 4db1352acc12f84b4672d864ad3bcf13417d4b5c5aeb1b6ff084998954c14fde.

The first screenshot showed an unchecked row; the final verification after reconnecting showed it checked. Two running app variants share com.formZ.formZ and the SDK plugin directory. UI automation repeatedly reported concurrent UI changes and capture timeouts. Registration is accepted from the final checked row; subsequent behavior gates still require independent stable host checks. No geometry, selection, or activation behavior is inferred from registration.

## Remaining gates

G002–G012 have not been implemented or accepted. Follow ticket order; record actual host observations and prior-gate regressions before advancing.
