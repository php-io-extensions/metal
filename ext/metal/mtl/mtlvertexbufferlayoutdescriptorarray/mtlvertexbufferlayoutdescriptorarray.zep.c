
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
#include "src/mtl-vertexdescriptor.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLVertexBufferLayoutDescriptorArray_MTLVertexBufferLayoutDescriptorArray)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLVertexBufferLayoutDescriptorArray, MTLVertexBufferLayoutDescriptorArray, metal, mtl_mtlvertexbufferlayoutdescriptorarray_mtlvertexbufferlayoutdescriptorarray, metal_mtl_mtlvertexbufferlayoutdescriptorarray_mtlvertexbufferlayoutdescriptorarray_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLVertexBufferLayoutDescriptorArray_MTLVertexBufferLayoutDescriptorArray, objectAtIndexedSubscript)
{
	zval *handle_param = NULL, *index_param = NULL, _0, _1;
	zend_long handle, index;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &index_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, index);
	RETURN_LONG(mtl_mtlvertexbufferlayoutdescriptorarray_object_at_indexed_subscript(&_0, &_1));
}

PHP_METHOD(Metal_MTL_MTLVertexBufferLayoutDescriptorArray_MTLVertexBufferLayoutDescriptorArray, setObjectAtIndexedSubscript)
{
	zval *handle_param = NULL, *bufferDesc_param = NULL, *index_param = NULL, _0, _1, _2;
	zend_long handle, bufferDesc, index;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(bufferDesc)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &handle_param, &bufferDesc_param, &index_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, bufferDesc);
	ZVAL_LONG(&_2, index);
	mtl_mtlvertexbufferlayoutdescriptorarray_set_object_at_indexed_subscript(&_0, &_1, &_2);
}

