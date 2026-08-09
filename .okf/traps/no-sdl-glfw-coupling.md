---
type: Trap
title: No SDL3/GLFW coupling
description: Standalone product boundary
tags: [metal, trap, isolation]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: config
    resource: /config.json
    title: Zephir config
---

# Trap

Copy-pasting `config.m4` / install scripts from sdl3 or glfw and leaving `pkg-config sdl3` / `-lGLFW` behind.

# Why it matters

Metal is a **standalone** Darwin extension. Accidental SDL/GLFW link flags or shared headers reintroduce coupling and break the product story (native AppKit + Metal only).

# Checks

- `composer.json` / `config.json` mention only Apple frameworks.[^config]
- No `require` on `php-io-extensions/sdl3` or `glfw`.
- Examples must not `use Sdl3\…` or `Glfw\…`.

See [Standalone Darwin scope](/orientation/standalone-darwin.md).

[^config]: Zephir config
