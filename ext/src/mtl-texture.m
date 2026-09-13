#include "mtl-texture.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtltexturedescriptor_texture2d_descriptor_with_pixel_format_width_height_mipmapped(zval *pixelFormat, zval *width, zval *height, zval *mipmapped)
{
    @autoreleasepool {
        MTLTextureDescriptor *td = [MTLTextureDescriptor
            texture2DDescriptorWithPixelFormat:(MTLPixelFormat) mtl_arg_long(pixelFormat)
                                         width:(NSUInteger) mtl_arg_long(width)
                                        height:(NSUInteger) mtl_arg_long(height)
                                     mipmapped:mtl_arg_bool(mipmapped)];
        return mtl_handle_for(td);
    }
}

zend_long mtl_mtltexturedescriptor_usage(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLTextureDescriptor *td = MTL_ARG_AS(MTLTextureDescriptor, handle);
        r = td != nil ? (zend_long) [td usage] : 0;
    }
    return r;
}

void mtl_mtltexturedescriptor_set_usage(zval *handle, zval *usage)
{
    @autoreleasepool {
        MTLTextureDescriptor *td = MTL_ARG_AS(MTLTextureDescriptor, handle);
        if (td == nil) return;
        [td setUsage:(MTLTextureUsage) mtl_arg_long(usage)];
    }
}

zend_long mtl_mtltexturedescriptor_storage_mode(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLTextureDescriptor *td = MTL_ARG_AS(MTLTextureDescriptor, handle);
        r = td != nil ? (zend_long) [td storageMode] : 0;
    }
    return r;
}

void mtl_mtltexturedescriptor_set_storage_mode(zval *handle, zval *storageMode)
{
    @autoreleasepool {
        MTLTextureDescriptor *td = MTL_ARG_AS(MTLTextureDescriptor, handle);
        if (td == nil) return;
        [td setStorageMode:(MTLStorageMode) mtl_arg_long(storageMode)];
    }
}

zend_long mtl_mtltexture_width(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLTexture> t = MTL_ARG_PROTO(MTLTexture, handle);
        r = t != nil ? (zend_long) [t width] : 0;
    }
    return r;
}

zend_long mtl_mtltexture_height(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLTexture> t = MTL_ARG_PROTO(MTLTexture, handle);
        r = t != nil ? (zend_long) [t height] : 0;
    }
    return r;
}

zend_long mtl_mtltexture_pixel_format(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLTexture> t = MTL_ARG_PROTO(MTLTexture, handle);
        r = t != nil ? (zend_long) [t pixelFormat] : 0;
    }
    return r;
}

