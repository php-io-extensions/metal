
extern zend_class_entry *metal_bridge_bridge_ce;

ZEPHIR_INIT_CLASS(Metal_Bridge_Bridge);

PHP_METHOD(Metal_Bridge_Bridge, retain);
PHP_METHOD(Metal_Bridge_Bridge, release);
PHP_METHOD(Metal_Bridge_Bridge, isValid);
PHP_METHOD(Metal_Bridge_Bridge, className);
PHP_METHOD(Metal_Bridge_Bridge, pointerOf);
PHP_METHOD(Metal_Bridge_Bridge, adopt);
PHP_METHOD(Metal_Bridge_Bridge, errorDescription);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_bridge_bridge_retain, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_bridge_bridge_release, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_bridge_bridge_isvalid, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_metal_bridge_bridge_classname, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_bridge_bridge_pointerof, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_bridge_bridge_adopt, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, className, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, pointerBits, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_metal_bridge_bridge_errordescription, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_bridge_bridge_method_entry) {
	PHP_ME(Metal_Bridge_Bridge, retain, arginfo_metal_bridge_bridge_retain, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_Bridge_Bridge, release, arginfo_metal_bridge_bridge_release, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_Bridge_Bridge, isValid, arginfo_metal_bridge_bridge_isvalid, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_Bridge_Bridge, className, arginfo_metal_bridge_bridge_classname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_Bridge_Bridge, pointerOf, arginfo_metal_bridge_bridge_pointerof, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_Bridge_Bridge, adopt, arginfo_metal_bridge_bridge_adopt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_Bridge_Bridge, errorDescription, arginfo_metal_bridge_bridge_errordescription, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
