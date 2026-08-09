---
type: Playbook
title: Regenerate committed ext/
description: Maintainer steps before tagging
resource: /scripts/prepare-ext.sh
tags: [metal, playbook, packaging]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: prepare
    resource: /scripts/prepare-ext.sh
    title: prepare-ext.sh
  - id: gitignore
    resource: /.gitignore
    title: .gitignore
  - id: readme
    resource: /README.md
    title: README
---

# When

Before tagging a Packagist/PIE release, or after changing `.zep` / `src/*.m` / `src/*.h`.

# Steps

1. On macOS with Zephir + matching PHP:

```bash
bash scripts/prepare-ext.sh
```

2. Smoke build (**use `-j1`**):

```bash
cd ext && phpize && ./configure --enable-metal && make -j1
php -n -d extension="$(pwd)/modules/metal.so" --ri metal
```

3. Run demo / smoke:

```bash
METAL_DEMO_MAX_FRAMES=90 php -n -d extension="$(pwd)/modules/metal.so" ../examples/proof_window.php
```

4. Commit regenerable artifacts that belong in git (`ext/` sources, `config.m4`, `Makefile.frag`, `ide/<version>/` stubs matching `config.json`) — not phpize junk.[^gitignore]
5. Update `.okf` + `log.md` if the public surface changed.

# Notes

- Set `ZEPHIR_BIN` if `zephir` is not on `PATH`.[^prepare]
- `fixup-zephir-register.py` fixes truncated `ZEPHIR_REGISTER_CLASS` names (Zephir 0.19).
- See traps: [ObjC Makefile.frag](/traps/objc-makefile-frag.md), [Framework link](/traps/framework-shared-libadd.md), [Parallel make](/traps/parallel-make.md).

[^prepare]: prepare-ext.sh
[^gitignore]: .gitignore
