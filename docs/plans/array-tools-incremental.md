# Array tool: incremental development and baseline plan

- Date: November 1, 2026
- Status: Planned; every gate below is **Not started**
- Proposal: [Feature list and interaction contract](../proposals/array-tools.md)
- Planning branch: `feature/array-tools-proposal`
- Starting repository commit: `3d4ec3f`

## Baseline rule

Each numbered gate adds **one behavior**, with **one focused acceptance test**. Each gate starts from the previous gate's accepted commit; it may use earlier capabilities, but must not introduce unrelated behavior. All previously accepted gates remain the regression baseline. A failure means fix or revise the current gate before moving on.

The baseline is more than a binary: it includes the implementation commit, test fixture, exact host/toolchain versions, settings/seed, expected result, observed result, and evidence. Native bundle build/signature checks are prerequisites for host tests, not evidence that the host test passed. Earlier sample builds and Scatter's self-check do not mark any Array gate complete.

Start each gate on its own feature branch, for example `feature/array-g24-line-count` or `feature/array-s01-count-zero`, from an up-to-date `main` containing the accepted predecessor. Keep each change reviewable and merge accepted gates in order. Do not start a later branch from an unmerged predecessor and describe it as the current `main` baseline. No release tag is necessary for every micro-step; the accepted commit SHA identifies the baseline.

## How to execute one gate

1. Confirm the previous accepted commit and its evidence; read the relevant proposal policy and SDK declarations.
2. Define or reuse the smallest fixture for the row's single expected result. Resolve any policy needed by this row before coding it.
3. Implement only the new behavior. Put active Array source/resources/docs under proposed `projects/array/`; retain shared native build tooling under `scripts/`. These paths describe future additions, not existing runnable code.
4. Run the focused acceptance test and relevant accumulated regressions. A change to shared placement, transforms, RNG, picking, or lifecycle requires rerunning its dependent prior gates. At phase boundaries, rerun the accumulated host fixture suite.
5. Record actual results and commit the passing code/test/doc change. Advance the baseline only after the expected result is demonstrated. A build-only pass or partial manual check leaves the runtime gate incomplete.

If a row reveals several independent failures, split it into named subgates before proceeding. Do not mark the parent accepted until those subgates pass. Fixture failures, unsupported host APIs, and unresolved policy decisions must be recorded rather than bypassed.

## Test conventions

- Fixture coordinates below use millimeters in a document explicitly set to that unit. Use source geometry parked away from the target layout and an explicit source anchor, so generated placements can be counted independently.
- Use a declared numeric tolerance appropriate to the operation before running geometric checks; record the actual tolerance rather than inventing precision from screenshots.
- Unless a row changes the setting, use independent copies, one source, original orientation, unit scale, and randomization off. Originals remain unchanged throughout; material creation stays off.
- `Count` means generated placements under the proposal's working policy. Multiple source objects count as one assembly only after G20 establishes that behavior.
- Coordinate/count tests should be automated when useful. Registration, topology/parameter retention, selection, Undo, and file reopening require actual form·Z tests. Toolchain and geometry-type claims apply only to the tested environment/type.

## Phase 1 — establish the smallest native operation

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G01 | Register the Array tool | Launch the built plugin in form·Z and confirm exactly one new Array tool is registered. |
| G02 | Native facetted-object copy | Duplicate one known facetted fixture; exactly one native facetted copy appears. |
| G03 | Translation | Place that copy's anchor at `(100, 0, 0)`; its measured anchor matches the target. |
| G04 | Undo the operation | One Undo restores the pre-operation object set. |
| G05 | Redo the operation | One Redo restores the same generated copy at the same location. |
| G06 | Cancel an unfinished operation | Cancel after temporary creation; the document returns to its original object set. |

Accepted G06 is the first operation baseline. Later tests must preserve the source and use the same verified native operation lifecycle.

