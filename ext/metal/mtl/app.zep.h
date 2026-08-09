
extern zend_class_entry *metal_mtl_app_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_App);

PHP_METHOD(Metal_MTL_App, init);
PHP_METHOD(Metal_MTL_App, poll);
PHP_METHOD(Metal_MTL_App, run);
PHP_METHOD(Metal_MTL_App, terminate);
PHP_METHOD(Metal_MTL_App, shouldQuit);
PHP_METHOD(Metal_MTL_App, resetQuit);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_app_init, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_app_poll, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_app_run, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_app_terminate, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_app_shouldquit, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_app_resetquit, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_app_method_entry) {
	PHP_ME(Metal_MTL_App, init, arginfo_metal_mtl_app_init, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_App, poll, arginfo_metal_mtl_app_poll, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_App, run, arginfo_metal_mtl_app_run, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_App, terminate, arginfo_metal_mtl_app_terminate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_App, shouldQuit, arginfo_metal_mtl_app_shouldquit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_App, resetQuit, arginfo_metal_mtl_app_resetquit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
