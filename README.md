# php-metal

[![PHP](https://img.shields.io/badge/php-%E2%89%A5%208.2-777bb4?logo=php&logoColor=white)](https://www.php.net)
[![Metal](https://img.shields.io/badge/Metal-macOS%20only-black)](https://developer.apple.com/metal/)
[![Built with Zephir](https://img.shields.io/badge/built%20with-Zephir-ff6a00)](https://zephir-lang.com/)
[![Platform](https://img.shields.io/badge/platform-macOS-lightgrey)](#requirements)
[![License: MIT](https://img.shields.io/badge/license-MIT-green)](#license)

> PHP extension for Apple Metal + AppKit — built with [Zephir](https://zephir-lang.com/), installable via [PHP PIE](https://github.com/php/pie).

`metal` is a **standalone macOS-only** binding: open an `NSWindow`, install a macOS
menu bar, draw through a `CAMetalLayer` with Metal, create offscreen
`MTLTexture` targets (0.7.1+) for headless engines/UIs, and blit those textures
into a live window (`Window::presentTexture`, 0.7.2+). It has no knowledge of
other windowing libraries.

PHP API is namespaced under `Metal\MTL\…` as static classes. Opaque native
handles are `int` values.

---

## Requirements

| Component            | Minimum version | Notes                                      |
| -------------------- | --------------- | ------------------------------------------ |
| PHP                  | 8.2             | ZTS and NTS                                |
| OS                   | macOS           | arm64 + x86_64 (PIE `os-families: darwin`) |
| Frameworks           | system          | Metal, AppKit, QuartzCore, Foundation      |
| Compiler             | Apple Clang     | Objective-C ARC                            |
| `php-dev` / `phpize` | matches PHP     | Required for non-PIE builds                |

---

## Installation

### Via PHP PIE (recommended)

```bash
pie install php-io-extensions/metal
```

macOS only — configure fails on other platforms.

### Platform installer

```bash
bash install-macos.sh
```

Laravel Herd:

```bash
bash install-macos-herd.sh
```

### Manual build (maintainers)

```bash
bash scripts/prepare-ext.sh
cd ext && phpize && ./configure --enable-metal && make -j1
php -n -d extension=modules/metal.so --ri metal
```

`scripts/prepare-ext.sh` regenerates Zephir C, syncs `src/` into `ext/src/`,
patches `config.m4`, installs `Makefile.frag` for `.m` sources, and strips
phpize junk so the committed `ext/` tree stays PIE-ready.

> Use `make -j1` (or the installer). Parallel make is fine for `.c` objects; the
> ObjC fragment is conservative.

---

## Quick start

```php
use Metal\MTL\App;
use Metal\MTL\Device;
use Metal\MTL\Menu;
use Metal\MTL\Window;

App::init();
Menu::installDefault('My App');
Menu::addItem('Demo', 'Quit Demo', 'q', 'quit');

$window = Window::create('Metal', 800, 600);
$device = Device::createSystemDefault();
Window::attachDevice($window, $device);

while (!Window::shouldClose($window) && !App::shouldQuit()) {
    App::poll();
    if (Menu::pollAction() === 'quit') {
        break;
    }
    Window::clear($window, 30, 30, 40, 255);
    usleep(16_000);
}

Window::destroy($window);
Device::release($device);
```

Demo:

```bash
php -d extension=./ext/modules/metal.so examples/proof_window.php
# optional smoke: METAL_DEMO_MAX_FRAMES=90 php -d extension=./ext/modules/metal.so examples/proof_window.php
```

---

## API surface (0.7)

| Class              | Role                                      |
| ------------------ | ----------------------------------------- |
| `Metal\MTL\App`    | `NSApplication` init / poll / quit        |
| `Metal\MTL\Window` | `NSWindow` + `CAMetalLayer` clear/present |
| `Metal\MTL\Menu`   | Menu bar + custom items / Quit            |
| `Metal\MTL\Device` | `MTLDevice` / command queue handles       |

---

## License

MIT — see [LICENSE](LICENSE).
