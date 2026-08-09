---
type: Convention
title: Sibling patterns
description: Patterns borrowed from posi / sdl3 / glfw (not dependencies)
tags: [metal, convention, packaging]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: composer
    resource: /composer.json
    title: metal composer.json
  - id: config
    resource: /config.json
    title: metal config.json
---

# Borrowed patterns (style only)

| Pattern | From | How metal uses it |
|---------|------|-------------------|
| Thin Zephir + C helpers | posi | `metal/mtl/*.zep` call `mtl_*` in `src/*.h` |
| PIE `type: php-ext`, `build-path: ext` | sdl3 / glfw / posi | Same layout in `composer.json` |
| Static namespaced classes | sdl3 / glfw | `Metal\MTL\{App,Window,Menu,Device}` |
| Opaque `int` handles | sdl3 / glfw | Devices, windows, queues, layers |
| Version `0.7.1`, PHP ≥ 8.2 | siblings | Aligned release target |
| IDE stubs path | sdl3 | `config.json` stubs → `ide/%version%/%namespace%/` |

# Not borrowed

- No `package-dependencies` / pkg-config third-party libs (unlike SDL3/GLFW).
- No Linux installers; Darwin-only `os-families`.
- No shared code or composer `require` on sdl3/glfw/posi.

Keep this boundary explicit in docs and CI so metal never grows accidental cross-links.
