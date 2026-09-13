#include "mtl-computecommandencoder.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

void mtl_mtlcomputecommandencoder_set_compute_pipeline_state(zval *handle, zval *state)
{
    @autoreleasepool {
        id<MTLComputeCommandEncoder> e = MTL_ARG_PROTO(MTLComputeCommandEncoder, handle);
        id<MTLComputePipelineState> p = MTL_ARG_PROTO(MTLComputePipelineState, state);
        /* The SDK declares state nonnull; a nil send would trap inside
           Metal's validation layer, so an unresolvable handle is a no-op
           here. */
        if (e == nil || p == nil) return;
        [e setComputePipelineState:p];
    }
}

void mtl_mtlcomputecommandencoder_set_buffer_offset_at_index(zval *handle, zval *buffer, zval *offset, zval *index)
{
    @autoreleasepool {
        id<MTLComputeCommandEncoder> e = MTL_ARG_PROTO(MTLComputeCommandEncoder, handle);
        zend_long off = mtl_arg_long(offset);
        zend_long idx = mtl_arg_long(index);
        /* offset and index are NSUIntegers: a negative would wrap to an
           enormous unsigned value, so it is rejected in glue. buffer is
           nullable in the SDK — 0 (nil) is a legal unbind. */
        if (e == nil || off < 0 || idx < 0) return;
        [e setBuffer:MTL_ARG_PROTO(MTLBuffer, buffer)
              offset:(NSUInteger) off
             atIndex:(NSUInteger) idx];
    }
}

void mtl_mtlcomputecommandencoder_set_texture_at_index(zval *handle, zval *texture, zval *index)
{
    @autoreleasepool {
        id<MTLComputeCommandEncoder> e = MTL_ARG_PROTO(MTLComputeCommandEncoder, handle);
        zend_long idx = mtl_arg_long(index);
        if (e == nil || idx < 0) return;
        [e setTexture:MTL_ARG_PROTO(MTLTexture, texture)
              atIndex:(NSUInteger) idx];
    }
}

void mtl_mtlcomputecommandencoder_dispatch_threadgroups_threads_per_threadgroup(zval *handle, zval *threadgroupsPerGridWidth, zval *threadgroupsPerGridHeight, zval *threadgroupsPerGridDepth, zval *threadsPerThreadgroupWidth, zval *threadsPerThreadgroupHeight, zval *threadsPerThreadgroupDepth)
{
    @autoreleasepool {
        id<MTLComputeCommandEncoder> e = MTL_ARG_PROTO(MTLComputeCommandEncoder, handle);
        zend_long gw = mtl_arg_long(threadgroupsPerGridWidth);
        zend_long gh = mtl_arg_long(threadgroupsPerGridHeight);
        zend_long gd = mtl_arg_long(threadgroupsPerGridDepth);
        zend_long tw = mtl_arg_long(threadsPerThreadgroupWidth);
        zend_long th = mtl_arg_long(threadsPerThreadgroupHeight);
        zend_long td = mtl_arg_long(threadsPerThreadgroupDepth);
        /* Both MTLSizes are triples of NSUIntegers. A negative component
           would wrap to an enormous unsigned value; a zero one makes the
           dispatch degenerate and Metal rejects it. Neither reaches the
           selector. Whether the threadgroup size is legal for the bound
           pipeline is the caller's business — MTLComputePipelineState
           reports maxTotalThreadsPerThreadgroup and threadExecutionWidth
           for exactly that. */
        if (e == nil || gw <= 0 || gh <= 0 || gd <= 0 || tw <= 0 || th <= 0 || td <= 0) return;
        [e dispatchThreadgroups:MTLSizeMake((NSUInteger) gw, (NSUInteger) gh, (NSUInteger) gd)
          threadsPerThreadgroup:MTLSizeMake((NSUInteger) tw, (NSUInteger) th, (NSUInteger) td)];
    }
}

void mtl_mtlcomputecommandencoder_dispatch_threads_threads_per_threadgroup(zval *handle, zval *threadsPerGridWidth, zval *threadsPerGridHeight, zval *threadsPerGridDepth, zval *threadsPerThreadgroupWidth, zval *threadsPerThreadgroupHeight, zval *threadsPerThreadgroupDepth)
{
    @autoreleasepool {
        id<MTLComputeCommandEncoder> e = MTL_ARG_PROTO(MTLComputeCommandEncoder, handle);
        zend_long gw = mtl_arg_long(threadsPerGridWidth);
        zend_long gh = mtl_arg_long(threadsPerGridHeight);
        zend_long gd = mtl_arg_long(threadsPerGridDepth);
        zend_long tw = mtl_arg_long(threadsPerThreadgroupWidth);
        zend_long th = mtl_arg_long(threadsPerThreadgroupHeight);
        zend_long td = mtl_arg_long(threadsPerThreadgroupDepth);
        /* Same component guard as the uniform variant. This is the
           non-uniform dispatch: threadsPerGrid need not be a multiple of
           the threadgroup size, and the device must support non-uniform
           threadgroup sizes — that capability query is not bound this
           wave, so an unsupported device surfaces as a command-buffer
           error rather than a refusal here. */
        if (e == nil || gw <= 0 || gh <= 0 || gd <= 0 || tw <= 0 || th <= 0 || td <= 0) return;
        [e dispatchThreads:MTLSizeMake((NSUInteger) gw, (NSUInteger) gh, (NSUInteger) gd)
     threadsPerThreadgroup:MTLSizeMake((NSUInteger) tw, (NSUInteger) th, (NSUInteger) td)];
    }
}
