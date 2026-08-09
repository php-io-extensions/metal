---
type: CoreType
title: Metal\\MTL\\App
description: NSApplication init, poll, quit flags
resource: /metal/mtl/app.zep
tags: [metal, api, app]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: app-zep
    resource: /metal/mtl/app.zep
    title: app.zep
  - id: app-h
    resource: /src/metal-app.h
    title: metal-app.h
---

# Schema

| Method | Returns | Maps to |
|--------|---------|---------|
| `init()` | `bool` | `mtl_app_init` |
| `poll()` | `bool` | `mtl_app_poll` — `false` when quit requested |
| `run()` | `void` | `mtl_app_run` (blocking) |
| `terminate()` | `void` | `mtl_app_terminate` |
| `shouldQuit()` | `bool` | `mtl_app_should_quit` |
| `resetQuit()` | `void` | `mtl_app_reset_quit` |

All methods are `public static` on `Metal\MTL\App`.[^app-zep]

# Examples

```php
use Metal\MTL\App;

App::init();
while (App::poll()) {
    // ... draw / handle menu actions ...
}
```

Prefer `poll()` over `run()` from PHP — see [poll vs run](/traps/poll-vs-run.md).

[^app-zep]: app.zep
