
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
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLVertexDescriptor_MTLVertexDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLVertexDescriptor, MTLVertexDescriptor, metal, mtl_mtlvertexdescriptor_mtlvertexdescriptor, metal_mtl_mtlvertexdescriptor_mtlvertexdescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLVertexDescriptor_MTLVertexDescriptor, vertexDescriptor)
{

	RETURN_LONG(mtl_mtlvertexdescriptor_vertex_descriptor());
}

PHP_METHOD(Metal_MTL_MTLVertexDescriptor_MTLVertexDescriptor, attributes)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlvertexdescriptor_attributes(&_0));
}

PHP_METHOD(Metal_MTL_MTLVertexDescriptor_MTLVertexDescriptor, layouts)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlvertexdescriptor_layouts(&_0));
}

