---
type: Trap
title: Protocol audit, not interface audit
description: MTL types are protocols; the audit counts @protocol members and forward decls are not blocks.
tags: [trap, audit, metal]
status: stable
generated:
  by: claude-sonnet-5
  at: 2026-09-12T00:00:00Z
---

# Protocol audit, not interface audit

Metal's API objects (`MTLDevice`, `MTLCommandQueue`, `MTLBuffer`, …) are
`@protocol`s, not `@interface`s — `audit-headers.php` runs in protocol mode
for `MTL\*`/`QuartzCore\*` types and counts `@protocol Name <...> ... @end`
members exactly as it counts `@interface` members for appkit classes. A
type with no `init*`, no class-method factory, and no `@zep-construct`
does **not** automatically fail the way an appkit class would: it passes
construction if a bound producer exists — a C function
(`MTLCreateSystemDefaultDevice`) or a bound send on another type returning
this type's handle (`MTLDevice::newCommandQueue`) — declared with
`/*@audit factory <FQCN> Producer::method */`. A protocol with none of
these fails.

Inherited protocol members (e.g. `MTLResource`'s members as adopted by
`MTLBuffer`/`MTLTexture`, `MTLCommandEncoder`'s members as adopted by
`MTLRenderCommandEncoder`) audit on their **declaring header**, not on
every adopting type — binding `MTLCommandEncoder::endEncoding` once on
`MTLCommandEncoder` covers it for every type that adopts that protocol,
the same way an appkit superclass method covers its subclasses.

**The trap that actually bit this session:** a bare forward declaration
(`@protocol MTLDevice;`, or a comma list `@protocol A, B;`) looks like a
block opener to a naive scan. An earlier revision of `classBlocks()`
treated it as one, so `MTLCommandQueue.h` — which forward-declares
`MTLDevice`/`MTLCommandBuffer`/`MTLResidencySet` immediately before the
real `@protocol MTLCommandQueue <NSObject> ... @end` — audited as
`header=0` and failed outright. Fixed with a regression fixture; the real
SDK counts are `MTLCommandQueue=11`, `MTLDevice=120`. Any future header
with a forward-declared protocol name before its real definition is this
trap waiting to recur — check `classBlocks()`'s forward-decl skip before
trusting a suspiciously low `header=N`.
