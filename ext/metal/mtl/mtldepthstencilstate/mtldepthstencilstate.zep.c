
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
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLDepthStencilState_MTLDepthStencilState)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLDepthStencilState, MTLDepthStencilState, metal, mtl_mtldepthstencilstate_mtldepthstencilstate, metal_mtl_mtldepthstencilstate_mtldepthstencilstate_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLDepthStencilState_MTLDepthStencilState, label)
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
	mtl_mtldepthstencilstate_label(&result, &_0);
	RETURN_CCTOR(&result);
}

