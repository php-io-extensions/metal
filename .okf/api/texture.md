---
type: API
title: Metal\MTL\Texture
description: Offscreen RGBA8Unorm MTLTexture for headless engines/UIs
tags: [api, metal, texture, headless]
status: draft
---

# Role

Opaque offscreen render-target texture (no NSWindow). Added in **0.7.1** so downstream packages (metal-gfx, game engines, UIs) can draw without a window.

# Methods

| Method | Notes |
|--------|--------|
| `create(device, w, h)` | RGBA8Unorm, Shared/Managed storage |
| `release(texture)` | Caller owns handle |
| `getWidth` / `getHeight` | |
| `clear(texture, queue, r,g,b,a=255)` | GPU clear; ints 0..255 |
| `writePixel` / `readPixel` | CPU path for framebuffer-style access |
| `fillRect(texture, x, y, w, h, r,g,b,a=255)` | **0.7.4+** one `replaceRegion` solid rect (not per-pixel) |
| `readPixels(texture, queue)` | Full RGBA8888 byte string |

# Related

- C ABI: `src/metal-texture.h`
- Consumers: `microscrap/metal` helpers `mtl_texture_*`, `microscrap/metal-gfx` `MetalHandledFramebuffer`
