
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
#include "src/mtl-computepipeline.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLComputePipelineState_MTLComputePipelineState)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLComputePipelineState, MTLComputePipelineState, metal, mtl_mtlcomputepipelinestate_mtlcomputepipelinestate, metal_mtl_mtlcomputepipelinestate_mtlcomputepipelinestate_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLComputePipelineState_MTLComputePipelineState, label)
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
	mtl_mtlcomputepipelinestate_label(&result, &_0);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLComputePipelineState_MTLComputePipelineState, maxTotalThreadsPerThreadgroup)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlcomputepipelinestate_max_total_threads_per_threadgroup(&_0));
}

PHP_METHOD(Metal_MTL_MTLComputePipelineState_MTLComputePipelineState, threadExecutionWidth)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlcomputepipelinestate_thread_execution_width(&_0));
}

