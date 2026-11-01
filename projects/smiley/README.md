# Smiley

Native form·Z C tool derived from the SDK Triangle example. Click once to set the center and again to set the radius. The tool constructs a planar head with two eye holes and a mouth hole on the drawing plane; cursor tracking updates the preview. Canceling removes the temporary object. A second click at the center removes it without creating a face.

## Build and install

Set up the local SDK as described in [SDK setup](../../sdk/README.md), then run from the repository root:

```sh
./projects/smiley/build.sh
```

`build.sh` also works from another working directory. Output is `build/Smiley/`, containing the universal `Smiley.fzp` bundle and its companion `smiley.ENU.fzr` and `smiley.bmp` resources. Each build replaces that output directory.

For a manual host check, copy the complete `build/Smiley/` folder into the target form·Z installation's `Plugins/` directory and restart form·Z. Keep the resource files beside the bundle. The development workstation has a `Plugins/` directory under `/Applications/formZ 10/formZ 10.0 pro/`; installations elsewhere should use their own location. The build script does not install the plugin.

Verify tool registration, two-click creation, cursor tracking, and cancellation in a disposable document. Inspect the face's three holes on both the default and a rotated drawing plane. The code requests an icon position immediately to the right of the 3D rectangle tool; actual host UI placement needs manual verification.

## Source map

- `src/c/smiley_init.c`: entry point, host function sets, resource loading, registration, and teardown.
- `src/c/smiley_tool.c`: callbacks, drawing-plane mapping, and faceted geometry.
- `src/h/smiley.h`: plugin and tool IDs, resource IDs, and shared host state.
- `src/fzr/`: English resources and bitmap icon.

The shape proportions and segment counts are constants near the top of `smiley_tool.c`. The bundle is signed ad hoc for development. Successful compilation does not establish host compatibility; the SDK folder name and its internal version labels differ.

Retain the original AutoDesSys notices. Read [AUTODESSYS_NOTICE.txt](AUTODESSYS_NOTICE.txt) for the original vendor copyright note required by the SDK-derived material.
