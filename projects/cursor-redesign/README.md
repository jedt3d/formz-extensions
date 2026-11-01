# Cursor redesign

Plan for replacing formZ 10's cursor artwork with sharp 1× and Retina versions
that load through formZ's existing, unchanged cursor loader. No artwork has
been made yet. Read [FINDINGS.md](FINDINGS.md) first: it records how formZ
loads cursors, what the hotspot file means, and the defects this plan works
around.

## Constraints from the findings

- formZ loads only `Contents/Resources/Cursors/Cur_<id>.tif` and always shows
  it at **32 × 32 points**. `HD/` folders and `@2x` names are ignored.
- Retina works when `Cur_<id>.tif` itself contains 64 px art. A single 64 px
  image is sharp on Retina but soft on 1× displays. A file holding both
  32 px and 64 px versions (built with `tiffutil -cathidpicheck`, part of
  macOS) is sharp on both (FINDINGS.md §2a).
- Hotspots are top-left `x,y` in 32-pt space. The first line of
  `HotSpots.txt` must equal the number of rows, or the extra rows are ignored.
- IDs 1 and 2 are replaced by the system I-beam and crosshair; redesigning
  them has no visible effect.
- The installed app is vendor-signed and seals its resources. Replacing files
  inside it breaks that seal.

## Decisions

1. **Size (decided, 01 Nov 2026):** every cursor is a 32 × 32-pt HD cursor on
   macOS. Each `Cur_<id>.tif` carries a 64 px Retina representation and a
   32 px representation for 1× displays. The old 16 px cursors are redrawn at
   full 32-pt size, which also removes the stretching and misplaced hotspots
   (D4).
2. **Delivery (recommended):** test on a copy of `formZ.app` placed beside the
   original in `formZ 10.0 pro/`, so it still finds `Support/` and `Plugins/`.
   Never edit the installed app. Install with a script that backs up the
   original `Cursors/` folder and can restore it. Re-sign the copy ad hoc only
   if macOS refuses to launch it after the edit. For permanent use, send
   FINDINGS.md and the finished set to AutoDesSys, because every formZ update
   replaces the app and its cursors.
3. **Style (recommended):** follow macOS's own cursors.
   - Black glyph with a white outline 1 pt wide (2 px on Retina), aligned to
     the pixel grid, with no gradients or gloss.
   - Badges keep their meaning, as flat colours: green add, red
     subtract/forbidden, blue move/info.
   - Hands and magnifiers become outline drawings in the same weight,
     replacing the photographic 2015 art.
   - Hotspots go on a whole point at the visible tip or centre.

## Phases

| Phase | Work | Done when |
| --- | --- | --- |
| 0. Host checks | On a copy of the app: confirm D1 (`Cur_637` hotspot) and D4 (16 px scaling, via `Cur_6000` in list controls); confirm a re-signed copy launches. | Each item recorded as pass/fail in FINDINGS.md §7. |
| 1. Pipeline | `projects/cursor-redesign/` gets: a manifest (`id, family, hotspot x,y` in 32-pt space), master artwork per ID drawn on a 32-pt grid, and `build.sh` that exports 32 px + 64 px PNGs, merges them with `tiffutil -cathidpicheck` into `Cur_<id>.tif`, and writes `HotSpots.txt` with the correct count and CR line endings. Only `sips` and `tiffutil`; no new dependencies. | `build.sh` passes `sh -n` and produces a test set that the NSImage probe reads as 32 px + 64 px. |
| 2. Pilot | Redraw three cursors covering each case: `6000` (old 16 px), `611` (32 px arrow + badge), `637` (D1 victim). Install into the app copy. | Sharp on Retina and on a 1× display, click point exactly on the tip/centre. |
| 3. Families | Redraw by family, in this order (most-used first, per available call evidence): 30x hand/scrub/zoom (300–310), 6xx arrow-with-badge (601–637), 600x list, then the 2007 16 px groups (128–134, 2xx, 4xx, 5xx, 20xx, 30xx, 700x). | Every ID in the manifest has art and a hotspot. |
| 4. Package | Full `Cursors/` replacement folder: 99 `Cur_<id>.tif` files and `HotSpots.txt` with rows for every ID (including 309, 310, 507, 508). Leave out `HD/`, `@2x`, and the stray BMP; formZ doesn't read them. Install and rollback steps for a copy of the app. | Contact sheet of the new set reviewed; host check on the copy passes. |

## Repository rules for this project

- Never commit formZ's original cursor files or screenshots of them; they are
  third-party artwork (see `AGENTS.md`). Commit only new artwork, the
  manifest, scripts, and docs.
- Generated TIFFs go to `build/cursor-redesign/` (ignored).
- Don't modify the installed `/Applications/formZ 10/` app; work on a copy.

## Validation available today

The build needs only macOS command-line tools. Host loading, appearance, and
hotspot accuracy can only be checked inside formZ and are pending until
someone runs them.
