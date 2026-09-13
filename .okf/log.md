# Change log

## 2026-09-12 — Wave B closed (compute pipelines, compute + blit encoders)

Wave B of the spec's §6 wave plan is bound, which closes the 0.8.0 spec
waves: slice zero, Wave A and Wave B are all complete. 3 new types across
3 new `src/*.{h,m}` pairs, plus additions to `MTLDevice` and
`MTLCommandBuffer`. Bindings went 147 → 164.

**Types bound** (all `@audit partial`; counts in
[binding-rules.md](binding-rules.md)'s worked-example table, which now
carries the real Wave B audit lines):

- `src/mtl-computepipeline.{h,m}` — `MTLComputePipelineState` (`label`,
  `maxTotalThreadsPerThreadgroup`, `threadExecutionWidth`)
- `src/mtl-computecommandencoder.{h,m}` — `MTLComputeCommandEncoder`
  (5 calls: pipeline state, buffer/texture binding, uniform and
  non-uniform dispatch)
- `src/mtl-blitcommandencoder.{h,m}` — `MTLBlitCommandEncoder` (6 calls:
  buffer→buffer copy, fill, the buffer↔texture copy pair,
  `generateMipmapsForTexture`, `synchronizeResource`)
- `MTLDevice` +1 (`newComputePipelineStateWithFunctionError`),
  `MTLCommandBuffer` +2 (`computeCommandEncoder`, `blitCommandEncoder`)

**Both new encoders inherit `MTLCommandEncoder` and were verified to pass
its conformance-guarded calls.** `MTLComputeCommandEncoder` and
`MTLBlitCommandEncoder` adopt `MTLCommandEncoder` in the SDK, so
`MTL_ARG_PROTO(MTLCommandEncoder, …)` accepts their handles by protocol
inheritance; `proof_compute.php` round-trips `setLabel`/`label` on both
and ends both with `endEncoding`. No new bindings were needed for that —
which is the point of having bound those three on the base protocol.

**Deviations from the wave brief, header-driven:**

- The brief named the compute buffer binding `setBuffer(handle, buffer,
  offset, index)`. The header wins: `setBuffer:offset:atIndex:`
  (`MTLComputeCommandEncoder.h:66`) flattens house-style to
  `setBufferOffsetAtIndex`. That is the **same collision Wave A hit on the
  render encoder** — `setBufferOffset:atIndex:` (:72) flattens to the same
  name — and it takes the same resolution: first-bound keeps the plain
  name, the later-bound colliding selector takes a suffix chosen then.
  Nothing is reserved by binding one first.
- `setBytes:length:atIndex:` stays **unbound** (brief's instruction, and
  the right call independently): it is a raw pointer + length pair, the
  unguarded write primitive `MTLBuffer`'s accessors exist to avoid.
- `MTLCommandBuffer` binds only the **no-argument** encoder factories.
  `computeCommandEncoderWithDescriptor:` and
  `blitCommandEncoderWithDescriptor:` need `MTLComputePassDescriptor` /
  `MTLBlitPassDescriptor`, neither bound this wave, and
  `computeCommandEncoderWithDispatchType:` is a concurrency opinion the
  ext does not take for the caller.
- `MTLComputePipelineDescriptor` is **not** bound: the plain function
  factory is enough to dispatch a kernel, and the descriptor path only
  buys the options/reflection overloads.
- `synchronizeResource:` is macOS-only in the SDK
  (`API_UNAVAILABLE(ios)`, `MTLBlitCommandEncoder.h:50`) and this
  extension is macOS-only, so it binds unconditionally. **It closes only
  half of the managed-storage gap Wave A noted**: this is the GPU-side
  sync. `didModifyRange:` — the CPU-side half a managed buffer needs after
  a PHP write — is still unbound, so managed storage is still not fully
  serviceable. Shared storage remains the supported path.
- Both `MTLSize` arguments of each dispatch call, and the
  `MTLSize`/`MTLOrigin`/`NSRange` arguments of the blit calls, cross as
  component scalars per the house struct convention. `MTLSizeMake` /
  `MTLOriginMake` / `NSMakeRange` are C helpers, not sends, so the
  one-send law is untouched (same standing as `MTLRegionMake3D` in
  `mtl-texture.m`).

