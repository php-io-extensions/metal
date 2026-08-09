
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"

#include "metal-window.h"
#include <stdint.h>



/**
 * NSWindow + CAMetalLayer surface.
 * Handles are opaque ints owned by the caller until destroy().
 */
ZEPHIR_INIT_CLASS(Metal_MTL_Window)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL, Window, metal, mtl_window, metal_mtl_window_method_entry, 0);

	return SUCCESS;
}

/**
 * @return int Opaque window handle, or 0 on failure
 */
PHP_METHOD(Metal_MTL_Window, create)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long width, height, handle = 0;
	zval *title_param = NULL, *width_param = NULL, *height_param = NULL;
	zval title;

	ZVAL_UNDEF(&title);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(title)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &title_param, &width_param, &height_param);
	zephir_get_strval(&title, title_param);
	
            handle = (zend_long) mtl_window_create(Z_STRVAL(title), (int) width, (int) height);
        
	RETURN_MM_LONG(handle);
}

PHP_METHOD(Metal_MTL_Window, destroy)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            mtl_window_destroy((uintptr_t) window);
        
}

PHP_METHOD(Metal_MTL_Window, setTitle)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval title;
	zval *window_param = NULL, *title_param = NULL;
	zend_long window;

	ZVAL_UNDEF(&title);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_STR(title)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &window_param, &title_param);
	zephir_get_strval(&title, title_param);
	
            mtl_window_set_title((uintptr_t) window, Z_STRVAL(title));
        
	ZEPHIR_MM_RESTORE();
}

PHP_METHOD(Metal_MTL_Window, show)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            mtl_window_show((uintptr_t) window);
        
}

PHP_METHOD(Metal_MTL_Window, hide)
{
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            mtl_window_hide((uintptr_t) window);
        
}

PHP_METHOD(Metal_MTL_Window, shouldClose)
{
	zend_bool result = 0;
	zval *window_param = NULL;
	zend_long window;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            result = mtl_window_should_close((uintptr_t) window) == 1;
        
	RETURN_BOOL(result);
}

PHP_METHOD(Metal_MTL_Window, getWidth)
{
	zval *window_param = NULL;
	zend_long window, value = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            value = (zend_long) mtl_window_get_width((uintptr_t) window);
        
	RETURN_LONG(value);
}

PHP_METHOD(Metal_MTL_Window, getHeight)
{
	zval *window_param = NULL;
	zend_long window, value = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            value = (zend_long) mtl_window_get_height((uintptr_t) window);
        
	RETURN_LONG(value);
}

PHP_METHOD(Metal_MTL_Window, attachDevice)
{
	zend_bool result = 0;
	zval *window_param = NULL, *device_param = NULL;
	zend_long window, device;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &window_param, &device_param);
	
            result = mtl_window_attach_device((uintptr_t) window, (uintptr_t) device) == 1;
        
	RETURN_BOOL(result);
}

/**
 * @return int Opaque CAMetalLayer pointer, or 0
 */
PHP_METHOD(Metal_MTL_Window, getLayer)
{
	zval *window_param = NULL;
	zend_long window, handle = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &window_param);
	
            handle = (zend_long) mtl_window_get_layer((uintptr_t) window);
        
	RETURN_LONG(handle);
}

/**
 * Clear the drawable to RGBA (0..255 components) and present.
 */
PHP_METHOD(Metal_MTL_Window, clear)
{
	zend_bool result = 0;
	zval *window_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL, *a_param = NULL;
	zend_long window, r, g, b, a;

	ZEND_PARSE_PARAMETERS_START(4, 5)
		Z_PARAM_LONG(window)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(a)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 1, &window_param, &r_param, &g_param, &b_param, &a_param);
	if (!a_param) {
		a = 255;
	} else {
		}
	
            result = mtl_window_clear(
                (uintptr_t) window,
                ((float) r) / 255.0f,
                ((float) g) / 255.0f,
                ((float) b) / 255.0f,
                ((float) a) / 255.0f
            ) == 1;
        
	RETURN_BOOL(result);
}

