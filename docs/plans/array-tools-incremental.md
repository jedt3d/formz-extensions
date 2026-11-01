# Array tool: incremental LINE-first development plan

- Date: November 1, 2026
- Status: Planned; every gate below is **Not started**
- Proposal: [Feature list and interaction contract](../proposals/array-tools.md)
- Planning branch: `feature/array-tools-proposal`
- Source-code baseline: `3d4ec3f`; implementation starts from main after the proposal is accepted there

## Execution order and first usable milestone

**Finish LINE with the shared features before starting Rectangle.** Source pre-picking and post-picking are early behaviors in the first working pattern. Fxx labels in the proposal identify features; they do not define execution order. G001 onward below is the execution sequence.

This revision replaces the earlier unexecuted G/S numbering with one sequential gate list. No accepted runtime baselines are renumbered: none has passed. Shared features are tested through LINE, and later layouts extend that verified workflow. Path/edge/vertex-specific target selection is added with the first layout that actually needs it.

| Milestone | Result | Gate range |
| --- | --- | --- |
| Phase 1 | LINE tool entry and source picking | G001–G006 |
| Phase 2 | one working deterministic LINE | G007–G024 |
| Phase 3 | LINE source compatibility and copy/clone output | G025–G034 |
| Phase 4 | shared randomization proven on LINE | G035–G058 |
| Phase 5 | finish the LINE preview and operation lifecycle | G059–G066 |
| Phase 6 | Rectangle and 3D Grid inherit LINE services | G067–G072 |
| Phase 7 | Radial inherits LINE services | G073–G078 |
| Phase 8 | Path adds target-role picking and curve evaluation | G079–G096 |
| Phase 9 | Polygon Edges inherit Path evaluation | G097–G102 |
| Phase 10 | Vertices inherit shared output and variation | G103–G112 |

Saved editable array definitions remain a separate proposed follow-on after the seven-layout core release. Material work remains deferred.

## Baseline rule

Each gate adds **one behavior**, with **one focused acceptance test**, on the previous accepted commit. All accepted gates remain the regression baseline. A failure leaves the previous commit as the current baseline; fix or revise that gate before proceeding.

Keep implementation commit, fixture, exact host/toolchain versions, units/tolerance, settings/seed, expected/observed result, and test evidence with the accepted baseline. Compilation/signing and API declarations do not pass a runtime gate. Existing sample builds and Scatter's self-check do not pass Array gates.

Use a feature branch per gate, for example `feature/array-g002-source-prepick`, based on an up-to-date main containing the accepted predecessor. Merge accepted gates in sequence. A commit SHA identifies each baseline; no release tag per micro-step is needed.

## How to execute one gate

1. Confirm the previous accepted baseline and the policy relevant to the row.
2. Define the smallest fixture for its one expected result; resolve any required policy before coding.
3. Implement only that behavior. Future Array source/resources/docs belong under proposed `projects/array/`; shared build tooling stays under `scripts/`. These are proposed additions, not existing runnable code.
4. Run its focused test and affected accumulated regressions. Shared-code changes require dependent prior tests to rerun.
5. Record the result and accept the tested commit only if the new test and applicable regressions pass.

At phase boundaries, rerun the accumulated host fixtures. If one row reveals independent failures, explicitly split it before advancing. Report unsupported capabilities rather than silently changing the feature list.

## Test conventions

- Use millimeters in a document explicitly set to that unit, a source parked away from output, and a declared source anchor.
- Record a justified numeric tolerance before measuring. Screenshots alone do not establish precision.
- Unless changed by the current row, use one source, independent copies, original orientation, unit scale, and variation off. Preserve originals and existing materials.
- Count means generated placements, excluding originals. A multi-object source is one assembly only after its gate passes.
- Test native geometry and selection in form·Z; use meaningful automated checks for placement, counts, and seeded values. Type support applies only to the tested matrix.

## Phase 1 — LINE tool entry and source picking