## Phase 2 — establish source representation and linked output

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G07 | Smooth-solid source copy | Copy a known smooth-solid fixture; its output retains the native smooth-solid representation. |
| G08 | NURBS curve source copy | Copy a known NURBS curve; the output retains the native curve representation. |
| G09 | NURBS surface source copy | Copy a known NURBS surface; the output retains its native surface representation. |
| G10 | Controlled-solid source copy | Copy a parameterized solid; its copied parameter remains editable. |
| G11 | Controlled-object rotation | Rotate that copied fixture by 30 degrees; its parameter controls remain available. |
| G12 | Controlled-object uniform scale | Apply scale `1.25` to the copied fixture; its parameter controls remain available. |
| G13 | Unsupported transform detection | Request nonuniform scaling of a verified unsupported controlled type; creation is rejected with a specific reason before controls are lost. |
| G14 | Native linked repetition | Create one linked repetition through the chosen verified host mechanism; a source geometry edit propagates to it. |
| G15 | Independent-copy output choice | Make the same source edit with independent-copy output selected; the copy's geometry remains independent. |

Record which mechanism passed G14: legacy clone, component instance, or another verified mechanism. If both legacy clones and components are exposed later, test each in a separate additional gate. A flag declaration alone does not pass G13; verify the actual fixture's behavior.

## Phase 3 — establish Sources and Targets picking

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G16 | Source-only pre-picking | Select the source before activating Array; Sources contains that object without a redundant selection step. |
| G17 | Source post-picking | Activate Array with an empty selection and pick the source; Sources matches G16's source set. |
| G18 | Separate target pick set | Pick a target after Sources is assigned; the source identities remain unchanged. |
| G19 | Ambiguous-role handling | Preselect a source candidate and a curve that could also be a source; the tool requests explicit roles rather than guessing from pick order. |
| G20 | Multiple-object source assembly | Repeat a two-object assembly once; the two objects retain their relative transform in the generated assembly. |
| G21 | Target-only pre-picking | Preselect target vertices, then designate a source; the original target identities remain available. |
| G22 | Invalid-target explanation | Pick one unsupported target in the active stage; a specific reason appears and no output is committed. |
| G23 | Edit source selection | Replace Sources after targets were assigned; the target identities remain unchanged. |

Pre/post selection must feed the same validated sets. Use actual native selection completion gestures after verifying them; this plan does not invent Enter/double-click/modifier-key behavior.

## Phase 4 — establish Line placement semantics

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G24 | Line by count and pitch | Count 4, start `(0,0,0)`, pitch 100 along X produces anchors at X=`0,100,200,300`. |
| G25 | Line by interval within extent | Extent 250 and interval 100 produces X=`0,100,200`, with the remainder left unused. |
| G26 | Line count fitted to length | Count 4 across length 300 produces four placements including both endpoints. |
| G27 | Graphic line definition | Define the same line using graphic input; generated anchors match G24's numeric fixture. |
| G28 | Explicit source anchor | Select an offset source anchor; that anchor, rather than its bounding-box center, lands on the first layout point. |
| G29 | Numeric clear gap | Unrotated 100 mm-wide parts with a 25 mm bounding-extent gap produce 125 mm anchor intervals. |

G29 covers the declared simple bounding-extent rule, not arbitrary rotated packing. Add a separate acceptance gate for each additional clear-gap geometry/orientation case before enabling it.

## Phase 5 — extend deterministic placement to grids and radial layouts

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G30 | Rectangle layout | A `2 × 3` grid with pitches 100 and 200 produces exactly the six expected XY anchors. |
| G31 | 3D grid layout | Extending G30 to two Z layers at pitch 300 produces exactly twelve expected anchors. |
| G32 | Full-circle radial layout | Four placements at radius 100 produce four quarter-turn positions with no seam duplicate. |
| G33 | Partial radial arc | Three placements from 0 to 90 degrees produce anchors at 0, 45, and 90 degrees. |
| G34 | Radial angular interval | An arc from 0 to 100 degrees with step 30 produces 0, 30, 60, and 90 degrees. |
| G35 | Radial orientation | With radial-facing alignment selected, each fixture's declared forward axis points toward the center. |

S05–S08 below cover extent entry, a rotated grid frame, and graphic radial input. Each additional advertised graphic-input path requires its own parity test; G27 establishes only the Line case.

