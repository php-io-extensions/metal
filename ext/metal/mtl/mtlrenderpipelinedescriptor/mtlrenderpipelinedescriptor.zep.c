
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
#include "src/mtl-renderpipeline.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLRenderPipelineDescriptor, MTLRenderPipelineDescriptor, metal, mtl_mtlrenderpipelinedescriptor_mtlrenderpipelinedescriptor, metal_mtl_mtlrenderpipelinedescriptor_mtlrenderpipelinedescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, init)
{

	RETURN_LONG(mtl_mtlrenderpipelinedescriptor_init());
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, vertexFunction)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinedescriptor_vertex_function(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, setVertexFunction)
{
	zval *handle_param = NULL, *vertexFunction_param = NULL, _0, _1;
	zend_long handle, vertexFunction;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(vertexFunction)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &vertexFunction_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, vertexFunction);
	mtl_mtlrenderpipelinedescriptor_set_vertex_function(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, fragmentFunction)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinedescriptor_fragment_function(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, setFragmentFunction)
{
	zval *handle_param = NULL, *fragmentFunction_param = NULL, _0, _1;
	zend_long handle, fragmentFunction;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(fragmentFunction)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &fragmentFunction_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, fragmentFunction);
	mtl_mtlrenderpipelinedescriptor_set_fragment_function(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, vertexDescriptor)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinedescriptor_vertex_descriptor(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, setVertexDescriptor)
{
	zval *handle_param = NULL, *vertexDescriptor_param = NULL, _0, _1;
	zend_long handle, vertexDescriptor;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(vertexDescriptor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &vertexDescriptor_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, vertexDescriptor);
	mtl_mtlrenderpipelinedescriptor_set_vertex_descriptor(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, rasterSampleCount)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinedescriptor_raster_sample_count(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, setRasterSampleCount)
{
	zval *handle_param = NULL, *rasterSampleCount_param = NULL, _0, _1;
	zend_long handle, rasterSampleCount;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(rasterSampleCount)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &rasterSampleCount_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, rasterSampleCount);
	mtl_mtlrenderpipelinedescriptor_set_raster_sample_count(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, colorAttachments)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinedescriptor_color_attachments(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, label)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *handle_param = NULL, result, _0;
	zend_long handle;

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &handle_param);
	ZEPHIR_INIT_VAR(&result);
	ZVAL_LONG(&_0, handle);
	mtl_mtlrenderpipelinedescriptor_label(&result, &_0);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor, setLabel)
{
	zval *handle_param = NULL, *label = NULL, label_sub, _0;
	zend_long handle;

	ZVAL_UNDEF(&label_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_ZVAL(label)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &label);
	ZVAL_LONG(&_0, handle);
	mtl_mtlrenderpipelinedescriptor_set_label(&_0, label);
}

