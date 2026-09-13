#ifndef PHP_METAL_MTL_LIBRARY_H
#define PHP_METAL_MTL_LIBRARY_H

/*
 * Wave A partials of the MTLLibrary and MTLFunction protocols, both
 * declared in Metal's MTLLibrary.h — same-file companions bind in this
 * src pair per the house rule. MTLVertexAttribute, MTLAttribute,
 * MTLFunctionConstant and MTLCompileOptions also live in that header and
 * are untouched this wave (MTLCompileOptions deferred: every MTLDevice
 * compile entry point takes a nullable options object, and 0 = nil is
 * enough to compile from source).
 *
 * MTLLibrary is produced by MTLDevice::newLibraryWithSourceOptionsError,
 * the sanctioned NSError** pattern (returns {handle, error}); MTLFunction
 * by MTLLibrary::newFunctionWithName. functionNames crosses as a PHP list
 * of strings.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLLibrary wave A: newFunctionWithName, functionNames, label */
/*@audit factory MTL\MTLLibrary MTLDevice::newLibraryWithSourceOptionsError */

/*@zep MTL\MTLLibrary newFunctionWithName(int handle, string functionName) -> int */
zend_long mtl_mtllibrary_new_function_with_name(zval *handle, zval *functionName);

/*@zep MTL\MTLLibrary functionNames(int handle) -> array */
void mtl_mtllibrary_function_names(zval *return_value, zval *handle);

/*@zep MTL\MTLLibrary label(int handle) -> var */
void mtl_mtllibrary_label(zval *return_value, zval *handle);
/*@zep MTL\MTLLibrary setLabel(int handle, var label) -> void */
void mtl_mtllibrary_set_label(zval *handle, zval *label);

/*@audit partial MTL\MTLFunction wave A: name, functionType, label */
/*@audit factory MTL\MTLFunction MTLLibrary::newFunctionWithName */

/*@zep MTL\MTLFunction name(int handle) -> string */
void mtl_mtlfunction_name(zval *return_value, zval *handle);

/*@zep MTL\MTLFunction functionType(int handle) -> int */
zend_long mtl_mtlfunction_function_type(zval *handle);

/*@zep MTL\MTLFunction label(int handle) -> var */
void mtl_mtlfunction_label(zval *return_value, zval *handle);
/*@zep MTL\MTLFunction setLabel(int handle, var label) -> void */
void mtl_mtlfunction_set_label(zval *handle, zval *label);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_LIBRARY_H */
