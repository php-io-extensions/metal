---
type: Architecture
title: Layered stack
description: Zephir → C ABI headers → Objective-C bridges → Apple frameworks
resource: /config.json
tags: [metal, architecture, zephir, objc]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: config
    resource: /config.json
    title: Zephir config
  - id: app-h
    resource: /src/metal-app.h
    title: App C ABI
  - id: app-zep
    resource: /metal/mtl/app.zep
    title: App Zephir wrapper
  - id: prepare
    resource: /scripts/prepare-ext.sh
    title: prepare-ext.sh
---

# Layers

```text
PHP (Metal\MTL\{App,Window,Menu,Device})
        │  Zephir static methods + %{ %} inline C
        ▼
C ABI (src/metal-*.h)          mtl_* functions, uintptr_t handles
        │
        ▼
Objective-C (src/metal-*.m)    AppKit / Metal / QuartzCore / Foundation
        │
        ▼
macOS frameworks               NSApplication, NSWindow, NSMenu,
                               MTLDevice, CAMetalLayer
```

# Source map

| Layer | Path | Role |
|-------|------|------|
| Zephir | `metal/mtl/{app,window,menu,device}.zep` | Public PHP API |
| Headers | `src/metal-{app,window,menu,device}.h` | Stable C ABI for Zephir |
| ObjC | `src/metal-{app,window,menu,device}.m` | Bridge implementations |
| Zephir config | `config.json` | `extra-sources`, ARC, frameworks |
| Packaging | `scripts/prepare-ext.sh` | Generate + sync into `ext/`[^prepare] |
| PIE | `composer.json` | `build-path: ext`, Darwin-only |

# Design intent

- Keep Zephir thin: map 1:1 to C ABI (posi-style).[^app-zep]
- Keep ObjC behind C headers so Zephir never imports Objective-C directly.[^app-h]
- Prefer polling (`App::poll`) over `App::run` for PHP-driven loops — see [poll vs run](/traps/poll-vs-run.md).

[^config]: Zephir config
[^app-zep]: App Zephir wrapper
[^app-h]: App C ABI
[^prepare]: prepare-ext.sh
