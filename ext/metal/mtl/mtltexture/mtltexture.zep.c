
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
#include "src/mtl-texture.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLTexture_MTLTexture)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLTexture, MTLTexture, metal, mtl_mtltexture_mtltexture, metal_mtl_mtltexture_mtltexture_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLTexture_MTLTexture, width)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtltexture_width(&_0));
}

PHP_METHOD(Metal_MTL_MTLTexture_MTLTexture, height)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtltexture_height(&_0));
}

PHP_METHOD(Metal_MTL_MTLTexture_MTLTexture, pixelFormat)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtltexture_pixel_format(&_0));
}

PHP_METHOD(Metal_MTL_MTLTexture_MTLTexture, getBytesBytesPerRowFromRegionMipmapLevel)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *handle_param = NULL, *bytesPerRow_param = NULL, *x_param = NULL, *y_param = NULL, *z_param = NULL, *width_param = NULL, *height_param = NULL, *depth_param = NULL, *mipmapLevel_param = NULL, result, _0, _1, _2, _3, _4, _5, _6, _7, _8;
	zend_long handle, bytesPerRow, x, y, z, width, height, depth, mipmapLevel;

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZEND_PARSE_PARAMETERS_START(9, 9)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(bytesPerRow)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(z)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(depth)
		Z_PARAM_LONG(mipmapLevel)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 9, 0, &handle_param, &bytesPerRow_param, &x_param, &y_param, &z_param, &width_param, &height_param, &depth_param, &mipmapLevel_param);
	ZEPHIR_INIT_VAR(&result);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, bytesPerRow);
	ZVAL_LONG(&_2, x);
	ZVAL_LONG(&_3, y);
	ZVAL_LONG(&_4, z);
	ZVAL_LONG(&_5, width);
	ZVAL_LONG(&_6, height);
	ZVAL_LONG(&_7, depth);
	ZVAL_LONG(&_8, mipmapLevel);
	mtl_mtltexture_get_bytes_bytes_per_row_from_region_mipmap_level(&result, &_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLTexture_MTLTexture, replaceRegionMipmapLevelWithBytesBytesPerRow)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval bytes;
	zval *handle_param = NULL, *x_param = NULL, *y_param = NULL, *z_param = NULL, *width_param = NULL, *height_param = NULL, *depth_param = NULL, *mipmapLevel_param = NULL, *bytes_param = NULL, *bytesPerRow_param = NULL, _0, _1, _2, _3, _4, _5, _6, _7, _8;
	zend_long handle, x, y, z, width, height, depth, mipmapLevel, bytesPerRow, r = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&bytes);
	ZEND_PARSE_PARAMETERS_START(10, 10)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(z)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(depth)
		Z_PARAM_LONG(mipmapLevel)
		Z_PARAM_STR(bytes)
		Z_PARAM_LONG(bytesPerRow)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 10, 0, &handle_param, &x_param, &y_param, &z_param, &width_param, &height_param, &depth_param, &mipmapLevel_param, &bytes_param, &bytesPerRow_param);
	zephir_get_strval(&bytes, bytes_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, x);
	ZVAL_LONG(&_2, y);
	ZVAL_LONG(&_3, z);
	ZVAL_LONG(&_4, width);
	ZVAL_LONG(&_5, height);
	ZVAL_LONG(&_6, depth);
	ZVAL_LONG(&_7, mipmapLevel);
	ZVAL_LONG(&_8, bytesPerRow);
	r = mtl_mtltexture_replace_region_mipmap_level_with_bytes_bytes_per_row(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &bytes, &_8);
	RETURN_MM_BOOL(r == 1);
}

