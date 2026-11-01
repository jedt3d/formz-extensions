# form·Z Extensions

Small, independent form·Z development experiments: a native C tool, an SDK sample smoke test, a Python scatter palette, and a Python API inspection script. These are prototypes; a successful build or geometry self-check does not establish compatibility with every form·Z release.

Repository: [jedt3d/formz-extensions](https://github.com/jedt3d/formz-extensions).

## Projects

| Project | Purpose | Entry point | Validation |
| --- | --- | --- | --- |
| [Smiley](projects/smiley/README.md) | Draw a planar face with eye and mouth holes using two clicks | `projects/smiley/build.sh` | Universal macOS bundle build and signing verification; manual host check required |
| [Triangle](projects/triangle/README.md) | Rebuild the original SDK tool as a native smoke test | `projects/triangle/build.sh` | Universal macOS bundle build; manual host check required |
| [Scatter](projects/scatter/README.md) | Scatter copies of picked source objects across target faces with size variation | `projects/scatter/scatter.py`, `fzMain()` | Standalone geometry self-check; manual host palette check required |
| [Python API dump](projects/python-api-dump/README.md) | Inspect the actual `formzPythonInterface` API | `projects/python-api-dump/fz_api_dump.py`, `fzMain()` | Syntax check; API probing requires form·Z |

## Layout

```text
projects/
  smiley/                  Native C source, resources, and build entry point
  triangle/                Build entry point for the original SDK sample
  scatter/                 Python scatter experiment
  python-api-dump/          Python probe and a historical API snapshot
scripts/                   Shared native plugin build helper
sdk/                       Setup notes and local FZ_SDK_923 dependency (ignored)
references/                Reference catalog and local downloaded packages (ignored)
build/                     Generated bundles and preserved legacy output (ignored)
compile_flags.txt          Root-relative C editor include paths
AGENTS.md                  Repository development instructions
```

Every experiment owns its source and README. The SDK's own samples stay inside the SDK so their original project structure remains intact. Downloaded extensions are cataloged separately from the experiments developed here.

## Setup

### Native plugins

Use macOS with Apple Clang, a macOS SDK, and `codesign` available through the Xcode toolchain. No additional package manager is required by the build script.

Place an authorized copy of the SDK at `sdk/FZ_SDK_923/`, with `src/h/fz_api.h` underneath it. The SDK is a local dependency and is not downloaded automatically. Read [SDK setup](sdk/README.md) before building: the folder name and version labels in its headers differ.

From the repository root:

```sh
./projects/smiley/build.sh
```

This generates `build/Smiley/Smiley.fzp`, `smiley.ENU.fzr`, and `smiley.bmp`. The shared helper replaces the named output directory on each build, compiles arm64 and x86_64 slices, and applies an ad hoc signature. This is a local development build, not a notarized release.

To build the SDK's original Triangle sample as a separate smoke check:

```sh
./projects/triangle/build.sh
```

Native installation and manual checks are described in the [Smiley README](projects/smiley/README.md).

### Python experiments

The scripts use form·Z's embedded `formzPythonInterface`. A standalone Python installation can run Scatter's geometry self-check and compile both scripts, but cannot exercise form·Z objects or UI. The checked-in API capture records embedded Python 3.13.7; it is historical evidence, not a minimum-version declaration.

Run each script through form·Z's Python scripting interface using its `fzMain()` entry point. See the individual project READMEs for behavior and output paths. No pip dependencies are declared or needed by the standalone self-check.

## Validation

From the repository root:

```sh
sh -n scripts/build_plugin.sh projects/smiley/build.sh projects/triangle/build.sh
python3 -m py_compile projects/scatter/scatter.py projects/python-api-dump/fz_api_dump.py
python3 projects/scatter/scatter.py
./projects/smiley/build.sh
lipo -archs build/Smiley/Smiley.fzp/Contents/MacOS/Smiley
codesign --verify --strict build/Smiley/Smiley.fzp
```

Scatter prints `scatter self-check ok` on success. That check covers square sampling and scale bounds; it does not exercise selection, copying, normals, or the palette. Native compilation and signature checks do not exercise plugin loading or geometry inside form·Z. There is no automated host integration suite or CI configuration in this baseline.

## Reference material

[Reference inventory](references/INVENTORY.md) lists the local downloaded packages. [Organization notes](references/ORGANIZATION.md) record how loose files were grouped. Files with matching names, platform variants, archives, and numbered copies are preserved rather than deduplicated. These packages and the SDK remain on the original workstation and are not present in a fresh clone.

The Python API probe's [historical snapshot](projects/python-api-dump/reference/fz_api_dump.txt) is checked in because it supplies evidence for the experiments' API calls. Fresh probe output and Scatter logs are ignored.

## Development workflow

Design research: [Cinema 4D and Blender array workflows, with form·Z extension opportunities](docs/research/array-tools.md).

Array development: [Feature proposal](docs/proposals/array-tools.md) and [incremental development plan](docs/plans/array-tools-incremental.md). Complete LINE with shared picking, copy/clone, randomization, and lifecycle behavior before adding other layouts. Each gate adds one behavior and becomes the next baseline only after its focused test passes.

Execution artifacts: [Array spec](docs/specs/array-tools.md) and [published ticket index](docs/tickets/array-tools/README.md). The [GitHub parent spec](https://github.com/jedt3d/formz-extensions/issues/2) contains 33 child tickets with native dependency links.

This organization establishes the baseline on `main`. Subsequent development uses one `feature/<plan-name>` branch per development plan. For example, with a clean working tree:

```sh
git switch main
git pull --ff-only
git switch -c feature/scatter-concave-faces
```

Keep each plan scoped to its project, update its documentation, run the relevant checks, then push its feature branch and open a pull request into `main`. New experiments belong in their own `projects/<name>/` directory. Read [AGENTS.md](AGENTS.md) before making changes.

## Licensing

The existing [MIT license](LICENSE) applies to repository-authored material. SDK-derived code and resources retain AutoDesSys notices; see [third-party notices](THIRD_PARTY_NOTICES.md). The repository license does not replace vendor or downloaded-extension terms.
