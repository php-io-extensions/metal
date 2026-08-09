---
type: Orientation
title: Package overview
description: What metal is, version targets, and what it deliberately is not
resource: /composer.json
tags: [metal, orientation, php-ext, macos]
status: draft
generated: { by: cursor-agent/grok-4.5, at: "2026-08-09T03:05:00Z" }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: config
    resource: /config.json
    title: Zephir config
  - id: readme
    resource: /README.md
    title: README
  - id: demo
    resource: /examples/proof_window.php
    title: proof_window.php
  - id: texture
    resource: /metal/mtl/texture.zep
    title: Texture API (0.7.1)
---

# Summary

`php-io-extensions/metal` is a **standalone macOS-only** PHP extension (`type: php-ext`) that lets PHP open a native macOS window, install a standard menu bar (including Quit), draw/clear through Metal via a `CAMetalLayer`, and create **offscreen `MTLTexture`** targets for headless engines/UIs.[^composer][^readme][^texture]

| Fact | Value |
|------|--------|
| Package | `php-io-extensions/metal` |
| Extension name | `metal` |
| Version | `0.7.1` |
| PHP | `>= 8.2` |
| OS | **macOS** only (PIE `os-families: ["darwin"]`) |
| Architectures | macOS arm64 and x86_64 |
| Author | Project Saturn Studios, LLC |
| License | MIT |

# End capability

1. Initialize `NSApplication` and drive events from PHP (`App::poll`).
2. Create an `NSWindow` with a Metal-backed view (`Window::create`).
3. Install App \| File \| Edit \| Window \| Help with Quit / Cmd+Q (`Menu::installDefault`).
4. Attach `MTLDevice` and clear/present RGBA via Metal (`Device` + `Window::clear` with ints 0..255).
5. **(0.7.1+)** Create offscreen RGBA8 textures (`Texture::create`) — clear / writePixel / readPixels without a window — for metal-gfx, game engines, and UIs.

Demo: `examples/proof_window.php` (optional `METAL_DEMO_MAX_FRAMES` smoke).[^demo]

# What it is not

- Not a binding to SDL3, GLFW, or any cross-platform window kit.
- Not a full Metal rendering engine (shaders / mesh pipelines come later).
- Not available on Linux or Windows.

# Public namespace

Zephir classes live under `Metal\MTL\` (`metal/mtl/*.zep`). IDE stubs: `ide/0.7.1/Metal/MTL/`.

See [Standalone macOS scope](/orientation/standalone-darwin.md) and [Layered stack](/architecture/stack.md).

[^composer]: PIE package manifest
[^readme]: README
[^demo]: proof_window.php
[^texture]: Texture API (0.7.1)
