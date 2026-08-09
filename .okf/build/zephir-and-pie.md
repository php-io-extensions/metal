---
type: Playbook
title: Zephir + PIE install
description: Generate, configure, install on Darwin
resource: /composer.json
tags: [metal, build, pie, zephir]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: prepare
    resource: /scripts/prepare-ext.sh
    title: prepare-ext.sh
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
  - id: herd
    resource: /install-macos-herd.sh
    title: install-macos-herd.sh
  - id: readme
    resource: /README.md
    title: README
  - id: config-m4
    resource: /ext/config.m4
    title: Portable ext/config.m4
---

# Requirements

| Component | Notes |
|-----------|--------|
| macOS | arm64 or x86_64 |
| PHP | ≥ 8.2 with matching `phpize` / headers |
| Xcode CLT | Apple Clang + system frameworks |
| Zephir | For regenerating `ext/` (`ZEPHIR_BIN` optional) |

# PIE (consumers)

```bash
pie install php-io-extensions/metal
```

Uses `type: php-ext`, `build-path: "ext"`, `--enable-metal`.[^composer] Darwin-only.

# Platform installers

```bash
bash install-macos.sh
bash install-macos-herd.sh   # Laravel Herd
```

Installers verify Darwin, run prepare + `phpize` / configure / **`make -j1`**, install `.so`, enable for detected SAPIs.[^install][^herd]

# Manual maintainer build

```bash
bash scripts/prepare-ext.sh
cd ext && phpize && ./configure --enable-metal && make -j1
php -n -d extension=modules/metal.so --ri metal
```

`prepare-ext.sh`: `zephir generate` → sync `src/*` → `ext/src/` → copy `Makefile.frag` → patch `config.m4` + REGISTER fixup → strip phpize junk.[^prepare]

Prefer `make -j1` — see [Parallel make](/traps/parallel-make.md).

# Verify

```bash
php -d extension=./ext/modules/metal.so examples/proof_window.php
METAL_DEMO_MAX_FRAMES=90 php -d extension=./ext/modules/metal.so examples/proof_window.php
```

[^composer]: PIE package manifest
[^prepare]: prepare-ext.sh
[^install]: install-macos.sh
[^herd]: install-macos-herd.sh
[^readme]: README
[^config-m4]: Portable ext/config.m4
