---
type: Orientation
title: Standalone Darwin scope
description: macOS-only PIE constraints and zero coupling to SDL3/GLFW
resource: /composer.json
tags: [metal, darwin, isolation]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: config
    resource: /config.json
    title: Zephir config (frameworks)
  - id: config-m4
    resource: /ext/config.m4
    title: Portable ext/config.m4
---

# Darwin-only product

`composer.json` sets `php-ext.os-families` to `["darwin"]`.[^composer] `ext/config.m4` errors on non-Darwin hosts.[^config-m4]

Sibling packages `sdl3` and `glfw` support Linux + macOS. **Metal is stricter**: Darwin only.

# Zero coupling

This package must remain:

- Free of SDL3 headers, pkg-config, or link flags.
- Free of GLFW headers or link flags.
- Free of shared “window abstraction” C code from those siblings.

Style inspiration (layout, Zephir static classes, committed `ext/`) comes from posi/sdl3/glfw — **patterns only**, not runtime dependencies. See [Sibling patterns](/conventions/sibling-patterns.md) and [No SDL3/GLFW coupling](/traps/no-sdl-glfw-coupling.md).

# Frameworks (Apple only)

Linked frameworks (config.json + `METAL_SHARED_LIBADD`):[^config]

- Metal
- AppKit
- QuartzCore
- Foundation

No MetalKit dependency in the current link line.

[^composer]: PIE package manifest
[^config]: Zephir config (frameworks)
[^config-m4]: Portable ext/config.m4
