
extern zend_class_entry *metal_mtl_texture_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_Texture);

PHP_METHOD(Metal_MTL_Texture, create);
PHP_METHOD(Metal_MTL_Texture, release);
PHP_METHOD(Metal_MTL_Texture, getWidth);
PHP_METHOD(Metal_MTL_Texture, getHeight);
PHP_METHOD(Metal_MTL_Texture, clear);
PHP_METHOD(Metal_MTL_Texture, writePixel);
PHP_METHOD(Metal_MTL_Texture, fillRect);
PHP_METHOD(Metal_MTL_Texture, readPixel);
PHP_METHOD(Metal_MTL_Texture, readPixels);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_texture_create, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_texture_release, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_texture_getwidth, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_texture_getheight, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_texture_clear, 0, 5, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, queue, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_texture_writepixel, 0, 6, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_texture_fillrect, 0, 8, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_texture_readpixel, 0, 4, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, queue, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_texture_readpixels, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, queue, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_texture_method_entry) {
	PHP_ME(Metal_MTL_Texture, create, arginfo_metal_mtl_texture_create, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Texture, release, arginfo_metal_mtl_texture_release, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Texture, getWidth, arginfo_metal_mtl_texture_getwidth, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Texture, getHeight, arginfo_metal_mtl_texture_getheight, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Texture, clear, arginfo_metal_mtl_texture_clear, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Texture, writePixel, arginfo_metal_mtl_texture_writepixel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Texture, fillRect, arginfo_metal_mtl_texture_fillrect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Texture, readPixel, arginfo_metal_mtl_texture_readpixel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Texture, readPixels, arginfo_metal_mtl_texture_readpixels, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