**Guards added** (all memory-unsafe or wrapping patterns, all in glue):

- Every `NSUInteger` argument is rejected when negative — a negative would
  wrap to an enormous unsigned value. Both dispatches additionally reject
  a zero component in either `MTLSize` (degenerate, and Metal rejects it).
- `fillBuffer:range:value:` takes a `uint8_t`: a value outside 0–255 is
  refused rather than silently truncated.
- The two calls whose range this binding can cheaply check —
  `fillBufferRangeValue` and the buffer→buffer copy — validate the window
  against `[b length]` in subtraction form (no `offset+size` overflow) and
  refuse rather than encode. `[b length]` is a `GUARD_SELECTORS`
  validation read, guards-in-glue, not composition.
- The buffer↔texture pair is **not** range-guarded that way, by the same
  ruling the Wave A `getBytes` guard already makes for `mip > 0`: a
  texture's per-slice, per-level extent is arithmetic this binding has no
  business inventing, so those bounds stay Metal's own validation.
  Documented in the header, not silently omitted.

**Audit summary** (`php scripts/check-parity.php`, this session — new and
moved rows only; the full table is in
[binding-rules.md](binding-rules.md)):

```
MTL\MTLBlitCommandEncoder    header=25   bound=6    reserved=0    construct=0    PARTIAL
MTL\MTLCommandBuffer         header=39   bound=8    reserved=0    construct=0    PARTIAL
MTL\MTLComputeCommandEncoder header=39   bound=5    reserved=0    construct=0    PARTIAL
MTL\MTLComputePipelineState  header=13   bound=3    reserved=0    construct=0    PARTIAL
MTL\MTLDevice                header=120  bound=11   reserved=0    construct=0    PARTIAL
audited=32 skipped=1 failures=0
AUDIT_OK
```

**Wave-close checklist** (spec §11, run for real this session):

- `php scripts/gen-zep.php` → `GEN_OK` (`classes=33 methods=164
  optimizers=164`)
- `php scripts/check-parity.php` → `PARITY_OK` (`zep_calls=164
  optimizers=164 prototypes=164 extra_sources=18`) then `AUDIT_OK`
  (`audited=32 skipped=1 failures=0`)
- `php scripts/tests/audit-protocol.php` → `AUDIT_PROTOCOL_OK`
- `php scripts/tests/parity-guard.php` → `PARITY_GUARD_OK`
- `bash scripts/prepare-ext.sh` → `PREPARE_EXT_OK`; `bash
  install-macos.sh` (with `HERD_PHP_84_INI_SCAN_DIR` exported) → built,
  `php --ri metal` reports `0.8.0`
- `php scripts/verify-reflection.php` → `REFLECTION_OK` (`classes=33
  failures=0`)
- `php examples/proof_compute.php` → `PROOF_COMPUTE_OK` (new exit gate)
- `php examples/proof_triangle.php` → `PROOF_TRIANGLE_OK`
- `php examples/proof_headless.php` → `PROOF_HEADLESS_OK`
- `php examples/proof_view.php` → exit 2, documented SKIP (still awaiting
  the ext-appkit `Bridge::adopt` point release)

**`examples/proof_compute.php`** is the Wave B exit gate: it compiles
`out[i] = in[i] * 2 + 1` over `uint` from MSL source at runtime, builds a
compute pipeline state, dispatches 64 elements as
`maxTotalThreadsPerThreadgroup`/`threadExecutionWidth`-sized threadgroups
and asserts every element exactly; then re-runs the same kernel through
`dispatchThreads` over a deliberately non-multiple 50-element grid against
a sentinel-prefilled buffer, asserting both the 50 computed values and the
14 untouched ones. The blit leg fills 64 bytes with `0xAB`, copies them to
a second buffer, asserts both, and asserts that three deliberately bad
fills (value `0x100`, an over-long range, a negative location) were
refused in glue and never reached the GPU; then it round-trips a 64-byte
payload buffer → texture → buffer through both long copy selectors and
generates mipmaps. Enum ints are grep-verified against the
CommandLineTools SDK with `header:line` comments, and every error path
prints `Bridge::errorDescription`.

**Still open after Wave B** (0.8.0 spec waves are complete; these are the
known gaps, not wave work):

