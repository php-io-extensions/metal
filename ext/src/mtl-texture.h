#ifndef PHP_METAL_MTL_TEXTURE_H
#define PHP_METAL_MTL_TEXTURE_H

/*
 * Slice-zero partials of MTLTextureDescriptor (@interface) and the
 * MTLTexture protocol, both declared in Metal's MTLTexture.h.
 * getBytes crosses the pixel buffer back as a PHP string: the glue
 * allocates length = bytesPerRow * height * depth, sends the one
 * getBytes message, and returns the buffer. MTLRegion crosses as its
 * six integer components (spec §4 struct convention).
 *
 * replaceRegion is the same seam in the other direction: the PHP string
 * is the upload source, so the glue refuses any request whose region
 * leaves the texture (checked at mip 0; mip > 0 bounds are Metal's own
 * validation) or whose string is shorter than
 * bytesPerRow * height * depth — Metal would otherwise read past the
 * string. Both are guards in glue, not composition.
 *
 * Whether bytesPerRow is the *right* stride for the pixel format and
 * region width is the caller's contract with Metal, not something either
 * binding checks: the guards only prove the string is long enough for the
 * stride you passed and that the region fits. A wrong-but-large-enough
 * stride gives you skewed pixels, exactly as it would in Objective-C.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLTextureDescriptor slice zero: texture2D factory, usage, storageMode */

/*@zep MTL\MTLTextureDescriptor texture2DDescriptorWithPixelFormatWidthHeightMipmapped(int pixelFormat, int width, int height, bool mipmapped) -> int */
zend_long mtl_mtltexturedescriptor_texture2d_descriptor_with_pixel_format_width_height_mipmapped(zval *pixelFormat, zval *width, zval *height, zval *mipmapped);

/*@zep MTL\MTLTextureDescriptor usage(int handle) -> int */
zend_long mtl_mtltexturedescriptor_usage(zval *handle);
/*@zep MTL\MTLTextureDescriptor setUsage(int handle, int usage) -> void */
void mtl_mtltexturedescriptor_set_usage(zval *handle, zval *usage);

/*@zep MTL\MTLTextureDescriptor storageMode(int handle) -> int */
zend_long mtl_mtltexturedescriptor_storage_mode(zval *handle);
/*@zep MTL\MTLTextureDescriptor setStorageMode(int handle, int storageMode) -> void */
void mtl_mtltexturedescriptor_set_storage_mode(zval *handle, zval *storageMode);

/*@audit partial MTL\MTLTexture wave A: dims, pixelFormat, getBytes, replaceRegion */
/*@audit factory MTL\MTLTexture MTLDevice::newTextureWithDescriptor */

/*@zep MTL\MTLTexture width(int handle) -> int */
zend_long mtl_mtltexture_width(zval *handle);
/*@zep MTL\MTLTexture height(int handle) -> int */
zend_long mtl_mtltexture_height(zval *handle);
/*@zep MTL\MTLTexture pixelFormat(int handle) -> int */
zend_long mtl_mtltexture_pixel_format(zval *handle);

/*@zep MTL\MTLTexture getBytesBytesPerRowFromRegionMipmapLevel(int handle, int bytesPerRow, int x, int y, int z, int width, int height, int depth, int mipmapLevel) -> string */
void mtl_mtltexture_get_bytes_bytes_per_row_from_region_mipmap_level(zval *return_value, zval *handle, zval *bytesPerRow, zval *x, zval *y, zval *z, zval *width, zval *height, zval *depth, zval *mipmapLevel);

/*@zep MTL\MTLTexture replaceRegionMipmapLevelWithBytesBytesPerRow(int handle, int x, int y, int z, int width, int height, int depth, int mipmapLevel, string bytes, int bytesPerRow) -> bool */
zend_long mtl_mtltexture_replace_region_mipmap_level_with_bytes_bytes_per_row(zval *handle, zval *x, zval *y, zval *z, zval *width, zval *height, zval *depth, zval *mipmapLevel, zval *bytes, zval *bytesPerRow);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_TEXTURE_H */
