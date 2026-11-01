# Spec: form·Z Array tools — LINE-first delivery

## Problem Statement

A form·Z modeler needs a dedicated array-creation workflow with predictable placement and controlled random variation across several layouts. Transform-tool copy modes and the existing rectangular, radial, and path tools do not by themselves express the requested unified workflow. The request is for one consistent tool, not a claim that native form·Z cannot already make these arrangements.

The tool must work with pre-picked and post-picked sources, preserve supported native geometry, and distinguish source objects from the geometry guiding placement. A passing facetted-object or straight-line test must not be used as evidence that NURBS, smooth solids, parametric objects, or curved boundaries work.

The project also needs incremental delivery: one newly tested behavior builds on the last accepted baseline. Shared behavior must become usable on LINE before more layouts are added.

## Solution

Provide one Array tool with LINE, Rectangle, 3D Grid, Radial, Path, Polygon Edges, and Vertices layouts. Tool Options contain source/output selection, applicable placement controls, and shared seeded randomization for interval/gap, size, rotation, and position.

Deliver LINE first through small working slices. Complete source picking, deterministic placement, native-geometry checks, copy/verified linked output, shared randomization, preview, Apply, cancellation, Undo/Redo, and committed-output reopening before declaring LINE_READY. The later layouts reuse that tested workflow and introduce their own placement and target-selection behavior incrementally.

Material functionality is deferred. Preserve existing source assignments and create no new materials. Saved editable array definitions are a proposed later phase and are not included in the core implementation tickets.

## User Stories

