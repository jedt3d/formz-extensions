# Ticket #3 gate evidence

Branch: `feature/array-ticket-3-line`. Planning baseline: merge of current `origin/main` and the approved `feature/array-tools-proposal` branch. No gate is accepted from a build result alone.

## G001 — Register the Array tool

Status: PASS — 2026-11-01, standard form·Z 10.0 Extensions Manager host check. Accepted implementation commit: `f74d7a1c94968e7ec1ddf8f2bb289271bccf128e` (planning baseline `af6997c`).

RED: standard `/Applications/formZ 10/formZ 10.0 pro/formZ.app`, form·Z 10.0, Extensions Manager, alphabetical A section: Animate tools followed by Augment Uploader; no Array row. Existing empty Untitled1 document, meter units. No source or guide, seed, placement, or geometry tolerance applies to registration.

Expected GREEN: exactly one enabled Array row (type Tool, vendor formZ-dev).

Observed GREEN: after installing the complete build/Array directory and relaunching form·Z, Extensions Manager displays exactly one checked Array row between Animate Turntable View and Augment Uploader: Type Tool, Kind Plugin, Version 0.1.0.0, Vendor formZ-dev. Captured in this session through the native UI screenshot. The existing empty document remains empty; no geometry code is present.

Build checks: shared/project build scripts pass sh -n; universal binary has x86_64 and arm64; codesign --verify succeeds. Binary SHA-256: 4db1352acc12f84b4672d864ad3bcf13417d4b5c5aeb1b6ff084998954c14fde.

The first screenshot showed an unchecked row; the final verification after reconnecting showed it checked. Two running app variants share com.formZ.formZ and the SDK plugin directory. UI automation repeatedly reported concurrent UI changes and capture timeouts. Registration is accepted from the final checked row; subsequent behavior gates still require independent stable host checks. No geometry, selection, or activation behavior is inferred from registration.

## G002 — Incomplete LINE input

Status: BLOCKED before implementation; accepted baseline is G001 commit above.

Array activation/Tool Options could not be tested reliably: native UI automation reported “The user changed … Re-query the latest state”, `timeoutReached`, `noWindowsAvailable`, and a ScreenCaptureKit capture failure. Both standard formZ.app and formZ cursor-test.app were running with the same bundle identifier, and process inspection confirmed both mapped the same installed Array binary. A direct full-path reconnect and an automation-session reset did not yield reliable continuing control. The exact cause of the control failures is unconfirmed; concurrent UI use and the shared identifier must be eliminated before continuing.

No Apply/selection/placement behavior has been implemented, accepted, or inferred. No G002 RED or GREEN result is claimed. The standard host needs an uninterrupted test session, with the other form·Z variant closed by its owner. Do not build later gates while this host test is blocked.

## Remaining gates

G003–G012 have not been implemented or accepted. Follow ticket order; record actual host observations and prior-gate regressions before advancing.

## Review

Matt Pocock two-axis review of `af6997c...f74d7a1`: Standards found no hard violation or material code smell; an optional notice-path comment was corrected. Spec found no G001 implementation blocker; its requested accepted-commit reference is recorded above. Reviewers did not independently reproduce host checks. No ticket-completion claim is made.
