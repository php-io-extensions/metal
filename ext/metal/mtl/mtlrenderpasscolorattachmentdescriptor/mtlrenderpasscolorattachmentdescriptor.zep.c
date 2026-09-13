
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
#include "src/mtl-renderpass.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLRenderPassColorAttachmentDescriptor_MTLRenderPassColorAttachmentDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLRenderPassColorAttachmentDescriptor, MTLRenderPassColorAttachmentDescriptor, metal, mtl_mtlrenderpasscolorattachmentdescriptor_mtlrenderpasscolorattachmentdescriptor, metal_mtl_mtlrenderpasscolorattachmentdescriptor_mtlrenderpasscolorattachmentdescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLRenderPassColorAttachmentDescriptor_MTLRenderPassColorAttachmentDescriptor, clearColor)
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
	mtl_mtlrenderpasscolorattachmentdescriptor_clear_color(&result, &_0);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLRenderPassColorAttachmentDescriptor_MTLRenderPassColorAttachmentDescriptor, setClearColor)
{
	double red, green, blue, alpha;
	zval *handle_param = NULL, *red_param = NULL, *green_param = NULL, *blue_param = NULL, *alpha_param = NULL, _0, _1, _2, _3, _4;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(handle)
		Z_PARAM_ZVAL(red)
		Z_PARAM_ZVAL(green)
		Z_PARAM_ZVAL(blue)
		Z_PARAM_ZVAL(alpha)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &handle_param, &red_param, &green_param, &blue_param, &alpha_param);
	red = zephir_get_doubleval(red_param);
	green = zephir_get_doubleval(green_param);
	blue = zephir_get_doubleval(blue_param);
	alpha = zephir_get_doubleval(alpha_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_DOUBLE(&_1, red);
	ZVAL_DOUBLE(&_2, green);
	ZVAL_DOUBLE(&_3, blue);
	ZVAL_DOUBLE(&_4, alpha);
	mtl_mtlrenderpasscolorattachmentdescriptor_set_clear_color(&_0, &_1, &_2, &_3, &_4);
}

