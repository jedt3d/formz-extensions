# Icon redesign

Plan for redrawing formZ 10's interface icons so they are sharp on Retina
displays, using formZ's existing icon loader with no code changes. No new
artwork has been made yet. Read [FINDINGS.md](FINDINGS.md) first; the
constraints below come from it.

## What the tests established

- formZ loads `Contents/Resources/Icons/Cic_<id>.ENU.bmp` (and
  `Cic_<id>.Dark.ENU.bmp` first in dark mode) at run time. Edited files are
  used without re-signing.
- formZ scales each bitmap into its button. A file at **2× the original
  pixel size, under the same name**, is drawn at the original size with
  Retina detail. Verified for 48 px tool icons in light and dark mode.
- Format to produce: BMP, 40-byte header, 32-bit BGRA with **straight
  (non-premultiplied) alpha** in the 4th byte, bottom-up rows, pixel data at
  offset 54. Checked on the originals: of 141,454 semi-transparent pixels in
  the first 400 files, 38,922 have a colour value above their alpha, which
  premultiplied data cannot have.
- Most icons have no dark variant; formZ falls back to the light file.
  Icon buttons keep a light grey background in dark mode.

## Scope

| Original size | Files | With a known UI location | Target size |
| --- | --- | --- | --- |
| 48 × 48 | 554 | 396 | 96 × 96 |
| 32 × 32 | 116 | 22 | 64 × 64 |
| 16 × 16 | 84 | 69 | 32 × 32 |
| 18 × 18 | 52 | 8 | 36 × 36 |
| 128 × 128 | 19 | 19 | decide after Phase 0 |
| all other sizes (9–64 px) | the rest | mixed | 2× |

Counts are light-mode files from Codex's `inventory.csv`. Of the 48 px
icons, 323 belong to tools and commands, 34 to Tool Options, and 167 have no
known location yet. Icons with no known location come last.

## Style brief (decided 01 Nov 2026)

Fusion 360's approach (flat isometric shapes, colour by object type) with
SketchUp's colour discipline (few colours, one accent). Original artwork
only; the references guide principles, never shapes.

- **Grid:** 48-unit artboard (drawn once, exported at 96 px); keep about
  3 units of margin.
- **Outline:** navy `#1F3550`, 2 units, round joins, on every icon.
- **Accent:** red `#E0362C` only for action and direction (arrows, moving
  part, end point).
- **2D tools** (lines, curves, shapes): navy strokes, light-blue fill
  `#DCEBF7` where a shape is closed. formZ's point markers are kept as
  hollow white start point and red end point.
- **Object families,** flat 3-tone isometric faces (top / left / right):
  solids blue `#8EC3EE / #4F95D6 / #2F6DB0`; surfaces/NURBS orange; subdivision
  purple; meshes gold (tones set when those families start).
- **Variants:** one small badge in the bottom-right corner (green `#2E9E4F`
  ＋ add, red − subtract).
- **Must still read** in grey (formZ's Saturation setting) and on the light
  grey button background used in both light and dark mode.
- **formZ's icon decides what is drawn; the style decides how.** Copy each
  current icon's subject, composition and viewpoint (for example the tilted
  paint can, the vase-shaped revolve, the sphere-on-block fillet). Never take
  a subject from SketchUp, Fusion or other references.
- **Trace, don't redesign (01 Nov 2026):** each icon is traced over formZ's
  original at 48 units: same silhouette, faces, point positions and digit
  positions, rendered as 2D navy outlines with flat colour fills. The
  contact sheet's overlay tile (new at 50% over old) should show the two
  matching. Only the Pick arrow (3169) is a deliberate redesign, and it is
  approved as is.
- **Isometric rendering** for every object, including the Pick arrow, which
  keeps formZ's 3D extruded look.
- **formZ's colour conventions stay:** yellow `#F2C200` for start points,
  axes and fillet highlights; white for intermediate points; red for end
  points and action arrows.

## Decisions for you

1. **Visual direction:** decided; see the style brief above.
2. **How the art is made.** Recommended: vector masters (SVG, or a design
   tool that exports SVG/PNG) drawn on the 1× grid, exported as 2× PNG.
   Vector masters also allow a 3× or Windows export later.
3. **Who draws.** Hand-drawn remasters look best. AI or automatic upscaling
   is faster but blurs fine lines; use it only to prototype.
4. **Distribution.** The originals are AutoDesSys artwork, and remasters of
   them are derivative work. Keep them for your own use, or agree terms with
   AutoDesSys before sharing them. This repo commits only new masters, the
   manifest and the scripts, never the vendor's files.

## Phases

