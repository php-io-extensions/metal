# Public PHP API

All public classes live under `Metal\MTL` and expose **static** methods. Opaque native objects are PHP `int` handles (`uintptr_t` in C).

`Window::clear` / `Texture::clear` take **RGBA integers 0..255** (default alpha 255); the C ABI uses floats 0..1.

* [Metal\\MTL\\App](app.md) - NSApplication init, poll, quit flags
* [Metal\\MTL\\Window](window.md) - NSWindow + CAMetalLayer; `getDevice` / `presentTexture` (0.7.2+)
* [Metal\\MTL\\Menu](menu.md) - Default menu bar, custom items, action poll
* [Metal\\MTL\\Device](device.md) - MTLDevice / command queue handles
* [Metal\\MTL\\Texture](texture.md) - Offscreen RGBA8Unorm textures (0.7.1+) for headless engines/UIs
* [Metal\\MTL\\Input](input.md) - Keyboard / mouse / gamepad (0.7.2+; AppKit + GameController)
