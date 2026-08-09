# Agent guidance — php-io-extensions/metal

1. **Read [`.okf/index.md`](.okf/index.md) first** before changing architecture, API, or packaging.
2. Open only the concept files you need; prefer `status: stable` when present (most are currently `draft`).
3. This package is **macOS-only** and has **zero coupling** to SDL3/GLFW — do not add those dependencies.
4. Public PHP API: `Metal\MTL\{App,Window,Menu,Device,Texture}` static methods wrapping `src/metal-*.h`.
5. `Window::clear` / `Texture::clear` use **integer RGBA 0..255** (C ABI floats 0..1). Offscreen textures are for headless engines/UIs (`Texture`, since **0.7.1**).
6. Build gotchas: `Makefile.frag` for `.m`, `METAL_SHARED_LIBADD -framework …`, explicit `CAMetalLayer` assignment, prefer `make -j1`.
7. Demo: `examples/proof_window.php`; smoke with `METAL_DEMO_MAX_FRAMES`.
8. When you learn a durable package fact, **update the matching `.okf` concept**, bump `generated.at`, and append `.okf/log.md`.
9. Do not invent APIs not present in `.zep` / headers.
