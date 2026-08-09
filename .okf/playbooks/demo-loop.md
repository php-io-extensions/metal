---
type: Playbook
title: Minimal demo loop
description: examples/proof_window.php — window, animated clear, Quit
resource: /examples/proof_window.php
tags: [metal, playbook, demo]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: demo
    resource: /examples/proof_window.php
    title: proof_window.php
  - id: readme
    resource: /README.md
    title: README
---

# Goal

Prove the extension can init AppKit, show a window, install a menu bar with Quit, attach Metal, and animate a clear color until the user quits.

# Canonical demo

```bash
php -d extension=./ext/modules/metal.so examples/proof_window.php
```

Smoke (auto-exit after N frames):

```bash
METAL_DEMO_MAX_FRAMES=90 php -d extension=./ext/modules/metal.so examples/proof_window.php
```

# What the demo does[^demo]

1. `App::init()` / `App::resetQuit()`
2. `Menu::installDefault('Metal Demo')` + `Menu::addItem('Demo', 'Quit Demo', 'q', 'quit')`
3. `Window::create(…, 960, 540)` + `Device::createSystemDefault()` + `attachDevice`
4. Loop: `App::poll()` → `Menu::pollAction()` → animated `Window::clear($w, $r, $g, $b, 255)` (ints 0..255)
5. Exit on window close, quit action / Cmd+Q, or `METAL_DEMO_MAX_FRAMES`
6. `Window::destroy` + `Device::release`

# Acceptance criteria

- Window appears with menu bar; Demo → Quit Demo and Cmd+Q work.
- Drawable shows an animated RGB pulse.
- Smoke env exits cleanly with `demo exited cleanly`.
- No SDL3/GLFW symbols.

[^demo]: proof_window.php
