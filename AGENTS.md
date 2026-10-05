# Agent guidance — php-io-extensions/metal

1. **Read [`.okf/index.md`](.okf/index.md) first** before changing the API, the Objective-C, or packaging. Open only the concepts the change touches.
2. **Bindings are 1:1.** One PHP class per Metal type, one method per selector, keywords joined in camelCase. No defaults, no composites, no convenience that Metal does not have. Values come from the macOS SDK headers.
3. **Handles.** `final`, private `__construct`, not cloneable, not serializable, `pointer(): int`, `static fromPointer(int $pointer): static`. Box by the binding's declared type (`metal_box` / `metal_box_owned`). The identity table is per thread. `fromPointer(0)` and a wrong class throw `MetalException`.
4. **Enums are string-or-int backed PHP enums, cases FULLY UPPERCASE.** No class constants. Flag parameters are `Enum|int`. `MTLResourceOptions` cannot repeat the integer 0, so that value is `STORAGE_MODE_SHARED`.
5. **Errors.** `NSError**` is dropped from the signature and a nil result throws `MetalException`. `METAL_BEGIN` / `METAL_END` turn `NSException` into `MetalException`. MINIT sets `METAL_ERROR_MODE=1` when unset, so a descriptor Metal would abort on is an exception instead.
6. **Addresses.** `string|int` bytes: a short string and address 0 throw `ValueError`. Any other address is trusted. Say so on the stub.
7. **The stub is the declaration.** Edit `stubs/*.stub.php`, regenerate with `php84 /opt/homebrew/opt/php@8.4/lib/php/build/gen_stub.php stubs`, and commit both. Never hand-edit `*_arginfo.h`.
8. **Build.** `./install-macos.sh` into Homebrew `php@8.4` and `php@8.4-zts`. Pest at `-d memory_limit=128M` on both. Gate a commit on the suite's exit code.
9. **Durable facts go in `.okf`.** Update the matching concept and append `.okf/log.md`.
10. **Version** is `PHP_METAL_VERSION` in `php_metal.h`: 0.10.0. macOS only.
