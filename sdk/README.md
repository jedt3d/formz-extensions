# Local form·Z SDK

Place the SDK distribution in `sdk/FZ_SDK_923/`. The existing workstation copy was moved here from the workspace root without changing its files. The directory is Git-ignored and is not included in a clone.

The build helper requires:

```text
sdk/FZ_SDK_923/src/h/fz_api.h
```

Other useful locations in that distribution:

- `src/h/`: API declarations and vendor notice in `formZ_vendor.h`.
- `Samples/Tools/Triangle/`: the native sample used as the starting point for Smiley.
- `Samples/Tools/star/`, `frame/`, and `random_trans/`: additional tool references.
- `Samples/Workspace/`: original platform workspaces.
- `Doc/HTML/formZApi.htm`: local HTML documentation entry point.

The directory is named `FZ_SDK_923`, while `src/h/formZ_vendor.h` identifies itself as SDK 8.6.3, dated December 3, 2018. Treat the headers and available host function sets as evidence; the folder name alone does not prove SDK version or host compatibility.

Obtain the SDK through an authorized AutoDesSys distribution and retain its terms. Its header contains a proprietary notice; the repository's MIT license does not license this dependency. Keep original vendor filenames and sample layouts intact so relative paths in the supplied projects remain meaningful.
