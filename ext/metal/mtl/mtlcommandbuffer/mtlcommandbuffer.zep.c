
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
#include "src/mtl-commandbuffer.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLCommandBuffer_MTLCommandBuffer)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLCommandBuffer, MTLCommandBuffer, metal, mtl_mtlcommandbuffer_mtlcommandbuffer, metal_mtl_mtlcommandbuffer_mtlcommandbuffer_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLCommandBuffer_MTLCommandBuffer, renderCommandEncoderWithDescriptor)
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
	RETURN_LONG(mtl_mtlcommandbuffer_render_command_encoder_with_descriptor(&_0, &_1));
}

PHP_METHOD(Metal_MTL_MTLCommandBuffer_MTLCommandBuffer, computeCommandEncoder)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlcommandbuffer_compute_command_encoder(&_0));
}

PHP_METHOD(Metal_MTL_MTLCommandBuffer_MTLCommandBuffer, blitCommandEncoder)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlcommandbuffer_blit_command_encoder(&_0));
}

PHP_METHOD(Metal_MTL_MTLCommandBuffer_MTLCommandBuffer, presentDrawable)
{
	zval *handle_param = NULL, *drawable_param = NULL, _0, _1;
	zend_long handle, drawable;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(drawable)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &drawable_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, drawable);
	mtl_mtlcommandbuffer_present_drawable(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLCommandBuffer_MTLCommandBuffer, commit)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	mtl_mtlcommandbuffer_commit(&_0);
}

PHP_METHOD(Metal_MTL_MTLCommandBuffer_MTLCommandBuffer, waitUntilCompleted)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	mtl_mtlcommandbuffer_wait_until_completed(&_0);
}

PHP_METHOD(Metal_MTL_MTLCommandBuffer_MTLCommandBuffer, status)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlcommandbuffer_status(&_0));
}

PHP_METHOD(Metal_MTL_MTLCommandBuffer_MTLCommandBuffer, error)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlcommandbuffer_error(&_0));
}

