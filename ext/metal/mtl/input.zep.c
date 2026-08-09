
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

#include "metal-input.h"
#include <stdint.h>



/**
 * Keyboard / mouse / gamepad queries over AppKit + GameController (0.7.2+).
 * Call App::poll() each frame so scroll deltas reset and events drain.
 */
ZEPHIR_INIT_CLASS(Metal_MTL_Input)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL, Input, metal, mtl_input, metal_mtl_input_method_entry, 0);

	return SUCCESS;
}

/**
 * @return bool true if macOS virtual key code is currently down
 */
PHP_METHOD(Metal_MTL_Input, keyDown)
{
	zend_bool result = 0;
	zval *keycode_param = NULL;
	zend_long keycode;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(keycode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &keycode_param);
	
            result = mtl_input_key_down((int) keycode) == 1;
        
	RETURN_BOOL(result);
}

/**
 * Mouse button: 0=left, 1=right, 2=middle.
 */
PHP_METHOD(Metal_MTL_Input, mouseButtonDown)
{
	zend_bool result = 0;
	zval *button_param = NULL;
	zend_long button;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &button_param);
	
            result = mtl_input_mouse_button_down((int) button) == 1;
        
	RETURN_BOOL(result);
}

/**
 * Mouse position as [x, y].
 * window=0 → screen coords; otherwise content-view local for that window handle.
 * Y grows upward (AppKit). Empty array on failure.
 */
PHP_METHOD(Metal_MTL_Input, mousePosition)
{
	zval out;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *window_param = NULL;
	zend_long window;

	ZVAL_UNDEF(&out);
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(window)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &window_param);
	if (!window_param) {
		window = 0;
	} else {
		}
	ZEPHIR_INIT_VAR(&out);
	array_init(&out);
	
            double x = 0.0, y = 0.0;
            if (mtl_input_mouse_position((uintptr_t) window, &x, &y)) {
                array_init(&out);
                add_next_index_double(&out, x);
                add_next_index_double(&out, y);
            } else {
                array_init(&out);
            }
        
	RETURN_CTOR(&out);
}

/**
 * Scroll deltas since the last App::poll() begin as [dx, dy].
 */
PHP_METHOD(Metal_MTL_Input, mouseScrollDelta)
{
	zval out;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

	ZVAL_UNDEF(&out);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&out);
	array_init(&out);
	
            double dx = 0.0, dy = 0.0;
            mtl_input_mouse_scroll_delta(&dx, &dy);
            array_init(&out);
            add_next_index_double(&out, dx);
            add_next_index_double(&out, dy);
        
	RETURN_CTOR(&out);
}

PHP_METHOD(Metal_MTL_Input, gamepadCount)
{
	zend_long n = 0;
	
            n = mtl_input_gamepad_count();
        
	RETURN_LONG(n);
}

/**
 * @return string Product / vendor name, or "" if missing
 */
PHP_METHOD(Metal_MTL_Input, gamepadName)
{
	zval name;
	zval *index_param = NULL;
	zend_long index;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &index_param);
	
            char buf[256];
            buf[0] = '\0';
            if (mtl_input_gamepad_name((int) index, buf, (int) sizeof(buf))) {
                ZVAL_STRING(&name, buf);
            } else {
                ZVAL_STRING(&name, "");
            }
        
	RETURN_CTORW(&name);
}

/**
 * Gamepad digital button (see metal-input.h layout).
 */
PHP_METHOD(Metal_MTL_Input, gamepadButtonDown)
{
	zend_bool result = 0;
	zval *index_param = NULL, *button_param = NULL;
	zend_long index, button;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(index)
		Z_PARAM_LONG(button)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &index_param, &button_param);
	
            result = mtl_input_gamepad_button_down((int) index, (int) button) == 1;
        
	RETURN_BOOL(result);
}

/**
 * Gamepad axis (sticks -1..1, triggers 0..1).
 */
PHP_METHOD(Metal_MTL_Input, gamepadAxis)
{
	double value = 0;
	zval *index_param = NULL, *axis_param = NULL;
	zend_long index, axis;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(index)
		Z_PARAM_LONG(axis)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &index_param, &axis_param);
	
            value = (double) mtl_input_gamepad_axis((int) index, (int) axis);
        
	RETURN_DOUBLE(value);
}

/**
 * Snapshot: ["name" => string, "buttons" => int[15], "axes" => float[6]] or [] if missing.
 */
PHP_METHOD(Metal_MTL_Input, gamepadState)
{
	zval out;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *index_param = NULL;
	zend_long index;

	ZVAL_UNDEF(&out);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &index_param);
	ZEPHIR_INIT_VAR(&out);
	array_init(&out);
	
            char buf[256];
            buf[0] = '\0';
            if (!mtl_input_gamepad_name((int) index, buf, (int) sizeof(buf))) {
                array_init(&out);
            } else {
                zval buttons, axes;
                int i;
                array_init(&out);
                add_assoc_string(&out, "name", buf);
                array_init(&buttons);
                for (i = 0; i < 15; i++) {
                    add_next_index_long(&buttons, mtl_input_gamepad_button_down((int) index, i) ? 1 : 0);
                }
                add_assoc_zval(&out, "buttons", &buttons);
                array_init(&axes);
                for (i = 0; i < 6; i++) {
                    add_next_index_double(&axes, (double) mtl_input_gamepad_axis((int) index, i));
                }
                add_assoc_zval(&out, "axes", &axes);
            }
        
	RETURN_CTOR(&out);
}

