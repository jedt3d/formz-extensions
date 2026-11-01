# Proposal: form·Z Array tool

- Date: November 1, 2026
- Status: Proposed; implementation has not started
- Branch: `feature/array-tools-proposal`
- Repository baseline: `3d4ec3f`
- Development plan: [Incremental gates](../plans/array-tools-incremental.md)

## Objective

Create a dedicated Array tool with consistent placement and randomization controls across seven layouts. Support native source geometry and both pre-picking and post-picking. Develop one behavior at a time; a passing, recorded gate becomes the baseline for the next gate.

form·Z already has Rectangular Array, Radial Array, and Place Along Path. The new tool's value is a consistent workflow, controlled random variation, vertex placement, explicit polygon-edge policies, and geometry preservation. See the [source-backed research](../research/array-tools.md#what-formz-already-provides) for existing-tool evidence and SDK limitations.

## Feature list

Fxx labels are stable feature identifiers, not development priorities. Shared workflow features are listed first below. The [development plan](../plans/array-tools-incremental.md) defines execution order with sequential Gxxx gates, beginning with source pre-picking and post-picking immediately after registration.

| ID | Feature | Required behavior |
| --- | --- | --- |
| F14 | Shared Tool Options | One Array tool, seven layout modes, layout-specific placement controls, and shared randomization controls. |
| F11 | Pre-picking | Accept source preselection, target-only preselection, and unambiguous mixed-role selections. |
| F12 | Post-picking | Collect Sources and Targets separately; target picking preserves source selection. |
| F10 | Copy / linked output | Offer independent copies and verified native linked repetition behavior; distinguish legacy clones and components during feasibility tests. |
| F13 | Native geometry | Target facetted, NURBS, smooth-solid, and controlled/parametric sources without silently converting geometry or dropping controls. |
| F15 | Operation lifecycle | Repeatable preview, cancellation cleanup, and one-operation Undo/Redo. |
| F08 | Placement semantics | Distinguish count, pitch, clear gap, and fit-to-extent; use explicit units and percentage references. |
| F09 | Randomization | Independently vary interval/gap, size, rotation, and position using numeric ranges or percentages with defined reference values; provide a repeatable seed. |
| F01 | Line | Place by count, numeric interval, or overall length; support graphic and numeric layout definition. |
| F02 | Rectangle | Two-dimensional grid with independent counts, spacing, and dimensions along two axes. |
| F03 | Cube / 3D grid | Three-dimensional grid with independent counts, spacing, and dimensions; unequal side lengths are allowed. |
| F04 | Radial | Center, axis/plane, radius, full circle or arc, count or angular interval, and orientation choice. |
| F05 | Path | Lines/polylines and supported curved/NURBS paths; count or arc-length interval, endpoint margins, and orientation/roll. |
| F06 | Polygon edges | Selected edges or shape boundary; whole-perimeter or per-edge placement, with explicit corner and shared-vertex handling. |
| F07 | Vertices | Exactly one repetition per target topological vertex, with optional randomized transforms. |
| F16 | Saved editability | Recommended follow-on capability: save an array definition, reopen it, and regenerate its owned output. Feasibility and host integration remain unverified. |

All features above are planned, not tested capabilities. F01–F15 describe the proposed core release based on the discussion. F16 is a proposed follow-on beyond that release.

## First usable milestone: LINE with shared features

Build and test the shared behavior through one complete LINE workflow before adding Rectangle or another layout:

1. Register the LINE-capable tool, then establish source pre-picking and post-picking.
2. Produce ordinary LINE copies with count/interval/length, source anchors, graphic/numeric input, and source selection editing.
3. Prove native source preservation and the independent-copy versus verified linked-output choice through LINE.
4. Add each shared randomization parameter separately, including seed stability and numeric/percentage inputs, through LINE Tool Options.
5. Complete LINE preview replacement, Apply, cancellation, Undo/Redo, and saved committed output.
6. Run the accumulated visible-tool fixtures and record the accepted commit as **LINE_READY**.

Rectangle development starts only after LINE_READY passes. Later patterns reuse these verified services and add their own placement generator, applicable controls, and focused regression fixtures. Do not build every layout's deterministic placements first and integrate randomization or lifecycle at the end.

Some behavior needs a second layout: Path introduces target-object role picking and curve orientation; Vertices adds vertex-target scope; Radial adds angular intervals; Rectangle permits the first layout-switch test. These additions remain separate gates in their layout phases. This does not postpone ordinary source pre/post picking or other shared LINE behavior.

## Proposed interface

One **Array** icon/command opens Tool Options with these groups:

1. **Sources / Output:** source summary, source anchor, and copy/linked-output selection.
2. **Layout:** Line, Rectangle, 3D Grid, Radial, Path, Polygon Edges, or Vertices.
3. **Placement / Targets:** only the controls relevant to the chosen layout, plus an explicit target summary.
4. **Randomization:** size, rotation, position, applicable spacing/gap variation, coordinate frame, and seed.
5. **Preview / Apply:** inspect and commit the current result or cancel it.

Vertex mode displays a derived target count and no spacing field. Radial mode exposes angular placement. Grid modes expose per-axis counts and spacing. Layout changes preserve valid source selections and shared settings while revalidating targets. Optional future layout-specific icons can activate the same tool with a preset layout; separate implementations are unnecessary.

These are interface proposals. Exact native controls, selection gestures, and command registration must be verified in the installed host.

## Selection contract

Keep **Sources** and **Targets** as separate pick sets, with visible counts and pick/edit/replace actions.

