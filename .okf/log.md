# Log

## 2026-10-28

* **Version**: 0.11.0 in `PHP_METAL_VERSION` (`php_metal.h`), `AGENTS.md`, README and the index; `branch-alias` `dev-main` is `0.11.x-dev`. Promoted with the Venusian 0.11 ecosystem. No API or behaviour change. Built and loaded on Homebrew PHP 8.4 NTS and ZTS: 49 passed on each.
* **Coverage**: `scripts/support.php` writes `SUPPORT.md` and the README's API badge from clang's AST dump of the macOS SDK (15.4, the floor): every method and property accessor of Metal.framework's classes, categories and protocols (Metal's objects are protocols, so protocol methods count, unlike AppKit's), of QuartzCore's CAMetalLayer, CAMetalDrawable, CAEDRMetadata and CAMetalDisplayLink, and Metal's MTL C functions, not deprecated or unavailable on macOS. Bound when a stub declares the method the selector gives (parts joined), found up the superclass and adopted-protocol graph; a renamed getter (`isDepthWriteEnabled`) also binds under its property's name. `--check` exits 1 when the list or badge is stale. 189 / 1738 (10.9%).

## 2026-10-08

Staged-window presentation and HDR: drawable timeout, transaction presents, EDR, colorspace, `CAEDRMetadata`, drawable `presentedTime` / `drawableID`, timed and paced presents. Suite 49 on Homebrew PHP 8.4 NTS and ZTS.

## 2026-10-04

Created the bundle for 0.10.0. The extension binds Metal and CAMetalLayer 1:1. The suite is 46 tests, 455 assertions, green on Homebrew PHP 8.4 NTS and ZTS. On this M1 a private buffer's `contents` pointer is not nil, and the gate's hypotenuse resolves along the main diagonal at two of four samples.