- The render-pass **depth/stencil attachment family**
  (`MTLRenderPassDepthAttachmentDescriptor`,
  `MTLRenderPassStencilAttachmentDescriptor` and their accessors) is
  unbound — `MTLDepthStencilState` exists but cannot be attached to a
  pass yet.
- `MTLCompileOptions` is still unbound; `options = 0` (nil) remains the
  only from-source compile path.
- `MTLBuffer::didModifyRange:` — the CPU-side half of managed storage,
  half-closed by `synchronizeResource:` above.
- `examples/proof_view.php` still exits 2, awaiting ext-appkit's
  `Bridge::adopt` point release (spec §7).
- Deferred by the spec itself: heaps, argument buffers, fences/events,
  indirect command buffers, raytracing, counters/capture, MetalFX.

## 2026-09-12 — Wave A review fixes

Review of the Wave A branch returned four Important findings plus minors.
All fixed in one pass:

- **Protocol handles are now conformance-checked.** `MTL_ARG_PROTO`
  resolved a handle and cast it, so an `MTLTexture` handle passed to
  `MTLBuffer::contentsBytes` sent `contents` to a texture and **aborted
  the process** with an unrecognized-selector `NSException`. The macro now
  tests `conformsToProtocol:` and reads as nil otherwise — same shape as
  `MTL_ARG_AS`'s `isKindOfClass:`, nullable semantics preserved, protocol
  inheritance respected (a render encoder still satisfies
  `MTLCommandEncoder`). `mtl-rendercommandencoder.m`'s raw
  `mtl_arg_object()` + bare casts moved to `MTL_ARG_PROTO` too, as did the
  two `setVertexFunction`/`setFragmentFunction` casts in
  `mtl-renderpipeline.m` and `setTexture` in `mtl-renderpass.m`. The guard
  lives in an inline helper in `mtl-value.h`, so it is not a send against
  the composite budget and needed no `GUARD_SELECTORS` entry. See
  [bridge.md](bridge.md).
- **The selector-collision rationale was backwards.**
  `setVertexBufferOffset:atIndex:` flattens to the *same* name Wave A
  bound (`setVertexBufferOffsetAtIndex`), so binding one first "leaves the
  other free" is false. The names stay (mechanically correct); the
  rationale is now the appkit collision precedent — later-bound colliding
  selector takes a distinguishing suffix chosen at bind time. Corrected in
  `binding-rules.md`, this log's Wave A entry, and
  `src/mtl-rendercommandencoder.h`.
- **"Exactly one non-zero" was stale in three places** (`binding-rules.md`,
  `README.md`, `src/mtl-device.h`) — all now say: exactly one non-zero
  when the send happened, `{0, 0}` when the binding refused to send.
- **The private-storage claim was false on unified memory.**
  `src/mtl-buffer.h` claimed `contents` is NULL for private buffers. The
  NULL check stays as belt-and-braces, but the claim is gone: storage-mode
  correctness (reading a private buffer, `didModifyRange:` on a managed
  one) is the caller's problem, per house policy.
- **Audit narrowing:** an `array`-returning `@audit factory` producer is
  accepted only when the selector ends in `Error` (the NSError** pattern).
  A plain list producer — the reviewer demonstrated
  `MTLLibrary::functionNames` satisfying a construction path — is rejected
  again. Two new fixtures (`src-good-errorfactory`,
  `src-bad-arrayfactory`) and two new assertions in `audit-protocol.php`;
  both verified to fail against the pre-narrowing script.
- **Minors:** `getBytes`/`replaceRegion` guards now say in-comment that
  only mip 0 is bounds-checked and mip > 0 is Metal's own validation;
  `src/mtl-texture.h` states that whether `bytesPerRow` is the *right*
  stride is the caller's contract; `setContentsBytes` with an empty string
  at an in-range offset now returns `true` (no-op success) instead of
  `false`, while an empty write past the end is still refused.

Pipeline re-run clean after the fixes (`GEN_OK`, `PARITY_OK`, `AUDIT_OK`
audited=29 failures=0, `AUDIT_PROTOCOL_OK`, `PARITY_GUARD_OK`,
`REFLECTION_OK` classes=30, `PROOF_TRIANGLE_OK`, `PROOF_HEADLESS_OK`), and
the reviewer's abort repro (`MTLBuffer::contentsBytes($textureHandle,0,4)`)
now returns `""` with the process intact.

