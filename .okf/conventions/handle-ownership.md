---
type: Convention
title: Handle ownership
description: Opaque ints, release/destroy rules
resource: /src/metal-window.h
tags: [metal, convention, memory]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: window-h
    resource: /src/metal-window.h
    title: metal-window.h
  - id: device-h
    resource: /src/metal-device.h
    title: metal-device.h
  - id: device-m
    resource: /src/metal-device.m
    title: metal-device.m
---

# Rules

| Handle | Create | Destroy / release |
|--------|--------|-------------------|
| Window | `Window::create` | `Window::destroy` (caller owns)[^window-h] |
| Device | `Device::createSystemDefault` | `Device::release` |
| Command queue | `Device::newCommandQueue` | `Device::releaseCommandQueue` |
| Texture (0.7.1+) | `Texture::create` | `Texture::release` |
| Layer | `Window::getLayer` | Do **not** free — owned by the view |
| Device from window (0.7.2+) | `Window::getDevice` | Do **not** release — borrowed from the window |

# Semantics

- `0` means failure / null; never call destroy/release on `0` (bridges no-op, but avoid).
- Device handles are `__bridge_retained` and freed with `CFRelease`.[^device-m]
- `Window::attachDevice` stores the device pointer and creates an internal queue for `clear`; releasing the PHP-side device while a window still references it is unsafe — destroy the window first (or keep the device alive until destroy).
- `Window::getDevice` returns a borrowed handle (same lifetime as the attached device). `presentTexture` borrows the texture for the blit; caller still owns and must `Texture::release`.

# Checklist

1. Create window → attach device → loop → destroy window → release device.
2. Offscreen: create device → create texture → use → release texture → release device (no window required).
3. Windowed blit (0.7.2+): attach device → create texture → `presentTexture` each frame → release texture → destroy window → release device.
4. Do not share window/texture handles across process forks.
5. Prefer one app init per process; `App::init` is idempotent.

[^window-h]: metal-window.h
[^device-m]: metal-device.m
