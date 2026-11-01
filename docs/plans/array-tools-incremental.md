# Array tool: incremental LINE-first development plan

- Date: November 1, 2026
- Status: Planned; every gate below is **Not started**
- Proposal: [Feature list and interaction contract](../proposals/array-tools.md)
- Planning branch: `feature/array-tools-proposal`
- Source-code baseline: `3d4ec3f`; implementation starts from main after the proposal is accepted there

## Execution order and first usable milestone

**Finish LINE with the shared features before starting Rectangle.** Source pre-picking and post-picking are early behaviors in the first working pattern. F01–F16 in the proposal now follow the delivery sequence; each feature must meet its listed gates before the next feature begins. G001 onward below is the execution sequence.

This revision renumbers the unexecuted feature and gate lists to reflect delivery order and explicit geometry test cases. No accepted runtime baseline is renumbered: none has passed. Shared features are tested through LINE, and later layouts extend that verified workflow. Path/edge/vertex-specific target selection is added with the first layout that actually needs it.

| Milestone | Features completed | Result | Gate range |
| --- | --- | --- | --- |
| Phase 1 | F01–F03 | LINE tool entry and source picking | G001–G006 |
| Phase 2 | F04–F05 | One working deterministic LINE | G007–G024 |
| Phase 3 | F06–F07 | LINE source compatibility and copy/clone output | G025–G036 |
| Phase 4 | F08 | Shared randomization proven on LINE | G037–G060 |
| Phase 5 | F09 | Finish the LINE preview and operation lifecycle | G061–G068 |
| Phase 6 | F10–F11 | Rectangle and 3D Grid inherit LINE services | G069–G074 |
| Phase 7 | F12 | Radial inherits LINE services | G075–G080 |
| Phase 8 | F13 | Path adds target-role picking and curve evaluation | G081–G101 |
| Phase 9 | F14 | Polygon Edges inherit Path evaluation | G102–G110 |
| Phase 10 | F15 | Vertices inherit shared output and variation | G111–G120 |

Saved editable array definitions remain a separate proposed follow-on after the seven-layout core release. Material work remains deferred.

## Baseline rule

Each gate adds **one behavior**, with **one focused acceptance test**, on the previous accepted commit. All accepted gates remain the regression baseline. A failure leaves the previous commit as the current baseline; fix or revise that gate before proceeding.

Keep implementation commit, fixture, exact host/toolchain versions, units/tolerance, settings/seed, expected/observed result, and test evidence with the accepted baseline. Compilation/signing and API declarations do not pass a runtime gate. Existing sample builds and Scatter's self-check do not pass Array gates.

Use a feature branch per gate, for example `feature/array-g003-source-prepick`, based on an up-to-date main containing the accepted predecessor. Merge accepted gates in sequence. A commit SHA identifies each baseline; no release tag per micro-step is needed.

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

## Selectable source and guide/target fixtures

Provide explicit fixture choices in the development test setup. These are test inputs, not extra production layouts. Record the chosen object identities and actual host geometry types; a source/guide pair may be supplied by an existing model fixture rather than generated automatically. Expose a choice only when its supporting gate is available; an unavailable case must state its missing capability. No fixture selector or Array runtime has been implemented by this planning task.

| Source choice | Geometry to copy | First native-copy gate |
| --- | --- | --- |
| SRC01 | Facetted object | G007 |
| SRC02 | Smooth solid | G025 |
| SRC03 | Geometrically straight NURBS curve | G026 |
| SRC04 | Curved NURBS curve | G027 |
| SRC05 | NURBS surface/object | G028 |
| SRC06 | Solid with recorded NURBS faces | G029 |
| SRC07 | Controlled/parametric solid | G030 |

| Guide/target choice | Placement input | First dedicated gate |
| --- | --- | --- |
| TGT01 | Graphic/numeric straight LINE; no path object | G012 / G019 |
| TGT02 | Selected straight line/edge | G086 |
| TGT03 | Polygonal polyline | G087 |
| TGT04 | Geometrically straight NURBS curve | G088 |
| TGT05 | Curved NURBS path | G089 |
| TGT06 | Arc | G090 |
| TGT07 | Native curve/spline object, with its host type recorded | G091 |
| TGT08 | Straight NURBS surface/object boundary edge | G107 |
| TGT09 | Curved NURBS surface/object boundary edge | G108 |
| TGT10 | Straight solid boundary edge | G109 |
| TGT11 | Curved solid boundary edge | G110 |

