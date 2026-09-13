#include "mtl-commandqueue.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtlcommandqueue_command_buffer(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLCommandQueue> q = MTL_ARG_PROTO(MTLCommandQueue, handle);
        r = q != nil ? mtl_handle_for([q commandBuffer]) : 0;
    }
    return r;
}

void mtl_mtlcommandqueue_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLCommandQueue> q = MTL_ARG_PROTO(MTLCommandQueue, handle);
        NSString *l = q != nil ? [q label] : nil;
        if (l == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, l);
    }
}

void mtl_mtlcommandqueue_set_label(zval *handle, zval *label)
{
    @autoreleasepool {
        id<MTLCommandQueue> q = MTL_ARG_PROTO(MTLCommandQueue, handle);
        if (q == nil) return;
        [q setLabel:(Z_TYPE_P(label) == IS_NULL ? nil : mtl_arg_string(label))];
    }
}