## Phase 6 — establish native path evaluation and orientation

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G36 | Polyline path distance | Sample the fixture `(0,0,0) → (100,0,0) → (100,200,0)` at distances `0,150,300`; anchors match the analytically expected positions. |
| G37 | NURBS path distance | Place at equal arc-length intervals on a curved NURBS fixture; measured distances match an independently verified host length reference. |
| G38 | Arc path adapter | Place five items over a known semicircular arc; their angular positions match the expected equal-length divisions. |
| G39 | Path by fixed interval | On a 250 mm path with interval 100, placement distances are `0,100,200`. |
| G40 | Start margin | Add a 20 mm start margin to the fixed-interval fixture; the first distance becomes 20 mm from the path start. |
| G41 | End margin | Add an end margin to the fixture; no anchor crosses the reduced usable endpoint. |
| G42 | Closed-path seam | Place eight items around a closed curve; there are eight unique placements and no duplicate at closure. |
| G43 | Tangent alignment | At a smooth curved-path station, the fixture's forward axis matches the evaluated path tangent. |
| G44 | Roll control | Apply 30 degrees of roll at the same station; orientation differs from G43 only by that roll around the tangent. |

Piecewise paths, joined splines, nonplanar frame transport, upright alignment, and every additional adapter require separate named subgates before being advertised. Successful NURBS extraction does not pass those tests.

## Phase 7 — establish Polygon Edges and Vertices

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G45 | Whole-perimeter polygon spacing | On a 100 mm square, interval 75 produces perimeter distances `0,75,150,225,300,375`, continuing across corners. |
| G46 | Per-edge polygon spacing | On the same square, restart interval 75 on each edge; resulting positions match the declared per-edge rule. |
| G47 | Shared-corner deduplication | With both ends of adjacent edges included, a shared topological corner produces exactly one placement. |
| G48 | Selected-edge scope | Designate two edges of a polygon; no placements are generated on unselected edges. |
| G49 | Smooth-solid curved edge | Use a verified curved solid boundary edge; placements follow the native curve rather than display facets. |
| G50 | Selected-vertex layout | Select five distinct target vertices; exactly five anchors are placed at those vertices. |
| G51 | All-vertices object scope | Explicitly designate a box as an All Vertices target; eight topological vertices produce eight placements. |
| G52 | Repeated vertex references | Supply the same topological vertex through adjacent selections; it produces one placement. |
| G53 | Distinct coincident vertices | Two distinct vertex identities at the same coordinate produce two placements under the proposed identity policy. |
| G54 | Display-resolution independence | Change only the target's display refinement; the topological-vertex placement count remains unchanged. |

G50 does not establish NURBS control-point distribution. Decide polygon-corner orientation separately before applying tangent alignment at discontinuities; a dedicated orientation fixture must pass before that option is exposed there.

## Phase 8 — add one randomization channel at a time

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G55 | Repeatable seed | Identical seed, element identities, and settings produce identical sampled channel values. |
| G56 | Position variation in units | X jitter limited to ±10 mm stays within that bound relative to nominal anchors. |
| G57 | Position variation in percent | A 100 mm reference pitch with ±10% jitter produces the same bound as G56. |
| G58 | Uniform size variation in percent | ±10% size variation produces uniform scale factors in `[0.9,1.1]`. |
| G59 | Numeric size range | A numeric uniform scale range `[0.8,1.2]` stays within those bounds. |
| G60 | Independent-axis size variation | On a supported fixture, independent XYZ ranges affect only their assigned axes. |
| G61 | Rotation variation in degrees | Z-only variation in `[-15,15]` degrees produces no X/Y rotational variation. |
| G62 | Rotation variation in percent | Base angle 30 degrees with ±50% delta gives a ±15 degree variation bound. |
| G63 | Interval variation in units | Nominal pitch 100 mm with ±10 mm variation produces successive intervals in `[90,110]`. |
| G64 | Interval variation in percent | Nominal pitch 100 mm with ±10% variation has the same bounds as G63. |
| G65 | Clear-gap variation | On G29's supported fixture, gap variation of ±5 mm produces clear gaps in `[20,30]`. |
| G66 | Radial angular interval variation | Nominal 30 degree step with ±10% variation produces successive angular steps in `[27,33]` degrees within the selected arc. |
| G67 | Zero-variation equivalence | All variation ranges set to zero reproduce the deterministic placement fixture exactly. |
| G68 | Randomized extent remainder | Fixed-extent interval mode stops before crossing its boundary and preserves sampled intervals rather than silently rescaling them. |

