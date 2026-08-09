---
type: Convention
title: Committed ext/ notes
description: What to ship for Packagist/PIE (sibling conventions)
resource: /scripts/prepare-ext.sh
tags: [metal, packaging, ext]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: gitignore
    resource: /.gitignore
    title: .gitignore
  - id: prepare
    resource: /scripts/prepare-ext.sh
    title: prepare-ext.sh
  - id: patch
    resource: /scripts/patch-config-m4.py
    title: patch-config-m4.py
  - id: frag
    resource: /scripts/Makefile.frag
    title: Makefile.frag
  - id: config-m4
    resource: /ext/config.m4
    title: ext/config.m4
---

# PIE expectation

`composer.json` sets `"build-path": "ext"`.[^composer] Consumers build from the **committed generated tree**.

# Maintainer pipeline (`scripts/prepare-ext.sh`)[^prepare]

1. `zephir generate`
2. Copy `src/*.h` / `src/*.m` → `ext/src/`
3. Copy `scripts/Makefile.frag` → `ext/Makefile.frag`
4. `patch-config-m4.py` + `fixup-zephir-register.py`
5. Strip phpize artifacts (Makefiles, configure, modules, objects, …)

# Critical packaging facts

| Fact | Why |
|------|-----|
| ObjC via `Makefile.frag` | phpize mishandles `.m` rules — see [ObjC Makefile.frag](/traps/objc-makefile-frag.md)[^frag] |
| `METAL_SHARED_LIBADD=-framework …` | `PHP_ADD_FRAMEWORK` does not link into the shared module — see [Framework link](/traps/framework-shared-libadd.md)[^patch] |
| Darwin `AC_MSG_ERROR` | Fail configure off macOS[^config-m4] |
| No pkg-config third-party libs | System frameworks only |

# What not to commit

`.gitignore` excludes phpize junk and objects.[^gitignore] Never ship host-absolute paths.

[^composer]: PIE package manifest
[^prepare]: prepare-ext.sh
[^frag]: Makefile.frag
[^patch]: patch-config-m4.py
[^config-m4]: ext/config.m4
[^gitignore]: .gitignore
