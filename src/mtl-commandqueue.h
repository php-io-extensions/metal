#ifndef PHP_METAL_MTL_COMMANDQUEUE_H
#define PHP_METAL_MTL_COMMANDQUEUE_H

/*
 * Slice-zero partial of the MTLCommandQueue protocol. Construction is
 * MTLDevice::newCommandQueue (factory marker below). commandBuffer is
 * the slice's path to encoding; label round-trips for debugging.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLCommandQueue slice zero: commandBuffer, label */
/*@audit factory MTL\MTLCommandQueue MTLDevice::newCommandQueue */

/*@zep MTL\MTLCommandQueue commandBuffer(int handle) -> int */
zend_long mtl_mtlcommandqueue_command_buffer(zval *handle);

/*@zep MTL\MTLCommandQueue label(int handle) -> var */
void mtl_mtlcommandqueue_label(zval *return_value, zval *handle);
/*@zep MTL\MTLCommandQueue setLabel(int handle, var label) -> void */
void mtl_mtlcommandqueue_set_label(zval *handle, zval *label);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_COMMANDQUEUE_H */
