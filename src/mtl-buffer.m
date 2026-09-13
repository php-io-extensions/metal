#include "mtl-buffer.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtlbuffer_length(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLBuffer> b = MTL_ARG_PROTO(MTLBuffer, handle);
        r = b != nil ? (zend_long) [b length] : 0;
    }
    return r;
}

void mtl_mtlbuffer_contents_bytes(zval *return_value, zval *handle, zval *offset, zval *length)
{
    @autoreleasepool {
        id<MTLBuffer> b = MTL_ARG_PROTO(MTLBuffer, handle);
        zend_long off = mtl_arg_long(offset);
        zend_long len = mtl_arg_long(length);
        if (b == nil || off < 0 || len <= 0) {
            ZVAL_EMPTY_STRING(return_value);
            return;
        }
        /* Window guard: [b length] is a second send used only to validate
           the requested range before the declared `contents` send —
           guards-in-glue ruling (scripts/check-parity.php
           GUARD_SELECTORS), not composition. Subtraction form avoids any
           offset+length overflow. */
        NSUInteger blen = [b length];
        if ((NSUInteger) off > blen || (NSUInteger) len > blen - (NSUInteger) off) {
            ZVAL_EMPTY_STRING(return_value);
            return;
        }
        void *p = [b contents];
        if (p == NULL) { /* nothing CPU-visible to copy from */
            ZVAL_EMPTY_STRING(return_value);
            return;
        }
        zend_string *buf = zend_string_alloc((size_t) len, 0);
        memcpy(ZSTR_VAL(buf), (const char *) p + (size_t) off, (size_t) len);
        ZSTR_VAL(buf)[(size_t) len] = '\0';
        ZVAL_NEW_STR(return_value, buf);
    }
}

zend_long mtl_mtlbuffer_set_contents_bytes(zval *handle, zval *bytes, zval *offset)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLBuffer> b = MTL_ARG_PROTO(MTLBuffer, handle);
        zval *src = mtl_deref(bytes);
        zend_long off = mtl_arg_long(offset);
        if (b == nil || src == NULL || Z_TYPE_P(src) != IS_STRING || off < 0) return 0;
        size_t len = Z_STRLEN_P(src);
        /* Same window guard as contentsBytes. */
        NSUInteger blen = [b length];
        if ((NSUInteger) off > blen || (NSUInteger) len > blen - (NSUInteger) off) return 0;
        /* Writing nothing at an in-range offset is a successful no-op, not
           a failure: there is nothing to copy and nothing went wrong. */
        if (len == 0) return 1;
        void *p = [b contents];
        if (p == NULL) return 0;
        memcpy((char *) p + (size_t) off, Z_STRVAL_P(src), len);
        r = 1;
    }
    return r;
}
