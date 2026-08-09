---
type: CoreType
title: Metal\\MTL\\Device
description: MTLDevice / command queue handles
resource: /metal/mtl/device.zep
tags: [metal, api, device]
status: draft
generated: { by: okf-documentation-generator/cursor, at: 2026-08-08T23:54:53Z }
sources:
  - id: device-zep
    resource: /metal/mtl/device.zep
    title: device.zep
  - id: device-h
    resource: /src/metal-device.h
    title: metal-device.h
---

# Schema

| Method | Returns | Notes |
|--------|---------|--------|
| `createSystemDefault()` | `int` | Opaque MTLDevice; `0` if unavailable |
| `release(int $device)` | `void` | Balances create |
| `newCommandQueue(int $device)` | `int` | Opaque queue; `0` on failure |
| `releaseCommandQueue(int $queue)` | `void` | |
| `getName(int $device)` | `string` | UTF-8 name, or `""` |

# Notes

- `Window::attachDevice` creates its own command queue internally for `clear`; standalone queues are for advanced callers.
- Always `release` devices you create; see [Handle ownership](/conventions/handle-ownership.md).

# Examples

```php
use Metal\MTL\Device;

$dev = Device::createSystemDefault();
$name = Device::getName($dev);
Device::release($dev);
```

[^device-zep]: device.zep
