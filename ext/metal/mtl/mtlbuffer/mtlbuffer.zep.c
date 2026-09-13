
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "src/mtl-buffer.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLBuffer_MTLBuffer)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLBuffer, MTLBuffer, metal, mtl_mtlbuffer_mtlbuffer, metal_mtl_mtlbuffer_mtlbuffer_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLBuffer_MTLBuffer, length)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlbuffer_length(&_0));
}

PHP_METHOD(Metal_MTL_MTLBuffer_MTLBuffer, contentsBytes)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *handle_param = NULL, *offset_param = NULL, *length_param = NULL, result, _0, _1, _2;
	zend_long handle, offset, length;

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(offset)
		Z_PARAM_LONG(length)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &handle_param, &offset_param, &length_param);
	ZEPHIR_INIT_VAR(&result);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, offset);
	ZVAL_LONG(&_2, length);
	mtl_mtlbuffer_contents_bytes(&result, &_0, &_1, &_2);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLBuffer_MTLBuffer, setContentsBytes)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval bytes;
	zval *handle_param = NULL, *bytes_param = NULL, *offset_param = NULL, _0, _1;
	zend_long handle, offset, r = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&bytes);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_STR(bytes)
		Z_PARAM_LONG(offset)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &handle_param, &bytes_param, &offset_param);
	zephir_get_strval(&bytes, bytes_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, offset);
	r = mtl_mtlbuffer_set_contents_bytes(&_0, &bytes, &_1);
	RETURN_MM_BOOL(r == 1);
}

