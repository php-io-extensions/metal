# Directory Update Log

## 2026-08-09
* **Docs 0.7.1**: Orientation/overview + API index + C ABI + handle ownership refreshed for `Metal\MTL\Texture`. ScrapyardIO seeders updated to document offscreen textures / headless engines. User-facing copy: **macOS**, not Darwin.

## 2026-08-08
* **Release prep 0.7.0**: Package → `0.7.0`; stubs `ide/0.7.0/`; ScrapyardIO `EcosystemContentManifest` + seeders `php-io-extensions/metal/0.7.x/*`. Herd reinstall verified (`phpversion('metal')=0.7.0`). Ready for public repo + `pie install`.
* **Update**: Refreshed bundle against completed sources — `Window::clear` RGBA ints 0..255; installers; `proof_window.php`; `prepare-ext.sh`; traps (Makefile.frag, `METAL_SHARED_LIBADD`, CAMetalLayer, `make -j1`). No MetalKit.
* **Update**: Refreshed build/packaging concepts after parallel work landed `scripts/prepare-ext.sh`, patched `ext/config.m4` (Darwin gate + frameworks), and generated `ext/` sources. Still awaiting `examples/`, README, and `ide/` stubs.
* **Initialization**: Created OKF v0.2 knowledge bundle for `php-io-extensions/metal` grounded in `composer.json`, `config.json`, `src/*.h` / `src/*.m`, and Zephir classes under `metal/mtl/*.zep`.
* **Creation**: Orientation, architecture, API (App/Window/Menu/Device), build/packaging, conventions, traps, and playbooks.
* **Note**: Bundle marked `draft` pending Angel human verification of OKF content.

* **0.7.1**: Added `Metal\MTL\Texture` offscreen RGBA8 create/clear/read/write for headless engines/UIs/metal-gfx. Stubs `ide/0.7.1/`.
