#ifndef PHP_METAL_MTL_BRIDGE_H
#define PHP_METAL_MTL_BRIDGE_H

/*
 * The only glue in the extension: the handle registry, the raw-pointer
 * seam to sibling extensions (ext-appkit adopts our CAMetalLayer pointer;
 * ext-moltenvk will too), and an NSError description reader for the
 * sanctioned NSError** return pattern. Nothing here decides how Metal
 * is used.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@zep Bridge\Bridge retain(int handle) -> bool */
zend_long mtl_bridge_retain(zval *handle);
/*@zep Bridge\Bridge release(int handle) -> void */
void mtl_bridge_release(zval *handle);
/*@zep Bridge\Bridge isValid(int handle) -> bool */
zend_long mtl_bridge_is_valid(zval *handle);
/*@zep Bridge\Bridge className(int handle) -> var */
void mtl_bridge_class_name(zval *return_value, zval *handle);

/* ---- cross-extension pointer seam (spec §5.4) ---- */

/*@zep Bridge\Bridge pointerOf(int handle) -> int */
zend_long mtl_bridge_pointer_of(zval *handle);
/*@zep Bridge\Bridge adopt(string className, int pointerBits) -> int */
zend_long mtl_bridge_adopt(zval *className, zval *pointerBits);

/* ---- NSError reader (spec §5.3 pattern) ---- */

/*@zep Bridge\Bridge errorDescription(int handle) -> var */
void mtl_bridge_error_description(zval *return_value, zval *handle);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_BRIDGE_H */
