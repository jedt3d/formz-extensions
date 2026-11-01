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

F01 onward now follows the order in which features are completed. Finish a feature's focused gates before starting the next feature. Earlier unexecuted feature IDs have been replaced; F01–F16 cover the current scope, and the sequence can grow as features are added. The [development plan](../plans/array-tools-incremental.md#feature-to-gate-delivery-map) maps each feature to its sequential tests.

| ID | Feature | Required behavior |
| --- | --- | --- |
| F01 | Tool shell and required-input state | Register one Array tool with an initial LINE interface; Apply remains unavailable with incomplete input. |
| F02 | Source pre-picking | Adopt valid source preselection without a redundant selection step. |
| F03 | Source post-picking | Select sources after activation, complete that pick set, or cancel it. |
| F04 | One native copy and basic operation lifecycle | Create and position one copy, then prove Undo, Redo, and unfinished-operation cancellation. |
| F05 | Deterministic LINE and placement controls | Count, pitch, clear gap, interval/overall length, graphic/numeric entry, source anchors, and assembly behavior. |
| F06 | Native source compatibility | Test straight/curved NURBS sources, NURBS surfaces/objects and NURBS-faced solids, smooth solids, and controlled solids separately; preserve their native representations and supported controls. |
| F07 | Copy versus linked output | Prove independent copies and the chosen native linked mechanism through LINE; distinguish legacy clones and components during feasibility tests. |
| F08 | Shared randomization on LINE | Add interval/gap, size, rotation, and position variation one channel at a time, with numeric/percentage references and a reproducible seed. |
| F09 | Complete LINE preview and output lifecycle | Finish preview, Apply, cancellation, multi-element Undo/Redo, and committed-output reopening; preserve existing material assignments. Accept LINE_READY here. |
| F10 | Rectangle and first layout switching | Add a two-axis grid and its extents, then prove shared-setting retention across the first two layouts. |
| F11 | Cube / 3D Grid | Extend the accepted grid to three axes with independent counts/spacing/extents and unequal side lengths. |
| F12 | Radial | Add center, axis/plane, radius, circle/arc, count/angular interval, radial orientation, and angular interval variation. |
| F13 | Path and target-role picking | Add separate Sources/Targets picking, then test straight edges, straight NURBS paths, curved NURBS paths, arcs, and native curve/spline objects; prove arc-length placement and orientation. |
| F14 | Polygon Edges and native object boundaries | Add whole-perimeter/per-edge policies and corner rules; separately test polygon edges, straight/curved NURBS boundaries, and straight/curved solid edges. |
| F15 | Vertices | Add vertex-target selection and scope, one repetition per topological vertex, and the applicable shared random transforms. |
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

F01–F09 complete that first-pattern baseline. F10–F15 add the remaining layouts in order. F16 is the proposed saved-editability follow-on.

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

### Selectable geometry test cases

Every applicable test must identify **Source fixture** and **Guide/target fixture** independently. A NURBS object can be the thing copied along a straight LINE; a solid object can be copied along a NURBS curve. These test different capabilities. The [plan's fixture catalog](../plans/array-tools-incremental.md#selectable-source-and-guidetarget-fixtures) makes those choices explicit, with separate acceptance evidence for each case.

A selected straight polygon edge, a geometrically straight NURBS curve, and a curved NURBS/native curve are separate guide cases. A whole solid or NURBS surface is a source/target owner, not automatically a path: designate its actual boundary edge for edge placement. A pass on a facetted line or object does not pass any NURBS or solid case. Keep unimplemented cases unavailable with an explanation instead of silently converting them to facets.

## Material scope and exclusions

**Material work is deferred.** Preserve existing source material assignments; add no material controls, new materials, or material-parameter variation in this plan. Retain the future rule: if material variation is developed later, duplicate the source material and give each generated variation a unique suffix.

Also outside this proposal's core release: surface/volume scatter, deformation along a path, collision-free packing, merging/boolean trimming of repetitions, and a general effectors/fields system. NURBS control-point distribution is not implied by Vertex mode. These exclusions preserve the agreed scope; they do not remove native form·Z functionality.

## Delivery and success criteria

Use the [incremental plan](../plans/array-tools-incremental.md): one new behavior and one focused acceptance test per gate. A gate is accepted only with a known-good commit, actual evidence, and passing prior regression checks. Documentation, compilation, and runtime passes are recorded separately.

LINE_READY is the first usable shared-feature baseline. The other six layouts extend it incrementally; each reruns the applicable shared workflow tests before becoming a baseline for the next pattern.

The first complete release is one committed-copy/verified-linked-output Array tool covering F01–F15, with all seven layouts, randomization, both picking workflows, and a tested geometry support matrix. Saved editable definitions (F16) follow their own gates. If a required capability fails, report the specific limitation and revise the proposal; do not quietly narrow the feature list or claim an untested type works.

This branch contains proposal and research documents only. No Array runtime code, new test runner, or host behavior is implemented here.
