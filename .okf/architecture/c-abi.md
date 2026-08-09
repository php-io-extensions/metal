---
type: Architecture
title: C ABI surface
description: Opaque uintptr_t handles and mtl_* entry points
resource: /src/metal-app.h
tags: [metal, abi, c]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: app-h
    resource: /src/metal-app.h
    title: metal-app.h
  - id: window-h
    resource: /src/metal-window.h
    title: metal-window.h
  - id: menu-h
    resource: /src/metal-menu.h
    title: metal-menu.h
  - id: device-h
    resource: /src/metal-device.h
    title: metal-device.h
  - id: texture-h
    resource: /src/metal-texture.h
    title: metal-texture.h
  - id: window-zep
    resource: /metal/mtl/window.zep
    title: window.zep
---

# Conventions

- Success/boolean outcomes: C `int` where `1` = true/success, `0` = false/failure (Zephir maps to `bool`).
- Native objects: `uintptr_t` opaque handles exposed to PHP as `int`; `0` means failure or null.
- Headers are C-linkage (`extern "C"`) and do not expose Objective-C types.

# Modules

## App (`metal-app.h`)[^app-h]

| Function | Notes |
|----------|--------|
| `mtl_app_init` | Idempotent `NSApplication` setup |
| `mtl_app_poll` | Drain events once; returns `0` if quit requested |
| `mtl_app_run` | Blocking `[NSApp run]` (rarely used from PHP) |
| `mtl_app_terminate` | Request quit |
| `mtl_app_should_quit` / `mtl_app_reset_quit` | Quit flag |

## Window (`metal-window.h`)[^window-h]

| Function | Notes |
|----------|--------|
| `mtl_window_create` | Title + size; owns handle until destroy |
| `mtl_window_destroy` / show / hide / set_title | Lifecycle |
| `mtl_window_should_close` | Close or app quit |
| `mtl_window_get_width` / `get_height` | Content size |
| `mtl_window_attach_device` | Bind MTLDevice to CAMetalLayer |
| `mtl_window_get_layer` | Opaque CAMetalLayer pointer |
| `mtl_window_clear` | RGBA **floats 0..1**; PHP `Window::clear` takes ints 0..255 and scales[^window-zep] |

## Menu (`metal-menu.h`)[^menu-h]

| Function | Notes |
|----------|--------|
| `mtl_menu_install_default` | App\|File\|Edit\|Window\|Help + Quit |
| `mtl_menu_add_item` | Custom item + `action_id` token |
| `mtl_menu_poll_action` | Copy pending action_id into buffer |

## Device (`metal-device.h`)[^device-h]

| Function | Notes |
|----------|--------|
| `mtl_device_create_system_default` | Retained MTLDevice |
| `mtl_device_release` | CFRelease |
| `mtl_device_new_command_queue` / `mtl_command_queue_release` | Queue handles |
| `mtl_device_get_name` | UTF-8 name into caller buffer |

## Texture (`metal-texture.h`) — 0.7.1+[^texture-h]

| Function | Notes |
|----------|--------|
| `mtl_texture_create_rgba8` | Offscreen RGBA8Unorm; Shared/Managed storage |
| `mtl_texture_release` | CFRelease |
| `mtl_texture_get_width` / `get_height` | Dimensions |
| `mtl_texture_clear` | GPU clear; RGBA **floats 0..1** |
| `mtl_texture_write_pixel` / `read_pixel` | CPU pixel access |
| `mtl_texture_read_rgba8` | Full tightly packed RGBA8888 into caller buffer |

PHP mapping: [API index](/api/index.md). Ownership: [Handle ownership](/conventions/handle-ownership.md).

[^app-h]: metal-app.h
[^window-h]: metal-window.h
[^menu-h]: metal-menu.h
[^device-h]: metal-device.h
[^texture-h]: metal-texture.h
[^window-zep]: window.zep
