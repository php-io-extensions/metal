
extern zend_class_entry *metal_mtl_window_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_Window);

PHP_METHOD(Metal_MTL_Window, create);
PHP_METHOD(Metal_MTL_Window, destroy);
PHP_METHOD(Metal_MTL_Window, setTitle);
PHP_METHOD(Metal_MTL_Window, show);
PHP_METHOD(Metal_MTL_Window, hide);
PHP_METHOD(Metal_MTL_Window, shouldClose);
PHP_METHOD(Metal_MTL_Window, getWidth);
PHP_METHOD(Metal_MTL_Window, getHeight);
PHP_METHOD(Metal_MTL_Window, attachDevice);
PHP_METHOD(Metal_MTL_Window, getLayer);
PHP_METHOD(Metal_MTL_Window, clear);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_create, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_destroy, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_settitle, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_show, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_hide, 0, 1, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_shouldclose, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_getwidth, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_getheight, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_attachdevice, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_getlayer, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_window_clear, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, window, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_window_method_entry) {
	PHP_ME(Metal_MTL_Window, create, arginfo_metal_mtl_window_create, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Window, destroy, arginfo_metal_mtl_window_destroy, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Window, setTitle, arginfo_metal_mtl_window_settitle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Window, show, arginfo_metal_mtl_window_show, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Window, hide, arginfo_metal_mtl_window_hide, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Window, shouldClose, arginfo_metal_mtl_window_shouldclose, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Window, getWidth, arginfo_metal_mtl_window_getwidth, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Window, getHeight, arginfo_metal_mtl_window_getheight, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Window, attachDevice, arginfo_metal_mtl_window_attachdevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Window, getLayer, arginfo_metal_mtl_window_getlayer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_Window, clear, arginfo_metal_mtl_window_clear, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
