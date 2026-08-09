# Public PHP API

All public classes live under `Metal\MTL` and expose **static** methods. Opaque native objects are PHP `int` handles (`uintptr_t` in C).

`Window::clear` takes **RGBA integers 0..255** (default alpha 255); the C ABI uses floats 0..1.

* [Metal\\MTL\\App](app.md) - NSApplication init, poll, quit flags
* [Metal\\MTL\\Window](window.md) - NSWindow + CAMetalLayer create/clear/present
* [Metal\\MTL\\Menu](menu.md) - Default menu bar, custom items, action poll
* [Metal\\MTL\\Device](device.md) - MTLDevice / command queue handles
