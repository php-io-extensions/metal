
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
#include "src/ca-metallayer.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_QuartzCore_CAMetalDrawable_CAMetalDrawable)
{
	ZEPHIR_REGISTER_CLASS(Metal\\QuartzCore\\CAMetalDrawable, CAMetalDrawable, metal, quartzcore_cametaldrawable_cametaldrawable, metal_quartzcore_cametaldrawable_cametaldrawable_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_QuartzCore_CAMetalDrawable_CAMetalDrawable, texture)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_cametaldrawable_texture(&_0));
}

PHP_METHOD(Metal_QuartzCore_CAMetalDrawable_CAMetalDrawable, layer)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_cametaldrawable_layer(&_0));
}

