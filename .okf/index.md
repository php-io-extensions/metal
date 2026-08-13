---
okf_version: "0.2"
---

# php-io-extensions/metal

macOS-only PHP extension: Zephir static classes → thin C ABI → Objective-C (AppKit + Metal + QuartzCore + Foundation + GameController). Open an `NSWindow`, install a macOS menu bar (with Quit), clear/present via `CAMetalLayer`, create offscreen `MTLTexture` targets for headless engines/UIs (0.7.1+), blit textures into a live window (`Window::presentTexture`, 0.7.2+), and query keyboard/mouse/gamepad via `Metal\\MTL\\Input` (0.7.2+).

**Prefer** concepts with `status: stable` when present; content is currently `draft` pending Angel’s human verification of the OKF docs (implementation facts are grounded in shipped sources).

# Orientation

* [Package overview](orientation/overview.md) - What metal is, version targets, and what it deliberately is not
* [Standalone macOS scope](orientation/standalone-darwin.md) - macOS-only PIE constraints and zero coupling to SDL3/GLFW

# Architecture

* [Layered stack](architecture/stack.md) - Zephir → C ABI headers → `.m` bridges → Apple frameworks
* [C ABI surface](architecture/c-abi.md) - Opaque `uintptr_t` handles and `mtl_*` entry points
* [Objective-C bridge](architecture/objc-bridge.md) - AppKit/Metal/QuartzCore ownership and ARC

# Public PHP API

* [Metal\\MTL\\App](api/app.md) - NSApplication init, poll, quit flags
* [Metal\\MTL\\Window](api/window.md) - NSWindow + CAMetalLayer; clear uses RGBA ints 0..255
* [Metal\\MTL\\Menu](api/menu.md) - Default menu bar, custom items, action poll
* [Metal\\MTL\\Device](api/device.md) - MTLDevice / command queue handles
* [Metal\\MTL\\Texture](api/texture.md) - Offscreen RGBA8 textures (0.7.1+)
* [Metal\\MTL\\Input](api/input.md) - Keyboard / mouse / gamepad (0.7.2+; scalar mouse 0.7.5+)

# Build & packaging

* [Zephir + PIE install](build/zephir-and-pie.md) - prepare-ext, install-macos*.sh, PIE, make -j1
* [Committed ext/ notes](build/packaging-ext.md) - Makefile.frag, METAL_SHARED_LIBADD, strip phpize junk

# Conventions

* [Sibling patterns](conventions/sibling-patterns.md) - Patterns borrowed from posi / sdl3 / glfw (not dependencies)
* [Handle ownership](conventions/handle-ownership.md) - Opaque ints, release/destroy rules

# Traps

* [Darwin-only builds](traps/darwin-only.md) - Linux/Windows will not build or load
* [No SDL3/GLFW coupling](traps/no-sdl-glfw-coupling.md) - Standalone product boundary
* [poll vs run](traps/poll-vs-run.md) - Prefer App::poll() from PHP event loops
* [ObjC Makefile.frag required](traps/objc-makefile-frag.md) - phpize mishandles .m sources
* [Framework link via METAL_SHARED_LIBADD](traps/framework-shared-libadd.md) - PHP_ADD_FRAMEWORK is not enough
* [Explicit CAMetalLayer assignment](traps/cametal-layer-assign.md) - Do not rely on layerClass alone
* [Prefer make -j1](traps/parallel-make.md) - Conservative ObjC fragment builds
* [NSBeep on unhandled keys](traps/nsbeep-unhandled-keys.md) - View must swallow keyDown for polled input

# Playbooks

* [Minimal demo loop](playbooks/demo-loop.md) - examples/proof_window.php + METAL_DEMO_MAX_FRAMES
* [Regenerate committed ext/](playbooks/regenerate-ext.md) - Maintainer steps before tagging

# Indexes

* [Orientation](orientation/) — start here
* [Architecture](architecture/)
* [API](api/)
* [Build](build/)
* [Conventions](conventions/)
* [Traps](traps/)
* [Playbooks](playbooks/)
