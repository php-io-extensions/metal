
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
#include "src/mtl-depthstencil.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLDepthStencilDescriptor_MTLDepthStencilDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLDepthStencilDescriptor, MTLDepthStencilDescriptor, metal, mtl_mtldepthstencildescriptor_mtldepthstencildescriptor, metal_mtl_mtldepthstencildescriptor_mtldepthstencildescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLDepthStencilDescriptor_MTLDepthStencilDescriptor, init)
{

	RETURN_LONG(mtl_mtldepthstencildescriptor_init());
}

PHP_METHOD(Metal_MTL_MTLDepthStencilDescriptor_MTLDepthStencilDescriptor, depthCompareFunction)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtldepthstencildescriptor_depth_compare_function(&_0));
}

PHP_METHOD(Metal_MTL_MTLDepthStencilDescriptor_MTLDepthStencilDescriptor, setDepthCompareFunction)
{
	zval *handle_param = NULL, *depthCompareFunction_param = NULL, _0, _1;
	zend_long handle, depthCompareFunction;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(depthCompareFunction)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &depthCompareFunction_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, depthCompareFunction);
	mtl_mtldepthstencildescriptor_set_depth_compare_function(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLDepthStencilDescriptor_MTLDepthStencilDescriptor, depthWriteEnabled)
{
	zval *handle_param = NULL, _0;
	zend_long handle, r = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	r = mtl_mtldepthstencildescriptor_depth_write_enabled(&_0);
	RETURN_BOOL(r == 1);
}

PHP_METHOD(Metal_MTL_MTLDepthStencilDescriptor_MTLDepthStencilDescriptor, setDepthWriteEnabled)
{
	zend_bool depthWriteEnabled;
	zval *handle_param = NULL, *depthWriteEnabled_param = NULL, _0, _1;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_BOOL(depthWriteEnabled)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &depthWriteEnabled_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_BOOL(&_1, (depthWriteEnabled ? 1 : 0));
	mtl_mtldepthstencildescriptor_set_depth_write_enabled(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLDepthStencilDescriptor_MTLDepthStencilDescriptor, label)
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
	mtl_mtldepthstencildescriptor_label(&result, &_0);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLDepthStencilDescriptor_MTLDepthStencilDescriptor, setLabel)
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
	mtl_mtldepthstencildescriptor_set_label(&_0, label);
}

