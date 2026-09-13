
extern zend_class_entry *metal_quartzcore_cametallayer_cametallayer_ce;

ZEPHIR_INIT_CLASS(Metal_QuartzCore_CAMetalLayer_CAMetalLayer);

PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, init);
PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, device);
PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setDevice);
PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, pixelFormat);
PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setPixelFormat);
PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, drawableSize);
PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setDrawableSize);
PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, framebufferOnly);
PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setFramebufferOnly);
PHP_METHOD(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, nextDrawable);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_quartzcore_cametallayer_cametallayer_init, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_quartzcore_cametallayer_cametallayer_device, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_quartzcore_cametallayer_cametallayer_setdevice, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, device, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_quartzcore_cametallayer_cametallayer_pixelformat, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_quartzcore_cametallayer_cametallayer_setpixelformat, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pixelFormat, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_quartzcore_cametallayer_cametallayer_drawablesize, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_quartzcore_cametallayer_cametallayer_setdrawablesize, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_quartzcore_cametallayer_cametallayer_framebufferonly, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_quartzcore_cametallayer_cametallayer_setframebufferonly, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, framebufferOnly, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_quartzcore_cametallayer_cametallayer_nextdrawable, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_quartzcore_cametallayer_cametallayer_method_entry) {
	PHP_ME(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, init, arginfo_metal_quartzcore_cametallayer_cametallayer_init, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, device, arginfo_metal_quartzcore_cametallayer_cametallayer_device, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setDevice, arginfo_metal_quartzcore_cametallayer_cametallayer_setdevice, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, pixelFormat, arginfo_metal_quartzcore_cametallayer_cametallayer_pixelformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setPixelFormat, arginfo_metal_quartzcore_cametallayer_cametallayer_setpixelformat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, drawableSize, arginfo_metal_quartzcore_cametallayer_cametallayer_drawablesize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setDrawableSize, arginfo_metal_quartzcore_cametallayer_cametallayer_setdrawablesize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, framebufferOnly, arginfo_metal_quartzcore_cametallayer_cametallayer_framebufferonly, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, setFramebufferOnly, arginfo_metal_quartzcore_cametallayer_cametallayer_setframebufferonly, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_QuartzCore_CAMetalLayer_CAMetalLayer, nextDrawable, arginfo_metal_quartzcore_cametallayer_cametallayer_nextdrawable, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