## 2026-09-12 — Wave A closed (buffers, shader compile, pipelines, draws)

Wave A of the spec's §6 wave plan is bound: textured/shaded drawing, from
compiling MSL at runtime to a byte-checked triangle on an offscreen
texture. 17 new types across 7 new `src/*.{h,m}` pairs, plus additions to
`MTLDevice` and `MTLTexture`. Bindings went 56 → 147.

**Types bound** (all `@audit partial`; counts in
[binding-rules.md](binding-rules.md)'s worked-example table, which now
carries the real Wave A audit lines):

- `src/mtl-buffer.{h,m}` — `MTLBuffer` (length, guarded contents
  read/write)
- `src/mtl-library.{h,m}` — `MTLLibrary`, `MTLFunction` (same-file
  companions)
- `src/mtl-renderpipeline.{h,m}` — `MTLRenderPipelineDescriptor`, its
  color-attachment array + attachment descriptor, `MTLRenderPipelineState`
- `src/mtl-vertexdescriptor.{h,m}` — `MTLVertexDescriptor`, both element
  descriptors and both subscript arrays
- `src/mtl-depthstencil.{h,m}` — `MTLDepthStencilDescriptor`,
  `MTLDepthStencilState`
- `src/mtl-sampler.{h,m}` — `MTLSamplerDescriptor`, `MTLSamplerState`
- `src/mtl-rendercommandencoder.{h,m}` — `MTLRenderCommandEncoder`
  (15 calls: pipeline/resource binding, viewport, scissor, raster state,
  three draws)
- `MTLDevice` +6 (buffer ×2, library, pipeline state, depth-stencil state,
  sampler state), `MTLTexture` +1 (`replaceRegion…`)

**The `NSError**` pattern is live.** `newLibraryWithSourceOptionsError`
and `newRenderPipelineStateWithDescriptorError` return
`{handle, error}`; `mtl_ret_handle_error` (`src/mtl-value.h`) builds the
shape, and the error handle is only registered when no object came back.
`MTLCompileOptions` is **deferred** — `options` is a nullable handle and
`0` is nil, which is all a from-source compile needs.

**Deviations from the wave brief, header-driven:**

- Encoder selectors are flattened house-style, so
  `setVertexBuffer:offset:atIndex:` binds as `setVertexBufferOffsetAtIndex`
  (etc.). That flattening is **not injective**:
  `setVertexBufferOffset:atIndex:` collapses to the same name, as do the
  fragment pair and the `attributeStride` overloads. Per the appkit
  collision precedent (`drawKnob`/`drawKnobRect`,
  `postNotificationNameObject`/`...UserInfo`), the first-bound selector
  keeps the plain name and the later-bound colliding one takes a
  distinguishing suffix decided at bind time — binding one first reserves
  nothing.
- `MTLRenderPipelineDescriptor` binds `rasterSampleCount`, not the
  deprecated `sampleCount` (both are in the header).
- `MTLVertexDescriptor` is constructed by its own `+vertexDescriptor`
  class factory, not alloc+init.
- `blendingEnabled`/`depthWriteEnabled` keep the property name and send
  the SDK's `isX` getter.
- `MTLBuffer`'s `contents` pointer does not cross into PHP:
  `contentsBytes`/`setContentsBytes` memcpy through a `[b length]`-checked
  window and return `""`/`false` rather than touching memory out of range.
  Private-storage buffers (NULL contents) are treated as invalid, and
  managed-storage `didModifyRange:` is not bound this wave.
- `newBufferWithBytesLengthOptions` takes only the PHP string: the
  selector's `length:` is the string's own byte length, the one value that
  cannot read past what PHP handed us.

**Toolchain amendments** (both forced by real SDK headers, both covered by
the negative controls):

- `audit-headers.php`: an `@audit factory` producer may return `int` *or*
  `array` — the NSError** producers are how `MTLLibrary` and
  `MTLRenderPipelineState` are constructed at all.
