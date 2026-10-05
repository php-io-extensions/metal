---
type: Runbook
title: Build, install, test
description: install-macos.sh into php84 and zhp, then the Pest suite.
resource: install-macos.sh
tags: [build, macos, pest]
status: draft
generated: { by: grok/4.7, at: 2026-10-04T22:46:00-04:00 }
sources:
  - id: installer
    resource: install-macos.sh
    title: install-macos.sh
  - id: config
    resource: config.m4
    title: config.m4
---

# Overview

`bash install-macos.sh` builds in a temp copy (the checkout stays clean) for Homebrew php@8.4 (NTS, `php84`) and php@8.4-zts (`zhp`). It installs `metal.so` into each `extension_dir`, ad-hoc signs it, and writes `30-metal.ini`. Other PHPs: pass the binaries as arguments.[^installer]

`config.m4` writes each `.m` rule itself (`-x objective-c -fno-objc-arc -fobjc-exceptions`) because `PHP_ADD_SOURCES` only knows `.c`/`.s`/`.S`/`.cpp`. It links Foundation, Metal, QuartzCore, and objc.[^config]

```bash
php84 --ri metal && zhp --ri metal
composer install
php84 -d memory_limit=128M vendor/bin/pest
zhp -d memory_limit=128M vendor/bin/pest
rm -rf vendor composer.lock .phpunit.cache
```

Both suites must exit 0. The gate test draws a stencil-then-cover triangle into a 4× target, resolves it, blits through a buffer, and reads the pixels back.

[^installer]: install-macos.sh
[^config]: config.m4
