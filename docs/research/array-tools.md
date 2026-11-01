# Array creation study: Cinema 4D, Blender, and form·Z extension opportunities

Research date: November 1, 2026. Scope: object/geometry repetition, alignment, variation, instancing, and editable workflows. This is documentation research, not a runtime comparison or performance benchmark.

The current product scope and development sequence are maintained in the [Array proposal](../proposals/array-tools.md) and [incremental plan](../plans/array-tools-incremental.md). The observations and earlier recommendations below are supporting research; the proposal is the current feature-list reference.

## Version baseline

- Blender's official release listing identifies **5.2.3 LTS**, updated October 22, 2026, as an active release; 5.3 is beta. The comparison includes the redesigned 5.x modifiers, with a separate legacy note. [Blender releases](https://www.blender.org/releases/)
- Maxon's **Cinema 4D 2027 help** supplies the Cloner documentation baseline. This identifies the documentation consulted, not the version installed on this workstation or a verified shipping-release claim. The docs distinguish Basic distributions from Advanced node distributions introduced in 2026.1. [Cloner settings](https://help.maxon.net/c4d/2027/en-us/Content/html/OMOGRAPH_CLONER-ID_OBJECTPROPERTIES.html)
- Older Blender tutorials often describe only the legacy Array. Blender 5.0 introduced Geometry Nodes-based Array, Scatter on Surface, Instance on Elements, and Randomize Instances modifiers, among others. Treat these as packaged tools in addition to custom Geometry Nodes graphs. [Blender 5.0 modeling release notes](https://developer.blender.org/docs/release_notes/5.0/modeling/)

## What “array” means in each application

Cinema 4D's literal **Array Object** is a comparatively narrow generator: child objects repeat around its origin using radius, copy count, wave amplitude, and frequency controls. Its Copies value excludes the still-visible original, so total objects equal Copies plus one. This is separate from general distribution across a sphere's surface. [Array overview](https://help.maxon.net/c4d/en-us/Content/html/OARRAY.html), [Array settings](https://help.maxon.net/c4d/2027/en-us/Content/html/OARRAY-ID_OBJECTPROPERTIES.html)

The broader Cinema 4D comparison is **MoGraph Cloner**: child source objects, distribution patterns, Effectors, and Fields. A Cloner can be nested and converted into editable objects when needed. [Cloner overview](https://help.maxon.net/c4d/2026/en-us/Content/html/OMOGRAPH_CLONER.html)

Blender's current **Array modifier** has Line, Circle, Curve, and Transform shapes. Surface scattering and element instancing have their own modifiers; arbitrary arrangements can also be assembled in Geometry Nodes. These capabilities do not all live in one Array panel. [Array modifier](https://docs.blender.org/manual/en/5.0/modeling/modifiers/generate/array.html), [5.2 Generate modifiers](https://docs.blender.org/manual/en/5.2/modeling/modifiers/generate/index.html), [Geometry Nodes index](https://docs.blender.org/manual/en/5.0/modeling/geometry_nodes/index.html)

## Feature comparison

| Task | Cinema 4D | Blender | Similarity or difference |
| --- | --- | --- | --- |
| Straight repetition | Cloner Linear; per-step or endpoint transforms. [Settings][c4d-cloner] | Array Line; relative, absolute, or endpoint spacing. [Array][blender-array] | Both expose numerical repetition; spacing conventions differ. |
| Circle or partial arc | Cloner Radial: radius, count, plane, start/end angle, alignment. [Settings][c4d-cloner] | Array Circle: radius, axis, full circle/arc, count or angular distance. [Array][blender-array] | Both provide a direct circular workflow in current versions. |
| Rectangular/spatial grid | Cloner Grid: XYZ counts; spacing or overall extent. [Settings][c4d-cloner] | Stack arrays or construct a point lattice using grid/line primitives and instancing. [Legacy Array][blender-legacy], [Mesh nodes][blender-mesh] | Dedicated Cloner mode versus composition; current Array's listed shapes do not include Grid. |
| Staggered/honeycomb pattern | Dedicated Cloner Honeycomb, alternating row offsets. [Settings][c4d-cloner] | Build staggered rows in a Geometry Nodes setup. [Geometry Nodes][blender-nodes] | Direct preset versus a custom procedural construction; Blender column is a design inference, not a claimed built-in honeycomb button. |
| Repeat along a curve | Cloner Object/spline supports count, step, even spacing, tangent alignment, and rail orientation. [Spline documentation][c4d-spline] | Array Curve, or Curve to Points sampling followed by instancing. [Array][blender-array], [Curve to Points][blender-curve-points] | Both can place rigid repetitions along paths. |
| Surface and element placement | Object distribution includes points, edges, polygon centers, surface, volume, and normal alignment. [Object distribution][c4d-object] | Separate Scatter on Surface and Instance on Elements tools. [Release notes][blender-modifiers], [Element instancing][blender-elements] | Comparable families; distinct tools and selection semantics. |
| Surface density and separation | Cloner surface distribution has count and seed. [Object distribution][c4d-object] | Scatter on Surface offers amount/density, masks, and Poisson minimum spacing. [Scatter][blender-scatter] | Do not equate random surface copies with minimum-distance sampling. |
| Volume filling | Cloner volume distribution; grid can be bounded by shapes. [Object distribution][c4d-object], [Grid settings][c4d-cloner] | Distribute Points in Volume supports random or regular-grid points, then instance geometry. [Volume points][blender-volume] | Both cover volume workflows; mesh-to-volume preparation may be needed in Blender. |
| Multiple source objects | Cloner child order supports Iterate, Random, or Blend. [Clone arrangement][c4d-node] | Element instancing can use a collection and select sources randomly, sequentially, or by index. [Element instancing][blender-elements] | Sequence/random choice are common; C4D's Blend additionally interpolates compatible source properties. |
| Variation and falloff | Effectors modify transforms and other clone properties; Fields weight their influence. [Effectors][c4d-effectors] | Current Array has seeded transform/scale/flipping variation; custom fields can drive node setups. [Array][blender-array], [Fields](https://docs.blender.org/manual/en/latest/modeling/geometry_nodes/fields.html) | C4D foregrounds effectors and spatial controls; Blender foregrounds modifiers and node composition. |
| Memory and final geometry | Instance, Render Instance, and Multi-Instance modes. [Settings][c4d-cloner] | Instances can stay references; Realize Instances materializes geometry for subsequent operations. [Instance on Points][blender-instances], [Array][blender-array] | Both distinguish instances from materialized geometry; their representations and restrictions are not identical. |
| Merge and end treatment | Not established here as equivalent to Blender's Array mesh-welding controls. | Current Array merges by distance after realization; legacy Array additionally documents start/end caps and first/last merging. [Array][blender-array], [Legacy][blender-legacy] | Geometry construction is a separate concern from object placement. |

## Important distinctions

### Rigid placement versus deformation

Blender's legacy **Fit Curve** determines how many repeated copies fit the curve's length; it does not itself bend the result along the path. The separate **Curve modifier** deforms a mesh along a curve. Rigid curve instancing instead places and orients individual repetitions using sampled positions and frames. [Legacy Array][blender-legacy], [Curve modifier](https://docs.blender.org/manual/id/4.5/modeling/modifiers/deform/curve.html), [Curve to Points][blender-curve-points]

This matters for railings, seats, and bolts: keeping each part rigid is different from deforming a continuous tiled strip. A tool specification should explicitly choose one behavior rather than use “follow curve” for both.

### Seeded randomness versus collision guarantees

Blender's Scatter on Surface documents a minimum distance for sampled points in Poisson Disk mode. That is not a promise that differently sized or rotated source meshes cannot intersect. Full-object collision or packing needs an additional rule and validation. [Scatter][blender-scatter]

### Live editing versus baked copies

Blender modifiers evaluate non-destructively until applied; stack order affects the result. C4D Cloner retains its sources and settings until made editable. Creating ordinary copies with a script does not automatically reproduce either application's persistent generator behavior. [Blender modifier introduction](https://docs.blender.org/manual/en/5.0/modeling/modifiers/introduction.html), [Cloner overview](https://help.maxon.net/c4d/2026/en-us/Content/html/OMOGRAPH_CLONER.html)

Instance performance is also conditional. C4D Render Instances have restrictions including individual deformation and source animation state; Multi-Instance further optimizes repeated geometry. These names should not be used as interchangeable labels for ordinary copies. [Instance documentation](https://help.maxon.net/c4d/2026/en-us/Content/html/OINSTANCE-ID_OBJECTPROPERTIES.html)

## Design lessons for an extension plan

These are recommendations inferred from the comparison, not claims about form·Z's API capabilities:

1. Specify distribution separately from source selection: positions, orientation, scale, and source index are distinct controls.
2. Make count semantics explicit, including whether the original is counted and whether closed loops duplicate an endpoint.
3. Offer spacing by count, absolute step, and overall extent only where each has a clear geometric meaning.
4. Name orientation choices explicitly: retain source orientation, follow tangent, align to normal, and choose an up direction.
5. Preserve a random seed and parameters so changes can be reproduced.
6. Distinguish a preview, committed copies, linked instances, and a saved editable generator. Each is a separate implementation commitment.
7. Keep distribution, geometry merging, and collision avoidance separately testable.

## What form·Z already provides

The current vendor comparison lists rectangular/radial copy arrays, transformation macros, alignment/distribution, surface and volume scatter, and surface painting. Components and instancing are also listed. Therefore, basic duplication, scattering, and instances should not be presented as new capabilities that form·Z lacks. Edition availability differs. [AutoDesSys comparison](https://autodessys.com/formz_comparison/)

form·Z 10 Pro's **Paint Objects** already offers random rotation/scale, three collision-avoidance levels, real-world brush diameter, density falloff, and bounding-box preview. Its source can include objects, groups, and components. These overlap with many proposed “scatter improvements”; copying the feature list alone would add little. [Official Paint Objects documentation](https://support.formz.com/hc/en-us/articles/26244079632915-form-Z-10-New-Features)

The installed form·Z 10 English resources confirm dedicated **Rectangular Array** and **Radial Array** commands, independently of the transform tools' copying modes. `tools.ENU.fzr:3579` describes rectangular copies in all three Cartesian directions; line 3588 identifies Radial Array. `formZ_Interface.ENU.fzr:9772` lists rectangular Quantity/Offset controls; lines 9778–9793 list polar Quantity, Total Angle, Angle Between Items, Rotate Items, Height Offset, and output organization choices. Both resources are under `/Applications/formZ 10/formZ 10.0 pro/formZ.app/Contents/Resources/`. This verifies installed names and descriptions, not a completed UI test.

**Place Along Path** is another existing command. Its manual documents count or distance placement, start/center/end justification, orientation modes, start/end offsets, a controller, and optional component creation. The earlier recommendation understated this overlap: a new path tool must add value beyond those controls. [Official Place Along Path manual](https://s3.us-east-2.amazonaws.com/assets.autodessys.com/manuals/formz10/formZ_Pro/responsive_html/07530_Place_Along_Path.html)

Whether Place Along Path handles an entire closed polygon boundary or independent selected edges with the required corner policies remains unverified. Saved regeneration, array randomization, and detailed material-link behavior also need host validation. **Unknown is not absent.**

## Evidence in this repository and local SDK

These are inspected declarations and existing prototype behavior, not a claim that all calls have been exercised in the installed host. SDK files are local ignored dependencies; see [SDK setup](../../sdk/README.md).

| Requirement | Evidence | What remains to verify |
| --- | --- | --- |
| Copy and place objects | `projects/scatter/scatter.py:103` copies sources and applies scale/move; the [captured API](../../projects/python-api-dump/reference/fz_api_dump.txt) lists `copy`, `rotate`, `scale`, and `transform` at lines 211, 248, 250, and 267 | Rotation/matrix argument conventions, axes/pivots, and grouped-source semantics in the host |
| Native copy/matrix operations | `sdk/FZ_SDK_923/src/h/fz_objt_api.h:2247` declares `fz_objt_edit_copy_objt`; line 2435 declares `fz_objt_edit_transform_objt` | Acquire current host function sets and confirm correct project insertion/operation lifetime |
| Linked repetitions | `sdk/FZ_SDK_923/src/h/fz_objt_symb_api.h:143` documents symbol-instance placement, with the function declaration at line 189 | Interaction of this older symbol API with current component definitions, editing, and export |
| Distance-based path positions and orientation | `sdk/FZ_SDK_923/src/h/fz_objt_ncrv_api.h:561` exposes NURBS extraction; `fz_ncrv_api.h:1475` declares equal arc-length sampling by point count; line 621 declares point/tangent evaluation | Selected-path extraction, endpoints, closed loops, piecewise paths, and stable roll/up direction |
| Editable saved array | `sdk/FZ_SDK_923/src/h/fz_otyp_api.h:45` describes custom controlled objects with parameter data; line 828 declares parameter I/O callbacks | Persistent source/path references, regeneration, save/reopen, copy/paste, and Undo/Redo behavior |
| Change monitoring | `sdk/FZ_SDK_923/src/h/fz_notf_api.h:143` documents project notifications including dirty/open/save and Undo/Redo events | Dependency tracking and regeneration without recursive updates |
| Shared materials and later variation | `sdk/FZ_SDK_923/src/h/fz_objt_attr_api.h:100` sets an object's surface-style reference; `fz_rmtl_api.h:1441` declares duplication, and line 2320 declares generic material parameters | Preserve existing object/face assignments and mappings; verify duplication, unique naming, and parameter editing for varied materials, including renderer-specific properties |

The existing Scatter implementation is a useful prototype, not a general array engine. It uses fan triangulation for convex faces (`projects/scatter/scatter.py:27`), reads only the outer loop (line 45), and translates copies using bounding-box placement (line 56). It neither aligns copies to surface normals through rotation nor stores a reproducible random seed. Its current state is module memory rather than an array definition saved with the model. See its [README](../../projects/scatter/README.md).

## Clarified array-creation scope — November 1, 2026

The user wants a new array-creation workflow with the seven layouts below, shared placement/copy controls, and randomization. This supersedes the earlier narrower recommendation of separate Path, Pattern, Surface, and Variation extensions. A single Array command with layout modes is the recommended interface; plugin packaging and internal architecture remain undecided. These are requirements and proposals, not implemented capabilities. Material work is deferred.

| Required layout | Placement definition to specify |
| --- | --- |
| **Line** | Direction or two endpoints; count, interval, or fit-to-length |
| **Rectangle** | Two array axes, counts/intervals/extents per axis; filled grid versus perimeter behavior remains to be chosen |
| **Cube / 3D grid** | Three axes, counts/intervals/extents per axis; support rectangular volumes rather than requiring equal sides |
| **Radial** | Center, axis/plane, radius, full circle or arc, count/angular step; orientation relative to the center or tangent |
| **Path** | Selected path, count or distance interval, endpoint margins, alignment and roll; rigid source geometry |
| **Polygon edges** | Selected shape boundary or selected edges; perimeter distribution versus independent spacing on each edge; corner and shared-vertex policy |
| **Vertices / points** | One repetition anchored to each target vertex, with optional random size, rotation, and position variation; picking and vertex enumeration require host validation |

### Recommended command and Tool Options design

Use one **Array** command/icon with a **Layout** selector: Line, Rectangle, Cube / 3D Grid, Radial, Path, Polygon Edges, and Vertices. Layout buttons or a dropdown are presentation choices; exact native controls require UI/API verification. This keeps the variation controls and their meanings consistent while avoiding seven independent sets of options.

Tool Options should contain source/output controls, layout-specific placement controls, a shared Randomization section, and preview/apply controls. Keep the selected source and shared variation values when switching layouts where compatible; recompute the layout from those settings. Preview lifecycle and saved editability remain implementation checks, not established host capabilities.

Show only applicable controls. Vertex mode derives its count from the targets and has no interval/gap control. Radial mode exposes angular spacing; grid modes expose axis spacing. Shared randomization provides independent enable/range controls for size, rotation, position, applicable interval/gap variation, coordinate frame, and seed. Preserve each layout's placement values when switching back to it.

If frequent use later justifies direct access, optional commands such as **Array Along Path** or **Array at Vertices** can activate the same tool with a preset layout. These should share the same option definitions and implementation rather than become separately maintained tools. This shortcut scheme is a recommendation, not a confirmed requirement or verified host command-registration capability.

### Vertex layout behavior

- Create exactly one repetition per target vertex; repeated references to the same topological vertex should not produce extra copies. Distinct coincident vertices are not automatically merged by coordinate.
- Place the source origin/selected anchor at the vertex before optional position jitter. With position variation off, the anchor remains exactly on the vertex. Random size and rotation change the repetition without changing the one-per-vertex rule.
- Keep source orientation as the proposed default. Any normal/edge alignment must be explicit: a polygon corner or shared mesh vertex does not necessarily define one unique orientation.
- Derive and display the output count from the target vertex set. Vertex selection versus using all vertices of selected shapes, and treatment of generated/control vertices, still need a precise selection policy and host validation.

### Geometry compatibility and preservation

The intended Array scope includes facetted objects, smooth/ACIS solids, NURBS/nurbZ curves and surfaces, and parametric/controlled objects. This is a compatibility requirement, not a report of completed runtime tests. Source compatibility and target compatibility must be validated separately.

- **Sources:** copy or instance the native object and apply placement transforms. Preserve its geometry representation and, where supported by the chosen transforms, its parametric controls. Do not rebuild a source from display facets just to make an array. The general SDK object module explicitly covers smooth/facetted and controlled/plain objects (`sdk/FZ_SDK_923/src/h/fz_objt_api.h:30`); native copy and matrix-transform declarations are at lines 2247 and 2435.
- **Curve targets:** support distance-based placement and tangent evaluation on NURBS/nurbZ curves without converting the source or original path to polygonal geometry. Extraction and sampling APIs provide an investigation path (`fz_objt_ncrv_api.h:561`, `fz_ncrv_api.h:621`, and `fz_ncrv_api.h:1475`). Lines/polylines, arcs, splines, closed curves, and piecewise paths each require validation or an explicit adapter; one NURBS API does not establish every path type's compatibility.
- **Smooth solid edge targets:** evaluate supported actual boundary curves. A smooth surface or solid is not automatically a single path, and its display tessellation must not silently become the array target.
- **Vertex targets:** actual topological vertices, NURBS control points, and sampled curve points are different target sets. The existing Vertex layout refers to target vertices; control-point and sampled-point distribution require explicit modes/scope if included. Their counts must not change just because display resolution changes.
- **Parametric transformations:** `FZ_OTYP_NON_UNI_SCALE` documents whether an object retains its parameter data under independent-axis scaling (`fz_otyp_api.h:102`). Other flags describe restrictions on mirrored/handedness-changing transforms. Validate the source and requested random transform ranges before committing output. Explain unsupported combinations and request an explicit alternative rather than silently stripping controls or converting geometry. Uniform scale, rotation, and translation also require representative host tests.
- **Verification:** test native type and parameter retention after copying, placement, seeded size/rotation variation, Undo/Redo, and save/reopen. Test linked repetitions separately. The older local SDK declarations are evidence for feasibility, not a blanket promise about every installed or third-party object type.

### Pre-picking and post-picking — proposed interaction

Both entry paths must lead to the same Array operation and option state. Picking behavior is a proposed product contract; verify the native selection gestures and callbacks in the installed host before implementing it.

Maintain separate **Sources** and **Targets** pick sets. Sources are the objects/groups/components to repeat. Targets are a path, polygon boundary/edges, vertices, or objects whose vertices are explicitly requested. Graphic points used to construct a line/grid/radial layout are placement inputs, not automatically new source or target selections.

| Entry condition | Proposed behavior |
| --- | --- |
| Sources pre-picked | Activate Array, adopt a valid source-only selection, and continue directly to layout definition or target picking. Do not require a redundant Set Sources action. |
| Nothing pre-picked | Activate Array, pick one or more sources, finish that pick set, then define the layout or pick targets. |
| Sources pre-picked, targets post-picked | Keep the source set fixed while the next stage accepts only compatible targets. This is the normal mixed workflow for Path, Polygon Edges, and Vertices. |
| Source and target candidates pre-picked together | Populate both sets only when roles are unambiguous and satisfy the layout's validation rules. Otherwise keep the candidates visible for explicit Sources/Targets assignment; never assume the last-picked object is the path or promote an edge/vertex's owner to a source. |
| Only target subelements pre-picked | Retain the target candidates and request sources. Do not discard the target selection because the source stage is incomplete. |
| Whole target objects pre-picked for vertex enumeration | Require an explicit target role and All Vertices scope; whole objects can also be sources, so geometry type alone does not determine the role. |

Tool Options should expose **Sources** and **Targets** summaries, counts, and actions to pick/replace/edit each set. Source-only pre-picking should remain the short workflow. Explicit role assignment is available for mixed selections, not mandatory for every operation. Show which set is active and why a candidate is invalid.

Layout-specific stages:

- **Line:** Sources → start/direction/end or numeric definition → preview.
- **Rectangle / 3D grid:** Sources → origin, layout axes/extents or numeric definition → preview.
- **Radial:** Sources → center, axis/plane, radius/arc or numeric definition → preview.
- **Path:** Sources → compatible target path → preview.
- **Polygon Edges:** Sources → shape boundary or selected edges, with explicit target scope → preview.
- **Vertices:** Sources → selected vertices, or explicitly designated target objects with All Vertices scope → preview. Derive the count from the target set; each unique target vertex receives one repetition.

Changing layout retains valid sources and shared randomization settings. Revalidate targets against the new layout; keep compatible targets, and explain incompatible ones rather than silently reassigning their roles. Picking a target must not overwrite the source set. Source and target roles remain separate even when they refer to different parts of the same object; any unsupported self-reference must be explained before preview.

Random size/rotation/position apply only after targets and layout are defined. Preview updates must retain the seed so selecting more targets or adjusting options does not arbitrarily reroll already identified elements. Stable target identification and ordering need host validation.

Provide a way to return to source/target picking without losing parameter values. Cancel removes temporary preview output and preserves original geometry. Apply commits one undoable array operation; selecting the tool or merely completing an ambiguous preselection must not commit geometry. Native completion/cancel gestures and selection restoration require host testing.

SDK evidence: `sdk/FZ_SDK_923/src/h/fz_tool_api.h:502` describes pick-set count, line 515 the opt-out of pre-picking, line 708 the validation callback with set ID and invalid-reason output, and line 793 pick-set limits/topology/type rules. The cancel callback is declared at line 1035. These declarations support an implementation investigation; they do not prove that this complete interaction has been tested in form·Z.

### Shared placement and variation controls

- Preserve the user's choice of independent copies versus form·Z-linked repetitions/components, subject to verifying the distinction in the current API. Geometry linking and material linking are separate controls.
- Count, interval length, and fit-to-extent should use consistent terminology across layouts. Display whether a count includes the original/source, and whether a multi-object source selection is one repeated assembly or separate items.
- Distinguish **pitch** (placement-origin interval) from **clear gap** (space between occupied extents). A 100 mm-wide unrotated part with a 25 mm clear gap has a 125 mm pitch. Variable size/rotation makes clear-gap calculation depend on the chosen bounding/geometry rule.
- Randomize interval/gap, size, rotation, and position independently. Allow numeric ranges and percentages where meaningful: gap ±20% or ±10 mm; size ±10% or explicit numeric ranges; rotation in degrees; position in distance units or a percentage of the relevant interval/dimension. Define that percentage reference explicitly in the UI.
- Gap randomization varies successive intervals; position jitter offsets elements around their nominal placements. They must remain separate settings because they produce different layouts.
- Offer uniform versus per-axis size variation and local/layout/world coordinate choices where applicable. Preserve a seed for reproducible results. Proposed defaults and constraints need review before implementation.
- Decide how randomized intervals interact with a fixed extent: preserve intervals and leave a remainder, redistribute to fit, or permit the endpoint to move. A fixed count, fixed span, and unrestricted random intervals cannot all be independent constraints.
- Specify closed-loop seam handling and polygon corners explicitly. Avoid duplicate placements at shared vertices when that mode requests a continuous perimeter.

### Material behavior — deferred

The user has deferred material work. The current array plan preserves source material assignments and adds no material options or variation controls. The following agreement is retained for a future material feature; it is not part of the current implementation scope.

**Share source materials by default; duplicate materials when varying their parameters.** Ordinary array elements retain references to existing source materials. When material variation is enabled, create a new material copy for each distinct generated variation, modify the copy, and assign it to the corresponding element or elements. Preserve the original source materials.

The user requires a suffix on varied material copies. A proposed naming pattern is `SourceName_arr_<array-id>_v001`, with collision checking and adjustment to the host's verified name-length limit. For example, `Brick_arr_A01_v001` and `Brick_arr_A01_v002` identify two variations. The exact suffix format is a proposal, not a confirmed requirement. Regeneration should retain the association between a variation and its generated material rather than creating another set on every preview or update.

Preserve face-level assignments as well as object-level assignments and validate texture-map behavior under size/rotation changes. The existing transform tools expose a separate texture-map-control option; texture mapping is not equivalent to material duplication. [Official transform manual](https://s3.us-east-2.amazonaws.com/assets.autodessys.com/manuals/formz10/formZ_Pro/responsive_html/07000_Transforming_Objects.html)

Material-property variation remains a future feature. The duplication and parameter APIs are declared in the SDK, but the installed host's behavior, supported properties, renderer representations, naming limits, and Undo/regeneration lifecycle still require verification. Per-element variation must be applied to generated material copies rather than the shared originals.

### Recommended first development plan

The current [proposal](../proposals/array-tools.md#first-usable-milestone-line-with-shared-features) and [development plan](../plans/array-tools-incremental.md) require a complete **LINE_READY** baseline before additional patterns. The earlier path-first feasibility suggestion is superseded by the user's LINE-first sequencing decision.

Prove the shared behavior through LINE in small steps: source pre/post picking, native copy and transforms, count/pitch/length entry, geometry preservation, copy/verified linked output, each randomization channel, visible Tool Options, preview, Apply, cancellation, Undo/Redo, and committed-output save/reopen. Every step has one focused acceptance test and inherits the previous accepted commit.

Only after LINE_READY passes, add Rectangle, 3D Grid, Radial, Path, Polygon Edges, and Vertices. Target-role picking, curve orientation, angular intervals, vertex scope, and layout switching join the plan when a layout actually needs them. Reuse and rerun applicable shared behavior for each added pattern. Material features remain deferred, and saved editable definitions remain a proposed follow-on.

### Decisions to make before a production implementation

- **Editable generator or committed copies:** copies provide a smaller initial implementation; a saved editable array requires source references, parameter storage, and regeneration. Recommendation: target editable arrays, gated by the native persistence prototype.
- **Copies or instances:** copies allow independent editing; instances can share definitions but need host/component validation. Recommendation: make the output choice explicit once both paths are verified.
- **Layout policies:** confirm rectangle fill/perimeter behavior, polygon per-edge/whole-perimeter spacing, corner handling, percentage references, and randomized fit behavior before coding their algorithms.
- **Independent extensions or a shared package:** the recommended user interface is one Array command with seven modes and shared randomization. Optional layout shortcuts should open that same tool. Keep implementation plans on feature branches; code sharing and packaging should follow verified host constraints.

This research began on `feature/array-tool-research` and is carried into `feature/array-tools-proposal` with the feature proposal and incremental plan. Create subsequent implementation branches from the accepted baseline as described in that plan; no extension has been implemented by this study.

## Source and verification limits

All product claims above come from vendor manuals or vendor release notes. Some Blender English manual pages could not be fetched directly; the study uses indexed official English pages and official translated manual pages whose relevant parameter descriptions are available in English. Explicit version URLs document the feature at that version; a link does not establish the behavior of every earlier release.

No Cinema 4D/Blender scenes were opened, no timings were measured, and no undocumented collision, packing, or persistent form·Z generator capability is implied.

[c4d-cloner]: https://help.maxon.net/c4d/2027/en-us/Content/html/OMOGRAPH_CLONER-ID_OBJECTPROPERTIES.html
[c4d-spline]: https://help.maxon.net/c4d/s26/en-us/Content/html/OMOGRAPH_CLONER-ID_OBJECTPROPERTIES.html
[c4d-object]: https://help.maxon.net/c4d/2026/en-us/Content/html/OMOGRAPH_CLONER-ID_OBJECTPROPERTIES.html
[c4d-node]: https://help.maxon.net/c4d/en-us/Content/html/NET_MAXON_NEUTRON_ASSET_OP_CLONER-NET_MAXON_NODE_BASE_GROUP_INPUTS.html
[c4d-effectors]: https://help.maxon.net/c4d/2027/en-us/Content/html/7443.html
[blender-array]: https://docs.blender.org/manual/en/5.0/modeling/modifiers/generate/array.html
[blender-legacy]: https://docs.blender.org/manual/en/latest/modeling/modifiers/generate/array_legacy.html
[blender-modifiers]: https://developer.blender.org/docs/release_notes/5.0/modeling/
[blender-mesh]: https://docs.blender.org/manual/en/4.5/modeling/geometry_nodes/mesh/index.html
[blender-nodes]: https://docs.blender.org/manual/en/5.0/modeling/geometry_nodes/index.html
[blender-curve-points]: https://docs.blender.org/manual/uk/5.2/modeling/geometry_nodes/curve/operations/curve_to_points.html
[blender-elements]: https://docs.blender.org/manual/sl/latest/modeling/geometry_nodes/instances/instance_on_elements.html
[blender-scatter]: https://docs.blender.org/manual/nl/5.2/modeling/modifiers/generate/scatter_on_surface.html
[blender-volume]: https://docs.blender.org/manual/nl/5.2/modeling/geometry_nodes/point/distribute_points_in_volume.html
[blender-instances]: https://docs.blender.org/manual/en/latest/modeling/geometry_nodes/instances.html