- `audit-headers.php`: companion-header resolution now requires a real
  `@interface`/`@protocol` **block**, not just a mention. Metal
  forward-declares types in alphabetically earlier headers
  (`MTLFunction` in `MTLComputeCommandEncoder.h`, `MTLRenderPipelineState`
  and `MTLSamplerState` in `MTLArgumentEncoder.h`,
  `MTLRenderCommandEncoder` in `MTLCommandBuffer.h`), which would have
  audited four Wave A types against `header=0`. New fixture
  `FakeAliases.h` + an assertion in `audit-protocol.php` (`FakeQueue
  header=4`) pins it; the fixture was confirmed to fail against the
  pre-fix script.
- `check-parity.php`: `GUARD_SELECTORS` gains `length` for the buffer
  window guard, same guards-in-glue ruling as `width`/`height`.

**Wave-close checklist** (run for real this session):

- `php scripts/gen-zep.php` → `GEN_OK` (`classes=30 methods=147
  optimizers=147`)
- `php scripts/check-parity.php` → `PARITY_OK` (`zep_calls=147
  optimizers=147 prototypes=147 extra_sources=15`) then `AUDIT_OK`
  (`audited=29 skipped=1 failures=0`)
- `php scripts/tests/audit-protocol.php` → `AUDIT_PROTOCOL_OK`;
  `php scripts/tests/parity-guard.php` → `PARITY_GUARD_OK`
- `bash scripts/prepare-ext.sh && bash install-macos.sh` → `php --ri metal`
  reports 0.8.0
- `php scripts/verify-reflection.php` → `REFLECTION_OK` (`classes=30
  failures=0`)
- `php examples/proof_triangle.php` → `PROOF_TRIANGLE_OK` (Apple M1 Pro;
  centre pixel `64,128,191,255` = the shader's `(0.25, 0.5, 0.75, 1.0)`,
  both top corners `0,0,0,255` = the black clear)
- `php examples/proof_headless.php` → `PROOF_HEADLESS_OK` (still green)
- `php examples/proof_view.php` → exit 2, documented SKIP (ext-appkit
  `Bridge::adopt` still not shipped)

**Known Metal behaviour, not a binding bug:** a render-pipeline descriptor
with a nil `vertexFunction` does not come back as an `NSError` — Metal's
validation layer raises `failed assertion … vertexFunction must not be
nil` and aborts the process. Guarding that would be an opinion; it belongs
to `jovian/metal`, not here.

**Still open:** the render-**pass** depth/stencil attachment descriptor
family (`MTLRenderPassDepthAttachmentDescriptor`,
`MTLRenderPassStencilAttachmentDescriptor` and their arrays) remains
deferred — deferred out of slice zero by the final-review entry below, and
*not* picked up by Wave A either, which needed only the depth-stencil
*state* family. Also still open: `MTLCompileOptions`, Wave B
(compute/blit), `jovian/metal`, the ext-appkit `Bridge::adopt` point
release, and the Neo4j write-back.

## 2026-09-12 — final-review fixes (audit-in-parity, getBytes hardening, honest OKF)

Whole-branch review of slice zero found a handful of drifts between what
the OKF bundle claimed and what the toolchain/code actually did. Fixed in
one pass; the corrected facts:

- **`check-parity.php` now runs the audit itself.** Spec §11's intent —
  one command proves parity *and* header faithfulness — was not actually
  wired up: `check-parity.php` and `audit-headers.php` were two separate
  commands. `check-parity.php` now `passthru()`s `audit-headers.php` as
  its own last step, but only when auditing the real package root (a
  self-test's temp fixture tree has no real SDK counterpart, so it stays
  parity-only). `PARITY_OK` is followed by the audit's own output, ending
  `AUDIT_OK`.
- **Two negative-control suites ship, not one.** `scripts/tests/
  audit-protocol.php` (`AUDIT_PROTOCOL_OK`) was already real; this session
  ported `scripts/tests/parity-guard.php` (`PARITY_GUARD_OK`) from
  appkit's template (mechanical `ns_`→`mtl_`, `appkit`→`metal`,
  `NS\NSSample`→`MTL\MTLSample` rename, same discipline as the
  `gen-zep.php` doc-comment port). Both are named explicitly in
  toolchain.md/README.md/AGENTS.md now instead of one being described as
  if it were the audit gate itself.