Add a separate fixture for changing the seed, independent random channels, adding targets without rerolling existing ones, and gap-versus-position semantics before declaring the shared randomization feature complete. Verify random size on each promised native source family; a facetted fixture alone does not prove parametric retention.

## Phase 9 — integrate one shared tool and preview lifecycle

| Gate | Only new behavior | One focused acceptance test |
| --- | --- | --- |
| G69 | Layout switching retains shared settings | Change layout and return; source identities and shared randomization values remain unchanged. |
| G70 | Layout switching revalidates targets | Switch to an incompatible layout; invalid targets are explained without silently reassigning their roles. |
| G71 | Preview replacement | Change one parameter twice; only the latest preview output remains, without accumulated copies. |
| G72 | Preview cancellation | Cancel a previewed multi-element array; no temporary output remains in the document. |
| G73 | Multi-element commit Undo | Apply the preview; one Undo removes the complete generated array. |
| G74 | Committed output persistence | Save and reopen the document; committed outputs retain their positions and native geometry. |

G74 completes the primary sequence. Core acceptance also requires the supplementary gates below, inserted at their stated positions. Additional host limitations may reveal further gates, but none of the known checks below is left as an unplanned batch.

## Supplementary gates — still one behavior per baseline

Insert each S gate immediately after its stated predecessor, before continuing the main G sequence. When its predecessor is another S gate, the rows form a short chain. Each accepted S commit becomes the next baseline exactly like a G commit. All remain Not started.

| Gate | Insert after | Only new behavior | One focused acceptance test |
| --- | --- | --- | --- |
| S01 | G24 | Zero-count handling | Count zero is rejected without creating output. |
| S02 | S01 | Single-count handling | Count one creates one placement at the layout origin. |
| S03 | S02 | Positive interval validation | A zero interval is rejected before placement. |
| S04 | S03 | Output limit validation | A request exceeding the explicitly configured output limit is rejected before allocation. |
| S05 | G30 | Rectangle extent entry | A `2 × 3` grid fitted across extents 100 and 400 matches G30's anchors. |
| S06 | G31 | Volume extent entry | A `2 × 3 × 2` grid fitted across extents 100, 400, and 300 matches G31's anchors. |
| S07 | S06 | Tilted layout frame | Rotate the layout frame 90 degrees about Z; its local X pitch follows world Y. |
| S08 | G34 | Graphic radial definition | Graphic center/radius input reproduces the numeric radial fixture. |
| S09 | G23 | Explicit mixed preselection | Assign roles in a mixed preselection; both resulting sets match the designated identities. |
| S10 | S09 | Whole-object vertex targeting | Designate an object as an All Vertices target; it is not reassigned as a source. |
| S11 | G28 | Return to source picking | Re-enter source picking; previously entered placement values remain unchanged. |
| S12 | G44 | Upright path alignment | On a compatible planar path, the declared up axis remains world-up. |
| S13 | S12 | Nonplanar path frame | On a recorded nonplanar fixture, adjacent frames follow the reviewed transport rule without an unintended flip. |
| S14 | G47 | Polygon-corner orientation | With outgoing-edge orientation selected at a square corner, the forward axis follows the outgoing edge. |
| S15 | G55 | Change seed | Two recorded distinct seeds produce their respective reproducible, different fixture values. |
| S16 | G60 | Supported parametric nonuniform scale | A verified capable controlled fixture retains controls under the requested independent-axis scale. |
| S17 | G68 | Random channel independence | Change only size variation; sampled position-jitter values stay unchanged. |
| S18 | S17 | Stable target addition | Add one vertex target; existing identified targets retain their sampled values. |
| S19 | S18 | Randomization coordinate frame | In a 90-degree-rotated layout, local-X jitter follows world Y. |
| S20 | S19 | Vertex position variation | With ±10 mm X jitter, each selected vertex still owns one output within its declared bound. |
| S21 | S20 | Transform composition | Apply fixed scale, rotation, and jitter values together; the anchor/orientation matches an independently calculated transform. |
| S22 | S21 | Clear gap after size variation | With supported unrotated parts, the measured clearance stays at the requested gap after the parts' sizes vary. |
| S23 | S22 | Invalid random scale range | A scale range containing zero is rejected before generating output. |
| S24 | S23 | Controlled-source random size | A verified controlled fixture retains its parameters under the supported random uniform-size range. |
| S25 | S24 | Smooth-source random transform | A smooth-solid fixture retains its representation under the supported random-transform fixture. |
| S26 | S25 | NURBS-curve random transform | A NURBS curve retains its representation under the same supported transform fixture. |
| S27 | S26 | NURBS-surface random transform | A NURBS surface retains its representation under the same supported transform fixture. |
| S28 | G71 | Target deletion during preview | Delete the active target; the preview is invalidated with a missing-target reason. |
| S29 | S28 | Source deletion during preview | Delete the active source; Apply is unavailable and unrelated objects remain intact. |
| S30 | G73 | Multi-element Redo | One Redo restores the complete array removed by G73's Undo. |
| S31 | G74 | Preserve material assignments | Reopened outputs retain the source object/face material references. |
| S32 | S31 | No material creation | Creating the array leaves the document's material count unchanged. |
| S33 | S32 | Layout-specific options | Vertex layout has no editable gap or placement-count controls. |
| S34 | S33 | Incomplete-input UI | Apply stays disabled while a required source or target set is incomplete. |
| S35 | S34 | Remember layout values | Switch layouts and back; the original layout's placement values are restored. |
| S36 | S35 | Native completion gesture | The verified host pick-completion gesture advances to the correct next stage exactly once. |
| S37 | S36 | Picking-stage cancellation | Cancel while collecting sources/targets; the original document geometry is unchanged. |

