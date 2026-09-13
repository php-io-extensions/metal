#include "mtl-commandencoder.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

void mtl_mtlcommandencoder_end_encoding(zval *handle)
{
    @autoreleasepool {
        id<MTLCommandEncoder> e = MTL_ARG_PROTO(MTLCommandEncoder, handle);
        if (e == nil) return;
        [e endEncoding];
    }
}

void mtl_mtlcommandencoder_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLCommandEncoder> e = MTL_ARG_PROTO(MTLCommandEncoder, handle);
        NSString *l = e != nil ? [e label] : nil;
        if (l == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, l);
    }
}

void mtl_mtlcommandencoder_set_label(zval *handle, zval *label)
{
    @autoreleasepool {
        id<MTLCommandEncoder> e = MTL_ARG_PROTO(MTLCommandEncoder, handle);
        if (e == nil) return;
        [e setLabel:(Z_TYPE_P(label) == IS_NULL ? nil : mtl_arg_string(label))];
    }
}
