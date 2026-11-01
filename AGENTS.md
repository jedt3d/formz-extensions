# Repository instructions

## Scope and workflow

- This repository contains independent form·Z experiments, not a single application. Read the target project's README before editing it; preserve neighboring projects.
- After the initial organization baseline, start each development plan on `feature/<plan-name>` from an up-to-date `main`. Keep the branch and pull request scoped to that plan.
- Before changes, inspect the implementation, related configuration, and available logs. State the cause and the smallest complete fix; label missing evidence explicitly.
- Keep source, resources, and project-specific documentation in `projects/<name>/`. Shared build tooling belongs in `scripts/`.

## Native C work

- Before changing C API usage, inspect the declarations in local `sdk/FZ_SDK_923/src/h/` and the corresponding SDK sample. Read `sdk/README.md` for dependency setup and version caveats.
- Smiley uses SDK function sets and callbacks acquired from the host. Preserve plugin/tool UUIDs, function-set contracts, resource names, bundle metadata, and copyright notices unless the plan explicitly changes them.
- Keep `.fzr` and `.bmp` resources with their project. Smiley loads `smiley` resources and `smiley.bmp` by name; the build places them beside the `.fzp` bundle.
- Use each native project's `build.sh` entry point or `scripts/build_plugin.sh <source-directory> <Name>` for SDK samples. Build output is disposable under `build/<Name>/`; never store source there.
- Preserve source line endings when making unrelated edits to SDK-derived files.

## Python work

- Before changing form·Z Python calls, consult `projects/python-api-dump/reference/fz_api_dump.txt`. It records observed members, but many host docstrings are generic or inaccurate. Verify uncertain signatures in the host rather than inferring them from a name.
- Keep `fzMain()` and callback names compatible with the host. `formzPythonInterface` is supplied by form·Z; standalone Python cannot validate host interactions.
- Read the Scatter README before changing sampling or placement: convex outer loops and bounding-box placement are existing limitations, not general surface scattering guarantees.
- Keep fresh API dumps and logs beside their scripts and Git-ignored. Update the historical snapshot deliberately with host-version context when capturing new evidence.

## Dependencies and reference material

- SDK files and downloaded packages are local, ignored reference material. Read `references/README.md` before using or promoting any of that material into an active project.
- Preserve vendor source, filenames, platform variants, numbered copies, and notices. Review provenance and distribution terms before adding vendor material to Git. Keep the original MIT license and third-party notices distinct.
- Keep machine files, `.remember/`, caches, logs, and generated bundles out of commits.

## Completion checks

- For shell changes, run `sh -n` on the shared helper and native project build scripts. For native changes, build the affected plugin, verify its architecture slices and signature, and report whether host loading was tested.
- For Python changes, compile both scripts. For Scatter changes, also run `python3 projects/scatter/scatter.py`. Record host UI/geometry checks separately from standalone checks.
- For path or layout changes, inspect references in build scripts, `compile_flags.txt`, Python output locations, and READMEs; verify that original source and reference files remain accounted for.
- Before committing, inspect the staged diff and ignored-file exclusions. Report checks actually run and any host validation still pending. Never describe a build-only result as a successful form·Z runtime test.

## Agent skills

### Issue tracker

Specs and tickets use GitHub Issues in `jedt3d/formz-extensions`. Read `docs/agents/issue-tracker.md` before tracker operations.

### Triage labels

Use the five default Matt Pocock triage roles. Read `docs/agents/triage-labels.md` before applying or interpreting them.

### Domain docs

Use the single-context domain-doc layout. Read `docs/agents/domain.md` when exploring domain terminology or architectural decisions.
