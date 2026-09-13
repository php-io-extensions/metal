
extern zend_class_entry *metal_mtl_mtltexture_mtltexture_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_MTLTexture_MTLTexture);

PHP_METHOD(Metal_MTL_MTLTexture_MTLTexture, width);
PHP_METHOD(Metal_MTL_MTLTexture_MTLTexture, height);
PHP_METHOD(Metal_MTL_MTLTexture_MTLTexture, pixelFormat);
PHP_METHOD(Metal_MTL_MTLTexture_MTLTexture, getBytesBytesPerRowFromRegionMipmapLevel);
PHP_METHOD(Metal_MTL_MTLTexture_MTLTexture, replaceRegionMipmapLevelWithBytesBytesPerRow);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtltexture_mtltexture_width, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtltexture_mtltexture_height, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtltexture_mtltexture_pixelformat, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtltexture_mtltexture_getbytesbytesperrowfromregionmipmaplevel, 0, 9, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bytesPerRow, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, depth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mipmapLevel, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtltexture_mtltexture_replaceregionmipmaplevelwithbytesbytesperrow, 0, 10, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, depth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mipmapLevel, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bytes, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, bytesPerRow, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_mtltexture_mtltexture_method_entry) {
	PHP_ME(Metal_MTL_MTLTexture_MTLTexture, width, arginfo_metal_mtl_mtltexture_mtltexture_width, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLTexture_MTLTexture, height, arginfo_metal_mtl_mtltexture_mtltexture_height, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLTexture_MTLTexture, pixelFormat, arginfo_metal_mtl_mtltexture_mtltexture_pixelformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLTexture_MTLTexture, getBytesBytesPerRowFromRegionMipmapLevel, arginfo_metal_mtl_mtltexture_mtltexture_getbytesbytesperrowfromregionmipmaplevel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLTexture_MTLTexture, replaceRegionMipmapLevelWithBytesBytesPerRow, arginfo_metal_mtl_mtltexture_mtltexture_replaceregionmipmaplevelwithbytesbytesperrow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