1. As a modeler, I want one Array tool, so that placement and variation controls remain consistent across layouts.
2. As a modeler, I want a working LINE workflow first, so that shared behavior is proven before the tool expands.
3. As a modeler, I want to pre-pick my sources, so that activating Array continues from my existing selection.
4. As a modeler, I want to pick sources after activating Array, so that I can work tool-first.
5. As a modeler, I want to complete or cancel source picking using verified host gestures, so that the tool follows form·Z interaction conventions.
6. As a modeler, I want incomplete inputs to prevent Apply, so that I do not create unintended output.
7. As a modeler, I want to repeat one object or an explicitly defined assembly, so that relative source placement is retained.
8. As a modeler, I want to replace sources without losing placement settings, so that I can compare alternatives.
9. As a modeler, I want an explicit source anchor, so that placement is based on the intended point.
10. As a modeler, I want LINE placement by count and pitch, so that I can create a known number of evenly spaced repetitions.
11. As a modeler, I want LINE placement by interval within an extent, so that I can fill a run without exceeding its boundary.
12. As a modeler, I want to fit a count to a LINE length, so that endpoint spacing is predictable.
13. As a modeler, I want graphic and numeric LINE inputs, so that I can work by snapping or dimensions.
14. As a modeler, I want layout-relative axes, so that the array is not restricted to world X.
15. As a modeler, I want pitch distinguished from clear gap, so that spacing describes the intended distance.
16. As a modeler, I want invalid counts, intervals, and excessive output requests explained before creation, so that failure does not leave partial output.
17. As a modeler, I want to repeat facetted sources, so that ordinary polygonal objects work.
18. As a modeler, I want to repeat a straight NURBS source, so that its representation is not replaced by a polygonal line.
19. As a modeler, I want to repeat curved NURBS sources and NURBS surfaces, so that native geometry is retained.
20. As a modeler, I want to repeat smooth and NURBS-faced solids, so that solid geometry remains solid.
21. As a modeler, I want supported parametric controls preserved, so that copies remain editable in the host.
22. As a modeler, I want unsupported nonuniform transforms identified, so that controls are not silently discarded.
23. As a modeler, I want independent copies, so that editing a source does not change those copies.
24. As a modeler, I want a verified native linked-output option, so that source geometry edits can propagate when requested.
25. As a modeler, I want position variation in document units or a defined percentage, so that jitter has a clear meaning.
26. As a modeler, I want uniform and supported per-axis size variation, so that repetition can vary in size.
27. As a modeler, I want rotation variation with explicit angle units and percentage references, so that orientation changes are predictable.
28. As a modeler, I want interval/gap variation separated from position jitter, so that the two different effects can be controlled independently.
29. As a modeler, I want a repeatable seed, so that I can reproduce an arrangement.
30. As a modeler, I want independent random channels, so that adjusting size does not unexpectedly reroll position.
31. As a modeler, I want existing placements to retain their random identity when count increases, so that small edits do not replace the whole arrangement.
32. As a modeler, I want zero variation to reproduce deterministic placement, so that disabling variation is predictable.
33. As a modeler, I want preview updates to replace earlier preview output, so that changes do not accumulate duplicates.
34. As a modeler, I want cancellation to remove temporary output, so that original geometry remains intact.
35. As a modeler, I want one-operation Undo/Redo for an applied array, so that the array behaves as one operation.
36. As a modeler, I want committed output to survive save/reopen, so that created geometry is durable.
37. As a modeler, I want Rectangle and 3D Grid layouts with independent axis spacing and extents, so that I can arrange rows and volumes.
38. As a modeler, I want layout changes to retain applicable shared settings, so that I can compare patterns efficiently.
39. As a modeler, I want Radial circle/arc placement, orientation, and angular interval variation, so that circular arrangements use the same workflow.
40. As a modeler, I want separate Sources and Targets pick sets, so that selecting a guide does not replace my source selection.
41. As a modeler, I want ambiguous mixed selections to request explicit roles, so that selection order does not silently change the result.
42. As a modeler, I want straight edges, straight NURBS paths, curved NURBS paths, arcs, and native curves tested separately, so that each advertised guide is supported on evidence.
43. As a modeler, I want path spacing measured by physical arc length, so that a curve's parameterization does not distort the intervals.
44. As a modeler, I want path margins, tangent alignment, and roll controls, so that placement follows the intended orientation.
45. As a modeler, I want whole-perimeter and per-edge polygon placement with explicit corner rules, so that boundary arrays are predictable.
46. As a modeler, I want actual NURBS and solid boundary edges evaluated, so that display facets do not determine the result.
47. As a modeler, I want one repetition per target topological vertex, so that the target set determines the output count.
48. As a modeler, I want target-only vertex preselection retained while I choose a source, so that both picking orders work.
49. As a modeler, I want explicit selected-vertex and whole-object vertex scopes, so that target intent is visible.
50. As a modeler, I want repeated references to one vertex deduplicated without merging distinct coincident vertices, so that identity rules are consistent.
51. As a modeler, I want vertex placement independent of display refinement, so that changing tessellation does not change output count.
52. As a modeler, I want size/rotation variation at vertices and optional position jitter, so that each vertex still owns one repetition.
53. As a modeler, I want existing material references preserved without material creation, so that array creation does not alter my material library.
54. As a developer, I want each gate's accepted commit, fixture, and measured result recorded, so that the next test starts from a known baseline.
55. As a developer, I want source and guide fixture choices recorded independently, so that a pass is not generalized to untested geometry combinations.

## Implementation Decisions

- The user-facing boundary is one Array tool with layout-specific placement controls and shared variation/output behavior. Exact native control widgets and gesture bindings remain host-verification tasks.
- Feature order is F01 through F15 for the core delivery. F01–F09 establish LINE_READY; F10–F15 add Rectangle, 3D Grid, Radial, Path, Polygon Edges, and Vertices in that order.
- Source pre-picking and post-picking are early LINE capabilities. Target-object role picking is added with Path; vertex-target selection is added with Vertices.
- Sources and Targets remain separate roles. Whole curves and objects can be sources, so selection order or geometry type alone is insufficient to assign an ambiguous target role.
- Generate placements from native source copies or a separately verified native linked mechanism. Do not reconstruct smooth/NURBS sources from display facets.
- Evaluate supported native guide curves for physical-distance placement and tangents. Each advertised adapter gets its own host evidence.
- Native topological vertices, NURBS control points, sampled points, and display tessellation are distinct. Vertex mode addresses topological vertices.
- Preserve source geometry and material assignments. No material duplication, material controls, or shader-parameter variation is implemented in the core scope.
- Preserve seeded element/channel identity through updates. Interval variation and positional jitter remain separate controls.
- Honor verified object-type transform restrictions; unsupported combinations are explained before output is committed rather than silently removing controls.
- No Array runtime currently exists. Native SDK tool callbacks and object operations are the recommended feasibility route, not proof of host compatibility or a settled internal module hierarchy.
- Ticket boundaries are small, demoable end-to-end slices. The existing G001–G120 gates remain one-behavior tests executed in order inside those slices; they are not 120 independent implementation issues.
- Each accepted gate supplies the baseline for its successor. Each ticket is blocked by its immediate predecessor because the agreed delivery contract uses a cumulative, LINE-first baseline.

