#include "ca-metallayer.h"
#include "mtl-value.h"
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

zend_long mtl_cametallayer_init(void)
{
    @autoreleasepool {
        return mtl_handle_for([[CAMetalLayer alloc] init]);
    }
}

zend_long mtl_cametallayer_device(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        CAMetalLayer *l = MTL_ARG_AS(CAMetalLayer, handle);
        r = l != nil ? mtl_handle_for([l device]) : 0;
    }
    return r;
}

void mtl_cametallayer_set_device(zval *handle, zval *device)
{
    @autoreleasepool {
        CAMetalLayer *l = MTL_ARG_AS(CAMetalLayer, handle);
        if (l == nil) return;
        [l setDevice:MTL_ARG_PROTO(MTLDevice, device)];
    }
}

zend_long mtl_cametallayer_pixel_format(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        CAMetalLayer *l = MTL_ARG_AS(CAMetalLayer, handle);
        r = l != nil ? (zend_long) [l pixelFormat] : 0;
    }
    return r;
}

void mtl_cametallayer_set_pixel_format(zval *handle, zval *pixelFormat)
{
    @autoreleasepool {
        CAMetalLayer *l = MTL_ARG_AS(CAMetalLayer, handle);
        if (l == nil) return;
        [l setPixelFormat:(MTLPixelFormat) mtl_arg_long(pixelFormat)];
    }
}

void mtl_cametallayer_drawable_size(zval *return_value, zval *handle)
{
    @autoreleasepool {
        CAMetalLayer *l = MTL_ARG_AS(CAMetalLayer, handle);
        mtl_ret_cgsize(return_value, l != nil ? [l drawableSize] : CGSizeMake(0, 0));
    }
}

void mtl_cametallayer_set_drawable_size(zval *handle, zval *width, zval *height)
{
    @autoreleasepool {
        CAMetalLayer *l = MTL_ARG_AS(CAMetalLayer, handle);
        if (l == nil) return;
        [l setDrawableSize:CGSizeMake(mtl_arg_double(width), mtl_arg_double(height))];
    }
}

zend_long mtl_cametallayer_framebuffer_only(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        CAMetalLayer *l = MTL_ARG_AS(CAMetalLayer, handle);
        r = (l != nil && [l framebufferOnly]) ? 1 : 0;
    }
    return r;
}

void mtl_cametallayer_set_framebuffer_only(zval *handle, zval *framebufferOnly)
{
    @autoreleasepool {
        CAMetalLayer *l = MTL_ARG_AS(CAMetalLayer, handle);
        if (l == nil) return;
        [l setFramebufferOnly:mtl_arg_bool(framebufferOnly)];
    }
}

zend_long mtl_cametallayer_next_drawable(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        CAMetalLayer *l = MTL_ARG_AS(CAMetalLayer, handle);
        r = l != nil ? mtl_handle_for([l nextDrawable]) : 0;
    }
    return r;
}

zend_long mtl_cametaldrawable_texture(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<CAMetalDrawable> d = MTL_ARG_PROTO(CAMetalDrawable, handle);
        r = d != nil ? mtl_handle_for([d texture]) : 0;
    }
    return r;
}

zend_long mtl_cametaldrawable_layer(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<CAMetalDrawable> d = MTL_ARG_PROTO(CAMetalDrawable, handle);
        r = d != nil ? mtl_handle_for([d layer]) : 0;
    }
    return r;
}
