# Issue tracker: GitHub

Specs and tickets live in GitHub Issues in `jedt3d/formz-extensions`.

Use the installed `gh` CLI with an explicit `--repo jedt3d/formz-extensions` target. Check `gh repo view` before creating issues. The verified CLI version supports native parent/sub-issue relationships and issue dependencies.

Create one spec issue, then approved child tickets in dependency order. Supply multiline bodies through `--body-file`. Set the spec as `--parent` and direct blockers through `--blocked-by`. Verify the resulting native relationships after creation. If native dependencies are unavailable, explain the failure and use explicit blocking references in the child body; do not silently drop an edge.

Apply the configured ready-for-agent label to finalized specs and approved tickets. It describes specification/triage readiness, not permission to ignore open blockers. The parent spec coordinates the work; implementation proceeds through child tickets. Do not close or rewrite a parent spec while creating tickets.

Read the full issue and comments when a skill references an issue. Check existing issues before creating duplicate work. Preserve local issue-to-ticket mappings after publication.

PRs as a request surface: no.
