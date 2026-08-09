#import <Metal/Metal.h>
#import <Foundation/Foundation.h>
#import "metal-device.h"

static inline id mtl_bridge_id(uintptr_t handle)
{
    return handle ? (__bridge id)(void *)handle : nil;
}

static inline uintptr_t mtl_retain_handle(id object)
{
    if (!object) {
        return 0;
    }
    return (uintptr_t)(__bridge_retained void *)object;
}

uintptr_t mtl_device_create_system_default(void)
{
    @autoreleasepool {
        id<MTLDevice> device = MTLCreateSystemDefaultDevice();
        return mtl_retain_handle(device);
    }
}

void mtl_device_release(uintptr_t device)
{
    if (!device) {
        return;
    }
    CFRelease((void *)device);
}

uintptr_t mtl_device_new_command_queue(uintptr_t device)
{
    @autoreleasepool {
        id<MTLDevice> dev = mtl_bridge_id(device);
        if (!dev) {
            return 0;
        }
        id<MTLCommandQueue> queue = [dev newCommandQueue];
        return mtl_retain_handle(queue);
    }
}

void mtl_command_queue_release(uintptr_t queue)
{
    if (!queue) {
        return;
    }
    CFRelease((void *)queue);
}

int mtl_device_get_name(uintptr_t device, char *out, int out_len)
{
    if (!device || !out || out_len <= 0) {
        return 0;
    }

    @autoreleasepool {
        id<MTLDevice> dev = mtl_bridge_id(device);
        if (!dev) {
            return 0;
        }
        NSString *name = dev.name ?: @"unknown";
        BOOL ok = [name getCString:out maxLength:(NSUInteger)out_len encoding:NSUTF8StringEncoding];
        return ok ? 1 : 0;
    }
}
