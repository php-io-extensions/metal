#ifndef PHP_METAL_MTL_COMMANDENCODER_H
#define PHP_METAL_MTL_COMMANDENCODER_H

/*
 * Slice-zero partial of the MTLCommandEncoder protocol — the base every
 * encoder conforms to. endEncoding binds here (declaring header), and
 * handles are untyped, so render/compute/blit encoder handles all pass
 * through these calls.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLCommandEncoder slice zero: endEncoding, label */
/*@audit factory MTL\MTLCommandEncoder MTLCommandBuffer::renderCommandEncoderWithDescriptor */

/*@zep MTL\MTLCommandEncoder endEncoding(int handle) -> void */
void mtl_mtlcommandencoder_end_encoding(zval *handle);

/*@zep MTL\MTLCommandEncoder label(int handle) -> var */
void mtl_mtlcommandencoder_label(zval *return_value, zval *handle);
/*@zep MTL\MTLCommandEncoder setLabel(int handle, var label) -> void */
void mtl_mtlcommandencoder_set_label(zval *handle, zval *label);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_COMMANDENCODER_H */
