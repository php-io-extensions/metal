
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


ZEPHIR_INIT_CLASS(Metal_MTL_MTLVertexAttributeDescriptor_MTLVertexAttributeDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLVertexAttributeDescriptor, MTLVertexAttributeDescriptor, metal, mtl_mtlvertexattributedescriptor_mtlvertexattributedescriptor, metal_mtl_mtlvertexattributedescriptor_mtlvertexattributedescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLVertexAttributeDescriptor_MTLVertexAttributeDescriptor, format)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlvertexattributedescriptor_format(&_0));
}

PHP_METHOD(Metal_MTL_MTLVertexAttributeDescriptor_MTLVertexAttributeDescriptor, setFormat)
{
	zval *handle_param = NULL, *format_param = NULL, _0, _1;
	zend_long handle, format;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &format_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, format);
	mtl_mtlvertexattributedescriptor_set_format(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLVertexAttributeDescriptor_MTLVertexAttributeDescriptor, offset)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlvertexattributedescriptor_offset(&_0));
}

PHP_METHOD(Metal_MTL_MTLVertexAttributeDescriptor_MTLVertexAttributeDescriptor, setOffset)
{
	zval *handle_param = NULL, *offset_param = NULL, _0, _1;
	zend_long handle, offset;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(offset)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &offset_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, offset);
	mtl_mtlvertexattributedescriptor_set_offset(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLVertexAttributeDescriptor_MTLVertexAttributeDescriptor, bufferIndex)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlvertexattributedescriptor_buffer_index(&_0));
}

PHP_METHOD(Metal_MTL_MTLVertexAttributeDescriptor_MTLVertexAttributeDescriptor, setBufferIndex)
{
	zval *handle_param = NULL, *bufferIndex_param = NULL, _0, _1;
	zend_long handle, bufferIndex;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(bufferIndex)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &bufferIndex_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, bufferIndex);
	mtl_mtlvertexattributedescriptor_set_buffer_index(&_0, &_1);
}

