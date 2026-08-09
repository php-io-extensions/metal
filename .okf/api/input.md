---
type: CoreType
title: Metal\\MTL\\Input
description: Keyboard, mouse, and gamepad queries (AppKit + GameController)
resource: /metal/mtl/input.zep
tags: [metal, api, input]
status: draft
generated: { by: cursor-agent/grok-4.5, at: 2026-08-09T06:55:00Z }
sources:
  - id: input-zep
    resource: /metal/mtl/input.zep
    title: input.zep
  - id: input-h
    resource: /src/metal-input.h
    title: metal-input.h
---

# Schema

| Method | Returns | Maps to |
|--------|---------|---------|
| `keyDown(int $keycode)` | `bool` | `mtl_input_key_down` — macOS virtual key codes |
| `mouseButtonDown(int $button)` | `bool` | `mtl_input_mouse_button_down` — 0 left, 1 right, 2 middle |
| `mousePosition(int $window = 0)` | `array` | `mtl_input_mouse_position` — `[x, y]`; `0` = screen |
| `mouseScrollDelta()` | `array` | `mtl_input_mouse_scroll_delta` — `[dx, dy]` since last `App::poll` |
| `gamepadCount()` | `int` | `mtl_input_gamepad_count` |
| `gamepadName(int $index)` | `string` | `mtl_input_gamepad_name` |
| `gamepadButtonDown(int $index, int $button)` | `bool` | `mtl_input_gamepad_button_down` |
| `gamepadAxis(int $index, int $axis)` | `float` | `mtl_input_gamepad_axis` |
| `gamepadState(int $index)` | `array` | PHP snapshot over name/buttons/axes |

All methods are `public static` on `Metal\MTL\Input` (0.7.2+).[^input-zep]

# Semantics

- Call `App::poll()` each frame. Scroll deltas clear at the start of each poll; keys/mouse buttons use live system state (CoreGraphics / `NSEvent`).
- Mouse / stick **Y grows upward** (AppKit / GameController).
- Gamepads use Apple's **GameController** framework (`GCController`), not SDL/GLFW.
- Button / axis integer layouts are documented in [`metal-input.h`](/src/metal-input.h).

# Examples

```php
use Metal\MTL\App;
use Metal\MTL\Input;

App::init();
while (App::poll()) {
    if (Input::keyDown(0x0D)) { // W
        // ...
    }
    [$x, $y] = Input::mousePosition($window);
}
```

[^input-zep]: input.zep
