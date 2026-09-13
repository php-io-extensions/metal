# metal

Metal (+ QuartzCore's CAMetal*) bound 1:1 into PHP. One static method per
Objective-C selector/protocol member, no opinions: this extension is Metal
plus the glue PHP cannot provide for itself (a handle registry, a
cross-extension pointer seam, and an NSError reader). GPU only — no
windows, no menus, no input, no widgets; that all belongs to ext-appkit.
Composition belongs in `jovian/metal` (a PHP function per ext call),
`venusian-metal` (composition), and Surface (abstraction) — not here.

Requires **macOS (Darwin arm64 or x86_64) and PHP 8.4+**. No Linux, no
Windows — Metal is Apple-only. Install with `bash install-macos.sh`
(`install-macos-herd.sh` puts Herd's PHP first on PATH; a non-interactive
shell also needs `HERD_PHP_84_INI_SCAN_DIR` exported first).

## Bound surface (0.8.0)

### Slice zero — clear and present

| Type | Slice-zero surface |
|---|---|
| `MTL\MTLDevice` | `createSystemDefault()`, `name`, `newCommandQueue`, `newTextureWithDescriptor` (partial) |
| `MTL\MTLCommandQueue` | `commandBuffer`, `label`/`setLabel` |
| `MTL\MTLCommandBuffer` | `renderCommandEncoderWithDescriptor`, `presentDrawable`, `commit`, `waitUntilCompleted`, `status`, `error` |
| `MTL\MTLCommandEncoder` | `endEncoding`, `label`/`setLabel` (covers encoders that adopt it) |
| `MTL\MTLRenderPassDescriptor` (+ color attachment descriptors) | factory + `colorAttachments`; attachment `texture`/`loadAction`/`storeAction` |
| `MTL\MTLTextureDescriptor` / `MTL\MTLTexture` | `texture2D` factory, `usage`/`storageMode`; `dims`, `pixelFormat`, `getBytes` (readback, byte-checked) |
| `QuartzCore\CAMetalLayer` / `CAMetalDrawable` | `device`, `pixelFormat`, `drawableSize`, `framebufferOnly`, `nextDrawable`; drawable `texture`/`layer` |
| `Bridge\Bridge` | handle registry (`retain`/`release`/`isValid`/`className`), pointer seam (`pointerOf`/`adopt`), `errorDescription` |

### Wave A — textured and shaded drawing

| Type | Wave A surface |
|---|---|
| `MTL\MTLDevice` (+6) | `newBufferWithLengthOptions`, `newBufferWithBytesLengthOptions`, `newLibraryWithSourceOptionsError`, `newRenderPipelineStateWithDescriptorError`, `newDepthStencilStateWithDescriptor`, `newSamplerStateWithDescriptor` |
| `MTL\MTLBuffer` | `length`, `contentsBytes`, `setContentsBytes` (both bounds-guarded; `""`/`false` when out of range) |
| `MTL\MTLLibrary` / `MTL\MTLFunction` | `newFunctionWithName`, `functionNames`, `label`/`setLabel`; function `name`, `functionType`, `label`/`setLabel` |
| `MTL\MTLRenderPipelineDescriptor` (+ color attachment array/descriptor) | `init()`, vertex/fragment function, `vertexDescriptor`, `rasterSampleCount`, `colorAttachments`, `label`; attachment `pixelFormat`, `blendingEnabled` |
| `MTL\MTLRenderPipelineState` | `label` |
| `MTL\MTLVertexDescriptor` (+ attribute/layout descriptors and arrays) | `vertexDescriptor()`, `attributes`, `layouts`; attribute `format`/`offset`/`bufferIndex`; layout `stride`/`stepFunction`/`stepRate`; both subscript pairs |
| `MTL\MTLDepthStencilDescriptor` / `MTL\MTLDepthStencilState` | `init()`, `depthCompareFunction`, `depthWriteEnabled`, `label`; state `label` |
| `MTL\MTLSamplerDescriptor` / `MTL\MTLSamplerState` | `init()`, `minFilter`/`magFilter`, `sAddressMode`/`tAddressMode`, `label`; state `label` |
| `MTL\MTLRenderCommandEncoder` | `setRenderPipelineState`, `setVertexBufferOffsetAtIndex`, `setFragmentBufferOffsetAtIndex`, `setVertexTextureAtIndex`, `setFragmentTextureAtIndex`, `setFragmentSamplerStateAtIndex`, `setViewport`, `setScissorRect`, `setCullMode`, `setFrontFacingWinding`, `setTriangleFillMode`, `setDepthStencilState`, and three draw calls |
| `MTL\MTLTexture` (+1) | `replaceRegionMipmapLevelWithBytesBytesPerRow` (guarded like `getBytes`) |

### Wave B — compute and blit

| Type | Wave B surface |
|---|---|
| `MTL\MTLDevice` (+1) | `newComputePipelineStateWithFunctionError` |
| `MTL\MTLCommandBuffer` (+2) | `computeCommandEncoder`, `blitCommandEncoder` |
| `MTL\MTLComputePipelineState` | `label`, `maxTotalThreadsPerThreadgroup`, `threadExecutionWidth` |
| `MTL\MTLComputeCommandEncoder` | `setComputePipelineState`, `setBufferOffsetAtIndex`, `setTextureAtIndex`, `dispatchThreadgroupsThreadsPerThreadgroup`, `dispatchThreadsThreadsPerThreadgroup` (non-uniform) |
| `MTL\MTLBlitCommandEncoder` | `copyFromBufferSourceOffsetToBufferDestinationOffsetSize`, `fillBufferRangeValue`, the buffer↔texture copy pair, `generateMipmapsForTexture`, `synchronizeResource` |

Both new encoders adopt `MTLCommandEncoder`, so their handles pass
`endEncoding` and `label`/`setLabel` unchanged — protocol inheritance
satisfies the conformance guard. `setBytes:length:atIndex:` is
deliberately unbound (a raw pointer + length pair, the primitive
`MTLBuffer`'s guarded accessors exist to avoid); stage small constants
through a buffer. `fillBufferRangeValue` refuses a value outside 0–255
(the selector takes a `uint8_t`), and it and the buffer-to-buffer copy
refuse an out-of-range window; the buffer↔texture copies leave
slice/level bounds to Metal's own validation, as the texture `getBytes`
guard already does for `mip > 0`. `synchronizeResource` closes the
GPU-side half of managed storage — `didModifyRange:` is still unbound, so
shared storage stays the supported path.

Shader compilation and pipeline creation use the sanctioned `NSError**`
pattern: they return `{handle: int, error: int}` with exactly one member
non-zero when the call was actually made — both are zero when the binding
refused to send (a nil device or descriptor handle) — and
`Bridge::errorDescription` reads the error. `MTLCompileOptions`
is not bound yet — pass `0` (nil), which is enough to compile MSL from
source. Encoder selectors are flattened house-style, so
`setVertexBuffer:offset:atIndex:` is `setVertexBufferOffsetAtIndex`.

Everything else in these headers (blocks/async completion handlers among
them) is out of scope for this wave, sanctioned by `@audit partial` rather
than itemized — `reserved=0` on every slice-zero type today.
`php scripts/audit-headers.php` verifies bound + reserved (+ construct)
against the SDK header's member count for every type; a type only starts
itemizing its unbindable members as commented `@reserved` signatures once
it graduates to fully-bound (Wave A+), per the "nothing silently omitted"
house rule.

Metal's API objects are protocols obtained from factories, not alloc'd —
`MTLDevice::createSystemDefault()` is a bound C-function factory,
`MTLDevice::newCommandQueue` and `CAMetalLayer::nextDrawable` are
send-based factories for `MTLCommandQueue` and `CAMetalDrawable`
respectively. Objects (and protocol instances) are `int` handles (0 = nil);
raw pointer bits (`Bridge::pointerOf`/`Bridge::adopt`) are the only
currency this extension shares with sibling extensions such as ext-appkit
(which owns `CALayer`/`NSView`; this extension owns `CAMetalLayer`).

## Proofs

```bash
php examples/proof_headless.php   # PROOF_HEADLESS_OK — offscreen clear+readback, no appkit
php examples/proof_triangle.php   # PROOF_TRIANGLE_OK — MSL compiled at runtime, one triangle drawn and byte-checked
php examples/proof_compute.php    # PROOF_COMPUTE_OK — MSL kernel dispatched over 64 uints, then blit fill/copy, all byte-checked
php examples/proof_view.php       # ext-appkit window + view; SKIP (exit 2) until ext-appkit ships Bridge::adopt
```

## Working on this extension

`src/*.h` is the single source of truth: `metal/**/*.zep` and `optimizers/`
are generated and must never be hand-edited. See
[`AGENTS.md`](AGENTS.md) for the rules and [`.okf/`](.okf/index.md) for the
full knowledge bundle.

```bash
php scripts/gen-zep.php               # annotations -> .zep + optimizers
php scripts/check-parity.php          # PARITY_OK: zep calls = optimizers = prototypes, then (real root) runs the audit below itself -> AUDIT_OK
php scripts/audit-headers.php         # AUDIT_OK: bound + reserved = SDK header members (protocol mode) — same audit, listed for standalone use
php scripts/tests/audit-protocol.php  # AUDIT_PROTOCOL_OK: negative control proving audit-headers.php can fail against bad fixtures
php scripts/tests/parity-guard.php    # PARITY_GUARD_OK: negative control proving check-parity.php can fail against bad fixtures
bash scripts/prepare-ext.sh && bash install-macos.sh  # build and install
php scripts/verify-reflection.php     # REFLECTION_OK: installed .so matches annotations
```
