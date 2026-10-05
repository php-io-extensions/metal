---
type: API
title: Bindings
description: Metal and CAMetalLayer classes bound in 0.10.0, grouped the way the slice plan lists them.
resource: stubs/
tags: [metal, api]
status: draft
generated: { by: grok/4.7, at: 2026-10-04T22:46:00-04:00 }
sources:
  - id: stubs
    resource: stubs/
    title: PHP stubs
---

# Overview

Every class below is `final`. Handles have a private constructor, `pointer()`, and `fromPointer()`. Enum cases are the SDK's macOS values.[^stubs]

# Device

`MTLCreateSystemDefaultDevice(): ?MTLDevice`. `MTLDevice`: `name`, `newCommandQueue`, `newTextureWithDescriptor`, `newBufferWithLengthOptions`, `newBufferWithBytesLengthOptions`, `newSamplerStateWithDescriptor`, `supportsTextureSampleCount`, `newLibraryWithSourceOptionsError`, `newRenderPipelineStateWithDescriptorError`, `newDepthStencilStateWithDescriptor`.

# Values and enums

`MTLOrigin`, `MTLSize`, `MTLRegion`, `MTLClearColor`, `MTLViewport`, `MTLScissorRect`, `CGSize`.

Enums: `MTLPixelFormat`, `MTLLoadAction`, `MTLStoreAction`, `MTLPrimitiveType`, `MTLIndexType`, `MTLTextureUsage`, `MTLStorageMode`, `MTLResourceOptions`, `MTLTextureType`, `MTLVertexFormat`, `MTLVertexStepFunction`, `MTLBlendFactor`, `MTLBlendOperation`, `MTLColorWriteMask`, `MTLSamplerMinMagFilter`, `MTLSamplerAddressMode`, `MTLCompareFunction`, `MTLStencilOperation`, `MTLCullMode`, `MTLWinding`, `MTLCommandBufferStatus`.

`MTLResourceOptions` packs three fields. PHP enum values cannot repeat, so `0` is `STORAGE_MODE_SHARED`. `CPU_CACHE_MODE_DEFAULT_CACHE` and `HAZARD_TRACKING_MODE_DEFAULT` are that same zero and are not separate cases.

# Resources

`MTLTextureDescriptor`, `MTLTexture`, `MTLBuffer`, `MTLSamplerDescriptor`, `MTLSamplerState`.

`MTLBuffer::contents()` is the address `contents` returns, or `0` when that pointer is nil. On an M1, a private buffer's pointer is not nil.

`replaceRegion…` and `getBytes…` take a string or an address. A string must hold `bytesPerRow × height` bytes.

# Pipelines

`MTLCompileOptions`, `MTLLibrary`, `MTLFunction`, `MTLVertexDescriptor` and its attribute and layout arrays and descriptors, `MTLRenderPipelineDescriptor`, `MTLRenderPipelineColorAttachmentDescriptor` and its array, `MTLRenderPipelineState`, `MTLStencilDescriptor`, `MTLDepthStencilDescriptor`, `MTLDepthStencilState`.

# Commands

`MTLCommandQueue`, `MTLCommandBuffer`, `MTLRenderPassDescriptor` and its colour, depth, and stencil attachments, `MTLRenderCommandEncoder`, `MTLBlitCommandEncoder`.

`commandBuffer`, `renderCommandEncoderWithDescriptor`, and `blitCommandEncoder` return autoreleased objects and are retained by `metal_box`, so they outlive the pool.

# Layer

`CAMetalLayer`, `CAMetalDrawable`. `MTLCommandBuffer::presentDrawable`. `nextDrawable()` may return null when the layer is not on screen; slice 8 drives it from an AppKit view.

[^stubs]: PHP stubs
