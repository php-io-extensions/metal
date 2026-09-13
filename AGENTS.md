# Agent guidelines — php-io-extensions/metal

## Knowledge Bundle (OKF)

This package ships an Open Knowledge Format bundle at [`.okf/`](.okf/). Before changing code or advising on this package: read [`.okf/index.md`](.okf/index.md) first, open only the concepts the task needs, prefer `status: stable` over `draft`. When you learn something durable, update the affected concept(s) and append `.okf/log.md`; new or changed concepts stay `status: draft` until a human verifies them.

## Binding rules (the spec: [`.okf/binding-rules.md`](.okf/binding-rules.md))

ext-appkit's binding rules apply wholesale, plus four Metal amendments:

1. One ext call = one Objective-C message send. The only sanctioned composite is `alloc`+`init...` inside init bindings (construction is glue, not composition).
2. One static method per selector/protocol member, no opinions: `MTLDevice` → `Metal\MTL\MTLDevice\MTLDevice`, generated file `metal/mtl/mtldevice/mtldevice.zep`.
3. Never hand-write `.zep` files or optimizers — they are generated from the `/*@zep ... */`, `/*@zep-construct ... */`, and `/*@audit ... */` lines in `src/*.h` by `php scripts/gen-zep.php`.
4. Every header member is either bound (`@zep`) or kept as a commented `@reserved` signature (blocks/async completion handlers, deprecated). Nothing is silently omitted.
5. **Metal amendment — protocol audit.** Metal's API objects are `@protocol`s, obtained from factories, never alloc'd. A type is constructible when a bound C-function factory or a bound producer send (`/*@audit factory <FQCN> Producer::method */`) yields its handle — `audit-headers.php` verifies this instead of demanding `init*`/`@zep-construct`.
6. **Metal amendment — C functions.** Top-level Metal C functions (`MTLCreateSystemDefaultDevice`, …) bind as static factory methods on their natural owner, annotated `@zep` like any other binding; one C call = one binding.
7. **Metal amendment — `NSError**` pattern.** A selector with a trailing `error:` out-param binds under its flattened name and returns `{handle, error}` (exactly one non-zero). Slice zero's simpler form: `error(handle) -> int` + `Bridge::errorDescription(handle)`.
8. **Metal amendment — pointer seam.** Every registry-handled type exposes `Bridge::pointerOf(handle): int` and `Bridge::adopt(class, pointerBits): int`. This is the only currency between ext-metal and sibling extensions (ext-appkit owns `CALayer`/`NSView`; ext-metal owns `CAMetalLayer`) — never a foreign registry handle. See [`.okf/traps/no-appkit-coupling.md`](.okf/traps/no-appkit-coupling.md) and [`.okf/traps/layer-pointer-seam.md`](.okf/traps/layer-pointer-seam.md).
9. Types: BOOL/NSInteger/NSUInteger/CGFloat/NSString/enum → bool/int/int/double/string/int; any object or protocol handle → int handle (0 = nil); structs → doubles in, assoc arrays out.
10. Inherited protocol members bind once on the declaring header (e.g. `MTLCommandEncoder::endEncoding` covers every encoder that adopts it) — handles are untyped.
11. All glue lives in `Metal\Bridge\Bridge` (`src/mtl-bridge.{h,m}`); no other bridge class may exist. There is deliberately **no pump** — Metal has no run loop.
12. No constants in the ext — enum values become PHP enums in `jovian/metal`.
13. Pipeline: `php scripts/gen-zep.php` → `php scripts/check-parity.php` (must print `PARITY_OK`, then — against the real root — runs `audit-headers.php` itself and must print `AUDIT_OK`) → `bash scripts/prepare-ext.sh` → `bash install-macos.sh` (export `HERD_PHP_84_INI_SCAN_DIR` in non-interactive shells) → `php scripts/verify-reflection.php`. Negative controls `php scripts/tests/audit-protocol.php` (`AUDIT_PROTOCOL_OK`) and `php scripts/tests/parity-guard.php` (`PARITY_GUARD_OK`) prove those two guards can actually fail against bad fixtures — run both before calling a wave done.
14. Zephir reserved words in selectors/parameter names get a trailing underscore; all-caps selectors/parameter names are emitted mixed-case (Zephir lexes all-caps identifiers as constants).
