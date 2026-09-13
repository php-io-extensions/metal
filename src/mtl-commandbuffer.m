#include "mtl-commandbuffer.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtlcommandbuffer_render_command_encoder_with_descriptor(zval *handle, zval *descriptor)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLCommandBuffer> cb = MTL_ARG_PROTO(MTLCommandBuffer, handle);
        MTLRenderPassDescriptor *rp = MTL_ARG_AS(MTLRenderPassDescriptor, descriptor);
        if (cb == nil || rp == nil) return 0;
        r = mtl_handle_for([cb renderCommandEncoderWithDescriptor:rp]);
    }
    return r;
}

zend_long mtl_mtlcommandbuffer_compute_command_encoder(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLCommandBuffer> cb = MTL_ARG_PROTO(MTLCommandBuffer, handle);
        r = cb != nil ? mtl_handle_for([cb computeCommandEncoder]) : 0;
    }
    return r;
}

zend_long mtl_mtlcommandbuffer_blit_command_encoder(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLCommandBuffer> cb = MTL_ARG_PROTO(MTLCommandBuffer, handle);
        r = cb != nil ? mtl_handle_for([cb blitCommandEncoder]) : 0;
    }
    return r;
}

void mtl_mtlcommandbuffer_present_drawable(zval *handle, zval *drawable)
{
    @autoreleasepool {
        id<MTLCommandBuffer> cb = MTL_ARG_PROTO(MTLCommandBuffer, handle);
        id<MTLDrawable> d = MTL_ARG_PROTO(MTLDrawable, drawable);
        if (cb == nil || d == nil) return;
        [cb presentDrawable:d];
    }
}

void mtl_mtlcommandbuffer_commit(zval *handle)
{
    @autoreleasepool {
        id<MTLCommandBuffer> cb = MTL_ARG_PROTO(MTLCommandBuffer, handle);
        if (cb == nil) return;
        [cb commit];
    }
}

void mtl_mtlcommandbuffer_wait_until_completed(zval *handle)
{
    @autoreleasepool {
        id<MTLCommandBuffer> cb = MTL_ARG_PROTO(MTLCommandBuffer, handle);
        if (cb == nil) return;
        [cb waitUntilCompleted];
    }
}

zend_long mtl_mtlcommandbuffer_status(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLCommandBuffer> cb = MTL_ARG_PROTO(MTLCommandBuffer, handle);
        r = cb != nil ? (zend_long) [cb status] : 0;
    }
    return r;
}

zend_long mtl_mtlcommandbuffer_error(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLCommandBuffer> cb = MTL_ARG_PROTO(MTLCommandBuffer, handle);
        NSError *e = cb != nil ? [cb error] : nil;
        r = e != nil ? mtl_handle_for(e) : 0;
    }
    return r;
}
