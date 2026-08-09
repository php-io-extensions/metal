# Architecture

* [Layered stack](stack.md) - Zephir → C ABI headers → `.m` bridges → Apple frameworks
* [C ABI surface](c-abi.md) - Opaque `uintptr_t` handles and `mtl_*` entry points
* [Objective-C bridge](objc-bridge.md) - AppKit/Metal/QuartzCore ownership and ARC