Test one changed dimension at a time: establish source compatibility against the accepted straight layout, then establish each new guide against an accepted source. After both pass, run the applicable shared regression cases for each source/guide combination that the support matrix will advertise. Each case records one feature/behavior, one source choice, one guide choice, expected result, actual result, and pass/fail status.

In particular, a straight NURBS line is not covered by a straight polygonal-edge pass, and curved-path spacing must use physical distance rather than equal curve parameter values. A whole solid does not become a path by virtue of being selected; identify its edge. Preserve the source and guide's native geometry during the test. Never mark an unrun source/guide cell supported based on display appearance or another cell's pass.

## Phase 1 — LINE tool entry and source picking

Start with one visible LINE mode. Verify source pre-picking and post-picking before building other source families or layouts. Native placement clicks are LINE inputs, not a target-object pick set.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G001 | Register the Array tool | Launch the built plugin in form·Z and confirm exactly one new Array tool is registered. |
| G002 | Incomplete LINE input | Apply stays disabled while the LINE source or required placement input is incomplete. |
| G003 | Source-only pre-picking | Select the source before activating Array; Sources contains that object without a redundant selection step. |
| G004 | Source post-picking | Activate Array with an empty selection and pick the source; Sources matches G003's source set. |
| G005 | Native source-pick completion | The verified host source-pick completion gesture advances to LINE placement exactly once. |
| G006 | Source-picking cancellation | Cancel while collecting LINE sources; the original document geometry is unchanged. |

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
| G026 | Straight NURBS source copy | Copy a geometrically straight NURBS source; the output retains its native NURBS representation rather than becoming a polygonal line. |
| G027 | Curved NURBS source copy | Copy a recorded curved NURBS source; the output retains its native curve representation. |
| G028 | NURBS surface source copy | Copy a known NURBS surface; the output retains its native surface representation. |
| G029 | NURBS-faced solid source copy | Copy a recorded solid with NURBS faces; the output remains a solid with the recorded native surface representation. |
| G030 | Controlled-solid source copy | Copy a parameterized solid; its copied parameter remains editable. |
| G031 | Controlled-object rotation | Rotate that copied fixture by 30 degrees; its parameter controls remain available. |
| G032 | Controlled-object uniform scale | Apply scale `1.25` to the copied fixture; its parameter controls remain available. |
| G033 | Unsupported transform detection | Request nonuniform scaling of a verified unsupported controlled type; creation is rejected with a specific reason before controls are lost. |
| G034 | Supported parametric nonuniform scale | A verified capable controlled fixture retains controls under the requested independent-axis scale. |
| G035 | Native linked repetition | Create one linked repetition through the chosen verified host mechanism; a source geometry edit propagates to it. |
| G036 | Independent-copy output choice | Make the same source edit with independent-copy output selected; the copy's geometry remains independent. |

## Phase 4 — shared randomization proven on LINE

Implement one random channel or rule per gate. Use LINE fixtures for seed, numeric/percentage inputs, axis frames, composition, gap behavior, stable placement identity, and native-geometry retention. Angular interval variation waits for Radial because LINE has no angular intervals.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G037 | Repeatable seed | Identical seed, element identities, and settings produce identical sampled channel values. |
| G038 | Change seed | Two recorded distinct seeds produce their respective reproducible, different fixture values. |
| G039 | Position variation in units | X jitter limited to ±10 mm stays within that bound relative to nominal anchors. |
| G040 | Position variation in percent | A 100 mm reference pitch with ±10% jitter produces the same bound as G039. |
| G041 | Uniform size variation in percent | ±10% size variation produces uniform scale factors in `[0.9,1.1]`. |
| G042 | Numeric size range | A numeric uniform scale range `[0.8,1.2]` stays within those bounds. |
| G043 | Independent-axis size variation | On a supported fixture, independent XYZ ranges affect only their assigned axes. |
| G044 | Rotation variation in degrees | Z-only variation in `[-15,15]` degrees produces no X/Y rotational variation. |
| G045 | Rotation variation in percent | Base angle 30 degrees with ±50% delta gives a ±15 degree variation bound. |
| G046 | Interval variation in units | Nominal pitch 100 mm with ±10 mm variation produces successive intervals in `[90,110]`. |
| G047 | Interval variation in percent | Nominal pitch 100 mm with ±10% variation has the same bounds as G046. |
| G048 | Clear-gap variation | On G024's supported fixture, gap variation of ±5 mm produces clear gaps in `[20,30]`. |
| G049 | Zero-variation equivalence | All variation ranges set to zero reproduce the deterministic placement fixture exactly. |
| G050 | Randomized extent remainder | Fixed-extent interval mode stops before crossing its boundary and preserves sampled intervals rather than silently rescaling them. |
| G051 | Random channel independence | Change only size variation; sampled position-jitter values stay unchanged. |
| G052 | Stable LINE count increase | Increase LINE count by one; the existing placement identities retain their sampled random-channel values. |
| G053 | Randomization coordinate frame | In a 90-degree-rotated layout, local-X jitter follows world Y. |
| G054 | Transform composition | Apply fixed scale, rotation, and jitter values together; the anchor/orientation matches an independently calculated transform. |
| G055 | Clear gap after size variation | With supported unrotated parts, the measured clearance stays at the requested gap after the parts' sizes vary. |
| G056 | Invalid random scale range | A scale range containing zero is rejected before generating output. |
| G057 | Controlled-source random size | A verified controlled fixture retains its parameters under the supported random uniform-size range. |
| G058 | Smooth-source random transform | A smooth-solid fixture retains its representation under the supported LINE random-transform fixture. |
| G059 | NURBS-curve random transform | A NURBS curve retains its representation under the same supported transform fixture. |
| G060 | NURBS-surface random transform | A NURBS surface retains its representation under the same supported transform fixture. |