- **Render-pass surface correction.** README's slice-zero table claimed
  "color/depth/stencil attachment descriptors"; only color attachment
  descriptors are bound (`MTLRenderPassColorAttachmentDescriptor`/
  `...Array`). Depth/stencil attachment descriptors are **deferred out of
  slice zero, into Wave A** — corrected to "color attachment descriptors"
  only.
- **`MTLTexture`/`MTLTextureDescriptor` were pulled forward from Wave A.**
  The original wave plan had them later, but `examples/proof_headless.php`'s
  byte-checked clear+readback exit proof needs a real texture to clear into
  and read back from — there is no way to prove the pipeline end-to-end
  without them, so they were bound in slice zero instead. Both moves (depth/
  stencil deferred, texture pulled forward) are net-neutral against the
  wave plan's intent (prove the pipeline, keep unbindable/deferred surface
  honestly out of scope) but do not match the wave plan's letter — **spec
  §6 (wave plan) and §11 (wave-close checklist) should be amended to say
  so.** The spec itself is not edited by this fix wave (controller ruling:
  docs describe what shipped; the spec's own amendment is separate,
  human-owned work).
- **`getBytes` hardening.** `MTLTexture::getBytesBytesPerRowFromRegionMipmapLevel`
  now `memset`s its output buffer to zero before the native call (so a
  driver that under-writes never leaks prior heap contents to PHP), and
  validates the requested region against the texture before calling
  `getBytes:bytesPerRow:fromRegion:mipmapLevel:` — negative offsets/sizes,
  zero width/height, and (at mip level 0) a region that overruns the
  texture's own `width`/`height` all now return `""` instead of undefined
  behavior. The `[t width]`/`[t height]` reads this needs are a second/third
  message send on a binding that otherwise sends exactly one selector;
  sanctioned as a **guards-in-glue** exception (bounds-check reads, not
  composition) — see `check-parity.php`'s `GUARD_SELECTORS` and the
  one-line comment at the call site.
- **`Bridge` ownership semantics corrected.** See `.okf/bridge.md`'s
  Ownership section — the prior text implied per-object retain counting;
  the registry is address-keyed with one strong reference per object, and
  `release()` drops that reference for **every** holder of the handle, not
  a per-caller count. `.okf/traps/layer-pointer-seam.md` gained an explicit
  warning that adopting a garbage pointer is undefined behavior, not a
  checked failure.
- **`proof_view.php` now releases its per-frame handles** (drawable,
  texture, pass descriptor, attachments array, attachment, command buffer,
  encoder) and fails if more than 10 of its 120 frames skip
  (`nextDrawable` returning 0) — previously it leaked one retain per frame
  per handle and had no skip budget. Still exits 2 (the ext-appkit
  `Bridge::adopt` gate) until that point release lands; this is expected,
  not a regression.
- **`ext/config.w32`** (an MSVC/Windows zephir build-config artifact) is
  Darwin+Linux-law contraband — Windows cannot compile this extension's
  `.m` files regardless. Removed from git, added to `.gitignore`, and
  `prepare-ext.sh`'s post-generate strip now deletes it every run so a
  fresh `zephir generate` never resurrects it into the tree.
- **`'CAMetalLayer'`, not `'CALayer'`**, is the adopt-string
  `.okf/binding-rules.md` and `.okf/traps/layer-pointer-seam.md` now use
  consistently, matching what `examples/proof_view.php` actually calls
  (`AppKitBridge::adopt('CAMetalLayer', $layerPtr)`) — controller ruling,
  both docs previously said `CALayer` in the walk-through prose.
- **Partial-type carve-out stated explicitly.** `.okf/binding-rules.md`'s
  "nothing silently omitted" restatement now has the one-sentence caveat:
  until a type is fully bound, `@audit partial` sanctions the gap (no
  itemized `@reserved` needed yet); on graduation, bound+reserved must
  equal the header count, per `.okf/traps/blocks-reserved.md`.

## 2026-09-12 — slice zero closed

Slice zero (spec `2026-09-12-ext-metal-0.8.0-design.md`, wave plan §6) is
closed: `MTLDevice` (partial) → `MTLCommandQueue`/`MTLCommandBuffer` →
`MTLRenderPassDescriptor` (+ attachment descriptors) → `CAMetalLayer`/
`CAMetalDrawable`, plus the `Bridge\Bridge` glue (7 calls) that makes the
pointer seam and NSError reading possible.

