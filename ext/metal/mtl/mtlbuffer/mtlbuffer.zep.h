
extern zend_class_entry *metal_mtl_mtlbuffer_mtlbuffer_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_MTLBuffer_MTLBuffer);

PHP_METHOD(Metal_MTL_MTLBuffer_MTLBuffer, length);
PHP_METHOD(Metal_MTL_MTLBuffer_MTLBuffer, contentsBytes);
PHP_METHOD(Metal_MTL_MTLBuffer_MTLBuffer, setContentsBytes);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlbuffer_mtlbuffer_length, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlbuffer_mtlbuffer_contentsbytes, 0, 3, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlbuffer_mtlbuffer_setcontentsbytes, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bytes, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_mtlbuffer_mtlbuffer_method_entry) {
	PHP_ME(Metal_MTL_MTLBuffer_MTLBuffer, length, arginfo_metal_mtl_mtlbuffer_mtlbuffer_length, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLBuffer_MTLBuffer, contentsBytes, arginfo_metal_mtl_mtlbuffer_mtlbuffer_contentsbytes, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLBuffer_MTLBuffer, setContentsBytes, arginfo_metal_mtl_mtlbuffer_mtlbuffer_setcontentsbytes, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
