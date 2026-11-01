# Array

Native Array tool, developed through the ordered host acceptance gates in [ticket #3](https://github.com/jedt3d/formz-extensions/issues/3).

Build from the repository root with `projects/array/build.sh`. Requires the ignored local SDK described in [sdk/README.md](../../sdk/README.md). Output is disposable under `build/Array/`.

Copy the complete `build/Array/` directory into the standard form·Z installation's `Plugins/SDK/Array/` while all form·Z variants are closed, then launch form·Z. The bitmap stays beside the bundle. Do not install a second copy on another extension search path.

G001 currently provides registration only. No geometry operation is implemented yet. G002 is blocked on reliable host UI control; close the cursor-test variant before continuing standard-host tests. [Gate results](tests/gates.md) distinguish build checks from observed host behavior. A gate may become the next baseline only after its host check passes.

The tool follows the SDK Triangle registration contract with independent plugin/tool UUIDs. Read [AUTODESSYS_NOTICE.txt](AUTODESSYS_NOTICE.txt) for SDK terms; repository-authored code is covered separately by the root license.
