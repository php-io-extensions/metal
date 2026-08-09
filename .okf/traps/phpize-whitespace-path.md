---
type: Trap
title: phpize rejects whitespace in build path
description: Homebrew phpize exits when the extension cwd contains spaces (e.g. Finder "metal copy")
resource: /install-macos.sh
tags: [metal, trap, phpize, macos]
status: draft
generated: { by: cursor-agent/grok-4.5, at: "2026-08-09T16:30:00Z" }
sources:
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
  - id: phpize
    resource: phpize (Homebrew)
    title: phpize whitespace check
---

# Symptom

```
Invalid build path '.../metal copy/ext'. Whitespace is not allowed in build path.
phpize failed.
```

# Cause

Homebrew `phpize` refuses source/build directories whose absolute path contains spaces or tabs.[^phpize]

Angel often installs from a Finder duplicate named `metal copy` so the ship tree's `ext/` stays Packagist-clean — that path hits the check.

# Fix

`install-macos.sh` detects whitespace in `SCRIPT_DIR`, rsyncs prepared `ext/` into a space-free temp dir (`$TMPDIR/metal-ext-build.*`), runs `phpize` / `configure` / `make` there, then installs the `.so`.[^install]

If `TMPDIR` itself has spaces, set `TMPDIR=/tmp` (or another space-free path) before running the installer.

Do **not** "fix" this by building inside the ship `metal/` tree when Angel asked to use the copy.

[^phpize]: phpize (Homebrew)
[^install]: install-macos.sh
