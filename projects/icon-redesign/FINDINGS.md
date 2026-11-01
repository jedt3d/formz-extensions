# formZ icon resources: loading and Retina test

Read-only investigation of formZ 10 on macOS, 01 November 2026. Prior work
reused: Codex inventory at
`~/.codex/visualizations/2026/11/01/01a1965d-ab68-7060-b0d7-367dfee8553b/formz-icon-inventory/`
(contact sheets, `inventory.csv` with UI mapping). The related cursor study
was closed as won't fix on macOS (jedt3d/formz-extensions#36): the Mac build
switches custom cursors off in modal dialogs and stubs out HD cursors.

Tags: **[verified]** read from the binary, files, or a test run;
**[inferred]** follows from verified facts but not yet seen in formZ.

## 1. What is in `Contents/Resources/Icons/` [verified]

- 997 files: 935 `Cic_<id>.ENU.bmp`, 57 `Cic_<id>.Dark.ENU.bmp`, 2 with the
  misspelled prefix `CIc_`, 1 named `Cic_<id>.ENU..bmp`, 2 PNG arrows.
- Format: Windows BMP, 40-byte header, pixel data at offset 54. 987 files are
  32-bit bottom-up BGRA with alpha in the 4th byte; 7 are 24-bit; 1 is
  top-down. `sips` reports "no alpha" for them; read the bytes directly.
- Sizes: 562 × 48 px (tool palettes), 123 × 16, 116 × 32, 52 × 18,
  19 × 128, 13 × 64, plus small UI pieces (9–25 px).
- Some 64/128 px icons sit in places that are clearly drawn smaller, such as
  the Animation palette controls `Cic_4277`–`4289` (128 px).

## 2. How formZ loads an icon [verified]

`fzrt_get_cicon` in `libFZRT.dylib`:

1. Opens `Resources/Icons/`.
2. If `fzrt_appr_is_darkmode()` is true, tries `Cic_%d.Dark.ENU.bmp` first;
   otherwise, or if that file is missing, `Cic_%d.ENU.bmp`.
3. Reads the bitmap itself (`fzrt_read_dib`), copies the pixels, and builds a
   `CGImage` (8 bits per component, 32 bits per pixel, alpha). No NSImage, no
   `@2x` lookup, one resolution per file.
4. Drawing (`fzrt_plot_cicon`) calls `CGContextDrawImage` into a rectangle
   supplied by the caller; `fzrt_get_c_icon_bounds` reports the bitmap's
   pixel size to callers that ask.

Open question: whether toolbar and palette buttons draw into a fixed
button-sized rectangle (then larger bitmaps become sharper) or into the
bitmap's own size (then larger bitmaps become larger icons). The 128 px
Animation icons point to the first [inferred].

## 3. Host test: `formZ icon-test.app` [verified in formZ, 01 Nov 2026]

**Result (user screenshots, Retina display, light mode):** every replaced
icon shows a thin magenta frame and the corner square at its normal size,
with nothing doubled or clipped. Seen in the tool palette, top toolbars, Tool
Options (Pick, Move), the Modify NURBS Surfaces flyout, and the Preferences
icon preview, where the same 48 px icons are also drawn at about half size.
The small Objects/Layers/Lights/Views icons are unchanged, as expected,
because only 48 px files were replaced.

What this establishes:
- formZ loads `Icons/Cic_<id>.ENU.bmp` from the bundle at run time, and
  edited files are used without re-signing.
- formZ draws each icon into the button's own rectangle and scales the
  bitmap to fit. A 96 px file in a 48-pt button is drawn at 2× density, as
  the hairline frame (½ pt) shows.
- The colour came out magenta, so the BGRA byte order is read as intended.
- Therefore, **icons can be made sharp on Retina by supplying 2× bitmaps
  under the same names**, unlike cursors.

**Dark mode (user screenshot, same day):** the same result; replaced icons
show the frame at normal size in the tool palette, top toolbars and Tool
Options. Only 8 of the 57 `.Dark.ENU.bmp` files are 48 px (39 are 16 px), so
in dark mode most tool icons still come from the light files; a missing dark
file falls back to the light one. Icons drawn without a frame are ones that
were not replaced (not 48 px, for example the 128 px File New/Close icons
`Cic_3782`/`3779`) [inferred from sizes, not matched one by one].

Not yet checked: whether the Preferences "Saturation" and "Tint" settings
still apply to 2× art, and whether 16–32 px and 128 px icons behave the same
when doubled.

`tools/make_icon_test_copy.py` (standard library only) copies `formZ.app`
to `formZ icon-test.app` beside it and replaces all 554 48 × 48 px icons
(light and dark) with 96 × 96 px versions: each pixel doubled, plus a 1 px
magenta frame and a 6 × 6 px magenta corner mark. The other 438 files are
unchanged. The installed app is only read; its signature still verifies.

In a tool palette, compare with the original:

| What you see in the test copy | Meaning |
| --- | --- |
| Icons unchanged, no magenta | formZ did not load these files (cached elsewhere, or a different source) |
| Icons twice as large or clipped | formZ sizes icons from the bitmap; 2× art would break the layout |
| Same size, thin magenta frame, small square top-left | formZ scales icons to the button: 2× art gives sharp Retina icons |

The colour may show as cyan instead of magenta if formZ reads the bytes in a
different channel order; either colour counts as "loaded".

Quit any running formZ first; the copy has the same bundle ID.
