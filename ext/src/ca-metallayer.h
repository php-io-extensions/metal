#ifndef PHP_METAL_CA_METALLAYER_H
#define PHP_METAL_CA_METALLAYER_H

/*
 * Slice-zero partial of QuartzCore's CAMetalLayer and the CAMetalDrawable
 * protocol (same header). This extension owns CAMetalLayer; ext-appkit
 * owns CALayer and NSView — the layer crosses to appkit as raw pointer
 * bits via Bridge::pointerOf, and appkit's Bridge::adopt + NSView
 * setWantsLayer/setLayer attach it. Inherited CALayer members
 * (contentsScale et al.) bind on CALayer in ext-appkit, never here.
 * Construction is alloc+init (sanctioned glue). drawableSize is CGSize:
 * doubles in, {width, height} out.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial QuartzCore\CAMetalLayer slice zero: device, pixelFormat, drawableSize, framebufferOnly, nextDrawable */

/*@zep-construct QuartzCore\CAMetalLayer init() -> int */
zend_long mtl_cametallayer_init(void);

/*@zep QuartzCore\CAMetalLayer device(int handle) -> int */
zend_long mtl_cametallayer_device(zval *handle);
/*@zep QuartzCore\CAMetalLayer setDevice(int handle, int device) -> void */
void mtl_cametallayer_set_device(zval *handle, zval *device);

/*@zep QuartzCore\CAMetalLayer pixelFormat(int handle) -> int */
zend_long mtl_cametallayer_pixel_format(zval *handle);
/*@zep QuartzCore\CAMetalLayer setPixelFormat(int handle, int pixelFormat) -> void */
void mtl_cametallayer_set_pixel_format(zval *handle, zval *pixelFormat);

/*@zep QuartzCore\CAMetalLayer drawableSize(int handle) -> array */
void mtl_cametallayer_drawable_size(zval *return_value, zval *handle);
/*@zep QuartzCore\CAMetalLayer setDrawableSize(int handle, double width, double height) -> void */
void mtl_cametallayer_set_drawable_size(zval *handle, zval *width, zval *height);

/*@zep QuartzCore\CAMetalLayer framebufferOnly(int handle) -> bool */
zend_long mtl_cametallayer_framebuffer_only(zval *handle);
/*@zep QuartzCore\CAMetalLayer setFramebufferOnly(int handle, bool framebufferOnly) -> void */
void mtl_cametallayer_set_framebuffer_only(zval *handle, zval *framebufferOnly);

/*@zep QuartzCore\CAMetalLayer nextDrawable(int handle) -> int */
zend_long mtl_cametallayer_next_drawable(zval *handle);

/*@audit partial QuartzCore\CAMetalDrawable texture + layer */
/*@audit factory QuartzCore\CAMetalDrawable CAMetalLayer::nextDrawable */

/*@zep QuartzCore\CAMetalDrawable texture(int handle) -> int */
zend_long mtl_cametaldrawable_texture(zval *handle);
/*@zep QuartzCore\CAMetalDrawable layer(int handle) -> int */
zend_long mtl_cametaldrawable_layer(zval *handle);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_CA_METALLAYER_H */
