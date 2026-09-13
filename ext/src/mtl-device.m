#include "mtl-device.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtldevice_create_system_default(void)
{
    @autoreleasepool {
        return mtl_handle_for(MTLCreateSystemDefaultDevice());
    }
}

void mtl_mtldevice_name(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLDevice> d = MTL_ARG_PROTO(MTLDevice, handle);
        NSString *n = d != nil ? [d name] : nil;
        if (n == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, n);
    }
}

zend_long mtl_mtldevice_new_command_queue(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLDevice> d = MTL_ARG_PROTO(MTLDevice, handle);
        r = d != nil ? mtl_handle_for([d newCommandQueue]) : 0;
    }
    return r;
}

zend_long mtl_mtldevice_new_texture_with_descriptor(zval *handle, zval *descriptor)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLDevice> d = MTL_ARG_PROTO(MTLDevice, handle);
        MTLTextureDescriptor *td = MTL_ARG_AS(MTLTextureDescriptor, descriptor);
        if (d == nil || td == nil) return 0;
        r = mtl_handle_for([d newTextureWithDescriptor:td]);
    }
    return r;
}

zend_long mtl_mtldevice_new_buffer_with_length_options(zval *handle, zval *length, zval *options)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLDevice> d = MTL_ARG_PROTO(MTLDevice, handle);
        zend_long len = mtl_arg_long(length);
        if (d == nil || len <= 0) return 0;
        r = mtl_handle_for([d newBufferWithLength:(NSUInteger) len
                                          options:(MTLResourceOptions) mtl_arg_long(options)]);
    }
    return r;
}

zend_long mtl_mtldevice_new_buffer_with_bytes_length_options(zval *handle, zval *bytes, zval *options)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLDevice> d = MTL_ARG_PROTO(MTLDevice, handle);
        zval *src = mtl_deref(bytes);
        if (d == nil || src == NULL || Z_TYPE_P(src) != IS_STRING || Z_STRLEN_P(src) == 0) return 0;
        /* length: is the PHP string's own byte length — the selector can
           then never be pointed past the memory PHP owns. */
        r = mtl_handle_for([d newBufferWithBytes:Z_STRVAL_P(src)
                                          length:(NSUInteger) Z_STRLEN_P(src)
                                         options:(MTLResourceOptions) mtl_arg_long(options)]);
    }
    return r;
}

void mtl_mtldevice_new_library_with_source_options_error(zval *return_value, zval *handle, zval *source, zval *options)
{
    @autoreleasepool {
        id<MTLDevice> d = MTL_ARG_PROTO(MTLDevice, handle);
        NSString *src = mtl_arg_string(source);
        MTLCompileOptions *opts = MTL_ARG_AS(MTLCompileOptions, options);
        if (d == nil || src == nil) { mtl_ret_handle_error(return_value, 0, 0); return; }
        NSError *error = nil;
        id<MTLLibrary> lib = [d newLibraryWithSource:src options:opts error:&error];
        /* Exactly one of the two is non-zero: the error handle is only
           registered when no library came back. */
        mtl_ret_handle_error(return_value,
                             mtl_handle_for(lib),
                             lib == nil ? mtl_handle_for(error) : 0);
    }
}

void mtl_mtldevice_new_render_pipeline_state_with_descriptor_error(zval *return_value, zval *handle, zval *descriptor)
{
    @autoreleasepool {
        id<MTLDevice> d = MTL_ARG_PROTO(MTLDevice, handle);
        MTLRenderPipelineDescriptor *rpd = MTL_ARG_AS(MTLRenderPipelineDescriptor, descriptor);
        if (d == nil || rpd == nil) { mtl_ret_handle_error(return_value, 0, 0); return; }
        NSError *error = nil;
        id<MTLRenderPipelineState> state = [d newRenderPipelineStateWithDescriptor:rpd error:&error];
        mtl_ret_handle_error(return_value,
                             mtl_handle_for(state),
                             state == nil ? mtl_handle_for(error) : 0);
    }
}

void mtl_mtldevice_new_compute_pipeline_state_with_function_error(zval *return_value, zval *handle, zval *computeFunction)
{
    @autoreleasepool {
        id<MTLDevice> d = MTL_ARG_PROTO(MTLDevice, handle);
        id<MTLFunction> fn = MTL_ARG_PROTO(MTLFunction, computeFunction);
        /* computeFunction is nonnull in the SDK, so an unresolvable handle
           is the no-send {0, 0} case rather than a nil send. */
        if (d == nil || fn == nil) { mtl_ret_handle_error(return_value, 0, 0); return; }
        NSError *error = nil;
        id<MTLComputePipelineState> state = [d newComputePipelineStateWithFunction:fn error:&error];
        mtl_ret_handle_error(return_value,
                             mtl_handle_for(state),
                             state == nil ? mtl_handle_for(error) : 0);
    }
}

zend_long mtl_mtldevice_new_depth_stencil_state_with_descriptor(zval *handle, zval *descriptor)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLDevice> d = MTL_ARG_PROTO(MTLDevice, handle);
        MTLDepthStencilDescriptor *dsd = MTL_ARG_AS(MTLDepthStencilDescriptor, descriptor);
        if (d == nil || dsd == nil) return 0;
        r = mtl_handle_for([d newDepthStencilStateWithDescriptor:dsd]);
    }
    return r;
}

zend_long mtl_mtldevice_new_sampler_state_with_descriptor(zval *handle, zval *descriptor)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLDevice> d = MTL_ARG_PROTO(MTLDevice, handle);
        MTLSamplerDescriptor *sd = MTL_ARG_AS(MTLSamplerDescriptor, descriptor);
        if (d == nil || sd == nil) return 0;
        r = mtl_handle_for([d newSamplerStateWithDescriptor:sd]);
    }
    return r;
}
