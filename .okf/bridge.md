---
type: Component
title: Metal\Bridge\Bridge — the only glue
description: >-
  Everything PHP cannot do without native code, and nothing else: handle
  registry, the cross-extension pointer seam, and an NSError reader for
  the sanctioned NSError** pattern.
resource: src/mtl-bridge.h
tags: [bridge, glue, metal]
status: stable
generated:
  by: claude-sonnet-5
  at: 2026-09-12T00:00:00Z
---

# Metal\Bridge\Bridge

Everything in `src/mtl-bridge.{h,m}` exists because PHP cannot itself hold an
Objective-C strong reference or read an `NSError*`. Nothing here decides how
Metal is used, and there is deliberately **no pump**: Metal has no run loop,
so the window/event loop belongs to ext-appkit (or Surface, eventually), not
here.

## Surface — 7 calls

Handle registry:

```c
/*@zep Bridge\Bridge retain(int handle) -> bool */
zend_long mtl_bridge_retain(zval *handle);
/*@zep Bridge\Bridge release(int handle) -> void */
void mtl_bridge_release(zval *handle);
/*@zep Bridge\Bridge isValid(int handle) -> bool */
zend_long mtl_bridge_is_valid(zval *handle);
/*@zep Bridge\Bridge className(int handle) -> var */
void mtl_bridge_class_name(zval *return_value, zval *handle);
```

Cross-extension pointer seam (spec §5, amendment 4):

```c
/*@zep Bridge\Bridge pointerOf(int handle) -> int */
zend_long mtl_bridge_pointer_of(zval *handle);
/*@zep Bridge\Bridge adopt(string className, int pointerBits) -> int */
zend_long mtl_bridge_adopt(zval *className, zval *pointerBits);
```

NSError reader (spec §5, amendment 3):

```c
/*@zep Bridge\Bridge errorDescription(int handle) -> var */
void mtl_bridge_error_description(zval *return_value, zval *handle);
```

## Ownership rule

**The registry is address-keyed, with exactly one strong reference per
object — there is no retain count.** `mtl_registry` is an
`NSMutableDictionary<NSNumber *, id>` keyed by the object's pointer bits
(`mtl_handle_for`, `src/mtl-bridge.m`). Registering an address that is
already a key is a no-op — `init`, `adopt`, or any other producer that
calls `mtl_handle_for` on a pointer already in the table does **not** add a
second reference; the dictionary already holds the one strong reference
that keeps the object alive, and nothing counts how many logical callers
think they "own" it.

- **`release()` drops the registry's one reference, full stop — for every
  holder of that handle, not per-caller.** There is no partial release: two
  PHP-land call sites that both hold the same handle and both call
  `Bridge::release($h)` do not each decrement a count — the first call
  removes the dictionary entry (and, since ARC/`NSMutableDictionary` held
  the only strong ref, deallocates the object); the second call is simply a
  no-op on an already-unregistered handle (`mtl_handle_release` returns
  early on an unknown key).
- **`retain()` reports registry validity only — it does not retain.**
  `Bridge::retain($h)` (`mtl_bridge_retain`) returns `true` iff `$h` still
  resolves in the registry; it does not add a reference, and calling it N
  times does not require N releases. Treat it as `isValid()`'s sibling, not
  as ref-counting.
- **Handles are untyped, so every binding type-checks its own receiver.**
  Nothing in an `int` says which class or protocol it points at, and PHP
  can hand any live handle to any binding. Class-typed glue has always
  resolved through `MTL_ARG_AS` (`isKindOfClass:`); since the Wave A
  review, protocol-typed glue resolves through `MTL_ARG_PROTO`, which
  tests `conformsToProtocol:` (`src/mtl-value.h`). Without it, passing an
  `MTLTexture` handle to `MTLBuffer::contentsBytes` sent `contents` to a
  texture — an unrecognized-selector `NSException`, which **aborts the
  process**, not something PHP can catch. A non-conforming handle now
  reads as nil, and every binding already treats nil as "no-op / empty
  result". Protocol inheritance counts, so a render-encoder handle still
  satisfies `MTLCommandEncoder`. The guard is glue, not a send against the
  one-call-one-send budget.
- **Handles are pointer-valued, and a released handle's address can be
  reused (ABA).** Once `release()` removes an entry, that same integer can
  come back as a *different* object's handle the next time Objective-C
  allocates at that address and something calls `mtl_handle_for`/`adopt` on
  it — the registry has no generation counter to detect this. A stale
  handle held past its `release()` is not reliably "dead": it may resolve
  to nil (nothing re-registered that address yet) or, worse, silently
  resolve to an unrelated live object. Callers must therefore treat a
  handle as owned by whoever conjured it (the call site that produced it),
  drop every reference to it at (or before) the `release()` call, and never
  read from or pass around a handle after releasing it.
- **Release what you acquire in per-frame loops.** A loop that creates
  handles every iteration (a drawable, its texture, a pass descriptor, an
  attachment array/attachment, a command buffer, an encoder — one of each,
  every frame) and never releases them leaks the registry's one strong
  reference per handle per frame, unboundedly, even though nothing is
  double-retained. `examples/proof_view.php`'s render loop calls
  `Bridge::release` on all seven per-frame handles at the bottom of each
  iteration for exactly this reason — see the loop body for the pattern.

Each side of a pointer-seam handoff (see [binding-rules.md](/binding-rules.md),
amendment 4) has its **own**, entirely separate registry — ext-metal's
`mtl_registry` and ext-appkit's own registry never share a dictionary — so
`init`-then-`adopt` across the seam really is two distinct single
references, one per side, each released independently through that side's
own `Bridge::release`. The "no second reference on re-registration" rule
above applies *within* one extension's registry; it does not describe the
cross-extension case.

## No pump

Metal has no run loop and no event queue — `commandBuffer` → `commit` →
`waitUntilCompleted` is synchronous, and `CAMetalLayer::nextDrawable`
returns (or blocks briefly) on the calling thread. There is no
`Bridge::pump()` in this extension, unlike ext-appkit's Bridge — whoever
drives a window loop (ext-appkit today, Surface eventually) owns that
concern; ext-metal takes no position on it.

## Reading an NSError

The slice-zero NSError path (`MTLCommandBuffer::error`) returns a registry
handle (0 = none); `Bridge::errorDescription($handle)` reads its
`localizedDescription` back as a PHP string. See
[binding-rules.md](/binding-rules.md) amendment 3 for the full
`{handle, error}` array shape reserved for Wave A's
`newLibraryWithSourceOptionsError`.

See [binding-rules.md](/binding-rules.md) for the marshalling conventions and
[traps/layer-pointer-seam.md](/traps/layer-pointer-seam.md) for the
CAMetalLayer handoff this seam exists for.
