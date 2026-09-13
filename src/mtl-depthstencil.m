#include "mtl-depthstencil.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtldepthstencildescriptor_init(void)
{
    @autoreleasepool {
        return mtl_handle_for([[MTLDepthStencilDescriptor alloc] init]);
    }
}

zend_long mtl_mtldepthstencildescriptor_depth_compare_function(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLDepthStencilDescriptor *d = MTL_ARG_AS(MTLDepthStencilDescriptor, handle);
        r = d != nil ? (zend_long) [d depthCompareFunction] : 0;
    }
    return r;
}

void mtl_mtldepthstencildescriptor_set_depth_compare_function(zval *handle, zval *depthCompareFunction)
{
    @autoreleasepool {
        MTLDepthStencilDescriptor *d = MTL_ARG_AS(MTLDepthStencilDescriptor, handle);
        if (d == nil) return;
        [d setDepthCompareFunction:(MTLCompareFunction) mtl_arg_long(depthCompareFunction)];
    }
}

zend_long mtl_mtldepthstencildescriptor_depth_write_enabled(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLDepthStencilDescriptor *d = MTL_ARG_AS(MTLDepthStencilDescriptor, handle);
        r = (d != nil && [d isDepthWriteEnabled]) ? 1 : 0;
    }
    return r;
}

void mtl_mtldepthstencildescriptor_set_depth_write_enabled(zval *handle, zval *depthWriteEnabled)
{
    @autoreleasepool {
        MTLDepthStencilDescriptor *d = MTL_ARG_AS(MTLDepthStencilDescriptor, handle);
        if (d == nil) return;
        [d setDepthWriteEnabled:mtl_arg_bool(depthWriteEnabled)];
    }
}

void mtl_mtldepthstencildescriptor_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        MTLDepthStencilDescriptor *d = MTL_ARG_AS(MTLDepthStencilDescriptor, handle);
        NSString *s = d != nil ? [d label] : nil;
        if (s == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, s);
    }
}

void mtl_mtldepthstencildescriptor_set_label(zval *handle, zval *label)
{
    @autoreleasepool {
        MTLDepthStencilDescriptor *d = MTL_ARG_AS(MTLDepthStencilDescriptor, handle);
        if (d == nil) return;
        [d setLabel:(Z_TYPE_P(label) == IS_NULL ? nil : mtl_arg_string(label))];
    }
}

void mtl_mtldepthstencilstate_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLDepthStencilState> s = MTL_ARG_PROTO(MTLDepthStencilState, handle);
        NSString *l = s != nil ? [s label] : nil;
        if (l == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, l);
    }
}
