
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

#include "metal-texture.h"
#include <stdint.h>
#include <stdlib.h>



/**
 * Offscreen MTLTexture (RGBA8Unorm) — headless render targets for engines/UIs.
 * Handles are opaque ints owned by the caller until release().
 */
ZEPHIR_INIT_CLASS(Metal_MTL_Texture)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL, Texture, metal, mtl_texture, metal_mtl_texture_method_entry, 0);

	return SUCCESS;
}

/**
 * @return int Opaque texture handle, or 0 on failure
 */
PHP_METHOD(Metal_MTL_Texture, create)
{
	zval *device_param = NULL, *width_param = NULL, *height_param = NULL;
	zend_long device, width, height, handle = 0;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(device)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &device_param, &width_param, &height_param);
	
			handle = (zend_long) mtl_texture_create_rgba8((uintptr_t) device, (int) width, (int) height);
		
	RETURN_LONG(handle);
}

PHP_METHOD(Metal_MTL_Texture, release)
{
	zval *texture_param = NULL;
	zend_long texture;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &texture_param);
	
			mtl_texture_release((uintptr_t) texture);
		
}

PHP_METHOD(Metal_MTL_Texture, getWidth)
{
	zval *texture_param = NULL;
	zend_long texture, w = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &texture_param);
	
			w = mtl_texture_get_width((uintptr_t) texture);
		
	RETURN_LONG(w);
}

PHP_METHOD(Metal_MTL_Texture, getHeight)
{
	zval *texture_param = NULL;
	zend_long texture, h = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &texture_param);
	
			h = mtl_texture_get_height((uintptr_t) texture);
		
	RETURN_LONG(h);
}

/**
 * GPU clear. RGBA components are integers 0..255.
 */
PHP_METHOD(Metal_MTL_Texture, clear)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, *queue_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL, *a_param = NULL, _0;
	zend_long texture, queue, r, g, b, a, ok = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(5, 6)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(queue)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(a)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 5, 1, &texture_param, &queue_param, &r_param, &g_param, &b_param, &a_param);
	if (!a_param) {
		a = 255;
	} else {
		}
	
			ok = mtl_texture_clear(
				(uintptr_t) texture,
				(uintptr_t) queue,
				((float) r) / 255.0f,
				((float) g) / 255.0f,
				((float) b) / 255.0f,
				((float) a) / 255.0f
			);
		
	ZEPHIR_INIT_VAR(&_0);
	if (ok) {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_BOOL(&_0, 1);
	} else {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_BOOL(&_0, 0);
	}
	RETURN_CCTOR(&_0);
}

/**
 * CPU write one RGBA8 pixel (0..255).
 */
PHP_METHOD(Metal_MTL_Texture, writePixel)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, *x_param = NULL, *y_param = NULL, *r_param = NULL, *g_param = NULL, *b_param = NULL, *a_param = NULL, _0;
	zend_long texture, x, y, r, g, b, a, ok = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(6, 7)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(r)
		Z_PARAM_LONG(g)
		Z_PARAM_LONG(b)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(a)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 6, 1, &texture_param, &x_param, &y_param, &r_param, &g_param, &b_param, &a_param);
	if (!a_param) {
		a = 255;
	} else {
		}
	
			ok = mtl_texture_write_pixel(
				(uintptr_t) texture,
				(int) x,
				(int) y,
				(unsigned char) (r < 0 ? 0 : (r > 255 ? 255 : r)),
				(unsigned char) (g < 0 ? 0 : (g > 255 ? 255 : g)),
				(unsigned char) (b < 0 ? 0 : (b > 255 ? 255 : b)),
				(unsigned char) (a < 0 ? 0 : (a > 255 ? 255 : a))
			);
		
	ZEPHIR_INIT_VAR(&_0);
	if (ok) {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_BOOL(&_0, 1);
	} else {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_BOOL(&_0, 0);
	}
	RETURN_CCTOR(&_0);
}

/**
 * CPU read one RGBA8 pixel as [r, g, b, a] ints 0..255, or empty array on failure.
 */
PHP_METHOD(Metal_MTL_Texture, readPixel)
{
	zval out;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *texture_param = NULL, *queue_param = NULL, *x_param = NULL, *y_param = NULL;
	zend_long texture, queue, x, y;

	ZVAL_UNDEF(&out);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(queue)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &texture_param, &queue_param, &x_param, &y_param);
	ZEPHIR_INIT_VAR(&out);
	array_init(&out);
	
			unsigned char r = 0, g = 0, b = 0, a = 0;
			if (mtl_texture_read_pixel((uintptr_t) texture, (uintptr_t) queue, (int) x, (int) y, &r, &g, &b, &a)) {
				array_init(&out);
				add_next_index_long(&out, (zend_long) r);
				add_next_index_long(&out, (zend_long) g);
				add_next_index_long(&out, (zend_long) b);
				add_next_index_long(&out, (zend_long) a);
			} else {
				array_init(&out);
			}
		
	RETURN_CTOR(&out);
}

/**
 * Full RGBA8888 tightly packed bytes (row-major), or "" on failure.
 */
PHP_METHOD(Metal_MTL_Texture, readPixels)
{
	zval bytes;
	zval *texture_param = NULL, *queue_param = NULL;
	zend_long texture, queue;

	ZVAL_UNDEF(&bytes);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(queue)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &texture_param, &queue_param);
	
			int w = mtl_texture_get_width((uintptr_t) texture);
			int h = mtl_texture_get_height((uintptr_t) texture);
			if (w <= 0 || h <= 0) {
				ZVAL_EMPTY_STRING(&bytes);
			} else {
				size_t need = (size_t) w * (size_t) h * 4u;
				unsigned char *buf = (unsigned char *) emalloc(need);
				int n = mtl_texture_read_rgba8((uintptr_t) texture, (uintptr_t) queue, buf, (int) need);
				if (n <= 0) {
					efree(buf);
					ZVAL_EMPTY_STRING(&bytes);
				} else {
					ZVAL_STRINGL(&bytes, (char *) buf, n);
					efree(buf);
				}
			}
		
	RETURN_CTORW(&bytes);
}

