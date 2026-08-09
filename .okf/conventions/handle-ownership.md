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
| Layer | `Window::getLayer` | Do **not** free — owned by the view |

# Semantics

- `0` means failure / null; never call destroy/release on `0` (bridges no-op, but avoid).
- Device handles are `__bridge_retained` and freed with `CFRelease`.[^device-m]
- `Window::attachDevice` stores the device pointer and creates an internal queue for `clear`; releasing the PHP-side device while a window still references it is unsafe — destroy the window first (or keep the device alive until destroy).

# Checklist

1. Create window → attach device → loop → destroy window → release device.
2. Do not share window handles across process forks.
3. Prefer one app init per process; `App::init` is idempotent.

[^window-h]: metal-window.h
[^device-m]: metal-device.m
