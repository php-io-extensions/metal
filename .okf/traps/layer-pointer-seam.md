---
type: Trap
title: CAMetalLayer pointer seam
description: CAMetalLayer lives here, CALayer lives in ext-appkit; the layer crosses as pointer bits.
tags: [trap, pointer-seam, metal]
status: stable
generated:
  by: claude-sonnet-5
  at: 2026-09-12T00:00:00Z
---

# CAMetalLayer pointer seam

`CAMetalLayer` lives in **ext-metal**; base `CALayer` (and `NSView`) lives in
**ext-appkit** — this split is stated in both bundles (this file here;
ext-appkit's own bundle carries the matching note — see
[../log.md](/log.md) for the cross-repo reminder, since that repo is not
this plan's to edit).

The layer crosses the extension boundary as **pointer bits**, never a
registry handle from either side: metal calls `Bridge::pointerOf($layer)`,
hands the int to PHP-land, and appkit calls its own
`Bridge::adopt('CAMetalLayer', $pointerBits)` before `NSView::setWantsLayer`/
`setLayer`. Each `adopt` is a **retain** on the adopting side, on top of
whatever retain the originating side already holds from its own
`init`/`alloc`.

**The trap:** do not also retain on the metal side when adopting on the
appkit side "just in case", and do not forget the release on whichever side
releases the pointer when it is done with it. A stray extra retain on the
metal side never gets a matching release (appkit's `release` only balances
appkit's `adopt`), and a forgotten release on either side leaks the
underlying `CAMetalLayer`/`CALayer*`. This is the same retain-must-equal-
release discipline as any other Objective-C pointer, but the pointer-seam
handoff makes it easy to double up because two independent registries are
now holding the same address.

`examples/proof_view.php` is written against this seam and exits 2 (SKIP)
until ext-appkit ships the matching `Bridge::adopt`/`Bridge::pointerOf`
glue (a small 0.8.x ext-appkit point release, not part of this plan).
`examples/proof_headless.php` proves the metal-only half (offscreen
texture, no layer, no appkit) independently.

**Plain warning: `adopt` does not check the pointer.** `Bridge::adopt`
casts whatever integer it is given back to an Objective-C object pointer
(`(__bridge id) p`) and, for a known class name, verifies `isKindOfClass:`
— but for an unrecognized class name (or a garbage/stale integer that
happens to `NSClassFromString` to something, or simply does not point at a
live Objective-C object at all) there is no way to verify the pointer is
real before it gets sent a message. Adopting a garbage pointer — a value
that was never `Bridge::pointerOf()`'d from a live object on the other
side, or a stale one whose underlying object has since been deallocated —
is **undefined behavior: a crash, or worse, a silent type confusion**, not
a checked failure PHP can catch. The seam trusts PHP-land: only ever pass
`adopt` a pointer that came from this exact call's own `pointerOf()` on a
handle you know is still valid (see `.okf/bridge.md`'s ABA note — a handle
whose registry entry was released may already be stale on the producing
side too).
