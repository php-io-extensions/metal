
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
#include "src/mtl-device.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLDevice_MTLDevice)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLDevice, MTLDevice, metal, mtl_mtldevice_mtldevice, metal_mtl_mtldevice_mtldevice_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, createSystemDefault)
{

	RETURN_LONG(mtl_mtldevice_create_system_default());
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, name)
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
	mtl_mtldevice_name(&result, &_0);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newCommandQueue)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtldevice_new_command_queue(&_0));
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newTextureWithDescriptor)
{
	zval *handle_param = NULL, *descriptor_param = NULL, _0, _1;
	zend_long handle, descriptor;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(descriptor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &descriptor_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, descriptor);
	RETURN_LONG(mtl_mtldevice_new_texture_with_descriptor(&_0, &_1));
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newBufferWithLengthOptions)
{
	zval *handle_param = NULL, *length_param = NULL, *options_param = NULL, _0, _1, _2;
	zend_long handle, length, options;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(length)
		Z_PARAM_LONG(options)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &handle_param, &length_param, &options_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, length);
	ZVAL_LONG(&_2, options);
	RETURN_LONG(mtl_mtldevice_new_buffer_with_length_options(&_0, &_1, &_2));
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newBufferWithBytesLengthOptions)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval bytes;
	zval *handle_param = NULL, *bytes_param = NULL, *options_param = NULL, _0, _1;
	zend_long handle, options;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&bytes);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_STR(bytes)
		Z_PARAM_LONG(options)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &handle_param, &bytes_param, &options_param);
	zephir_get_strval(&bytes, bytes_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, options);
	RETURN_MM_LONG(mtl_mtldevice_new_buffer_with_bytes_length_options(&_0, &bytes, &_1));
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newLibraryWithSourceOptionsError)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval source;
	zval *handle_param = NULL, *source_param = NULL, *options_param = NULL, result, _0, _1;
	zend_long handle, options;

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&source);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_STR(source)
		Z_PARAM_LONG(options)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &handle_param, &source_param, &options_param);
	zephir_get_strval(&source, source_param);
	ZEPHIR_INIT_VAR(&result);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, options);
	mtl_mtldevice_new_library_with_source_options_error(&result, &_0, &source, &_1);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newRenderPipelineStateWithDescriptorError)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *handle_param = NULL, *descriptor_param = NULL, result, _0, _1;
	zend_long handle, descriptor;

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(descriptor)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &handle_param, &descriptor_param);
	ZEPHIR_INIT_VAR(&result);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, descriptor);
	mtl_mtldevice_new_render_pipeline_state_with_descriptor_error(&result, &_0, &_1);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newComputePipelineStateWithFunctionError)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *handle_param = NULL, *computeFunction_param = NULL, result, _0, _1;
	zend_long handle, computeFunction;

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(computeFunction)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &handle_param, &computeFunction_param);
	ZEPHIR_INIT_VAR(&result);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, computeFunction);
	mtl_mtldevice_new_compute_pipeline_state_with_function_error(&result, &_0, &_1);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newDepthStencilStateWithDescriptor)
{
	zval *handle_param = NULL, *descriptor_param = NULL, _0, _1;
	zend_long handle, descriptor;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(descriptor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &descriptor_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, descriptor);
	RETURN_LONG(mtl_mtldevice_new_depth_stencil_state_with_descriptor(&_0, &_1));
}

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newSamplerStateWithDescriptor)
{
	zval *handle_param = NULL, *descriptor_param = NULL, _0, _1;
	zend_long handle, descriptor;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(descriptor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &descriptor_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, descriptor);
	RETURN_LONG(mtl_mtldevice_new_sampler_state_with_descriptor(&_0, &_1));
}