Start with one visible LINE mode. Verify source pre-picking and post-picking before building other source families or layouts. Native placement clicks are LINE inputs, not a target-object pick set.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G001 | Register the Array tool | Launch the built plugin in form·Z and confirm exactly one new Array tool is registered. |
| G002 | Source-only pre-picking | Select the source before activating Array; Sources contains that object without a redundant selection step. |
| G003 | Source post-picking | Activate Array with an empty selection and pick the source; Sources matches G002's source set. |
| G004 | Native source-pick completion | The verified host source-pick completion gesture advances to LINE placement exactly once. |
| G005 | Source-picking cancellation | Cancel while collecting LINE sources; the original document geometry is unchanged. |
| G006 | Incomplete LINE input | Apply stays disabled while the LINE source or required placement input is incomplete. |

## Phase 2 — one working deterministic LINE

This establishes ordinary copies, count/interval/length entry, graphic input, anchors, source editing, assembly behavior, and the simple clear-gap rule in one usable pattern. Preserve a documented tolerance and explicit document units.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G007 | Native facetted-object copy | Duplicate one known facetted fixture; exactly one native facetted copy appears. |
| G008 | Translation | Place that copy's anchor at `(100, 0, 0)`; its measured anchor matches the target. |
| G009 | Undo the operation | One Undo restores the pre-operation object set. |
| G010 | Redo the operation | One Redo restores the same generated copy at the same location. |
| G011 | Cancel an unfinished operation | Cancel after temporary creation; the document returns to its original object set. |
| G012 | Line by count and pitch | Count 4, start `(0,0,0)`, pitch 100 along X produces anchors at X=`0,100,200,300`. |
| G013 | Zero-count handling | Count zero is rejected without creating output. |
| G014 | Single-count handling | Count one creates one placement at the layout origin. |
| G015 | Positive interval validation | A zero interval is rejected before placement. |
| G016 | Output limit validation | A request exceeding the explicitly configured output limit is rejected before allocation. |
| G017 | Line by interval within extent | Extent 250 and interval 100 produces X=`0,100,200`, with the remainder left unused. |
| G018 | Line count fitted to length | Count 4 across length 300 produces four placements including both endpoints. |
| G019 | Graphic line definition | Define the same line using graphic input; generated anchors match G012's numeric fixture. |
| G020 | Tilted LINE frame | Define a LINE along world Y; its local forward axis follows world Y rather than world X. |
| G021 | Explicit source anchor | Select an offset source anchor; that anchor, rather than its bounding-box center, lands on the first layout point. |
| G022 | Replace LINE source selection | Replace Sources in the working LINE tool; previously entered placement values remain unchanged. |
| G023 | Multiple-object source assembly | Repeat a two-object assembly once; the two objects retain their relative transform in the generated assembly. |
| G024 | Numeric clear gap | Unrotated 100 mm-wide parts with a 25 mm bounding-extent gap produce 125 mm anchor intervals. |

## Phase 3 — LINE source compatibility and copy/clone output

Run these through the existing LINE workflow. Record the actual linked mechanism; legacy clones and components are not presumed equivalent. Verify unsupported transforms against a real recorded object type before advertising detection.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G025 | Smooth-solid source copy | Copy a known smooth-solid fixture; its output retains the native smooth-solid representation. |
| G026 | NURBS curve source copy | Copy a known NURBS curve; the output retains the native curve representation. |
| G027 | NURBS surface source copy | Copy a known NURBS surface; the output retains its native surface representation. |
| G028 | Controlled-solid source copy | Copy a parameterized solid; its copied parameter remains editable. |
| G029 | Controlled-object rotation | Rotate that copied fixture by 30 degrees; its parameter controls remain available. |
| G030 | Controlled-object uniform scale | Apply scale `1.25` to the copied fixture; its parameter controls remain available. |
| G031 | Unsupported transform detection | Request nonuniform scaling of a verified unsupported controlled type; creation is rejected with a specific reason before controls are lost. |
| G032 | Supported parametric nonuniform scale | A verified capable controlled fixture retains controls under the requested independent-axis scale. |
| G033 | Native linked repetition | Create one linked repetition through the chosen verified host mechanism; a source geometry edit propagates to it. |
| G034 | Independent-copy output choice | Make the same source edit with independent-copy output selected; the copy's geometry remains independent. |

