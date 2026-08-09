---
type: Trap
title: poll vs run
description: Prefer App::poll() from PHP event loops
resource: /metal/mtl/app.zep
tags: [metal, trap, event-loop]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: app-zep
    resource: /metal/mtl/app.zep
    title: app.zep
  - id: app-h
    resource: /src/metal-app.h
    title: metal-app.h
  - id: app-m
    resource: /src/metal-app.m
    title: metal-app.m
---

# Trap

Calling `App::run()` from PHP and expecting to interleave Metal clears or menu polls.

# Why

`mtl_app_run` blocks in `[NSApp run]`.[^app-h] PHP cannot drive `Window::clear` / `Menu::pollAction` until the run loop exits.

# Prefer

```php
App::init();
while (App::poll()) {
    // clear / poll menu / business logic
}
```

`poll()` drains pending AppKit events once and returns `false` when quit was requested.[^app-zep]

Reserve `run()` for rare native-style entry points.

[^app-h]: metal-app.h
[^app-zep]: app.zep
