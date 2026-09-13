#include "mtl-sampler.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtlsamplerdescriptor_init(void)
{
    @autoreleasepool {
        return mtl_handle_for([[MTLSamplerDescriptor alloc] init]);
    }
}

zend_long mtl_mtlsamplerdescriptor_min_filter(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLSamplerDescriptor *d = MTL_ARG_AS(MTLSamplerDescriptor, handle);
        r = d != nil ? (zend_long) [d minFilter] : 0;
    }
    return r;
}

void mtl_mtlsamplerdescriptor_set_min_filter(zval *handle, zval *minFilter)
{
    @autoreleasepool {
        MTLSamplerDescriptor *d = MTL_ARG_AS(MTLSamplerDescriptor, handle);
        if (d == nil) return;
        [d setMinFilter:(MTLSamplerMinMagFilter) mtl_arg_long(minFilter)];
    }
}

zend_long mtl_mtlsamplerdescriptor_mag_filter(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLSamplerDescriptor *d = MTL_ARG_AS(MTLSamplerDescriptor, handle);
        r = d != nil ? (zend_long) [d magFilter] : 0;
    }
    return r;
}

void mtl_mtlsamplerdescriptor_set_mag_filter(zval *handle, zval *magFilter)
{
    @autoreleasepool {
        MTLSamplerDescriptor *d = MTL_ARG_AS(MTLSamplerDescriptor, handle);
        if (d == nil) return;
        [d setMagFilter:(MTLSamplerMinMagFilter) mtl_arg_long(magFilter)];
    }
}

zend_long mtl_mtlsamplerdescriptor_s_address_mode(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLSamplerDescriptor *d = MTL_ARG_AS(MTLSamplerDescriptor, handle);
        r = d != nil ? (zend_long) [d sAddressMode] : 0;
    }
    return r;
}

void mtl_mtlsamplerdescriptor_set_s_address_mode(zval *handle, zval *sAddressMode)
{
    @autoreleasepool {
        MTLSamplerDescriptor *d = MTL_ARG_AS(MTLSamplerDescriptor, handle);
        if (d == nil) return;
        [d setSAddressMode:(MTLSamplerAddressMode) mtl_arg_long(sAddressMode)];
    }
}

zend_long mtl_mtlsamplerdescriptor_t_address_mode(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLSamplerDescriptor *d = MTL_ARG_AS(MTLSamplerDescriptor, handle);
        r = d != nil ? (zend_long) [d tAddressMode] : 0;
    }
    return r;
}

void mtl_mtlsamplerdescriptor_set_t_address_mode(zval *handle, zval *tAddressMode)
{
    @autoreleasepool {
        MTLSamplerDescriptor *d = MTL_ARG_AS(MTLSamplerDescriptor, handle);
        if (d == nil) return;
        [d setTAddressMode:(MTLSamplerAddressMode) mtl_arg_long(tAddressMode)];
    }
}

void mtl_mtlsamplerdescriptor_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        MTLSamplerDescriptor *d = MTL_ARG_AS(MTLSamplerDescriptor, handle);
        NSString *s = d != nil ? [d label] : nil;
        if (s == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, s);
    }
}

void mtl_mtlsamplerdescriptor_set_label(zval *handle, zval *label)
{
    @autoreleasepool {
        MTLSamplerDescriptor *d = MTL_ARG_AS(MTLSamplerDescriptor, handle);
        if (d == nil) return;
        [d setLabel:(Z_TYPE_P(label) == IS_NULL ? nil : mtl_arg_string(label))];
    }
}

void mtl_mtlsamplerstate_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLSamplerState> s = MTL_ARG_PROTO(MTLSamplerState, handle);
        NSString *l = s != nil ? [s label] : nil;
        if (l == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, l);
    }
}