**Audit summary** (`php scripts/audit-headers.php`, this session):

```
Bridge\Bridge                            SKIP (glue, no SDK counterpart)
MTL\MTLCommandBuffer                     header=39   bound=6    reserved=0    construct=0    PARTIAL
MTL\MTLCommandEncoder                    header=7    bound=3    reserved=0    construct=0    PARTIAL
MTL\MTLCommandQueue                      header=11   bound=3    reserved=0    construct=0    PARTIAL
MTL\MTLDevice                            header=120  bound=4    reserved=0    construct=0    PARTIAL
MTL\MTLRenderPassAttachmentDescriptor    header=22   bound=6    reserved=0    construct=0    PARTIAL
MTL\MTLRenderPassColorAttachmentDescriptor header=2    bound=2    reserved=0    construct=0    OK
MTL\MTLRenderPassColorAttachmentDescriptorArray header=2    bound=2    reserved=0    construct=0    OK
MTL\MTLRenderPassDescriptor              header=29   bound=2    reserved=0    construct=0    PARTIAL
MTL\MTLTexture                           header=37   bound=4    reserved=0    construct=0    PARTIAL
MTL\MTLTextureDescriptor                 header=35   bound=5    reserved=0    construct=0    PARTIAL
QuartzCore\CAMetalDrawable                header=2    bound=2    reserved=0    construct=0    OK
QuartzCore\CAMetalLayer                   header=26   bound=9    reserved=0    construct=1    PARTIAL
audited=12 skipped=1 failures=0
AUDIT_OK
```

(`MTLCommandQueue=11` and `MTLDevice=120` are the real SDK header counts
recovered by the Task 2 forward-declaration fix — see
[traps/protocol-audit.md](traps/protocol-audit.md).)

**Wave-close checklist** (spec §11, run for real this session):

- `php scripts/gen-zep.php && php scripts/check-parity.php` → `PARITY_OK`
  (`classes=13 methods=56 optimizers=56`)
- `php scripts/tests/audit-protocol.php` → `AUDIT_PROTOCOL_OK`
- `bash scripts/prepare-ext.sh && bash install-macos.sh` (with
  `HERD_PHP_84_INI_SCAN_DIR` exported) → build complete, `php --ri metal`
  reports `0.8.0`
- `php scripts/verify-reflection.php` → `REFLECTION_OK` (`classes=13
  failures=0`, every class's annotated count == reflected count)
- `php examples/proof_headless.php` → `PROOF_HEADLESS_OK` (device: Apple
  M1 Pro; byte-checked offscreen clear+readback, no appkit)
- `php examples/proof_view.php` → exit 2, `SKIP: ext-appkit has no
  Bridge::adopt yet (spec §7 prerequisite)` — documented SKIP, counts as
  green per spec §11 until the ext-appkit point release lands
- `bash scripts/prepare-ext.sh` (final strip) + `git status --porcelain
  ext/` → empty (nothing un-strippable)

(Corrected by the 2026-09-12 — final-review fixes entry above:
`check-parity.php` now runs `audit-headers.php` itself as its last step
against the real root, so `php scripts/check-parity.php` alone now ends in
`AUDIT_OK`; `audit-protocol.php` and the newly-ported `parity-guard.php`
are the negative controls proving those two guards can fail, not the audit
gate itself. Treat this checklist's step list as historical for the
session it records, and the corrected entry above as current.)

**Cross-repo note:** the CAMetalLayer/CALayer split (this bundle's
[traps/layer-pointer-seam.md](traps/layer-pointer-seam.md)) is stated here;
ext-appkit's own `.okf/` bundle needs the matching note added on that
side — that repo is not this plan's to edit, so this is a note for the
ext-appkit `Bridge::adopt` point-release work, not an action taken here.

**Deferred to the next planning session (not this plan's job):** Wave A
(buffers, full `MTLTexture`, library/function/pipelines, render-encoder
draws — needs the `NSError**` pattern exercised via
`newLibraryWithSourceOptionsError`), Wave B (compute/blit), `jovian/metal`,
the ext-appkit `Bridge::adopt` point release itself, and the Neo4j graph
write-back of slice-zero decisions.