## Phase 4 — shared randomization proven on LINE

Implement one random channel or rule per gate. Use LINE fixtures for seed, numeric/percentage inputs, axis frames, composition, gap behavior, stable placement identity, and native-geometry retention. Angular interval variation waits for Radial because LINE has no angular intervals.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G035 | Repeatable seed | Identical seed, element identities, and settings produce identical sampled channel values. |
| G036 | Change seed | Two recorded distinct seeds produce their respective reproducible, different fixture values. |
| G037 | Position variation in units | X jitter limited to ±10 mm stays within that bound relative to nominal anchors. |
| G038 | Position variation in percent | A 100 mm reference pitch with ±10% jitter produces the same bound as G037. |
| G039 | Uniform size variation in percent | ±10% size variation produces uniform scale factors in `[0.9,1.1]`. |
| G040 | Numeric size range | A numeric uniform scale range `[0.8,1.2]` stays within those bounds. |
| G041 | Independent-axis size variation | On a supported fixture, independent XYZ ranges affect only their assigned axes. |
| G042 | Rotation variation in degrees | Z-only variation in `[-15,15]` degrees produces no X/Y rotational variation. |
| G043 | Rotation variation in percent | Base angle 30 degrees with ±50% delta gives a ±15 degree variation bound. |
| G044 | Interval variation in units | Nominal pitch 100 mm with ±10 mm variation produces successive intervals in `[90,110]`. |
| G045 | Interval variation in percent | Nominal pitch 100 mm with ±10% variation has the same bounds as G044. |
| G046 | Clear-gap variation | On G024's supported fixture, gap variation of ±5 mm produces clear gaps in `[20,30]`. |
| G047 | Zero-variation equivalence | All variation ranges set to zero reproduce the deterministic placement fixture exactly. |
| G048 | Randomized extent remainder | Fixed-extent interval mode stops before crossing its boundary and preserves sampled intervals rather than silently rescaling them. |
| G049 | Random channel independence | Change only size variation; sampled position-jitter values stay unchanged. |
| G050 | Stable LINE count increase | Increase LINE count by one; the existing placement identities retain their sampled random-channel values. |
| G051 | Randomization coordinate frame | In a 90-degree-rotated layout, local-X jitter follows world Y. |
| G052 | Transform composition | Apply fixed scale, rotation, and jitter values together; the anchor/orientation matches an independently calculated transform. |
| G053 | Clear gap after size variation | With supported unrotated parts, the measured clearance stays at the requested gap after the parts' sizes vary. |
| G054 | Invalid random scale range | A scale range containing zero is rejected before generating output. |
| G055 | Controlled-source random size | A verified controlled fixture retains its parameters under the supported random uniform-size range. |
| G056 | Smooth-source random transform | A smooth-solid fixture retains its representation under the supported LINE random-transform fixture. |
| G057 | NURBS-curve random transform | A NURBS curve retains its representation under the same supported transform fixture. |
| G058 | NURBS-surface random transform | A NURBS surface retains its representation under the same supported transform fixture. |

## Phase 5 — finish the LINE preview and operation lifecycle

Use the real LINE Tool Options, preview, Apply, and cancel workflow. This phase completes the first usable pattern rather than deferring lifecycle integration until every layout exists.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G059 | Preview replacement | Change one parameter twice; only the latest preview output remains, without accumulated copies. |
| G060 | Source deletion during preview | Delete the active source; Apply is unavailable and unrelated objects remain intact. |
| G061 | Preview cancellation | Cancel a previewed multi-element array; no temporary output remains in the document. |
| G062 | Multi-element commit Undo | Apply the preview; one Undo removes the complete generated array. |
| G063 | Multi-element Redo | One Redo restores the complete array removed by G062's Undo. |
| G064 | Committed output persistence | Save and reopen the document; committed outputs retain their positions and native geometry. |
| G065 | Preserve material assignments | Reopened outputs retain the source object/face material references. |
| G066 | No material creation | Creating the array leaves the document's material count unchanged. |

