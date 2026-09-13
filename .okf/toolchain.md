---
type: Runbook
title: Generate, verify, build, install
description: >-
  The pipeline that turns @zep annotations in src/*.h into a loadable
  extension, and the guards that keep it faithful.
tags: [toolchain, zephir, build]
status: stable
generated:
  by: claude-sonnet-5
  at: 2026-09-12T00:00:00Z
---

# Toolchain

The annotations in `src/*.h` are the single source of truth. Everything under
`metal/` and `optimizers/` is generated and prunes itself; never hand-edit.
Identical pipeline to appkit's, metal names.

## Pipeline

```bash
php scripts/gen-zep.php        # @zep/@zep-construct/@reserved/@audit lines -> .zep files + optimizers
php scripts/check-parity.php   # must print PARITY_OK, then (real root only) runs audit-headers.php itself -> AUDIT_OK
php scripts/audit-headers.php  # the same header audit, listed here for clarity / standalone use
bash scripts/prepare-ext.sh    # zephir generate, stage src/, Makefile.frag, patch config.m4
bash install-macos.sh          # phpize/configure/make, codesign, ini, php --ri metal
php scripts/verify-reflection.php  # loaded .so exposes exactly the annotated methods
```

`check-parity.php` invoking `audit-headers.php` as its own last step (spec §11
intent: one command proves parity **and** header faithfulness) only fires
when it is checking the real package root — a custom `argv[1]` root, as used
by `scripts/tests/parity-guard.php`'s temp fixture trees, has no real SDK
counterpart to audit against and stays parity-only.

`install-macos-herd.sh` is the same install with Herd's PHP first on PATH.

## Guards

- `check-parity.php` — zep bare calls ↔ optimizers ↔ C prototypes (names and
  arity), `config.json` extra-sources coverage, the composite guard (no binding
  sends more than its declared selector; `alloc`+`init` excepted, plus a
  narrow `GUARD_SELECTORS` allowance — `[t width]`/`[t height]`/`[b length]`
  sent only to bounds-check a region or window before the declared send
  (`MTLTexture::getBytesBytesPerRowFromRegionMipmapLevel` and Wave A's
  `replaceRegionMipmapLevelWithBytesBytesPerRow`; `MTLBuffer::contentsBytes`
  and `setContentsBytes`, which memcpy through the raw `contents` pointer
  and so must validate the window first) are guards-in-glue, not
  composition, and do not count toward the send budget). Once `PARITY_OK`
  prints, and only when auditing the real package root (not a self-test's
  temp fixture tree), `check-parity.php` itself runs the header audit via
  `audit-headers.php` in **protocol mode** as its last step and fails if
  that fails — `PARITY_OK` is followed by the audit's own output, ending in
  `AUDIT_OK` (bound + reserved must equal the SDK header's `@interface`
  *and* `@protocol` block member count per type; `@zep-construct` is
  printed as `construct=N` and is not part of that sum). A non-exempt type
  with no construction path (`init*`, no-handle factory returning int,
  `@zep-construct`, or an `@audit factory <FQCN> Producer::method` marker)
  fails. `ACCESS_ONLY` is the exemption list for types obtained from the
  system rather than alloc+init or factory — currently empty for metal
  (every slice-zero protocol has a real factory marker or producer).
  Companion types that live in another type's header (e.g.
  `CAMetalDrawable` alongside `CAMetalLayer` in `CAMetalLayer.h`) resolve by
  scanning for `@interface`/`@protocol Class` when `{Class}.h` is absent.
  MTL-prefixed types missing from the mapped framework resolve via
  `FRAMEWORK_FALLBACK` (`MTL` → also searches `Foundation`).
- The two negative-control suites that actually ship, both under
  `scripts/tests/`: `audit-protocol.php` (`AUDIT_PROTOCOL_OK`) proves
  `audit-headers.php`'s protocol counting, forward-declaration handling, and
  `@audit factory` marker validation can fail against bad fixtures;
  `parity-guard.php` (`PARITY_GUARD_OK`) proves `check-parity.php`'s parity
  and composite guards can fail against composite extra-sends, a missing or
  extra optimizer, an arity mismatch, an extra-sources hole or phantom
  entry, and an `@zep`/prototype mismatch — plus a positive control that the
  real package itself stays green (parity and, since that run uses the real
  root, the audit it now triggers).
- `verify-reflection.php` — the only guard that inspects the **installed**
  binary: for every class it asserts the reflected method count equals that
  class's `@zep` + `@zep-construct` count. The other guards compare source
  artefacts to each other or to the SDK headers and pass even when the
  extension cannot build, so this one closes that gap.
- `prepare-ext.sh` strips phpize leftovers (`Makefile`, `configure`,
  `modules/`, `*.lo`, `*.dSYM`, …) after generating C so `ext/` stays the
  ship-ready PIE/`phpize` input. Do not commit those artifacts.

## Gotchas

- PHP's `PHP_ADD_SOURCES_X` has no `*.m` case — `prepare-ext.sh` writes
  `ext/Makefile.frag` with one libtool rule per `.m` file.
- `PHP_EVAL_LIBLINE` drops `-framework` pairs — `config.m4` is patched to
  assign `METAL_SHARED_LIBADD=` directly (`scripts/patch-config-m4.php`).
- A copied Mach-O is SIGKILLed by macOS — the install re-signs with
  `xattr -cr` + `codesign --force --sign -`.
- `gen-zep.php` treats any source line containing the substring `@zep` as an
  annotation. File-header comments must not mention that token (write
  "bound or reserved" instead); a stray occurrence is a hard fail.
- Zephir lexes all-caps identifiers as constants, so a selector or parameter
  named `URL` is a syntax error; `gen-zep.php` emits `Url` (see
  [binding-rules.md](/binding-rules.md)).
- `zephir generate` reports parse failures as a bare
  `Syntax error in <file> on line N`, but on PHP 8.4 that message is swallowed
  by a deprecation notice raised from Zephir's own `ParseException`. Re-run with
  `-d error_reporting="E_ALL & ~E_DEPRECATED"` to see the file and line.
- `Zephir version has changed, use "zephir fullclean"` aborts generation until
  `zephir fullclean` is run; the install scripts do not do it automatically.
- Parity and header audit both pass on sources that Zephir cannot compile.
  Run `zephir generate` (or a full build) before declaring a wave finished.
- `install-macos.sh` needs `HERD_PHP_84_INI_SCAN_DIR` exported when run from
  a non-interactive shell (verified this session) — otherwise the install's
  own `php --ri metal` check runs against the wrong `php.ini` scan dir and
  can report a stale extension.
- **Metal-only:** audit runs in protocol mode for MTL types; an
  `@audit factory` marker must name a bound producer (a class/method already
  emitting a `@zep` binding) or the audit hard-fails — a typo'd producer name
  is caught the same way an unbound selector reference is.

See [binding-rules.md](/binding-rules.md) for what the generator emits and
[traps/protocol-audit.md](/traps/protocol-audit.md) for the forward-declaration
parsing trap this pipeline hit and fixed.
