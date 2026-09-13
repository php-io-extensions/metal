#include "mtl-blitcommandencoder.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

void mtl_mtlblitcommandencoder_copy_from_buffer_source_offset_to_buffer_destination_offset_size(zval *handle, zval *sourceBuffer, zval *sourceOffset, zval *destinationBuffer, zval *destinationOffset, zval *size)
{
    @autoreleasepool {
        id<MTLBlitCommandEncoder> e = MTL_ARG_PROTO(MTLBlitCommandEncoder, handle);
        id<MTLBuffer> src = MTL_ARG_PROTO(MTLBuffer, sourceBuffer);
        id<MTLBuffer> dst = MTL_ARG_PROTO(MTLBuffer, destinationBuffer);
        zend_long soff = mtl_arg_long(sourceOffset);
        zend_long doff = mtl_arg_long(destinationOffset);
        zend_long n = mtl_arg_long(size);
        /* Both buffers are nonnull in the SDK: an unresolvable handle is a
           no-op rather than a nil send. Offsets and size are NSUIntegers,
           so a negative would wrap to an enormous unsigned value. */
        if (e == nil || src == nil || dst == nil || soff < 0 || doff < 0 || n < 0) return;
        /* Window guard: [b length] on each buffer is a validation-guard
           read before the declared copy send — guards-in-glue ruling
           (scripts/check-parity.php GUARD_SELECTORS), not composition.
           Subtraction form avoids any offset+size overflow. */
        NSUInteger slen = [src length];
        NSUInteger dlen = [dst length];
        if ((NSUInteger) soff > slen || (NSUInteger) n > slen - (NSUInteger) soff) return;
        if ((NSUInteger) doff > dlen || (NSUInteger) n > dlen - (NSUInteger) doff) return;
        [e copyFromBuffer:src
             sourceOffset:(NSUInteger) soff
                 toBuffer:dst
        destinationOffset:(NSUInteger) doff
                     size:(NSUInteger) n];
    }
}

void mtl_mtlblitcommandencoder_fill_buffer_range_value(zval *handle, zval *buffer, zval *rangeLocation, zval *rangeLength, zval *value)
{
    @autoreleasepool {
        id<MTLBlitCommandEncoder> e = MTL_ARG_PROTO(MTLBlitCommandEncoder, handle);
        id<MTLBuffer> b = MTL_ARG_PROTO(MTLBuffer, buffer);
        zend_long loc = mtl_arg_long(rangeLocation);
        zend_long len = mtl_arg_long(rangeLength);
        zend_long v = mtl_arg_long(value);
        /* value is a uint8_t in the SDK: anything outside 0-255 would be
           silently truncated, so it is refused instead. */
        if (e == nil || b == nil || loc < 0 || len < 0 || v < 0 || v > 255) return;
        /* Same window guard as the buffer-to-buffer copy. */
        NSUInteger blen = [b length];
        if ((NSUInteger) loc > blen || (NSUInteger) len > blen - (NSUInteger) loc) return;
        [e fillBuffer:b
                range:NSMakeRange((NSUInteger) loc, (NSUInteger) len)
                value:(uint8_t) v];
    }
}

void mtl_mtlblitcommandencoder_copy_from_buffer_source_offset_source_bytes_per_row_source_bytes_per_image_source_size_to_texture_destination_slice_destination_level_destination_origin(zval *handle, zval *sourceBuffer, zval *sourceOffset, zval *sourceBytesPerRow, zval *sourceBytesPerImage, zval *sourceSizeWidth, zval *sourceSizeHeight, zval *sourceSizeDepth, zval *destinationTexture, zval *destinationSlice, zval *destinationLevel, zval *destinationOriginX, zval *destinationOriginY, zval *destinationOriginZ)
{
    @autoreleasepool {
        id<MTLBlitCommandEncoder> e = MTL_ARG_PROTO(MTLBlitCommandEncoder, handle);
        id<MTLBuffer> src = MTL_ARG_PROTO(MTLBuffer, sourceBuffer);
        id<MTLTexture> dst = MTL_ARG_PROTO(MTLTexture, destinationTexture);
        zend_long soff = mtl_arg_long(sourceOffset);
        zend_long bpr = mtl_arg_long(sourceBytesPerRow);
        zend_long bpi = mtl_arg_long(sourceBytesPerImage);
        zend_long w = mtl_arg_long(sourceSizeWidth);
        zend_long h = mtl_arg_long(sourceSizeHeight);
        zend_long d = mtl_arg_long(sourceSizeDepth);
        zend_long slice = mtl_arg_long(destinationSlice);
        zend_long level = mtl_arg_long(destinationLevel);
        zend_long ox = mtl_arg_long(destinationOriginX);
        zend_long oy = mtl_arg_long(destinationOriginY);
        zend_long oz = mtl_arg_long(destinationOriginZ);
        /* Both resources are nonnull in the SDK. Every remaining argument
           is an NSUInteger, so a negative would wrap; a zero-extent source
           size is a degenerate copy Metal rejects. The destination
           region's fit inside the texture's slice/level extent is Metal's
           own validation — deriving a mip level's extent is arithmetic
           this binding has no business inventing (same ruling as the
           MTLTexture getBytes guard for mip > 0). */
        if (e == nil || src == nil || dst == nil ||
            soff < 0 || bpr < 0 || bpi < 0 ||
            w <= 0 || h <= 0 || d <= 0 ||
            slice < 0 || level < 0 || ox < 0 || oy < 0 || oz < 0) return;
        [e copyFromBuffer:src
             sourceOffset:(NSUInteger) soff
        sourceBytesPerRow:(NSUInteger) bpr
      sourceBytesPerImage:(NSUInteger) bpi
               sourceSize:MTLSizeMake((NSUInteger) w, (NSUInteger) h, (NSUInteger) d)
                toTexture:dst
         destinationSlice:(NSUInteger) slice
         destinationLevel:(NSUInteger) level
        destinationOrigin:MTLOriginMake((NSUInteger) ox, (NSUInteger) oy, (NSUInteger) oz)];
    }
}

