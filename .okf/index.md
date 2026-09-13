---
okf_version: "0.2"
---

# metal — knowledge bundle

Faithful 1:1 Zephir binding of Metal (+ QuartzCore's CAMetal*) into PHP.
Read this index first, then open only the concepts the task needs.

- [binding-rules.md](/binding-rules.md) — appkit's rules inherited, plus the
  Metal amendments: protocol audit, `@audit factory` grammar, the `NSError**`
  pattern, the pointer seam.
- [bridge.md](/bridge.md) — the only glue: handle registry,
  pointerOf/adopt, errorDescription.
- [toolchain.md](/toolchain.md) — generate → parity → build → install
  pipeline and its guards (identical to appkit's, metal names).
- [traps/index.md](/traps/index.md) — no-appkit-coupling,
  protocol-audit, blocks-reserved, layer-pointer-seam.
- [log.md](/log.md) — change log; slice-zero, Wave A and Wave B close
  entries (the 0.8.0 spec waves are complete; the Wave B entry lists what
  is still open).

## Scope

GPU only: no windows, no menus, no input, no widgets — all of that belongs to
ext-appkit. Darwin only (arm64 + x86_64). Slice zero (0.8.0) proves the
pipeline: `MTLDevice` → `MTLCommandQueue`/`MTLCommandBuffer` →
`MTLRenderPassDescriptor` (+ attachment descriptors) → `CAMetalLayer`/
`CAMetalDrawable`, exited by `examples/proof_headless.php` (byte-checked,
no appkit) and `examples/proof_view.php` (appkit-gated, SKIP until
ext-appkit's `Bridge::adopt` point release lands). Wave A adds
textured/shaded drawing — `MTLBuffer`, `MTLLibrary`/`MTLFunction` (runtime
MSL compile via the `NSError**` pattern), the render-pipeline, vertex,
depth-stencil and sampler descriptor families, and
`MTLRenderCommandEncoder`'s binding/viewport/draw calls — exited by
`examples/proof_triangle.php`. Wave B closes the spec's wave plan with
compute and blit — `MTLComputePipelineState`,
`MTLComputeCommandEncoder` (uniform and non-uniform dispatch) and
`MTLBlitCommandEncoder` (copy, fill, buffer↔texture, mipmaps, managed
sync) — exited by `examples/proof_compute.php`.
