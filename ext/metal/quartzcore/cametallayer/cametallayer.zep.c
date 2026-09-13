
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
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Metal_QuartzCore_CAMetalLayer_CAMetalLayer)
{
	ZEPHIR_REGISTER_CLASS(Metal\\QuartzCore\\CAMetalLayer, CAMetalLayer, metal, quartzcore_cametallayer_cametallayer, metal_quartzcore_cametallayer_cametallayer_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, init)
{

	RETURN_LONG(mtl_cametallayer_init());
}

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, device)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_cametallayer_device(&_0));
}

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setDevice)
{
	zval *handle_param = NULL, *device_param = NULL, _0, _1;
	zend_long handle, device;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &device_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, device);
	mtl_cametallayer_set_device(&_0, &_1);
}

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, pixelFormat)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_cametallayer_pixel_format(&_0));
}

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setPixelFormat)
{
	zval *handle_param = NULL, *pixelFormat_param = NULL, _0, _1;
	zend_long handle, pixelFormat;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(pixelFormat)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &pixelFormat_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, pixelFormat);
	mtl_cametallayer_set_pixel_format(&_0, &_1);
}

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, drawableSize)
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
	mtl_cametallayer_drawable_size(&result, &_0);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setDrawableSize)
{
	double width, height;
	zval *handle_param = NULL, *width_param = NULL, *height_param = NULL, _0, _1, _2;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_ZVAL(width)
		Z_PARAM_ZVAL(height)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &handle_param, &width_param, &height_param);
	width = zephir_get_doubleval(width_param);
	height = zephir_get_doubleval(height_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_DOUBLE(&_1, width);
	ZVAL_DOUBLE(&_2, height);
	mtl_cametallayer_set_drawable_size(&_0, &_1, &_2);
}

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, framebufferOnly)
{
	zval *handle_param = NULL, _0;
	zend_long handle, r = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	r = mtl_cametallayer_framebuffer_only(&_0);
	RETURN_BOOL(r == 1);
}

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setFramebufferOnly)
{
	zend_bool framebufferOnly;
	zval *handle_param = NULL, *framebufferOnly_param = NULL, _0, _1;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_BOOL(framebufferOnly)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &framebufferOnly_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_BOOL(&_1, (framebufferOnly ? 1 : 0));
	mtl_cametallayer_set_framebuffer_only(&_0, &_1);
}

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, nextDrawable)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_cametallayer_next_drawable(&_0));
}

