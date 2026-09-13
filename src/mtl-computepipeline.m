#include "mtl-computepipeline.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

void mtl_mtlcomputepipelinestate_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLComputePipelineState> p = MTL_ARG_PROTO(MTLComputePipelineState, handle);
        NSString *l = p != nil ? [p label] : nil;
        if (l == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, l);
    }
}

zend_long mtl_mtlcomputepipelinestate_max_total_threads_per_threadgroup(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLComputePipelineState> p = MTL_ARG_PROTO(MTLComputePipelineState, handle);
        r = p != nil ? (zend_long) [p maxTotalThreadsPerThreadgroup] : 0;
    }
    return r;
}

zend_long mtl_mtlcomputepipelinestate_thread_execution_width(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLComputePipelineState> p = MTL_ARG_PROTO(MTLComputePipelineState, handle);
        r = p != nil ? (zend_long) [p threadExecutionWidth] : 0;
    }
    return r;
}
