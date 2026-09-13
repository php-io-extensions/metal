
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


ZEPHIR_INIT_CLASS(Metal_MTL_MTLVertexBufferLayoutDescriptor_MTLVertexBufferLayoutDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLVertexBufferLayoutDescriptor, MTLVertexBufferLayoutDescriptor, metal, mtl_mtlvertexbufferlayoutdescriptor_mtlvertexbufferlayoutdescriptor, metal_mtl_mtlvertexbufferlayoutdescriptor_mtlvertexbufferlayoutdescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLVertexBufferLayoutDescriptor_MTLVertexBufferLayoutDescriptor, stride)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlvertexbufferlayoutdescriptor_stride(&_0));
}

PHP_METHOD(Metal_MTL_MTLVertexBufferLayoutDescriptor_MTLVertexBufferLayoutDescriptor, setStride)
{
	zval *handle_param = NULL, *stride_param = NULL, _0, _1;
	zend_long handle, stride;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(stride)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &stride_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, stride);
	mtl_mtlvertexbufferlayoutdescriptor_set_stride(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLVertexBufferLayoutDescriptor_MTLVertexBufferLayoutDescriptor, stepFunction)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlvertexbufferlayoutdescriptor_step_function(&_0));
}

PHP_METHOD(Metal_MTL_MTLVertexBufferLayoutDescriptor_MTLVertexBufferLayoutDescriptor, setStepFunction)
{
	zval *handle_param = NULL, *stepFunction_param = NULL, _0, _1;
	zend_long handle, stepFunction;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(stepFunction)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &stepFunction_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, stepFunction);
	mtl_mtlvertexbufferlayoutdescriptor_set_step_function(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLVertexBufferLayoutDescriptor_MTLVertexBufferLayoutDescriptor, stepRate)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlvertexbufferlayoutdescriptor_step_rate(&_0));
}

PHP_METHOD(Metal_MTL_MTLVertexBufferLayoutDescriptor_MTLVertexBufferLayoutDescriptor, setStepRate)
{
	zval *handle_param = NULL, *stepRate_param = NULL, _0, _1;
	zend_long handle, stepRate;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(stepRate)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &stepRate_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, stepRate);
	mtl_mtlvertexbufferlayoutdescriptor_set_step_rate(&_0, &_1);
}

