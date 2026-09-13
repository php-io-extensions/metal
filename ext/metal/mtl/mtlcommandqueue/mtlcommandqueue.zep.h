
extern zend_class_entry *metal_mtl_mtlcommandqueue_mtlcommandqueue_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_MTLCommandQueue_MTLCommandQueue);

PHP_METHOD(Metal_MTL_MTLCommandQueue_MTLCommandQueue, commandBuffer);
PHP_METHOD(Metal_MTL_MTLCommandQueue_MTLCommandQueue, label);
PHP_METHOD(Metal_MTL_MTLCommandQueue_MTLCommandQueue, setLabel);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlcommandqueue_mtlcommandqueue_commandbuffer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_metal_mtl_mtlcommandqueue_mtlcommandqueue_label, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlcommandqueue_mtlcommandqueue_setlabel, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_INFO(0, label)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_mtlcommandqueue_mtlcommandqueue_method_entry) {
	PHP_ME(Metal_MTL_MTLCommandQueue_MTLCommandQueue, commandBuffer, arginfo_metal_mtl_mtlcommandqueue_mtlcommandqueue_commandbuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLCommandQueue_MTLCommandQueue, label, arginfo_metal_mtl_mtlcommandqueue_mtlcommandqueue_label, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLCommandQueue_MTLCommandQueue, setLabel, arginfo_metal_mtl_mtlcommandqueue_mtlcommandqueue_setlabel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
