---
type: Architecture
title: Objective-C bridge
description: AppKit/Metal/QuartzCore ownership and ARC
resource: /src/metal-window.m
tags: [metal, objc, appkit]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: app-m
    resource: /src/metal-app.m
    title: metal-app.m
  - id: window-m
    resource: /src/metal-window.m
    title: metal-window.m
  - id: menu-m
    resource: /src/metal-menu.m
    title: metal-menu.m
  - id: device-m
    resource: /src/metal-device.m
    title: metal-device.m
  - id: config
    resource: /config.json
    title: Zephir config
  - id: config-m4
    resource: /ext/config.m4
    title: Portable ext/config.m4
---

# Build flags

`config.json` lists `-fobjc-arc` and frameworks Metal / AppKit / QuartzCore / Foundation.[^config]

For PIE, `scripts/prepare-ext.sh` copies bridges into `ext/src/`. Linking uses `METAL_SHARED_LIBADD=… -framework …` (not `PHP_ADD_FRAMEWORK` alone) — see [Framework link trap](/traps/framework-shared-libadd.md). ObjC compile rules live in `Makefile.frag`.[^config-m4]

# App (`metal-app.m`)[^app-m]

- Creates shared `NSApplication`, sets `NSApplicationActivationPolicyRegular`.
- Installs a small `MTLAppDelegate` that sets a quit flag on terminate request but returns `NSTerminateCancel` so PHP can exit cleanly.
- `mtl_app_poll` drains pending events with a non-blocking `untilDate`.

# Window (`metal-window.m`)[^window-m]

- `MTLPhpView` implements `+layerClass` → `CAMetalLayer` **and** explicitly assigns `self.layer = [CAMetalLayer layer]` with `wantsLayer = YES`. Do not rely on `layerClass` alone — see [CAMetalLayer assignment](/traps/cametal-layer-assign.md).
- Pixel format `MTLPixelFormatBGRA8Unorm`; drawable size tracks backing scale.
- Window box holds `NSWindow`, view, delegate, device, and command queue.
- Closing the window sets a closed flag and calls `mtl_app_terminate`.
- `mtl_window_clear` acquires `nextDrawable`, clear pass, present, commit.

# Menu (`metal-menu.m`)[^menu-m]

- Standard main menu; Quit (Cmd+Q) sets pending action `"quit"` and terminates.
- Custom items store `action_id` in `representedObject`; `mtl_menu_poll_action` returns and clears it.

# Device (`metal-device.m`)[^device-m]

- Uses `__bridge_retained` / `CFRelease` so handles survive across PHP calls under ARC.
- System default device via `MTLCreateSystemDefaultDevice()`.

[^config]: Zephir config
[^config-m4]: Portable ext/config.m4
[^app-m]: metal-app.m
[^window-m]: metal-window.m
[^menu-m]: metal-menu.m
[^device-m]: metal-device.m
