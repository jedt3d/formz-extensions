# Array implementation tickets — published

Published and verified on November 1, 2026 in `jedt3d/formz-extensions`.

- Parent spec: [#2 — Array tools, LINE-first delivery](https://github.com/jedt3d/formz-extensions/issues/2).
- [Local spec](../../specs/array-tools.md), [detailed gate plan](../../plans/array-tools-incremental.md), and [approved tracker setup](../../drafts/array-tools-tracker-setup.md).
- Status: 33 core child issues published, 33 native parent links verified, and 32 native predecessor blocker edges verified.
- All issues are open and labelled `ready-for-agent`; this does not remove open blockers. No Array implementation gate has run.

The user approved all 33 vertical slices and the tracker configuration. These are implementation tickets, not 120 separate issues: each ticket retains its one-behavior gates and accepted-baseline order. Ticket 16 establishes LINE_READY; ticket 17 cannot start before that baseline passes. F16 saved editable definitions and material functionality have no core tickets.

## Published ticket order

1. **[Create the first usable LINE array (#3)](https://github.com/jedt3d/formz-extensions/issues/3)** — [local issue body](01-first-usable-line.md)

   **Blocked by:** None.

   **What it delivers:** A modeler can activate Array with pre-picked sources or select them afterward, enter a simple count/pitch LINE, create ordinary copies, and undo/redo or cancel the operation. The tool and native scene operation work together; this is not a shell-only or math-only ticket.

   **Focused gates:** G001–G012.

2. **[Validate LINE count and spacing inputs (#4)](https://github.com/jedt3d/formz-extensions/issues/4)** — [local issue body](02-line-input-validation.md)

   **Blocked by:** [01 / #3](https://github.com/jedt3d/formz-extensions/issues/3).

   **What it delivers:** A modeler receives a specific validation result for zero/single counts, invalid intervals, and requests beyond the configured output limit before geometry is allocated.

   **Focused gates:** G013–G016.

3. **[Place LINE arrays by extent or fitted count (#5)](https://github.com/jedt3d/formz-extensions/issues/5)** — [local issue body](03-line-extent-and-fit.md)

   **Blocked by:** [02 / #4](https://github.com/jedt3d/formz-extensions/issues/4).

   **What it delivers:** A modeler can choose fixed intervals within an extent or fit a generated count to an overall LINE length, with the expected endpoint/remainder behavior.

   **Focused gates:** G017–G018.

4. **[Define LINE graphically with anchors and assemblies (#6)](https://github.com/jedt3d/formz-extensions/issues/6)** — [local issue body](04-line-graphic-anchor-assembly.md)

   **Blocked by:** [03 / #5](https://github.com/jedt3d/formz-extensions/issues/5).

   **What it delivers:** A modeler can define a LINE graphically in its own frame, choose a source anchor, replace sources, repeat a multi-object assembly, and request the declared simple clear-gap behavior through the same working tool.

   **Focused gates:** G019–G024.

5. **[Preserve native source geometry in LINE arrays (#7)](https://github.com/jedt3d/formz-extensions/issues/7)** — [local issue body](05-line-native-source-types.md)

   **Blocked by:** [04 / #6](https://github.com/jedt3d/formz-extensions/issues/6).

   **What it delivers:** A modeler can choose smooth-solid, straight/curved NURBS, NURBS-surface, NURBS-faced-solid, and controlled-solid sources in the existing LINE workflow, with each type tested separately and preserved natively.

   **Focused gates:** G025–G030.

6. **[Validate controlled-object LINE transforms (#8)](https://github.com/jedt3d/formz-extensions/issues/8)** — [local issue body](06-line-controlled-transforms.md)

   **Blocked by:** [05 / #7](https://github.com/jedt3d/formz-extensions/issues/7).

   **What it delivers:** A modeler can rotate and scale supported controlled sources while retaining their parameters, and receives a specific rejection for verified unsupported nonuniform transformations before controls are lost.

   **Focused gates:** G031–G034.

7. **[Choose independent or verified linked LINE output (#9)](https://github.com/jedt3d/formz-extensions/issues/9)** — [local issue body](07-line-copy-or-linked.md)

   **Blocked by:** [06 / #8](https://github.com/jedt3d/formz-extensions/issues/8).

   **What it delivers:** A modeler can select independent copies or the verified native linked mechanism; source geometry edits propagate only for the chosen linked behavior.

   **Focused gates:** G035–G036.

8. **[Add seeded LINE position variation (#10)](https://github.com/jedt3d/formz-extensions/issues/10)** — [local issue body](08-line-seed-and-position.md)

   **Blocked by:** [07 / #9](https://github.com/jedt3d/formz-extensions/issues/9).

   **What it delivers:** A modeler can set a seed and position variation in units or a defined percentage through LINE Tool Options and obtain repeatable native scene placements.

   **Focused gates:** G037–G040.

9. **[Add LINE size variation (#11)](https://github.com/jedt3d/formz-extensions/issues/11)** — [local issue body](09-line-size-variation.md)

   **Blocked by:** [08 / #10](https://github.com/jedt3d/formz-extensions/issues/10).

   **What it delivers:** A modeler can vary LINE repetition size uniformly or independently by axis on supported sources using explicit percentage or numeric ranges.

   **Focused gates:** G041–G043.

10. **[Add LINE rotation variation (#12)](https://github.com/jedt3d/formz-extensions/issues/12)** — [local issue body](10-line-rotation-variation.md)

   **Blocked by:** [09 / #11](https://github.com/jedt3d/formz-extensions/issues/11).

   **What it delivers:** A modeler can vary LINE repetition rotation using degrees or a percentage of an explicit reference angle, and observe the intended native orientation changes.

   **Focused gates:** G044–G045.

11. **[Add LINE interval and clear-gap variation (#13)](https://github.com/jedt3d/formz-extensions/issues/13)** — [local issue body](11-line-interval-gap-variation.md)

   **Blocked by:** [10 / #12](https://github.com/jedt3d/formz-extensions/issues/12).

   **What it delivers:** A modeler can randomize nominal LINE intervals or the supported clear-gap rule separately from position jitter, with explicit numeric or percentage bounds.

   **Focused gates:** G046–G048.

12. **[Make LINE variation stable under edits (#14)](https://github.com/jedt3d/formz-extensions/issues/14)** — [local issue body](12-line-random-edit-stability.md)

   **Blocked by:** [11 / #13](https://github.com/jedt3d/formz-extensions/issues/13).

   **What it delivers:** A modeler can disable variation to recover the deterministic layout, preserve intervals within an extent, change one channel independently, and increase LINE count without rerolling existing placements.

   **Focused gates:** G049–G052.

13. **[Compose LINE variation in an explicit frame (#15)](https://github.com/jedt3d/formz-extensions/issues/15)** — [local issue body](13-line-transform-composition.md)

   **Blocked by:** [12 / #14](https://github.com/jedt3d/formz-extensions/issues/14).

   **What it delivers:** A modeler can use a declared randomization frame and combine supported size/rotation/position variation predictably; clear gaps follow varied sizes under the supported rule and invalid scale ranges are rejected.

   **Focused gates:** G053–G056.

14. **[Preserve native geometry under LINE variation (#16)](https://github.com/jedt3d/formz-extensions/issues/16)** — [local issue body](14-line-random-native-preservation.md)

   **Blocked by:** [13 / #15](https://github.com/jedt3d/formz-extensions/issues/15).

   **What it delivers:** A modeler can apply the supported random transforms to controlled, smooth-solid, NURBS-curve, and NURBS-surface LINE sources, with separate runtime evidence that representations and supported controls survive.

   **Focused gates:** G057–G060.

15. **[Complete LINE preview and operation history (#17)](https://github.com/jedt3d/formz-extensions/issues/17)** — [local issue body](15-line-preview-apply-history.md)

   **Blocked by:** [14 / #16](https://github.com/jedt3d/formz-extensions/issues/16).

   **What it delivers:** A modeler can revise a LINE preview without accumulating output, handle a deleted source, cancel temporary geometry, and Apply the complete array as one undoable/redoable operation.

   **Focused gates:** G061–G065.

16. **[Accept the durable LINE_READY baseline (#18)](https://github.com/jedt3d/formz-extensions/issues/18)** — [local issue body](16-line-ready-persistence.md)

   **Blocked by:** [15 / #17](https://github.com/jedt3d/formz-extensions/issues/17).

   **What it delivers:** A modeler can save and reopen committed LINE output with its native geometry and existing material assignments. The accumulated LINE workflow passes before another layout is developed.

   **Focused gates:** G066–G068.

17. **[Add Rectangle using the shared LINE workflow (#19)](https://github.com/jedt3d/formz-extensions/issues/19)** — [local issue body](17-rectangle-layout.md)

   **Blocked by:** [16 / #18](https://github.com/jedt3d/formz-extensions/issues/18).

   **What it delivers:** A modeler can create a two-axis Rectangle grid, enter its extents, and switch between LINE and Rectangle while retaining applicable shared settings and each layout's own values.

   **Focused gates:** G069–G072.

18. **[Extend Rectangle to a 3D Grid (#20)](https://github.com/jedt3d/formz-extensions/issues/20)** — [local issue body](18-three-dimensional-grid.md)

   **Blocked by:** [17 / #19](https://github.com/jedt3d/formz-extensions/issues/19).

   **What it delivers:** A modeler can add a third grid axis with independent pitch or extent while reusing accepted source selection, output, variation, and lifecycle behavior.

   **Focused gates:** G073–G074.

19. **[Add Radial placement and angular variation (#21)](https://github.com/jedt3d/formz-extensions/issues/21)** — [local issue body](19-radial-layout.md)

   **Blocked by:** [18 / #20](https://github.com/jedt3d/formz-extensions/issues/20).

   **What it delivers:** A modeler can create full-circle or arc arrays with numeric/graphic input, angular spacing, radial orientation, and seeded angular interval variation through the shared tool.

   **Focused gates:** G075–G080.

20. **[Assign Path Sources and Targets explicitly (#22)](https://github.com/jedt3d/formz-extensions/issues/22)** — [local issue body](20-path-role-picking.md)

   **Blocked by:** [19 / #21](https://github.com/jedt3d/formz-extensions/issues/21).

   **What it delivers:** A modeler can retain Sources while assigning a compatible guide, resolve ambiguous mixed preselection, reject invalid targets with a reason, and replace a source without losing target identities. This is verifiable selection behavior in the active tool.

   **Focused gates:** G081–G085.

21. **[Place on straight and polyline path fixtures (#23)](https://github.com/jedt3d/formz-extensions/issues/23)** — [local issue body](21-straight-and-polyline-paths.md)

   **Blocked by:** [20 / #22](https://github.com/jedt3d/formz-extensions/issues/22).

   **What it delivers:** A modeler can select a straight line/edge, polygonal polyline, or geometrically straight NURBS guide and generate native placements at verified physical-distance stations for each distinct guide type.

   **Focused gates:** G086–G088.

22. **[Place along a curved NURBS path (#24)](https://github.com/jedt3d/formz-extensions/issues/24)** — [local issue body](22-curved-nurbs-path.md)

   **Blocked by:** [21 / #23](https://github.com/jedt3d/formz-extensions/issues/23).

   **What it delivers:** A modeler can choose a curved NURBS guide and obtain physical-distance placement verified independently of curve parameter spacing.

   **Focused gates:** G089–G089.

23. **[Place along an arc guide (#25)](https://github.com/jedt3d/formz-extensions/issues/25)** — [local issue body](23-arc-path.md)

   **Blocked by:** [22 / #24](https://github.com/jedt3d/formz-extensions/issues/24).

   **What it delivers:** A modeler can choose a native arc guide and obtain placements matching a known analytic arc fixture.

   **Focused gates:** G090–G090.

24. **[Place along a native curve or spline guide (#26)](https://github.com/jedt3d/formz-extensions/issues/26)** — [local issue body](24-native-spline-path.md)

   **Blocked by:** [23 / #25](https://github.com/jedt3d/formz-extensions/issues/25).

   **What it delivers:** A modeler can choose a recorded native curve/spline object and obtain native scene placement verified against its physical length; unsupported object types are not silently facetted.

   **Focused gates:** G091–G091.

25. **[Control path intervals margins and closure (#27)](https://github.com/jedt3d/formz-extensions/issues/27)** — [local issue body](25-path-spacing-margins-closure.md)

   **Blocked by:** [24 / #26](https://github.com/jedt3d/formz-extensions/issues/26).

   **What it delivers:** A modeler can use physical path intervals, start/end margins, and a closed-path distribution without a duplicate seam placement.

   **Focused gates:** G092–G095.

26. **[Orient repetitions along supported paths (#28)](https://github.com/jedt3d/formz-extensions/issues/28)** — [local issue body](26-path-orientation.md)

   **Blocked by:** [25 / #27](https://github.com/jedt3d/formz-extensions/issues/27).

   **What it delivers:** A modeler can choose tangent alignment, roll, and supported upright/nonplanar frame behavior, with independently checked orientation fixtures.

   **Focused gates:** G096–G099.

27. **[Revalidate active Path targets and preview (#29)](https://github.com/jedt3d/formz-extensions/issues/29)** — [local issue body](27-path-target-lifecycle.md)

   **Blocked by:** [26 / #28](https://github.com/jedt3d/formz-extensions/issues/28).

   **What it delivers:** A modeler receives a clear response when switching to an incompatible layout or deleting an active path target; targets are not silently reassigned and stale preview output is invalidated.

   **Focused gates:** G100–G101.

28. **[Distribute along polygon perimeters or edges (#30)](https://github.com/jedt3d/formz-extensions/issues/30)** — [local issue body](28-polygon-edge-layout.md)

   **Blocked by:** [27 / #29](https://github.com/jedt3d/formz-extensions/issues/29).

   **What it delivers:** A modeler can choose whole-perimeter or per-edge placement, selected edges, shared-corner deduplication, and explicit outgoing-edge corner orientation through the shared Array workflow.

   **Focused gates:** G102–G106.

29. **[Use native NURBS boundary edges as guides (#31)](https://github.com/jedt3d/formz-extensions/issues/31)** — [local issue body](29-nurbs-boundary-guides.md)

   **Blocked by:** [28 / #30](https://github.com/jedt3d/formz-extensions/issues/30).

   **What it delivers:** A modeler can select straight and curved NURBS surface/object boundary edges as guides, with separate distance/representation evidence rather than display-facet placement.

   **Focused gates:** G107–G108.

30. **[Use native solid edges as guides (#32)](https://github.com/jedt3d/formz-extensions/issues/32)** — [local issue body](30-solid-boundary-guides.md)

   **Blocked by:** [29 / #31](https://github.com/jedt3d/formz-extensions/issues/31).

   **What it delivers:** A modeler can select straight and curved solid boundary edges as guides, while preserving native edge evaluation and the source representation.

   **Focused gates:** G109–G110.

31. **[Create one repetition per target vertex (#33)](https://github.com/jedt3d/formz-extensions/issues/33)** — [local issue body](31-vertex-layout-and-picking.md)

   **Blocked by:** [30 / #32](https://github.com/jedt3d/formz-extensions/issues/32).

   **What it delivers:** A modeler can pre-pick target vertices before choosing a source or explicitly designate an object's All Vertices scope and obtain one repetition per selected topological vertex.

   **Focused gates:** G111–G114.

32. **[Preserve vertex identity and topology semantics (#34)](https://github.com/jedt3d/formz-extensions/issues/34)** — [local issue body](32-vertex-identity.md)

   **Blocked by:** [31 / #33](https://github.com/jedt3d/formz-extensions/issues/33).

   **What it delivers:** A modeler gets one output per unique topological identity: repeated references are deduplicated, distinct coincident vertices remain distinct, and display refinement does not change the count.

   **Focused gates:** G115–G117.

33. **[Finish seeded Vertex variation and options (#35)](https://github.com/jedt3d/formz-extensions/issues/35)** — [local issue body](33-vertex-variation-and-options.md)

   **Blocked by:** [32 / #34](https://github.com/jedt3d/formz-extensions/issues/34).

   **What it delivers:** A modeler can add a vertex target without rerolling existing identities and apply optional position variation while retaining one-per-vertex output; Vertex options omit inapplicable gap/count controls.

   **Focused gates:** G118–G120.

## Execution and verification

Work only a ticket whose native blockers are closed. The chain reflects the user's cumulative-baseline requirement; complete gates in order inside each ticket, record the measured results and accepted commit, and retain prior regression evidence. The parent spec is a coordination artifact, not a request to implement all features in one run.

Native issue relationships are authoritative. The local manifest records issue URLs, numbers, direct blocker mappings, and publication verification. Child issue bodies mirror GitHub; they omit a redundant Blocked by section because those edges are native.

No parent issue was closed or rewritten during child publication. Existing materials, runtime source, and host behavior are unchanged by this documentation/tracker task.
