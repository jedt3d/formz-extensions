# Claude Code instructions

@AGENTS.md

`AGENTS.md` (imported above) is the shared rulebook for every agent in this
repository. This file adds only what is specific to Claude Code. If the two
conflict, `AGENTS.md` wins; raise the conflict instead of working around it.

## Parallel agents share this folder

Codex and ChatGPT work in this repository at the same time as Claude.

- Run `git status --short --branch` and `git worktree list` before any change.
  Treat uncommitted changes you did not make as another agent's work in
  progress: never stage, stash, revert, reformat, or commit them, and never
  switch branches in a checkout that holds them.
- Create the `feature/<plan-name>` branch before the first edit. When the
  shared checkout is dirty or on another agent's branch, start from an
  up-to-date `main` in a sibling worktree instead of switching branches there:

  ```sh
  git fetch origin
  git worktree add ../formZ-dev-<plan-name> -b feature/<plan-name> origin/main
  ```

  Work, build, and commit inside that worktree. `build/` output is ignored
  and stays per worktree.
- Do not push, open pull requests, merge, or delete branches or worktrees
  belonging to another agent's plan. Ask the user first.
- When the `pspa_agent_relay` tools are available, check the inbox, claim the
  task, and lock the repository-relative paths you will edit before editing;
  release them when done. A human approves merges and accepted decisions.

## Local setup that is easy to miss

- The SDK (`sdk/FZ_SDK_923/`) and `references/` packages are ignored and exist
  only in the original checkout. A new worktree has neither. For native builds,
  verify `sdk/FZ_SDK_923/src/h/fz_api.h` exists in the worktree before
  building; if it is missing, say so and ask how the user wants the SDK made
  available. Never copy vendor material into a tracked path.
- `cat` is aliased to `bat` on this machine. Pass commit messages and PR bodies
  as files (`git commit -F`, `gh pr create --body-file`), and use
  `command cat` when reading plain text in a pipeline.

## Reporting

- form·Z itself is not driven from this session. State which checks from the
  `AGENTS.md` completion list actually ran, and list host loading, UI, and
  geometry checks as pending unless the user reports running them.
