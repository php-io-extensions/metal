
extern zend_class_entry *metal_mtl_menu_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_Menu);

PHP_METHOD(Metal_MTL_Menu, installDefault);
PHP_METHOD(Metal_MTL_Menu, addItem);
PHP_METHOD(Metal_MTL_Menu, pollAction);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_menu_installdefault, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, appName, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_menu_additem, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, menuTitle, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, itemTitle, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, keyEquivalent, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, actionId, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_menu_pollaction, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_menu_method_entry) {
	PHP_ME(Metal_MTL_Menu, installDefault, arginfo_metal_mtl_menu_installdefault, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Menu, addItem, arginfo_metal_mtl_menu_additem, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Menu, pollAction, arginfo_metal_mtl_menu_pollaction, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
