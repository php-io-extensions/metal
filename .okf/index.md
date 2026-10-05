---
okf_version: "0.2"
---

# ext-metal

1:1 PHP bindings of Metal and CAMetalLayer. Version 0.10.0. macOS only.

# API

* [Bindings](api/bindings.md) — Classes by group: device, values, resources, pipelines, commands, layer.

# Architecture

* [Object model](architecture/object-model.md) — Boxing by the declared type, one identity table per thread, retain rules, `fromPointer()`.
* [Errors](architecture/errors.md) — `MetalException` from `NSError**` and `NSException`.

# Runbooks

* [Build, install, test](runbooks/build.md) — `install-macos.sh` into php84 and zhp, Pest, clean tree.
* [Adding a binding](runbooks/adding-a-binding.md) — Stub, gen_stub, one `.m` per stub, `config.m4`, surface test.