### LINE_READY baseline — prerequisite for every additional layout

After G066, rerun all accepted LINE gates through the visible tool. The user must be able to pre-pick or post-pick a source, define a LINE graphically or numerically, choose copy/verified linked output, set spacing and seeded variation, review the preview, Apply, Undo/Redo, cancel, and reopen committed output. Preserve the tested native source types and material references. Record the tested commit as **LINE_READY** only when that accumulated suite passes.

LINE_READY is a checkpoint with no new behavior, not a bundled development gate. **Do not start Rectangle while it fails.** Target-object role assignment, curve alignment, angular intervals, vertex scope, and layout switching are deliberately outside this first-pattern milestone because they require another layout.

## Phase 6 — Rectangle and 3D Grid inherit LINE services

Only after LINE_READY, add rectangular position generation and then the third axis. Reuse the accepted source/picking, copy/clone, transforms, randomization, options, and lifecycle behavior. The second layout makes layout-switch tests meaningful for the first time.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G067 | Rectangle layout | A `2 × 3` grid with pitches 100 and 200 produces exactly the six expected XY anchors. |
| G068 | Rectangle extent entry | A `2 × 3` grid fitted across extents 100 and 400 matches G067's anchors. |
| G069 | Layout switching retains shared settings | Change layout and return; source identities and shared randomization values remain unchanged. |
| G070 | Remember layout values | Switch layouts and back; the original layout's placement values are restored. |
| G071 | 3D grid layout | Extending G067 to two Z layers at pitch 300 produces exactly twelve expected anchors. |
| G072 | Volume extent entry | A `2 × 3 × 2` grid fitted across extents 100, 400, and 300 matches G071's anchors. |

## Phase 7 — Radial inherits LINE services

Add radial positions, radial orientation, and angular interval variation. Reuse existing shared controls; verify how their units and frames map to this layout rather than creating a second randomization implementation.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G073 | Full-circle radial layout | Four placements at radius 100 produce four quarter-turn positions with no seam duplicate. |
| G074 | Partial radial arc | Three placements from 0 to 90 degrees produce anchors at 0, 45, and 90 degrees. |
| G075 | Radial angular interval | An arc from 0 to 100 degrees with step 30 produces 0, 30, 60, and 90 degrees. |
| G076 | Graphic radial definition | Graphic center/radius input reproduces the numeric radial fixture. |
| G077 | Radial orientation | With radial-facing alignment selected, each fixture's declared forward axis points toward the center. |
| G078 | Radial angular interval variation | Nominal 30 degree step with ±10% variation produces successive angular steps in `[27,33]` degrees within the selected arc. |

## Phase 8 — Path adds target-role picking and curve evaluation