## Testing Decisions

- Agreed primary test boundary: user-visible Array behavior from source/target selection and Tool Options through generated native scene output. Check counts, positions, geometry representation, preserved controls, shared identities, cancellation, and operation history at that boundary.
- Prefer this existing host/tool boundary to adding test-only public APIs. Mathematical helper tests may support coordinate/count/seed checks where useful; they do not replace a host test.
- Connect each new user-facing option to the working layout before accepting its gate. Passing an unconnected helper test does not complete a tool behavior.
- Existing native Smiley/Triangle builds establish build-tooling examples, not an Array runtime suite. Scatter's square-sampling self-check is prior art for a focused geometry check, not evidence of arbitrary host geometry support.
- Every case records one feature/gate, source fixture, guide fixture where applicable, actual geometry types, document units, tolerance, parameters/seed, expected result, observed result, and test evidence.
- Source choices include facetted objects, smooth solids, straight and curved NURBS curves, NURBS surfaces, NURBS-faced solids, and controlled solids. Guide choices include straight lines/edges, polylines, straight/curved NURBS paths, arcs, native curves, and straight/curved NURBS or solid boundary edges.
- Change one geometry dimension at a time initially. After source and guide cases pass, exercise the advertised combinations; an unrun combination is not marked supported.
- Use explicit millimeter fixtures and independently checked expectations. For example, four generated LINE placements at 100 mm pitch have anchors at 0, 100, 200, and 300 mm in the declared layout frame; this is a recorded test convention, not an implicit interpretation of an unlabeled control.
- Replay affected accepted regressions after shared-code changes. At LINE_READY and later layout checkpoints, rerun the applicable accumulated visible-tool cases. A failure retains the prior baseline.
- A gate is not accepted from an SDK declaration, successful compilation, signature check, or screenshot of a build log. All Array runtime gates are currently Not started.

## Out of Scope

- Material controls, material duplication, and material-property variation. If pursued later, the already-discussed rule is to duplicate varied materials and give them unique suffixes.
- Saved editable array definitions, dependency regeneration, and baking of procedural definitions; F16 remains a proposed follow-on, not core ticket scope.
- Surface/volume scatter, path deformation, collision-free packing, boolean trimming/merging, and a general effectors/fields system.
- Automatic NURBS control-point distribution or distribution over display tessellation under the name Vertices.
- Replacing native form·Z tools or claiming compatibility with untested third-party controlled-object types.
- Building all layouts before shared randomization and lifecycle work; LINE_READY is required first.

## Further Notes

This spec synthesizes the conversation and the current proposal at commit `27280eb`. The repository's detailed feature/gate plan remains the acceptance-case reference; issue bodies avoid prescribing implementation file locations.

Some earlier working policies remain proposals, including exact percentage references, count labeling, rectangle fill/perimeter presentation, corner orientation defaults, randomized fit behavior, and bounding-extent gap rules. Resolve a policy before its relevant gate and record the decision; do not silently treat an example fixture as a newly approved universal product rule.

The parent spec is a coordination artifact. Implement the approved child tickets in dependency order, not the entire spec in one run. Each ticket retains the ordered gates and previous-baseline requirement. No source code or runtime test has been implemented by creating this spec.