| Starting selection | Proposed workflow |
| --- | --- |
| Source objects pre-picked | Activate Array, adopt valid sources, then define the layout or pick targets. |
| Nothing pre-picked | Activate Array, pick and finish Sources, then define placement or collect Targets. |
| Sources pre-picked; targets post-picked | Freeze source roles while collecting compatible target geometry. |
| Sources and targets pre-picked together | Assign roles only if unambiguous; otherwise ask for explicit role assignment in Tool Options. |
| Target vertices pre-picked | Retain them, then collect sources. |
| Whole objects intended as vertex targets | Explicitly designate Targets and All Vertices scope; do not infer their role from geometry type alone. |

Never use selection order alone to decide which object is the source or path. Picking a target must not replace Sources. Returning to a selection stage preserves parameters. Graphic placement points and snapping do not automatically add vertex targets. Invalid selections show a reason and do not generate partial output.

## Working policies to review before their development gates

The user has not chosen every edge case. The following defaults make the tests concrete and reviewable; they are proposed policies, not silently accepted requirements.

| Topic | Proposed policy |
| --- | --- |
| Count | Count means generated placements; originals are retained and excluded. Grid total is `Nx × Ny × Nz`. A multiple-object source can be treated as one repeated assembly. |
| Layout origin | The first placement is at the defined layout origin. It may coincide with the source if the user chooses the same anchor; no hidden copy is added or removed. |
| Rectangle | Filled grid. Use Polygon Edges for perimeter placement; a rectangle-perimeter preset can be added later. |
| Vertex identity | Deduplicate references to the same topological vertex; retain distinct coincident vertices. Do not use display-tessellation vertices. |
| Vertex scope | Explicit Selected Vertices or All Vertices of designated target objects. NURBS control points and sampled points are separate future scopes. |
| Source orientation | Preserve source orientation initially; tangent/axis alignment and roll are explicit options. |
| Path distribution | Use physical arc length, not equal NURBS parameter increments. Closed paths have no repeated seam placement. |
| Polygon edges | Whole-perimeter spacing continues around the loop; per-edge mode restarts on each edge. Shared corner identities are deduplicated. Exact corner orientation is decided at its gate. |
| Numeric variation | Position/gap use document length units, rotation uses degrees, and numeric size uses explicit scale-factor ranges. Absolute-dimension size entry is a separate optional extension. |
| Percentage variation | Gap/pitch reference the configured nominal gap/pitch; size references source scale; position references the displayed nominal spacing per axis; rotation references an explicitly entered base angle. An undefined/zero reference requires numeric entry. |
| Random identity | Reproduce values from seed, stable element identity, and parameter channel. Adding a target should not reroll existing identified elements. |
| Random fit | Fixed-count mode preserves sampled intervals and allows total extent to change. Fixed-extent interval mode stops before crossing its boundary and leaves a remainder. Exact fit with randomized intervals is a later policy, not automatic rescaling. |
| Clear gap | First support an explicit bounding-extent rule in the layout direction. This is not a collision/packing guarantee for arbitrary rotations or curved paths. Define unsupported combinations before enabling them. |
| Parametric scaling | Validate object-type transform restrictions. Explain unsupported nonuniform/mirrored transforms before creation; never silently remove controls. |

If a policy changes, revise its expected test result before implementing the corresponding gate. An unresolved policy leaves that gate Not started; it does not block independent earlier gates.

## Geometry and output strategy

Recommended starting point: a native SDK tool using form·Z's tool callbacks, pick sets, and native object copy/transform operations. Existing scripts and compiled samples are references; this proposal does not yet choose a complete internal architecture or introduce a framework.

Source and target support are separate compatibility questions:

- Copy or instance native sources; preserve NURBS/smooth geometry and controlled-object data where the transform is supported.
- Evaluate supported native curves for path positions/tangents. Any adapter for arcs, polylines, piecewise paths, or solid boundary edges gets its own host test.
- Native topological vertices, control points, and sampled points must remain distinct.
- Independent copies, legacy clone behavior, and component instances must be investigated separately. Do not label them equivalent based only on an API name.
- Check the parameter-retention restriction for nonuniform scaling documented in `sdk/FZ_SDK_923/src/h/fz_otyp_api.h:102`.

Implement placement computation separately from scene creation only as far as needed for meaningful tests. Unit tests can verify coordinates, counts, bounds, and seeded values; host tests must verify registration, picking, geometry representation, linked editing, Undo, and saved behavior. Existing SDK declarations are evidence of possible implementation paths, not runtime proof. See the [research evidence](../research/array-tools.md#evidence-in-this-repository-and-local-sdk).

## Material scope and exclusions

**Material work is deferred.** Preserve existing source material assignments; add no material controls, new materials, or material-parameter variation in this plan. Retain the future rule: if material variation is developed later, duplicate the source material and give each generated variation a unique suffix.

Also outside this proposal's core release: surface/volume scatter, deformation along a path, collision-free packing, merging/boolean trimming of repetitions, and a general effectors/fields system. NURBS control-point distribution is not implied by Vertex mode. These exclusions preserve the agreed scope; they do not remove native form·Z functionality.

## Delivery and success criteria

Use the [incremental plan](../plans/array-tools-incremental.md): one new behavior and one focused acceptance test per gate. A gate is accepted only with a known-good commit, actual evidence, and passing prior regression checks. Documentation, compilation, and runtime passes are recorded separately.

LINE_READY is the first usable shared-feature baseline. The other six layouts extend it incrementally; each reruns the applicable shared workflow tests before becoming a baseline for the next pattern.

The first complete release is one committed-copy/verified-linked-output Array tool covering F01–F15, with all seven layouts, randomization, both picking workflows, and a tested geometry support matrix. Saved editable definitions (F16) follow their own gates. If a required capability fails, report the specific limitation and revise the proposal; do not quietly narrow the feature list or claim an untested type works.

This branch contains proposal and research documents only. No Array runtime code, new test runner, or host behavior is implemented here.