Each additional advertised path adapter and unsupported mirrored-transform case gets its own named continuation gate when its concrete host type is identified. Same-object source/target roles must either pass a separate explicit fixture or be reported as unsupported before selection is accepted. Those support choices must be recorded in the release matrix.

At a release checkpoint, rerun the full accepted regression suite; that checkpoint adds no new feature and is not another development gate. Never use the gate count alone as proof that every promised source/path combination has been tested.

## Feature-to-gate map

| Proposal feature | Main acceptance gates |
| --- | --- |
| F01 Line | G24–G29, S01–S04, S11 |
| F02 Rectangle | G30, S05 |
| F03 3D grid | G31, S06–S07 |
| F04 Radial | G32–G35, S08 |
| F05 Path | G36–G44, S12–S13 and each recorded adapter |
| F06 Polygon edges | G45–G49, S14 |
| F07 Vertices | G50–G54, S10, S20 |
| F08 Placement semantics | G24–G29, G33–G34, G39–G42, G45–G47, G68 |
| F09 Randomization | G55–G68, S15, S17–S27 |
| F10 Copy / linked output | G02, G14–G15 |
| F11 Pre-picking | G16, G19, G21, S09–S10 |
| F12 Post-picking | G17–G18, G20, G22–G23, S11, S36–S37 |
| F13 Native geometry | G07–G13, G37–G38, G49, S16, S24–S27 and the recorded support matrix |
| F14 Shared options | G69–G70, S33–S36 |
| F15 Lifecycle | G01, G03–G06, G71–G74, S28–S32, S37 |
| F16 Saved editability | E01–E08 and their explicit continuation tests |

## Follow-on phase — saved editable arrays (proposed F16)

This phase is recommended after core output is proven; it does not change the initial committed-copy scope. Treat each row as its own continuation gate from the accepted core baseline.

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

Parameter/geometry preservation, Undo/Redo of regeneration, and linked-output behavior each need separate continuation subgates before F16 is accepted. SDK controlled-object callbacks are an investigation path, not proof these cases work.

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
