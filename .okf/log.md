# Directory Update Log

## 2026-08-09
* **Version lock 0.7.2**: Corrected mistaken `0.7.3` bump. Package target is **`0.7.2`** everywhere (`composer.json`, `config.json`, `PHP_METAL_VERSION`, `ide/0.7.2/`). Removed `ide/0.7.3/`. Input + presentTexture ship in this cut.
* **Docs 0.7.2 catch-up**: OKF Window/C ABI/overview + ScrapyardIO seeders document `Window::getDevice` / `Window::presentTexture` (blit offscreen RGBA8 → CAMetalLayer). Stale `ide/0.7.1` path pointers → current stubs (`ide/0.7.2/`).
* **0.7.2 Input**: Added `Metal\MTL\Input` + `src/metal-input.{h,m}` (keyboard/mouse via CoreGraphics/NSEvent; gamepads via GameController). `mtl_app_poll` clears scroll and observes wheel events. Linked `-framework GameController -framework CoreGraphics`. Stubs `ide/0.7.2/`. Unblocks `microscrap/metal` helpers and later `metal-gfx` Human Input (`hi-metal-gfx`).
* **0.7.2 presentTexture**: `mtl_window_get_device` / `mtl_window_present_texture`; layer pixel format RGBA8Unorm + `framebufferOnly = NO` for blit. Stubs `ide/0.7.2/`. Unblocks windowed metal-gfx (`attachedTo` + handler present).
* **Docs 0.7.1**: Orientation/overview + API index + C ABI + handle ownership refreshed for `Metal\MTL\Texture`. ScrapyardIO seeders updated to document offscreen textures / headless engines. User-facing copy: **macOS**, not Darwin.

## 2026-08-08
* **Release prep 0.7.0**: Package → `0.7.0`; stubs `ide/0.7.0/`; ScrapyardIO `EcosystemContentManifest` + seeders `php-io-extensions/metal/0.7.x/*`. Herd reinstall verified (`phpversion('metal')=0.7.0`). Ready for public repo + `pie install`.
* **Update**: Refreshed bundle against completed sources — `Window::clear` RGBA ints 0..255; installers; `proof_window.php`; `prepare-ext.sh`; traps (Makefile.frag, `METAL_SHARED_LIBADD`, CAMetalLayer, `make -j1`). No MetalKit.
* **Update**: Refreshed build/packaging concepts after parallel work landed `scripts/prepare-ext.sh`, patched `ext/config.m4` (Darwin gate + frameworks), and generated `ext/` sources. Still awaiting `examples/`, README, and `ide/` stubs.
* **Initialization**: Created OKF v0.2 knowledge bundle for `php-io-extensions/metal` grounded in `composer.json`, `config.json`, `src/*.h` / `src/*.m`, and Zephir classes under `metal/mtl/*.zep`.
* **Creation**: Orientation, architecture, API (App/Window/Menu/Device), build/packaging, conventions, traps, and playbooks.
* **Note**: Bundle marked `draft` pending Angel human verification of OKF content.

* **0.7.1**: Added `Metal\MTL\Texture` offscreen RGBA8 create/clear/read/write for headless engines/UIs/metal-gfx. Stubs `ide/0.7.1/`.