Source pre/post picking already works in LINE. Now add the second pick set, mixed-role handling, path adapters, distance evaluation, and orientation. Reuse source selection, random transforms, output, and lifecycle. Test target invalidation and layout-role revalidation here because there is now a real target-object layout.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G079 | Separate target pick set | Pick a target after Sources is assigned; the source identities remain unchanged. |
| G080 | Ambiguous-role handling | Preselect a source candidate and a curve that could also be a source; the tool requests explicit roles rather than guessing from pick order. |
| G081 | Explicit mixed preselection | Assign roles in a mixed preselection; both resulting sets match the designated identities. |
| G082 | Invalid-target explanation | Pick one unsupported target in the active stage; a specific reason appears and no output is committed. |
| G083 | Edit source selection | Replace Sources after targets were assigned; the target identities remain unchanged. |
| G084 | Polyline path distance | Sample the fixture `(0,0,0) → (100,0,0) → (100,200,0)` at distances `0,150,300`; anchors match the analytically expected positions. |
| G085 | NURBS path distance | Place at equal arc-length intervals on a curved NURBS fixture; measured distances match an independently verified host length reference. |
| G086 | Arc path adapter | Place five items over a known semicircular arc; their angular positions match the expected equal-length divisions. |
| G087 | Path by fixed interval | On a 250 mm path with interval 100, placement distances are `0,100,200`. |
| G088 | Start margin | Add a 20 mm start margin to the fixed-interval fixture; the first distance becomes 20 mm from the path start. |
| G089 | End margin | Add an end margin to the fixture; no anchor crosses the reduced usable endpoint. |
| G090 | Closed-path seam | Place eight items around a closed curve; there are eight unique placements and no duplicate at closure. |
| G091 | Tangent alignment | At a smooth curved-path station, the fixture's forward axis matches the evaluated path tangent. |
| G092 | Roll control | Apply 30 degrees of roll at the same station; orientation differs from G091 only by that roll around the tangent. |
| G093 | Upright path alignment | On a compatible planar path, the declared up axis remains world-up. |
| G094 | Nonplanar path frame | On a recorded nonplanar fixture, adjacent frames follow the reviewed transport rule without an unintended flip. |
| G095 | Layout switching revalidates targets | Switch to an incompatible layout; invalid targets are explained without silently reassigning their roles. |
| G096 | Target deletion during preview | Delete the active target; the preview is invalidated with a missing-target reason. |

## Phase 9 — Polygon Edges inherit Path evaluation

Add perimeter/per-edge policies, corner identity/orientation, selected-edge scope, and verified smooth boundary adapters. Preserve shared source and lifecycle behavior; do not turn smooth paths into display facets.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G097 | Whole-perimeter polygon spacing | On a 100 mm square, interval 75 produces perimeter distances `0,75,150,225,300,375`, continuing across corners. |
| G098 | Per-edge polygon spacing | On the same square, restart interval 75 on each edge; resulting positions match the declared per-edge rule. |
| G099 | Shared-corner deduplication | With both ends of adjacent edges included, a shared topological corner produces exactly one placement. |
| G100 | Polygon-corner orientation | With outgoing-edge orientation selected at a square corner, the forward axis follows the outgoing edge. |
| G101 | Selected-edge scope | Designate two edges of a polygon; no placements are generated on unselected edges. |
| G102 | Smooth-solid curved edge | Use a verified curved solid boundary edge; placements follow the native curve rather than display facets. |

## Phase 10 — Vertices inherit shared output and variation

Add vertex-specific target preselection, explicit object scope, identity handling, and one-per-vertex placement. Reuse the LINE-qualified random transform channels. Vertex mode has no gap/count generation; its UI and target-identity stability need their own tests.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G103 | Target-only pre-picking | Preselect target vertices, then designate a source; the original target identities remain available. |
| G104 | Whole-object vertex targeting | Designate an object as an All Vertices target; it is not reassigned as a source. |
| G105 | Selected-vertex layout | Select five distinct target vertices; exactly five anchors are placed at those vertices. |
| G106 | All-vertices object scope | Explicitly designate a box as an All Vertices target; eight topological vertices produce eight placements. |
| G107 | Repeated vertex references | Supply the same topological vertex through adjacent selections; it produces one placement. |
| G108 | Distinct coincident vertices | Two distinct vertex identities at the same coordinate produce two placements under the proposed identity policy. |
| G109 | Display-resolution independence | Change only the target's display refinement; the topological-vertex placement count remains unchanged. |
| G110 | Stable target addition | Add one vertex target; existing identified targets retain their sampled values. |
| G111 | Vertex position variation | With ±10 mm X jitter, each selected vertex still owns one output within its declared bound. |
| G112 | Layout-specific options | Vertex layout has no editable gap or placement-count controls. |

## Shared regression contract for each added layout

After each later layout's placement tests pass, rerun the applicable LINE-qualified source/picking, copy/linked output, transform/randomization, preview, cancellation, Undo/Redo, native geometry, material-preservation, and save/reopen cases using that layout. These are regression applications of existing behaviors, not permission to introduce several features in one gate. If adaptation requires new behavior, add a separate focused gate before promoting that layout's baseline.