## Phase 5 — finish the LINE preview and operation lifecycle

Use the real LINE Tool Options, preview, Apply, and cancel workflow. This phase completes the first usable pattern rather than deferring lifecycle integration until every layout exists.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G061 | Preview replacement | Change one parameter twice; only the latest preview output remains, without accumulated copies. |
| G062 | Source deletion during preview | Delete the active source; Apply is unavailable and unrelated objects remain intact. |
| G063 | Preview cancellation | Cancel a previewed multi-element array; no temporary output remains in the document. |
| G064 | Multi-element commit Undo | Apply the preview; one Undo removes the complete generated array. |
| G065 | Multi-element Redo | One Redo restores the complete array removed by G064's Undo. |
| G066 | Committed output persistence | Save and reopen the document; committed outputs retain their positions and native geometry. |
| G067 | Preserve material assignments | Reopened outputs retain the source object/face material references. |
| G068 | No material creation | Creating the array leaves the document's material count unchanged. |

### LINE_READY baseline — prerequisite for every additional layout

After G068, rerun all accepted LINE gates through the visible tool. The user must be able to pre-pick or post-pick a source, define a LINE graphically or numerically, choose copy/verified linked output, set spacing and seeded variation, review the preview, Apply, Undo/Redo, cancel, and reopen committed output. Preserve the tested native source types and material references. Record the tested commit as **LINE_READY** only when that accumulated suite passes.

LINE_READY is a checkpoint with no new behavior, not a bundled development gate. **Do not start Rectangle while it fails.** Target-object role assignment, curve alignment, angular intervals, vertex scope, and layout switching are deliberately outside this first-pattern milestone because they require another layout.

## Phase 6 — Rectangle and 3D Grid inherit LINE services

Only after LINE_READY, add rectangular position generation and then the third axis. Reuse the accepted source/picking, copy/clone, transforms, randomization, options, and lifecycle behavior. The second layout makes layout-switch tests meaningful for the first time.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G069 | Rectangle layout | A `2 × 3` grid with pitches 100 and 200 produces exactly the six expected XY anchors. |
| G070 | Rectangle extent entry | A `2 × 3` grid fitted across extents 100 and 400 matches G069's anchors. |
| G071 | Layout switching retains shared settings | Change layout and return; source identities and shared randomization values remain unchanged. |
| G072 | Remember layout values | Switch layouts and back; the original layout's placement values are restored. |
| G073 | 3D grid layout | Extending G069 to two Z layers at pitch 300 produces exactly twelve expected anchors. |
| G074 | Volume extent entry | A `2 × 3 × 2` grid fitted across extents 100, 400, and 300 matches G073's anchors. |

## Phase 7 — Radial inherits LINE services

