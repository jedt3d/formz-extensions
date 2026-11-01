# Triangle SDK smoke test

Build the original form·Z SDK Triangle tool as a baseline native plugin. The original workspace already contained a `build/Triangle/` output directory; this project gives that experiment its own repeatable entry point without copying or modifying vendor source.

Set up the SDK using [SDK setup](../../sdk/README.md), then run from the repository root:

```sh
./projects/triangle/build.sh
```

The wrapper also works from other working directories. It builds `sdk/FZ_SDK_923/Samples/Tools/Triangle/` through the shared helper and writes `build/Triangle/`, replacing that directory. The output contains a universal `Triangle.fzp` bundle and the original companion resource files.

Source and original platform workspaces remain inside the local SDK; they are absent from a fresh clone until the SDK is supplied. This smoke test checks the SDK sample build path separately from the Smiley fork. A build and signature check does not prove successful loading or tool interaction inside form·Z.

For a manual host check, install the complete output folder under the target installation's `Plugins/` directory, restart form·Z, and exercise the original Triangle tool in a disposable document. Retain the SDK's notices and original resource filenames.
