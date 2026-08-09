
extern zend_class_entry *metal_mtl_input_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_Input);

PHP_METHOD(Metal_MTL_Input, keyDown);
PHP_METHOD(Metal_MTL_Input, mouseButtonDown);
PHP_METHOD(Metal_MTL_Input, mousePosition);
PHP_METHOD(Metal_MTL_Input, mouseScrollDelta);
PHP_METHOD(Metal_MTL_Input, gamepadCount);
PHP_METHOD(Metal_MTL_Input, gamepadName);
PHP_METHOD(Metal_MTL_Input, gamepadButtonDown);
PHP_METHOD(Metal_MTL_Input, gamepadAxis);
PHP_METHOD(Metal_MTL_Input, gamepadState);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_input_keydown, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, keycode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_input_mousebuttondown, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_input_mouseposition, 0, 0, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_input_mousescrolldelta, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_input_gamepadcount, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_input_gamepadname, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_input_gamepadbuttondown, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_input_gamepadaxis, 0, 2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, axis, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_input_gamepadstate, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_input_method_entry) {
	PHP_ME(Metal_MTL_Input, keyDown, arginfo_metal_mtl_input_keydown, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Input, mouseButtonDown, arginfo_metal_mtl_input_mousebuttondown, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Input, mousePosition, arginfo_metal_mtl_input_mouseposition, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Input, mouseScrollDelta, arginfo_metal_mtl_input_mousescrolldelta, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Input, gamepadCount, arginfo_metal_mtl_input_gamepadcount, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Input, gamepadName, arginfo_metal_mtl_input_gamepadname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Input, gamepadButtonDown, arginfo_metal_mtl_input_gamepadbuttondown, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Input, gamepadAxis, arginfo_metal_mtl_input_gamepadaxis, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Input, gamepadState, arginfo_metal_mtl_input_gamepadstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