Add radial positions, radial orientation, and angular interval variation. Reuse existing shared controls; verify how their units and frames map to this layout rather than creating a second randomization implementation.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G075 | Full-circle radial layout | Four placements at radius 100 produce four quarter-turn positions with no seam duplicate. |
| G076 | Partial radial arc | Three placements from 0 to 90 degrees produce anchors at 0, 45, and 90 degrees. |
| G077 | Radial angular interval | An arc from 0 to 100 degrees with step 30 produces 0, 30, 60, and 90 degrees. |
| G078 | Graphic radial definition | Graphic center/radius input reproduces the numeric radial fixture. |
| G079 | Radial orientation | With radial-facing alignment selected, each fixture's declared forward axis points toward the center. |
| G080 | Radial angular interval variation | Nominal 30 degree step with ±10% variation produces successive angular steps in `[27,33]` degrees within the selected arc. |

## Phase 8 — Path adds target-role picking and curve evaluation

Source pre/post picking already works in LINE. Now add the second pick set, mixed-role handling, path adapters, distance evaluation, and orientation. Reuse source selection, random transforms, output, and lifecycle. Test target invalidation and layout-role revalidation here because there is now a real target-object layout.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G081 | Separate target pick set | Pick a target after Sources is assigned; the source identities remain unchanged. |
| G082 | Ambiguous-role handling | Preselect a source candidate and a curve that could also be a source; the tool requests explicit roles rather than guessing from pick order. |
| G083 | Explicit mixed preselection | Assign roles in a mixed preselection; both resulting sets match the designated identities. |
| G084 | Invalid-target explanation | Pick one unsupported target in the active stage; a specific reason appears and no output is committed. |
| G085 | Edit source selection | Replace Sources after targets were assigned; the target identities remain unchanged. |
| G086 | Straight selected-path input | Use a selected 300 mm straight line/edge as the path; three stations at distances 0, 150, and 300 match the numeric LINE reference. |
| G087 | Polyline path distance | Sample the fixture `(0,0,0) → (100,0,0) → (100,200,0)` at distances `0,150,300`; anchors match the analytically expected positions. |
| G088 | Straight NURBS path input | Use a 300 mm geometrically straight NURBS path; measured stations match the same straight-path reference. |
| G089 | NURBS path distance | Place at equal arc-length intervals on a curved NURBS fixture; measured distances match an independently verified host length reference. |
| G090 | Arc path adapter | Place five items over a known semicircular arc; their angular positions match the expected equal-length divisions. |
| G091 | Native curve/spline path input | Use a recorded native curve/spline object; equal-distance stations match an independently verified host length reference. |
| G092 | Path by fixed interval | On a 250 mm path with interval 100, placement distances are `0,100,200`. |
| G093 | Start margin | Add a 20 mm start margin to the fixed-interval fixture; the first distance becomes 20 mm from the path start. |
| G094 | End margin | Add an end margin to the fixture; no anchor crosses the reduced usable endpoint. |
| G095 | Closed-path seam | Place eight items around a closed curve; there are eight unique placements and no duplicate at closure. |
| G096 | Tangent alignment | At a smooth curved-path station, the fixture's forward axis matches the evaluated path tangent. |
| G097 | Roll control | Apply 30 degrees of roll at the same station; orientation differs from G096 only by that roll around the tangent. |
| G098 | Upright path alignment | On a compatible planar path, the declared up axis remains world-up. |
| G099 | Nonplanar path frame | On a recorded nonplanar fixture, adjacent frames follow the reviewed transport rule without an unintended flip. |
| G100 | Layout switching revalidates targets | Switch to an incompatible layout; invalid targets are explained without silently reassigning their roles. |
| G101 | Target deletion during preview | Delete the active target; the preview is invalidated with a missing-target reason. |

## Phase 9 — Polygon Edges inherit Path evaluation

Add perimeter/per-edge policies, corner identity/orientation, selected-edge scope, and verified smooth boundary adapters. Preserve shared source and lifecycle behavior; do not turn smooth paths into display facets.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G102 | Whole-perimeter polygon spacing | On a 100 mm square, interval 75 produces perimeter distances `0,75,150,225,300,375`, continuing across corners. |
| G103 | Per-edge polygon spacing | On the same square, restart interval 75 on each edge; resulting positions match the declared per-edge rule. |
| G104 | Shared-corner deduplication | With both ends of adjacent edges included, a shared topological corner produces exactly one placement. |
| G105 | Polygon-corner orientation | With outgoing-edge orientation selected at a square corner, the forward axis follows the outgoing edge. |
| G106 | Selected-edge scope | Designate two edges of a polygon; no placements are generated on unselected edges. |
| G107 | Straight NURBS boundary edge | Use a recorded straight boundary edge of a NURBS surface/object; stations match its measured native length. |
| G108 | Curved NURBS boundary edge | Use a recorded curved boundary edge of a NURBS surface/object; placements follow its native curve rather than display facets. |
| G109 | Straight solid boundary edge | Select a recorded straight edge of a solid; equal-distance placements match the analytic line reference. |
| G110 | Smooth-solid curved edge | Use a verified curved solid boundary edge; placements follow the native curve rather than display facets. |

