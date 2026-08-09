---
type: Trap
title: Prefer make -j1
description: Parallel make is discouraged for this ObjC fragment build
resource: /README.md
tags: [metal, trap, build]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: readme
    resource: /README.md
    title: README
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
---

# Symptom

Flaky or confusing parallel build failures around ObjC `.lo` targets / fragment rules.

# Guidance

Use `make -j1` (installers and README recommend this).[^readme] Parallel make can work for pure `.c` objects; the ObjC `Makefile.frag` path is intentionally conservative.

```bash
cd ext && phpize && ./configure --enable-metal && make -j1
```

[^readme]: README
[^install]: install-macos.sh
