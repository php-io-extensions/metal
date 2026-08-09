---
type: CoreType
title: Metal\\MTL\\Menu
description: Default menu bar, custom items, action poll
resource: /metal/mtl/menu.zep
tags: [metal, api, menu]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: menu-zep
    resource: /metal/mtl/menu.zep
    title: menu.zep
  - id: menu-h
    resource: /src/metal-menu.h
    title: metal-menu.h
  - id: menu-m
    resource: /src/metal-menu.m
    title: metal-menu.m
---

# Schema

| Method | Returns | Notes |
|--------|---------|--------|
| `installDefault(string $appName)` | `bool` | App \| File \| Edit \| Window \| Help; Quit Cmd+Q |
| `addItem(string $menuTitle, string $itemTitle, string $keyEquivalent, string $actionId)` | `bool` | Creates top-level menu if missing; `""` key = none |
| `pollAction()` | `string` | Pending `actionId`, or `""` if none |

# Behavior notes

- `installDefault` is idempotent (replaces main menu).[^menu-h]
- Built-in Quit sets pending action `"quit"` and calls terminate.[^menu-m]
- Custom items with `actionId === "quit"` also terminate.
- Poll from the same loop that calls `App::poll()` so menu events are processed.

# Examples

```php
use Metal\MTL\Menu;

Menu::installDefault('Metal');
Menu::addItem('File', 'New', 'n', 'file.new');

$action = Menu::pollAction();
if ($action === 'file.new') {
    // ...
}
```

[^menu-zep]: menu.zep
[^menu-h]: metal-menu.h
[^menu-m]: metal-menu.m