## Phase 10 — Vertices inherit shared output and variation

Add vertex-specific target preselection, explicit object scope, identity handling, and one-per-vertex placement. Reuse the LINE-qualified random transform channels. Vertex mode has no gap/count generation; its UI and target-identity stability need their own tests.

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G111 | Target-only pre-picking | Preselect target vertices, then designate a source; the original target identities remain available. |
| G112 | Whole-object vertex targeting | Designate an object as an All Vertices target; it is not reassigned as a source. |
| G113 | Selected-vertex layout | Select five distinct target vertices; exactly five anchors are placed at those vertices. |
| G114 | All-vertices object scope | Explicitly designate a box as an All Vertices target; eight topological vertices produce eight placements. |
| G115 | Repeated vertex references | Supply the same topological vertex through adjacent selections; it produces one placement. |
| G116 | Distinct coincident vertices | Two distinct vertex identities at the same coordinate produce two placements under the proposed identity policy. |
| G117 | Display-resolution independence | Change only the target's display refinement; the topological-vertex placement count remains unchanged. |
| G118 | Stable target addition | Add one vertex target; existing identified targets retain their sampled values. |
| G119 | Vertex position variation | With ±10 mm X jitter, each selected vertex still owns one output within its declared bound. |
| G120 | Layout-specific options | Vertex layout has no editable gap or placement-count controls. |

## Shared regression contract for each added layout

After each later layout's placement tests pass, rerun the applicable LINE-qualified source/picking, copy/linked output, transform/randomization, preview, cancellation, Undo/Redo, native geometry, material-preservation, and save/reopen cases using that layout. These are regression applications of existing behaviors, not permission to introduce several features in one gate. If adaptation requires new behavior, add a separate focused gate before promoting that layout's baseline.

Keep interval variation separate from position jitter, and explain inapplicable controls. Native vertices, NURBS control points, and sampled points remain distinct. Every extra advertised curve adapter or unsupported mirrored-transform case needs a named fixture/gate. Same-object source/target roles must pass an explicit fixture or be reported unsupported before acceptance. Record the actual support matrix.

## Feature-to-gate delivery map

Feature numbers now represent the order of completed increments. Finish the gates in a row before starting the next feature. Each individual gate still adds just one behavior/test. Later patterns rerun the applicable shared tests as regressions.

| Feature in delivery order | Acceptance gates |
| --- | --- |
| F01 Tool shell and required-input state | G001–G002 |
| F02 Source pre-picking | G003 |
| F03 Source post-picking and completion | G004–G006 |
| F04 One native copy and basic operation lifecycle | G007–G011 |
| F05 Deterministic LINE and placement controls | G012–G024 |
| F06 Native source compatibility | G025–G034 |
| F07 Copy versus verified linked output | G035–G036 |
| F08 Shared randomization on LINE | G037–G060 |
| F09 Complete LINE preview and output lifecycle | G061–G068 |
| F10 Rectangle and first layout switching | G069–G072 |
| F11 3D Grid | G073–G074 |
| F12 Radial | G075–G080 |
| F13 Path and target-role picking | G081–G101 |
| F14 Polygon Edges and native object boundaries | G102–G110 |
| F15 Vertices | G111–G120 |
| F16 Saved editability (proposed follow-on) | E01–E08 |

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
| Fixture | Model/test identity, selected SRCxx and TGTxx choices where applicable, actual source/guide types, document units, settings, and seed |
| Expected / observed | Concrete measured result for the one acceptance test |
| Evidence | Automated output or reproducible host steps plus measurements/screenshots as appropriate |
| Regressions | Which prior checks ran and their results |
| Status | Not started, In progress, Failed, Blocked by a named dependency, or Accepted |
| Next baseline | Current commit only if accepted; otherwise the previous baseline remains current |

Do not mark a gate Accepted using screenshots of a build log, an API declaration, or an unexecuted test description. No Array host gate has been executed by this proposal-writing task.
