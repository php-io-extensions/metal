---
type: Trap
title: NSBeep on unhandled keys
description: MTLPhpView must accept first responder and swallow keyDown or AppKit beeps on arrows.
tags: [trap, metal, input, appkit]
status: draft
generated: { by: cursor-agent/grok-4.5, at: "2026-08-09T21:45:00Z" }
---

# Trap

Game-style input polls `mtl_input_key_down` from PHP. If `MTLPhpView` does not become first responder and implement `keyDown:` / `keyUp:`, AppKit emits **NSBeep** on arrow / space while the window is focused.

**Do:** `acceptsFirstResponder` → YES, empty `keyDown:` / `keyUp:`, `[window makeFirstResponder:view]` after show.

**Build:** edit `src/metal-window.m`, `prepare-ext`, build from a **/tmp copy** of `ext/` — never phpize inside the ship-ready `ext/` tree.
