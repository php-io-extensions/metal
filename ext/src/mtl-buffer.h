#ifndef PHP_METAL_MTL_BUFFER_H
#define PHP_METAL_MTL_BUFFER_H

/*
 * Wave A partial of the MTLBuffer protocol (Metal's MTLBuffer.h).
 * Construction is MTLDevice::newBufferWithLengthOptions /
 * newBufferWithBytesLengthOptions (factory marker below).
 *
 * The raw `contents` pointer cannot cross into PHP as a pointer — it would
 * be an unguarded read/write primitive. Both accessors below send the one
 * declared `contents` message and then memcpy through a bounds-checked
 * window: [b length] is read only to validate the window (guards-in-glue
 * precedent, see scripts/check-parity.php GUARD_SELECTORS), and an
 * out-of-range request returns "" / false rather than touching memory.
 * A NULL `contents` is guarded as invalid too — belt and braces, not a
 * claim about any particular storage mode (on unified memory a
 * private-storage buffer does not necessarily return NULL).
 *
 * Storage-mode correctness is the caller's problem, per house policy:
 * this binding does not inspect storageMode, does not stop you reading a
 * private buffer, and does not send didModifyRange: for you after a CPU
 * write to a managed one (that selector is not bound this wave).
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLBuffer wave A: length + guarded contents read/write */
/*@audit factory MTL\MTLBuffer MTLDevice::newBufferWithLengthOptions */

/*@zep MTL\MTLBuffer length(int handle) -> int */
zend_long mtl_mtlbuffer_length(zval *handle);

/*@zep MTL\MTLBuffer contentsBytes(int handle, int offset, int length) -> string */
void mtl_mtlbuffer_contents_bytes(zval *return_value, zval *handle, zval *offset, zval *length);

/*@zep MTL\MTLBuffer setContentsBytes(int handle, string bytes, int offset) -> bool */
zend_long mtl_mtlbuffer_set_contents_bytes(zval *handle, zval *bytes, zval *offset);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_BUFFER_H */
