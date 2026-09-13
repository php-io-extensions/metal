#ifndef PHP_METAL_MTL_DEPTHSTENCIL_H
#define PHP_METAL_MTL_DEPTHSTENCIL_H

/*
 * Wave A partials of Metal's MTLDepthStencil.h: MTLDepthStencilDescriptor
 * (alloc+init construction glue) and the MTLDepthStencilState protocol,
 * produced by MTLDevice::newDepthStencilStateWithDescriptor.
 * MTLStencilDescriptor, the front/back face stencil descriptors and the
 * state's device accessor are untouched this wave.
 *
 * depthWriteEnabled's SDK getter is isDepthWriteEnabled; the binding
 * keeps the property name and sends the getter (house getter=isX rule).
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLDepthStencilDescriptor wave A: depthCompareFunction, depthWriteEnabled, label */

/*@zep-construct MTL\MTLDepthStencilDescriptor init() -> int */
zend_long mtl_mtldepthstencildescriptor_init(void);

/*@zep MTL\MTLDepthStencilDescriptor depthCompareFunction(int handle) -> int */
zend_long mtl_mtldepthstencildescriptor_depth_compare_function(zval *handle);
/*@zep MTL\MTLDepthStencilDescriptor setDepthCompareFunction(int handle, int depthCompareFunction) -> void */
void mtl_mtldepthstencildescriptor_set_depth_compare_function(zval *handle, zval *depthCompareFunction);

/*@zep MTL\MTLDepthStencilDescriptor depthWriteEnabled(int handle) -> bool */
zend_long mtl_mtldepthstencildescriptor_depth_write_enabled(zval *handle);
/*@zep MTL\MTLDepthStencilDescriptor setDepthWriteEnabled(int handle, bool depthWriteEnabled) -> void */
void mtl_mtldepthstencildescriptor_set_depth_write_enabled(zval *handle, zval *depthWriteEnabled);

/*@zep MTL\MTLDepthStencilDescriptor label(int handle) -> var */
void mtl_mtldepthstencildescriptor_label(zval *return_value, zval *handle);
/*@zep MTL\MTLDepthStencilDescriptor setLabel(int handle, var label) -> void */
void mtl_mtldepthstencildescriptor_set_label(zval *handle, zval *label);

/*@audit partial MTL\MTLDepthStencilState wave A: label */
/*@audit factory MTL\MTLDepthStencilState MTLDevice::newDepthStencilStateWithDescriptor */

/*@zep MTL\MTLDepthStencilState label(int handle) -> var */
void mtl_mtldepthstencilstate_label(zval *return_value, zval *handle);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_DEPTHSTENCIL_H */
