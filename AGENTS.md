# Agent guidance — php-io-extensions/metal

1. **Read [`.okf/index.md`](.okf/index.md) first** before changing the API, the Objective-C, or packaging. Open only the concepts the change touches.
2. **Bindings are 1:1.** One PHP class per Metal type, one method per selector, keywords joined in camelCase. No defaults, no composites, no convenience that Metal does not have. Values come from the macOS SDK headers.
3. **Handles.** `final`, private `__construct`, not cloneable, not serializable, ``static fromPointer(int $pointer): ?static`. Box by the binding's declared type (`metal_box` / `metal_box_owned`). The identity table is per thread. `fromPointer()` trusts the address; `0` is `null`.
4. **Enums are string-or-int backed PHP enums, cases FULLY UPPERCASE.** No class constants. Flag paramestaticters are `Enum|int`. `MTLResourceOptions` cannot repeat the integer 0, so that value is `STORAGE_MODE_SHARED`.
5. **Errors.** `NSError**` is a by-reference `?NSError &$error` in native position; nil is `null`. `NSError`, `NSSize` and `CGColorSpace` are ext-appkit's (`ZEND_MOD_REQUIRED("appkit")`). `METAL_BEGIN` / `METAL_END` turn an `NSException` into the PHP `NSException`. MINIT sets `METAL_ERROR_MODE=1` when unset, so a descriptor Metal would abort on is an exception instead. Throwing on an `NSError` belongs in jovian/venusian-metal (`MetalException`).
6. Refusals. The rule, verbatim, as in appkit item 3. Kept refusals, each with a probe: address 0 as bytes or as a destination, a byte string shorter than the length, a negative render-encoder binding index. Every other integer reaches Metal as (NSUInteger). Any other address is trusted. See .okf/architecture/errors.md.
6a. The guard. Copy item 6 of harfbuzz/AGENTS.md. Replace the helper names with metal_resolve_bytes, metal_shader_bytes, metal_region_span.
6b. A kept refusal reads if (!METAL_PROBE_OFF("<id>") && (<check>)), carries /* binding:<id> */ on its throw line, has its sites entry, and a probe test in tests/Probes (metalProbe() in tests/Pest.php). Probe builds use METAL_CONFIGURE=--enable-metal-probes ./install-macos.sh. Never ship a probe build.
7. **The stub is the declaration.** Edit `stubs/*.stub.php`, regenerate with `php84 /opt/homebrew/opt/php@8.4/lib/php/build/gen_stub.php stubs`, and commit both. Never hand-edit `*_arginfo.h`.
8. **Build.** `./install-macos.sh` into Homebrew `php@8.4` and `php@8.4-zts`. Pest at `-d memory_limit=128M` on both. Gate a commit on the suite's exit code.
9. **Durable facts go in `.okf`.** Update the matching concept and append `.okf/log.md`.
10. **Version** is `PHP_METAL_VERSION` in `php_metal.h`: 0.11.1. macOS only.

