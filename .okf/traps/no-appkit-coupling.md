---
type: Trap
title: No AppKit coupling
description: ext-metal never links AppKit and never accepts appkit registry handles.
tags: [trap, layering, metal]
status: stable
generated:
  by: claude-sonnet-5
  at: 2026-09-12T00:00:00Z
---

# No AppKit coupling

ext-metal never links AppKit, never `#import`s an AppKit header, and never
accepts an ext-appkit registry handle as an argument or return value — only
raw pointer bits cross the seam (`Bridge::pointerOf`/`Bridge::adopt`, spec
§5 amendment 4). This is a hard architectural line, not a style preference:
the 0.7.x-era Metal extension died of exactly this coupling (composite
calls like `attachDevice`/`presentTexture` that reached into AppKit
directly), and this spec's greenfield rebuild does not inherit that
extension's code for that reason (§0/§3 of the spec).

ext-appkit owns `NSView`/`CALayer`; ext-metal owns `CAMetalLayer`. Whichever
side needs the other's object gets a pointer, wraps it with its own
`adopt`, and retains it in its own registry — never a shared handle space.
Link line stays `-framework Foundation -framework Metal -framework
QuartzCore`; if `AppKit` (or `Cocoa`) ever appears in `config.json`'s
`extra-libs` or a `#import` in `src/*.{h,m}`, that is this trap firing.
