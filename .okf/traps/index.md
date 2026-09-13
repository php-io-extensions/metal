---
okf_version: "0.2"
---

# metal — traps

Failure modes this extension has already hit, or is structurally exposed
to. Read the one relevant to the task at hand; these are not a tutorial.

- [no-appkit-coupling.md](/traps/no-appkit-coupling.md) — ext-metal never
  links AppKit, never accepts appkit registry handles; pointer bits only.
- [protocol-audit.md](/traps/protocol-audit.md) — MTL types are protocols;
  the audit counts `@protocol` members, and forward declarations are not
  blocks (the Task 2 fix this session recovered from).
- [blocks-reserved.md](/traps/blocks-reserved.md) — block/async Metal APIs
  are never bindable; `@audit partial` (not per-member `@reserved`) covers
  the gap until a type is fully bound.
- [layer-pointer-seam.md](/traps/layer-pointer-seam.md) — CAMetalLayer
  lives here, CALayer lives in ext-appkit; the layer crosses as pointer
  bits, and each side owns its own retain/release.