Keep interval variation separate from position jitter, and explain inapplicable controls. Native vertices, NURBS control points, and sampled points remain distinct. Every extra advertised curve adapter or unsupported mirrored-transform case needs a named fixture/gate. Same-object source/target roles must pass an explicit fixture or be reported unsupported before acceptance. Record the actual support matrix.

## Feature-to-gate map

| Proposal feature | Acceptance gates |
| --- | --- |
| F01 Line | G012, G013, G014, G015, G016, G017, G018, G019, G021, G022, G024 |
| F02 Rectangle | G067, G068 |
| F03 3D grid | G020, G071, G072 |
| F04 Radial | G073, G074, G075, G076, G077 |
| F05 Path | G084, G085, G086, G087, G088, G089, G090, G091, G092, G093, G094 |
| F06 Polygon edges | G097, G098, G099, G100, G101, G102 |
| F07 Vertices | G104, G105, G106, G107, G108, G109, G111 |
| F08 Placement semantics | G012, G017, G018, G019, G021, G024, G048, G074, G075, G087, G088, G089, G090, G097, G098, G099 |
| F09 Randomization | G035, G036, G037, G038, G039, G040, G041, G042, G043, G044, G045, G046, G047, G048, G049, G050, G051, G052, G053, G054, G055, G056, G057, G058, G078, G110, G111 |
| F10 Copy / linked output | G007, G033, G034 |
| F11 Pre-picking | G002, G080, G081, G103, G104 |
| F12 Post-picking | G003, G004, G005, G022, G023, G079, G082, G083 |
| F13 Native geometry | G025, G026, G027, G028, G029, G030, G031, G032, G055, G056, G057, G058, G085, G086, G102 |
| F14 Shared options | G004, G006, G069, G070, G095, G112 |
| F15 Lifecycle | G001, G005, G008, G009, G010, G011, G059, G060, G061, G062, G063, G064, G065, G066, G096 |
| F16 Saved editability | E01, E02, E03, E04, E05, E06, E07, E08 |

## Follow-on phase — saved editable arrays (proposed F16)

After the core release, each following row continues from its accepted predecessor. All are Not started. Add independent tests for regeneration Undo/Redo, native parameter retention, and linked output before claiming F16 complete.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| E01 | Store an array definition | An array's layout/count/seed can be read back from its stored definition. |
| E02 | Reopen the definition | Save/reopen restores the stored definition values. |
| E03 | Regenerate owned output | Change count from four to six; exactly six current outputs remain. |
| E04 | Source dependency update | Edit the source; updating the array regenerates from the new source geometry. |
| E05 | Path dependency update | Edit the target path; updating the array moves its placements to the new path. |
| E06 | Missing dependency handling | Remove a required source; update reports the missing reference without deleting unrelated objects. |
| E07 | Independent copied definitions | Copy an editable array; rebuilding one definition does not replace the other's output. |
| E08 | Bake editable output | Bake one definition; generated native objects remain after its procedural control is removed. |

## Evidence record for every accepted gate

Record these fields alongside the future project tests/documentation:

| Field | Required content |
| --- | --- |
| Gate and feature | Exact gate/subgate ID and related Fxx feature |
| Baseline | Previous accepted commit SHA |
| Change | Current implementation commit SHA |
| Environment | Exact form·Z build, OS/architecture, plugin build, SDK/toolchain details |
| Fixture | Model/test identity, source and target types, document units, settings, and seed |
| Expected / observed | Concrete measured result for the one acceptance test |
| Evidence | Automated output or reproducible host steps plus measurements/screenshots as appropriate |
| Regressions | Which prior checks ran and their results |
| Status | Not started, In progress, Failed, Blocked by a named dependency, or Accepted |
| Next baseline | Current commit only if accepted; otherwise the previous baseline remains current |

Do not mark a gate Accepted using screenshots of a build log, an API declaration, or an unexecuted test description. No Array host gate has been executed by this proposal-writing task.
