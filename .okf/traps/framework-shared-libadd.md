---
type: Trap
title: Framework link via METAL_SHARED_LIBADD
description: PHP_ADD_FRAMEWORK does not link frameworks into the shared module
resource: /scripts/patch-config-m4.py
tags: [metal, trap, build, link]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: patch
    resource: /scripts/patch-config-m4.py
    title: patch-config-m4.py
  - id: config-m4
    resource: /ext/config.m4
    title: ext/config.m4
---

# Symptom

Undefined symbols for AppKit / Metal / QuartzCore / Foundation when loading `metal.so`, even though configure “found” frameworks.

# Cause

`PHP_ADD_FRAMEWORK` is aimed at the PHP binary link line, **not** the extension shared module.[^patch]

# Fix

Patched `config.m4` sets:[^config-m4]

```m4
METAL_SHARED_LIBADD="$METAL_SHARED_LIBADD -framework Foundation -framework AppKit -framework Metal -framework QuartzCore"
PHP_SUBST(METAL_SHARED_LIBADD)
```

Keep this pattern in `scripts/patch-config-m4.py` — do not “simplify” back to `PHP_ADD_FRAMEWORK` alone.

[^patch]: patch-config-m4.py
[^config-m4]: ext/config.m4
