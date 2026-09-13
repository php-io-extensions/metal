#include "mtl-library.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtllibrary_new_function_with_name(zval *handle, zval *functionName)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLLibrary> l = MTL_ARG_PROTO(MTLLibrary, handle);
        NSString *n = mtl_arg_string(functionName);
        if (l == nil || n == nil) return 0;
        r = mtl_handle_for([l newFunctionWithName:n]);
    }
    return r;
}

void mtl_mtllibrary_function_names(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLLibrary> l = MTL_ARG_PROTO(MTLLibrary, handle);
        if (l == nil) { array_init(return_value); return; }
        mtl_ret_string_array(return_value, [l functionNames]);
    }
}

void mtl_mtllibrary_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLLibrary> l = MTL_ARG_PROTO(MTLLibrary, handle);
        NSString *s = l != nil ? [l label] : nil;
        if (s == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, s);
    }
}

void mtl_mtllibrary_set_label(zval *handle, zval *label)
{
    @autoreleasepool {
        id<MTLLibrary> l = MTL_ARG_PROTO(MTLLibrary, handle);
        if (l == nil) return;
        [l setLabel:(Z_TYPE_P(label) == IS_NULL ? nil : mtl_arg_string(label))];
    }
}

void mtl_mtlfunction_name(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLFunction> f = MTL_ARG_PROTO(MTLFunction, handle);
        NSString *s = f != nil ? [f name] : nil;
        /* name is nonnull per the SDK; an unresolvable handle still has to
           return a string, so "" stands in for "no function". */
        if (s == nil) { ZVAL_EMPTY_STRING(return_value); return; }
        mtl_ret_string(return_value, s);
    }
}

zend_long mtl_mtlfunction_function_type(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLFunction> f = MTL_ARG_PROTO(MTLFunction, handle);
        r = f != nil ? (zend_long) [f functionType] : 0;
    }
    return r;
}

void mtl_mtlfunction_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLFunction> f = MTL_ARG_PROTO(MTLFunction, handle);
        NSString *s = f != nil ? [f label] : nil;
        if (s == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, s);
    }
}

void mtl_mtlfunction_set_label(zval *handle, zval *label)
{
    @autoreleasepool {
        id<MTLFunction> f = MTL_ARG_PROTO(MTLFunction, handle);
        if (f == nil) return;
        [f setLabel:(Z_TYPE_P(label) == IS_NULL ? nil : mtl_arg_string(label))];
    }
}
