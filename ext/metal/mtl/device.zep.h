
extern zend_class_entry *metal_mtl_device_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_Device);

PHP_METHOD(Metal_MTL_Device, createSystemDefault);
PHP_METHOD(Metal_MTL_Device, release);
PHP_METHOD(Metal_MTL_Device, newCommandQueue);
PHP_METHOD(Metal_MTL_Device, releaseCommandQueue);
PHP_METHOD(Metal_MTL_Device, getName);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_device_createsystemdefault, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_device_release, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_device_newcommandqueue, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_device_releasecommandqueue, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, queue, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_device_getname, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_device_method_entry) {
	PHP_ME(Metal_MTL_Device, createSystemDefault, arginfo_metal_mtl_device_createsystemdefault, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Device, release, arginfo_metal_mtl_device_release, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Device, newCommandQueue, arginfo_metal_mtl_device_newcommandqueue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Device, releaseCommandQueue, arginfo_metal_mtl_device_releasecommandqueue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Device, getName, arginfo_metal_mtl_device_getname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