| Phase | Work | Done when |
| --- | --- | --- |
| 0. Remaining checks | Extend `tools/make_icon_test_copy.py` to double 16/18/32 px and 128 px icons too. In formZ, check that those still draw at their normal size, and that Preferences → Icon Display (Saturation, Tint) still applies to 2× art. | Each check recorded in FINDINGS.md. |
| 1. Pipeline | `manifest.csv` built from Codex's inventory: id, original size, target size, theme, UI location, priority. `tools/build_icons.py` (standard library only) turns 2× PNG exports into the BMP format above, checks size, depth and alpha, and writes `build/icon-redesign/Icons/`. A contact sheet compares old and new side by side. | Round trip verified: a PNG export of an original icon, enlarged 2×, builds to a BMP formZ draws exactly like the test copy. |
| 2. Pilot | Remaster about 10 icons that are always visible: the Pick, Line, Rectangle, Polygon and Move tools, plus the TOP/BOT/RGT/LFT view buttons. Install into a test copy and review on Retina and on a 1× display. | You approve the direction and the level of detail. |
| 3. Families | Remaster in order of visibility: tool palette (48 px) → top toolbars → Tool Options → palettes (16–32 px) → dialogs and preferences → icons with no known location. Add `.Dark` art only where an icon fails on dark backgrounds. | All manifest entries built; contact sheet reviewed per family. |
| 4. Package | Full `Icons/` replacement folder, plus `tools/install_icons.sh` that backs up the original folder, installs into a chosen app copy, and restores on request. | Installed copy reviewed in light and dark mode; rollback tested. |

## Pilot status (01 Nov 2026)

Ten masters in `masters/` (Pick 3169, V-Line 3033, Rectangle 3025, Polygon
3142, Circle 3038, Cube 3280, Extrusion 3422, Revolve 3023, Fillet 3480,
Paint 7235), rendered with:

```sh
swift projects/icon-redesign/tools/svg2bmp.swift build/icon-redesign/Icons 96 projects/icon-redesign/masters/*.svg
projects/icon-redesign/tools/install_icons.sh build/icon-redesign/Icons
```

`install_icons.sh` builds `formZ style-test.app` beside the original. A
comparison sheet (`build/icon-redesign/style-pilot-sheet.png`, not committed
because it contains vendor art) shows old vs new at Retina, 1×, greyscale
and on the dark-mode button.

Round 2 (after review): every pilot redrawn to follow formZ's own
composition: 3D extruded Pick arrow; V-Line as formZ's open path with
yellow/white/red points; yellow start points on Rectangle, Polygon and
Circle; Extrude with a see-through lower part; Revolve as a flared vase on a
yellow axis; Fillet as a sphere on a block with a yellow ring; Paint as
formZ's tilted can with red paint and handle.

Round 3: Pick arrow rebuilt as a symmetric arrow, rotated 32° and extruded
(`tools/pick_arrow.py` generates its master); the paint can pours a red
stream into a drop. **Approved by the user in formZ (01 Nov 2026).** Phase 2
done; next is Phase 3, starting with the rest of the 48 px tool palette.

## Phase 3 progress

Built icons and their formZ labels are listed in `manifest.csv` (id, name,
group, batch). Review with the contact sheet:

```sh
python3 projects/icon-redesign/tools/contact_sheet.py "/Applications/formZ 10/formZ 10.0 pro/formZ.app/Contents/Resources/Icons" build/icon-redesign/Icons projects/icon-redesign/manifest.csv build/icon-redesign/contact-sheet.html
```

| Batch | Group | Icons | Status |
| --- | --- | --- | --- |
| pilot | mixed | 10 | approved; all but Pick retraced over formZ's originals |
| 1 | Shapes (8), Draw (12, incl. Arc 3174) | 16 new | approved on the contact sheet (01 Nov 2026) |

Generators (masters are rewritten from these; edit the generator, not the SVG):
- `tools/gen_batch1.py`: point-based 2D icons (shapes, lines, splines, arcs)
  from measured formZ geometry; digits in Helvetica Bold 12.5, each checked
  and nudged clear of lines and dots.
- `tools/gen_traced3d.py`: Cube, Extrusion, Revolve, Fillet, Paint, traced as
  polygons and ellipses over the originals.
- `tools/pick_arrow.py`: the approved Pick arrow (3169).

The contact sheet's overlay tile shows each new icon at 50% over formZ's
original; it is the acceptance check for every batch.

## Repository rules

- Commit masters, manifest, scripts and docs only. Generated BMPs go to
  `build/icon-redesign/` (ignored). Never commit formZ's original icons or
  screenshots of them.
- Never modify the installed `/Applications/formZ 10/` app; build and test
  in a copy beside it, as `tools/make_icon_test_copy.py` does.
- Every formZ update replaces the bundle; reinstall the set after updating.

## Validation available today

`python3 -m py_compile tools/make_icon_test_copy.py`, plus the host test
recorded in FINDINGS.md §3. Phase 1 adds automated checks of the BMP output.
Appearance can only be judged inside formZ.
