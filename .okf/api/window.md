---
type: CoreType
title: Metal\\MTL\\Window
description: NSWindow + CAMetalLayer create/clear/present
resource: /metal/mtl/window.zep
tags: [metal, api, window]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:55:00Z }
sources:
  - id: window-zep
    resource: /metal/mtl/window.zep
    title: window.zep
  - id: window-h
    resource: /src/metal-window.h
    title: metal-window.h
  - id: window-m
    resource: /src/metal-window.m
    title: metal-window.m
---

# Schema

| Method | Returns | Notes |
|--------|---------|--------|
| `create(string $title, int $width, int $height)` | `int` | Opaque handle; `0` on failure. Default size 800×600 if ≤0 in C. |
| `destroy(int $window)` | `void` | Caller owns until destroy |
| `setTitle(int $window, string $title)` | `void` | |
| `show(int $window)` / `hide(int $window)` | `void` | |
| `shouldClose(int $window)` | `bool` | Closed flag or app quit |
| `getWidth` / `getHeight` | `int` | Content bounds |
| `attachDevice(int $window, int $device)` | `bool` | Required before `clear` / `presentTexture` |
| `getDevice(int $window)` | `int` | **0.7.2+** Borrowed `MTLDevice` from the window, or `0` |
| `getLayer(int $window)` | `int` | Opaque CAMetalLayer pointer |
| `clear(int $window, int $r, int $g, int $b, int $a = 255)` | `bool` | RGBA **0..255**; acquire drawable, clear, present |
| `presentTexture(int $window, int $texture)` | `bool` | **0.7.2+** Blit offscreen RGBA8 texture → drawable and present |

# Examples

```php
use Metal\MTL\App;
use Metal\MTL\Window;
use Metal\MTL\Device;

App::init();
$win = Window::create('Metal', 800, 600);
$dev = Device::createSystemDefault();
Window::attachDevice($win, $dev);

while (!Window::shouldClose($win) && App::poll()) {
    Window::clear($win, 26, 51, 102, 255);
}

Window::destroy($win);
Device::release($dev);
```

# Implementation notes

- View assigns a real `CAMetalLayer` to `self.layer` (do not rely on `+layerClass` alone on modern macOS).
- See trap: [CAMetalLayer assignment](../traps/cametal-layer-assign.md)
