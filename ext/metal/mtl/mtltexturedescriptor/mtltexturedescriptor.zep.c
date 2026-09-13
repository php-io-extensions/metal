
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


ZEPHIR_INIT_CLASS(Metal_MTL_MTLTextureDescriptor_MTLTextureDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLTextureDescriptor, MTLTextureDescriptor, metal, mtl_mtltexturedescriptor_mtltexturedescriptor, metal_mtl_mtltexturedescriptor_mtltexturedescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLTextureDescriptor_MTLTextureDescriptor, texture2DDescriptorWithPixelFormatWidthHeightMipmapped)
{
	zend_bool mipmapped;
	zval *pixelFormat_param = NULL, *width_param = NULL, *height_param = NULL, *mipmapped_param = NULL, _0, _1, _2, _3;
	zend_long pixelFormat, width, height;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(pixelFormat)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_BOOL(mipmapped)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &pixelFormat_param, &width_param, &height_param, &mipmapped_param);
	ZVAL_LONG(&_0, pixelFormat);
	ZVAL_LONG(&_1, width);
	ZVAL_LONG(&_2, height);
	ZVAL_BOOL(&_3, (mipmapped ? 1 : 0));
	RETURN_LONG(mtl_mtltexturedescriptor_texture2d_descriptor_with_pixel_format_width_height_mipmapped(&_0, &_1, &_2, &_3));
}

PHP_METHOD(Metal_MTL_MTLTextureDescriptor_MTLTextureDescriptor, usage)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtltexturedescriptor_usage(&_0));
}

PHP_METHOD(Metal_MTL_MTLTextureDescriptor_MTLTextureDescriptor, setUsage)
{
	zval *handle_param = NULL, *usage_param = NULL, _0, _1;
	zend_long handle, usage;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(usage)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &usage_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, usage);
	mtl_mtltexturedescriptor_set_usage(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLTextureDescriptor_MTLTextureDescriptor, storageMode)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtltexturedescriptor_storage_mode(&_0));
}

PHP_METHOD(Metal_MTL_MTLTextureDescriptor_MTLTextureDescriptor, setStorageMode)
{
	zval *handle_param = NULL, *storageMode_param = NULL, _0, _1;
	zend_long handle, storageMode;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(storageMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &storageMode_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, storageMode);
	mtl_mtltexturedescriptor_set_storage_mode(&_0, &_1);
}

