#ifndef PHP_METAL_MTL_BLITCOMMANDENCODER_H
#define PHP_METAL_MTL_BLITCOMMANDENCODER_H

/*
 * Wave B partial of the MTLBlitCommandEncoder protocol (its own header).
 * The protocol adopts MTLCommandEncoder, so endEncoding and label/setLabel
 * stay bound where the SDK declares them and a blit encoder handle
 * satisfies the conformance guard on those calls unchanged.
 *
 * Construction is MTLCommandBuffer::blitCommandEncoder (factory marker
 * below). Selectors are flattened house-style, which makes two of these
 * names very long; that is the faithful flattening of a nine-part
 * selector, not a nickname.
 *
 * Struct arguments cross as components (house convention): MTLSize as
 * three integers, MTLOrigin as three integers, NSRange as its location
 * and length. fillBuffer:range:value: takes a uint8_t value, so the
 * binding refuses anything outside 0-255 rather than truncating silently.
 *
 * Range guards: the two calls that write into a buffer through a range
 * this binding can cheaply check ([b length] is a validation-guard read,
 * see scripts/check-parity.php GUARD_SELECTORS) refuse an out-of-range
 * window instead of encoding it. The buffer-texture pair is not guarded
 * that way: a texture's per-slice, per-level extent is arithmetic this
 * binding has no business inventing (the same ruling the texture getBytes
 * guard already makes for mip > 0), so those bounds are Metal's own
 * validation to enforce. Every integer argument is still range-checked
 * against the NSUInteger wrap.
 *
 * synchronizeResource: is macOS-only in the SDK (API_UNAVAILABLE(ios)) and
 * this extension is macOS-only, so it binds unconditionally. It is the
 * blit-side counterpart to the managed-storage gap noted on MTLBuffer:
 * didModifyRange: (the CPU-side half) is still unbound, so a managed
 * buffer written from PHP is not yet fully serviceable.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLBlitCommandEncoder wave B: buffer copy/fill, buffer-texture copies, mipmap generation, managed-resource sync */
/*@audit factory MTL\MTLBlitCommandEncoder MTLCommandBuffer::blitCommandEncoder */

/*@zep MTL\MTLBlitCommandEncoder copyFromBufferSourceOffsetToBufferDestinationOffsetSize(int handle, int sourceBuffer, int sourceOffset, int destinationBuffer, int destinationOffset, int size) -> void */
void mtl_mtlblitcommandencoder_copy_from_buffer_source_offset_to_buffer_destination_offset_size(zval *handle, zval *sourceBuffer, zval *sourceOffset, zval *destinationBuffer, zval *destinationOffset, zval *size);

/*@zep MTL\MTLBlitCommandEncoder fillBufferRangeValue(int handle, int buffer, int rangeLocation, int rangeLength, int value) -> void */
void mtl_mtlblitcommandencoder_fill_buffer_range_value(zval *handle, zval *buffer, zval *rangeLocation, zval *rangeLength, zval *value);

/*@zep MTL\MTLBlitCommandEncoder copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin(int handle, int sourceBuffer, int sourceOffset, int sourceBytesPerRow, int sourceBytesPerImage, int sourceSizeWidth, int sourceSizeHeight, int sourceSizeDepth, int destinationTexture, int destinationSlice, int destinationLevel, int destinationOriginX, int destinationOriginY, int destinationOriginZ) -> void */
void mtl_mtlblitcommandencoder_copy_from_buffer_source_offset_source_bytes_per_row_source_bytes_per_image_source_size_to_texture_destination_slice_destination_level_destination_origin(zval *handle, zval *sourceBuffer, zval *sourceOffset, zval *sourceBytesPerRow, zval *sourceBytesPerImage, zval *sourceSizeWidth, zval *sourceSizeHeight, zval *sourceSizeDepth, zval *destinationTexture, zval *destinationSlice, zval *destinationLevel, zval *destinationOriginX, zval *destinationOriginY, zval *destinationOriginZ);

/*@zep MTL\MTLBlitCommandEncoder copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImage(int handle, int sourceTexture, int sourceSlice, int sourceLevel, int sourceOriginX, int sourceOriginY, int sourceOriginZ, int sourceSizeWidth, int sourceSizeHeight, int sourceSizeDepth, int destinationBuffer, int destinationOffset, int destinationBytesPerRow, int destinationBytesPerImage) -> void */
void mtl_mtlblitcommandencoder_copy_from_texture_source_slice_source_level_source_origin_source_size_to_buffer_destination_offset_destination_bytes_per_row_destination_bytes_per_image(zval *handle, zval *sourceTexture, zval *sourceSlice, zval *sourceLevel, zval *sourceOriginX, zval *sourceOriginY, zval *sourceOriginZ, zval *sourceSizeWidth, zval *sourceSizeHeight, zval *sourceSizeDepth, zval *destinationBuffer, zval *destinationOffset, zval *destinationBytesPerRow, zval *destinationBytesPerImage);

/*@zep MTL\MTLBlitCommandEncoder generateMipmapsForTexture(int handle, int texture) -> void */
void mtl_mtlblitcommandencoder_generate_mipmaps_for_texture(zval *handle, zval *texture);

/*@zep MTL\MTLBlitCommandEncoder synchronizeResource(int handle, int resource) -> void */
void mtl_mtlblitcommandencoder_synchronize_resource(zval *handle, zval *resource);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_BLITCOMMANDENCODER_H */
