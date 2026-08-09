---
type: Trap
title: Explicit CAMetalLayer assignment
description: Do not rely on layerClass alone — assign the layer explicitly
resource: /src/metal-window.m
tags: [metal, trap, objc, cametal]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: window-m
    resource: /src/metal-window.m
    title: metal-window.m
---

# Symptom

Window appears but Metal clear fails (`nextDrawable` nil / no visible clear), or the view’s layer is not a `CAMetalLayer`.

# Cause

Implementing `+layerClass` returning `[CAMetalLayer class]` is not always enough for AppKit to install a usable Metal layer on the content view.

# Fix

In `MTLPhpView` init, create and assign explicitly:[^window-m]

```objc
CAMetalLayer *metalLayer = [CAMetalLayer layer];
metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
/* … */
self.layer = metalLayer;
self.wantsLayer = YES;
self.metalLayer = metalLayer;
```

Keep `+layerClass` as well, but **do not remove** the explicit assignment.

[^window-m]: metal-window.m