void mtl_mtltexture_get_bytes_bytes_per_row_from_region_mipmap_level(zval *return_value, zval *handle, zval *bytesPerRow, zval *x, zval *y, zval *z, zval *width, zval *height, zval *depth, zval *mipmapLevel)
{
    @autoreleasepool {
        id<MTLTexture> t = MTL_ARG_PROTO(MTLTexture, handle);
        zend_long bpr = mtl_arg_long(bytesPerRow);
        zend_long xx = mtl_arg_long(x);
        zend_long yy = mtl_arg_long(y);
        zend_long zz = mtl_arg_long(z);
        zend_long w = mtl_arg_long(width);
        zend_long h = mtl_arg_long(height);
        zend_long d = mtl_arg_long(depth);
        zend_long mip = mtl_arg_long(mipmapLevel);
        if (t == nil || bpr <= 0 || h <= 0 || d <= 0 ||
            xx < 0 || yy < 0 || zz < 0 || w <= 0 || mip < 0) {
            ZVAL_EMPTY_STRING(return_value);
            return;
        }
        /* Region bounds guard: [t width]/[t height] are a second/third
           message send on top of the declared getBytes:..., sanctioned as
           a validation guard per the established guards-in-glue ruling
           (see scripts/check-parity.php GUARD_SELECTORS), not composition.
           Only mip 0 is checked here — [t width]/[t height] are the level-0
           dimensions, and deriving a mip level's extent would be arithmetic
           this binding has no business inventing. For mip > 0 the bounds
           are Metal's own validation to enforce. */
        if (mip == 0 && ((NSUInteger) xx + (NSUInteger) w > [t width] ||
                          (NSUInteger) yy + (NSUInteger) h > [t height])) {
            ZVAL_EMPTY_STRING(return_value);
            return;
        }
        size_t tmp, len;
        if (__builtin_mul_overflow((size_t) bpr, (size_t) h, &tmp) ||
            __builtin_mul_overflow(tmp, (size_t) d, &len)) {
            ZVAL_EMPTY_STRING(return_value);
            return;
        }
        zend_string *buf = zend_string_alloc(len, 0);
        memset(ZSTR_VAL(buf), 0, len);
        MTLRegion region = MTLRegionMake3D(
            (NSUInteger) xx, (NSUInteger) yy, (NSUInteger) zz,
            (NSUInteger) w, (NSUInteger) h, (NSUInteger) d);
        [t getBytes:ZSTR_VAL(buf)
        bytesPerRow:(NSUInteger) bpr
         fromRegion:region
        mipmapLevel:(NSUInteger) mip];
        ZSTR_VAL(buf)[len] = '\0';
        ZVAL_NEW_STR(return_value, buf);
    }
}

zend_long mtl_mtltexture_replace_region_mipmap_level_with_bytes_bytes_per_row(zval *handle, zval *x, zval *y, zval *z, zval *width, zval *height, zval *depth, zval *mipmapLevel, zval *bytes, zval *bytesPerRow)
{
    zend_long r = 0;
    @autoreleasepool {
        id<MTLTexture> t = MTL_ARG_PROTO(MTLTexture, handle);
        zval *src = mtl_deref(bytes);
        zend_long xx = mtl_arg_long(x);
        zend_long yy = mtl_arg_long(y);
        zend_long zz = mtl_arg_long(z);
        zend_long w = mtl_arg_long(width);
        zend_long h = mtl_arg_long(height);
        zend_long d = mtl_arg_long(depth);
        zend_long mip = mtl_arg_long(mipmapLevel);
        zend_long bpr = mtl_arg_long(bytesPerRow);
        if (t == nil || src == NULL || Z_TYPE_P(src) != IS_STRING ||
            bpr <= 0 || w <= 0 || h <= 0 || d <= 0 ||
            xx < 0 || yy < 0 || zz < 0 || mip < 0) {
            return 0;
        }
        /* Region bounds guard, as in getBytes: [t width]/[t height] are
           validation-only sends (GUARD_SELECTORS), not composition, and
           they are the level-0 dimensions — so only mip 0 is checked here
           and mip > 0 bounds are left to Metal's own validation. The
           source-length guard below applies at every level. */
        if (mip == 0 && ((NSUInteger) xx + (NSUInteger) w > [t width] ||
                          (NSUInteger) yy + (NSUInteger) h > [t height])) {
            return 0;
        }
        /* The source string must cover everything the selector will read:
           bytesPerRow * height * depth bytes. */
        size_t tmp, need;
        if (__builtin_mul_overflow((size_t) bpr, (size_t) h, &tmp) ||
            __builtin_mul_overflow(tmp, (size_t) d, &need)) {
            return 0;
        }
        if (Z_STRLEN_P(src) < need) return 0;
        MTLRegion region = MTLRegionMake3D(
            (NSUInteger) xx, (NSUInteger) yy, (NSUInteger) zz,
            (NSUInteger) w, (NSUInteger) h, (NSUInteger) d);
        [t replaceRegion:region
             mipmapLevel:(NSUInteger) mip
               withBytes:Z_STRVAL_P(src)
             bytesPerRow:(NSUInteger) bpr];
        r = 1;
    }
    return r;
}