void mtl_mtlblitcommandencoder_copy_from_texture_source_slice_source_level_source_origin_source_size_to_buffer_destination_offset_destination_bytes_per_row_destination_bytes_per_image(zval *handle, zval *sourceTexture, zval *sourceSlice, zval *sourceLevel, zval *sourceOriginX, zval *sourceOriginY, zval *sourceOriginZ, zval *sourceSizeWidth, zval *sourceSizeHeight, zval *sourceSizeDepth, zval *destinationBuffer, zval *destinationOffset, zval *destinationBytesPerRow, zval *destinationBytesPerImage)
{
    @autoreleasepool {
        id<MTLBlitCommandEncoder> e = MTL_ARG_PROTO(MTLBlitCommandEncoder, handle);
        id<MTLTexture> src = MTL_ARG_PROTO(MTLTexture, sourceTexture);
        id<MTLBuffer> dst = MTL_ARG_PROTO(MTLBuffer, destinationBuffer);
        zend_long slice = mtl_arg_long(sourceSlice);
        zend_long level = mtl_arg_long(sourceLevel);
        zend_long ox = mtl_arg_long(sourceOriginX);
        zend_long oy = mtl_arg_long(sourceOriginY);
        zend_long oz = mtl_arg_long(sourceOriginZ);
        zend_long w = mtl_arg_long(sourceSizeWidth);
        zend_long h = mtl_arg_long(sourceSizeHeight);
        zend_long d = mtl_arg_long(sourceSizeDepth);
        zend_long doff = mtl_arg_long(destinationOffset);
        zend_long bpr = mtl_arg_long(destinationBytesPerRow);
        zend_long bpi = mtl_arg_long(destinationBytesPerImage);
        /* Mirror of the buffer-to-texture guard: nonnull resources, no
           NSUInteger wrap, no degenerate source size. The source region's
           fit inside the texture's slice/level extent, and the
           destination window implied by bytesPerRow/bytesPerImage, are
           Metal's own validation. */
        if (e == nil || src == nil || dst == nil ||
            slice < 0 || level < 0 || ox < 0 || oy < 0 || oz < 0 ||
            w <= 0 || h <= 0 || d <= 0 ||
            doff < 0 || bpr < 0 || bpi < 0) return;
        [e copyFromTexture:src
               sourceSlice:(NSUInteger) slice
               sourceLevel:(NSUInteger) level
              sourceOrigin:MTLOriginMake((NSUInteger) ox, (NSUInteger) oy, (NSUInteger) oz)
                sourceSize:MTLSizeMake((NSUInteger) w, (NSUInteger) h, (NSUInteger) d)
                  toBuffer:dst
         destinationOffset:(NSUInteger) doff
    destinationBytesPerRow:(NSUInteger) bpr
  destinationBytesPerImage:(NSUInteger) bpi];
    }
}

void mtl_mtlblitcommandencoder_generate_mipmaps_for_texture(zval *handle, zval *texture)
{
    @autoreleasepool {
        id<MTLBlitCommandEncoder> e = MTL_ARG_PROTO(MTLBlitCommandEncoder, handle);
        id<MTLTexture> t = MTL_ARG_PROTO(MTLTexture, texture);
        /* texture is nonnull in the SDK. */
        if (e == nil || t == nil) return;
        [e generateMipmapsForTexture:t];
    }
}

void mtl_mtlblitcommandencoder_synchronize_resource(zval *handle, zval *resource)
{
    @autoreleasepool {
        id<MTLBlitCommandEncoder> e = MTL_ARG_PROTO(MTLBlitCommandEncoder, handle);
        id<MTLResource> r = MTL_ARG_PROTO(MTLResource, resource);
        /* Any MTLBuffer or MTLTexture handle conforms to MTLResource;
           resource is nonnull in the SDK. */
        if (e == nil || r == nil) return;
        [e synchronizeResource:r];
    }
}
