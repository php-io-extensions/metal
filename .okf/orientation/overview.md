---
type: Orientation
title: Package overview
description: What metal is, version targets, and what it deliberately is not
resource: /composer.json
tags: [metal, orientation, php-ext]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
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
---

# Summary

`php-io-extensions/metal` is a **standalone Darwin-only** PHP extension (`type: php-ext`) that lets PHP open a native macOS window, install a standard menu bar (including Quit), and draw/clear through Metal via a `CAMetalLayer`.[^composer][^readme]

| Fact | Value |
|------|--------|
| Package | `php-io-extensions/metal` |
| Extension name | `metal` |
| Version | `0.7.0` |
| PHP | `>= 8.2` |
| OS | Darwin only (`os-families: ["darwin"]`) |
| Architectures | macOS arm64 and x86_64 |
| Author | Project Saturn Studios, LLC |
| License | MIT |

# End capability

1. Initialize `NSApplication` and drive events from PHP (`App::poll`).
2. Create an `NSWindow` with a Metal-backed view (`Window::create`).
3. Install App \| File \| Edit \| Window \| Help with Quit / Cmd+Q (`Menu::installDefault`).
4. Attach `MTLDevice` and clear/present RGBA via Metal (`Device` + `Window::clear` with ints 0..255).

Demo: `examples/proof_window.php` (optional `METAL_DEMO_MAX_FRAMES` smoke).[^demo]

# What it is not

- Not a binding to SDL3, GLFW, or any cross-platform window kit.
- Not a full Metal rendering engine (v0.5 focuses on window + menu + clear/present).
- Not available on Linux or Windows.

# Public namespace

Zephir classes live under `Metal\MTL\` (`metal/mtl/*.zep`). IDE stubs: `ide/0.7.0/Metal/MTL/`.

See [Standalone Darwin scope](/orientation/standalone-darwin.md) and [Layered stack](/architecture/stack.md).

[^composer]: PIE package manifest
[^readme]: README
[^demo]: proof_window.php
