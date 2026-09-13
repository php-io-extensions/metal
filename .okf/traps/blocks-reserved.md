---
type: Trap
title: Blocks stay reserved
description: Block/async Metal APIs are never bindable; @reserved itemization becomes mandatory only once a type is fully bound.
tags: [trap, blocks, metal]
status: stable
generated:
  by: claude-sonnet-5
  at: 2026-09-12T00:00:00Z
---

# Blocks stay reserved

PHP has no Objective-C block type and this extension has no block-marshalling
Bridge glue, so completion-handler/async Metal APIs (`addCompletedHandler:`,
`newLibraryWithSource:options:completionHandler:`, and friends) are never
bindable and never get glue — sync paths (`commit`+`waitUntilCompleted`,
`error:` out-params) are the bound surface instead.

**Slice zero today:** the gap is sanctioned by `@audit partial`, not by
per-member `@reserved` lines — `grep -rn "@reserved" src/*.h` is empty and
`audit-headers.php` reports `reserved=0` for all 12 audited types; a
partial type is simply allowed to fall short of its header count with no
itemization.

**Once a type graduates to fully-bound** (Wave A+), that exemption ends:
every block/async member it still can't bind MUST appear as a commented
`@reserved` signature so `bound + reserved` equals the header count — the
same "nothing silently omitted" rule appkit's binding-rules.md states for
its own unbindable members (spec §4).
