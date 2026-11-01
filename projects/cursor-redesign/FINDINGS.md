# formZ cursor resources: behavior and defects

Review copy of a read-only investigation, 01 November 2026. Nothing in the
installed application was modified.

- Host: `/Applications/formZ 10/formZ 10.0 pro/formZ.app` (`CFBundleShortVersionString` 10.0;
  Codex's inventory records build 10.1.6), universal x86_64 + arm64, signed by
  team `RHEP6Z2P2J` with hardened runtime and 1,259 sealed resources.
- Folder: `Contents/Resources/Cursors/`.
- Prior work reused: Codex inventory at
  `~/.codex/visualizations/2026/11/01/01a1965d-ab68-7060-b0d7-367dfee8553b/formz-icon-inventory/`
  (cursor contact sheet `output/pdf/cursors-contact-sheets.pdf`, call-site
  evidence `resource-usage.csv`).

Each statement is tagged **[verified]** (read from the binary, file, or a test
run) or **[inferred]** (follows from verified facts but not observed inside
formZ).

## 1. What the folder contains [verified]

| Location | Files | Pixel sizes |
| --- | --- | --- |
| `Cursors/Cur_N.tif` | 99 | 66 × 16 px, 7 × 24 px, 23 × 32 px, 1 × 64 px (`Cur_614`), 1 × 128 px (`Cur_616`) |
| `Cursors/Cur_614@2x.tif` | 1 | 128 px |
| `Cursors/Cur_612.bmp` | 1 | 32 px, 24-bit RGB, no alpha |
| `Cursors/HD/Cur_N.tif` | 35 | exactly 2 × the base size for the same ID (16→32, 24→48, 32→64) |
| `Cursors/HotSpots.txt` | 1 | hotspot table |

- All TIFFs are 8-bit RGBA, uncompressed, sRGB, written by Photoshop CS–CS3.
  Two generations are visible: 2007 (16 px art, IDs 3–4, 128–134, 2xx, 4xx,
  5xx, 3xxx, 7xxx) and 2015 (24/32 px art plus `HD/`, IDs 1–2, 300–310,
  6xx, 6000–6001).
- `HD/Cur_1`, `Cur_2`, `Cur_6000`, `Cur_6001` are tagged 300 dpi; every other
  file is tagged 72 dpi.
- The 4th channel is stored two ways: 2007 files mark it "unspecified extra
  sample", 2015 files mark it "associated alpha". macOS ImageIO/NSImage treats
  both as alpha; Pillow drops the unspecified one and reports `RGB`. Use
  ImageIO (`sips`) or NSImage when inspecting these files.

## 2. How formZ loads a cursor [verified]

Loader: `libFZRT.dylib` (`Contents/Frameworks/`), identical logic in both
architecture slices. Called from the main executable through
`rsrc_get_cursor` → `fzrt_get_cursor`.

1. `fzrt_curs_init` opens `Resources/Cursors/HotSpots.txt`, reads the first
   integer as a row count, then reads exactly that many `id,x,y` rows
   (`fscanf "%d"`, then `"%d,%d,%d"` in a counted loop; x86_64 `0x3df97`–`0x3e0e5`).
2. `fzrt_get_cursor(id)` builds the name `Cur_%d.tif` inside `Cursors/`
   (x86_64 `0x3c01f`). There is no other path, suffix, or folder.
3. `fzrt_curs_find_hot_spot` defaults to **(7, 7)** and overwrites it if the
   ID is in the table (x86_64 `0x3dec2`).
4. `fzrt_curs_make_cursor`:
   - If the name contains `Cur_2.` → returns `[NSCursor crosshairCursor]`;
     `Cur_1.` → `[NSCursor IBeamCursor]`. The TIFF art for IDs 1 and 2 is
     never shown.
   - Otherwise `[[NSImage alloc] initWithContentsOfFile:]`, then
     `setSize:(32, 32)` unconditionally (x86_64 literal at `0xa3738` = 32.0;
     arm64 `mov x8, #0x4040000000000000` at `0x3d6b8`), then
     `[[NSCursor alloc] initWithImage:hotSpot:]` with the table values passed
     through unchanged as points.
   - Results are cached by filename.
5. The disassembled loader functions call no `backingScaleFactor` or
   `addRepresentation:` (both selectors exist elsewhere in the dylib), and
   the dylib has no `HD` or `@2x` string: the two-character `HD` byte runs
   sit inside the code section, not in a string table.

### Test of the loading call outside formZ [verified]

A Swift probe replicating step 4 (`NSImage(contentsOfFile:)`, `size = 32×32`,
best representation for a 2× context) produced:

| File loaded | Representations NSImage found | Picked on Retina |
| --- | --- | --- |
| `Cur_614.tif` (with `Cur_614@2x.tif` beside it) | 64 px only | 64 px — the `@2x` file is not loaded |
| `Cur_611.tif` | 32 px | 32 px (upscaled on Retina) |
| `Cur_3001.tif` | 16 px | 16 px (upscaled 2× even on a 1× display) |
| `Cur_611` + `HD/Cur_611` merged with `tiffutil -cathidpicheck` | 32 px and 64 px | 64 px |

## 2a. HD artwork under the standard name [verified outside formZ]

`tools/cursortest.swift` loads a file the way formZ does (`initWithContentsOfFile:`,
`setSize:(32,32)`, `NSCursor initWithImage:hotSpot:`) and renders the cursor
image into 32 px (1× display) and 64 px (2× display) bitmaps. "Solid" is
the share of visible pixels that are fully opaque; blur lowers it.

| File saved as `Cur_<id>.tif` | 1× display | 2× (Retina) display |
| --- | --- | --- |
| 611 base (32 px) | 32 px rep, 84% solid | 32 px upscaled, 53% |
| 611 `HD/` (64 px) | 64 px downsampled, 48% | **64 px, 56% — sharp** |
| 611 base + HD merged (`tiffutil -cathidpicheck`) | 32 px, 84% | **64 px, 56%** |
| 305 base / HD / merged | 63% / 21% / 63% | 33% / **38%** / **38%** |
| 6000 base (16 px) / HD (32 px) / merged | 61% / 44% / 44% | 59% / 37% / 37% |

- Putting the HD file under the standard name works: formZ's call loads it
  and macOS uses the 64 px pixels on Retina. 1× displays get a softer,
  downsampled cursor; a merged file keeps both sharp.
- The 2015 HD art is not just a bigger copy. The 6xx badges are redrawn as
  glossy green/red spheres, while the base files use flat badges.
- For the old 16 px IDs, `HD/` art is only 32 px. Under the forced 32-pt size
  that is 1× density, so it is still upscaled on Retina, and its hotspots
  would need doubling (for example `6000`: (7,7) → about (15,15)).
- Not yet observed inside formZ (see §7).

## 2b. When formZ's own cursors reach the screen [verified in code; host partly]

- `fzrt_set_cursor` returns without doing anything while `_in_modal_dlog` is
  set (both architectures). **Inside a modal dialog, formZ's cursors are
  never shown and macOS keeps its arrow.**
- `fzrt_curs_set_cursor(nil)` falls back to `[NSCursor arrowCursor]`.
- `update_cursor` handles only ID 0 (standard cursor), 1, 2, 6000 and 6001.
  Other IDs are set directly by feature code (animation tracks and timeline,
  image viewer, scrubbing).
- Host observation, 01 Nov 2026: the image viewer's zoom and scrub tools show
  the macOS arrow in **both** the original and the test copy, so the test
  copy did not cause it. It fits the modal-dialog rule if that viewer is
  modal (not confirmed).
- Places to check custom cursors: non-modal windows and palettes — the
  Animation palette timeline and tracks (`302`, `303`, `611`) and
  multi-column lists in palettes (`6000`, `6001`).

## 3. HotSpots.txt format [verified]

- Line 1: row count. Then `id,x,y` per row. Line endings are mixed CR, CRLF
  and one bare LF (between `624` and `631`); `fscanf` skips all of them.
- `x, y` are measured from the **top-left** of the image, in pixels of the
  base (1×) file, which formZ then uses as points. Checked against art:
  `Cur_3001` (16 px crosshair) centre ring = (7,7); `Cur_601` (32 px arrow)
  tip outline = (4,16); `Cur_611` (32 px arrow + cross) = (7,24).
- Value groups: 50 IDs use the default-looking (7,7); the 32 px "arrow with
  badge" family uses (4,16) for 601–605 and 621–623, and (7,24) for 611–617,
  624, 631–637.

## 4. Defects

| # | Defect | Effect | Status |
| --- | --- | --- | --- |
| D1 | `HotSpots.txt` declares **94** rows but contains **95**. The header is a plain row count, not a zero-based last index: the loader reads row 0, then rows 1–93. The last row `637,7,24` is never read. `tools/hsparse.c` replays the loop on the real file: `count=94 … last=636`, `left unread: 637,7,24`. | `Cur_637` gets the default (7,7) instead of (7,24): the click point is 17 pt above the arrow tip. | Parse [verified]; on-screen effect [inferred] |
| D2 | `Cursors/HD/` (35 files) is never opened by the loader. formZ has an HD switch: `update_cursor` (`cursor.c`) calls `fzrt_set_curs_hd(1)` when the main display is at least 1716 units wide (`cmp w8, #0x6b4`). But on macOS, `fzrt_set_curs_hd`, `fzrt_get_curs_hd` and `fzrt_curs_hd_avail` are stubs that return 0 in both architectures, and the loader never asks for the flag. The HD mechanism is switched off in the Mac build; it is probably used on Windows (not checked). | Retina displays draw 1× art upscaled; all HD artwork is dead weight on macOS. | [verified] |
| D3 | `@2x` siblings are not loaded: `initWithContentsOfFile:` reads one file and does not look for `@2x`. | `Cur_614@2x.tif` is unused. | [verified] |
| D4 | Every cursor is forced to 32×32 pt, but hotspots are not scaled. | 16 px cursors are drawn 2× (blocky) on every display and their hotspot lands at source pixel (3.5, 3.5) instead of the centre; 24 px cursors are scaled 1.33× with the same mismatch. Applies to whichever of the 66 × 16 px and 7 × 24 px cursors formZ still requests. | Scaling and hotspot pass-through [verified]; whether the 16/24 px IDs are still requested is not proven (see §5) |
| D5 | IDs 309, 310, 507, 508 have files but no hotspot row. | They fall back to (7,7). Correct only if their art is centred there. | [verified] |
| D6 | IDs 607, 608 have hotspot rows but no files. | Requests for them return no cursor (`rsrc_get_cursor FAILED` string exists in the caller). | Rows/files [verified]; whether they are requested is unknown |
| D7 | `Cur_612.bmp` is a stray 24-bit BMP. | Never loaded (loader only builds `.tif` names). | [verified] |
| D8 | `Cur_614.tif` (base) is byte-identical to `HD/Cur_614.tif` (64 px); `Cur_616.tif` (base) is 128 px. | These two are downsampled to 32 pt — accidentally the only cursors that are sharp on Retina. Suggests someone tried to fix Retina by replacing base files. | [verified] |
| D9 | Mixed dpi tags (300 vs 72) in `HD/`. | No runtime effect because `setSize:` overrides; would matter only if files were merged without resetting dpi. | [verified] |
| D10 | `Cur_305`/`Cur_306` (zoom with frame) use (5,5), which is empty space above the magnifier and frame. | The click point is not on any visible part of the art. May be deliberate (a corner of the zoom frame) or a 16 px-era leftover. | Position [verified]; intent unknown |

The rendering test in §2a shows D4: on `Cur_6000` the default (7,7) hotspot
sits in the top-left quarter of the stretched art instead of the centre of
the resize arrows.

## 5. Which cursors are actually used

Codex's static call evidence confirms constant IDs 1, 2, 301, 302, 303, 611,
6000 (animation, image viewer, list controls, rendering previews). Most other
IDs are probably selected through computed or table-driven IDs (for example
`update_cursor` in `cursor.c`), which static analysis cannot resolve. Treat
all 99 base IDs as potentially live until checked in the host.

`Cur_6000` (16 px, list controls) is the cheapest host check for D4: hover a
list column and compare the click point with the art.

## 6. Answers to the original questions

- **Retina vs HD**: same idea. `HD/` holds 2× art made in 2015, but formZ 10
  never reads it, so there is currently no working Retina path.
- **Why only one `@2x` file**: `Cur_614@2x.tif` looks like a single experiment.
  The loader cannot use `@2x` names at all (D3).
- **What would work without changing formZ**: one multi-representation TIFF
  per ID at the existing path — 32 px @ 72 dpi plus 64 px @ 144 dpi — made
  with `tiffutil -cathidpicheck`. NSImage loads both and picks the 64 px
  representation on Retina (§2 test). Hotspots stay in the 32-pt space.

## 6a. Proposed HotSpots.txt corrections

For the current art; a redesign defines new values in 32-pt space.

| Change | Rows | Reason |
| --- | --- | --- |
| Header 94 → 95 (or the final row count) | — | D1 |
| Add `309,5,5` and `310,5,5` | 309, 310 | Same art and layout as 305/306 without the centre dot |
| Add `507,7,7` and `508,7,7` | 507, 508 | Rotate-arrow siblings of 506 (7,7); keeps today's default explicitly |
| Drop `607`, `608` | 607, 608 | No files; harmless, but they mislead anyone reading the table |

## 7. Host checks still pending

`tools/make_test_copy.sh` builds `formZ cursor-test.app` beside the
installed app from the vendor's own art: base + `HD/` merged where HD is
exactly 2× (33 IDs; 614 and 616 skipped), `HotSpots.txt` rewritten with
97 rows, a correct count, the 6a additions, and 16/24 px hotspots scaled to
32-pt space (for example `6000` 7,7 → 14,14; `300` 7,7 → 9,9). Checked
outside formZ on 01 Nov 2026: the parse replay reads all 97 rows including
637; NSImage finds both representations (611: 32+64 px, picks 64 on
Retina). The copy's `codesign --verify` reports "a sealed resource is
missing or invalid"; the original still verifies.

The copy keeps the bundle ID `com.formZ.formZ`, so quit formZ before opening
it; otherwise macOS may just bring the running original forward.

**Result, 01 Nov 2026 (reported by the user):** the copy launched normally
without re-signing, despite the broken resource seal. Item 4 below passes.
Cursor appearance and hotspot accuracy (items 1–3) not yet reported.

None of the following has been run inside formZ:

1. D1: activate a tool that uses `Cur_637` and check the click point.
2. D4: hover a list control (`Cur_6000`) and check scale and click point.
3. A replaced multi-representation `Cur_N.tif` in a **copy** of the app shows
   sharp art on Retina and the correct hotspot.
4. Whether macOS still launches a copy whose sealed resources were edited:
   `codesign --verify` passes on the installed app now, and editing
   `Resources/Cursors/` breaks that seal (see the plan in `README.md`).
