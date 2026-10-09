/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 111ce10035ad7a19ba6ecd1eaacd18a1e825597c */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_CGSize___construct, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_CAMetalLayer___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_CAMetalLayer_layer, 0, 0, CAMetalLayer, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_CAMetalLayer_device, 0, 0, MTLDevice, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setDevice, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, MTLDevice, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_CAMetalLayer_pixelFormat, 0, 0, MTLPixelFormat, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setPixelFormat, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, pixelFormat, MTLPixelFormat, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_framebufferOnly, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setFramebufferOnly, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, framebufferOnly, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_CAMetalLayer_drawableSize, 0, 0, CGSize, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setDrawableSize, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, drawableSize, CGSize, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_CAMetalLayer_displaySyncEnabled arginfo_class_CAMetalLayer_framebufferOnly

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setDisplaySyncEnabled, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, displaySyncEnabled, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_contentsScale, 0, 0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setContentsScale, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, contentsScale, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_maximumDrawableCount, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setMaximumDrawableCount, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, maximumDrawableCount, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_CAMetalLayer_nextDrawable, 0, 0, CAMetalDrawable, 1)
ZEND_END_ARG_INFO()

#define arginfo_class_CAMetalLayer_allowsNextDrawableTimeout arginfo_class_CAMetalLayer_framebufferOnly

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setAllowsNextDrawableTimeout, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, allowsNextDrawableTimeout, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_CAMetalLayer_presentsWithTransaction arginfo_class_CAMetalLayer_framebufferOnly

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setPresentsWithTransaction, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, presentsWithTransaction, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_CAMetalLayer_wantsExtendedDynamicRangeContent arginfo_class_CAMetalLayer_framebufferOnly

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setWantsExtendedDynamicRangeContent, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, wantsExtendedDynamicRangeContent, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_colorspace, 0, 0, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setColorspace, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, colorspace, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_CAMetalLayer_EDRMetadata, 0, 0, CAEDRMetadata, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_setEDRMetadata, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, EDRMetadata, CAEDRMetadata, 1)
ZEND_END_ARG_INFO()

#define arginfo_class_CAMetalLayer_pointer arginfo_class_CAMetalLayer_maximumDrawableCount

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalLayer_fromPointer, 0, 1, IS_STATIC, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_CAMetalDrawable___construct arginfo_class_CAMetalLayer___construct

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_CAMetalDrawable_texture, 0, 0, MTLTexture, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_CAMetalDrawable_present, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_CAMetalDrawable_presentedTime arginfo_class_CAMetalLayer_contentsScale

#define arginfo_class_CAMetalDrawable_drawableID arginfo_class_CAMetalLayer_maximumDrawableCount

#define arginfo_class_CAMetalDrawable_pointer arginfo_class_CAMetalLayer_maximumDrawableCount

#define arginfo_class_CAMetalDrawable_fromPointer arginfo_class_CAMetalLayer_fromPointer

#define arginfo_class_CAEDRMetadata___construct arginfo_class_CAMetalLayer___construct

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_CAEDRMetadata_HDR10MetadataWithMinLuminanceMaxLuminanceOpticalOutputScale, 0, 3, CAEDRMetadata, 0)
	ZEND_ARG_TYPE_INFO(0, minNits, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, maxNits, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, opticalOutputScale, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_CAEDRMetadata_HLGMetadata, 0, 0, CAEDRMetadata, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_CAEDRMetadata_pointer arginfo_class_CAMetalLayer_maximumDrawableCount

#define arginfo_class_CAEDRMetadata_fromPointer arginfo_class_CAMetalLayer_fromPointer

ZEND_METHOD(CGSize, __construct);
ZEND_METHOD(CAMetalLayer, __construct);
ZEND_METHOD(CAMetalLayer, layer);
ZEND_METHOD(CAMetalLayer, device);
ZEND_METHOD(CAMetalLayer, setDevice);
ZEND_METHOD(CAMetalLayer, pixelFormat);
ZEND_METHOD(CAMetalLayer, setPixelFormat);
ZEND_METHOD(CAMetalLayer, framebufferOnly);
ZEND_METHOD(CAMetalLayer, setFramebufferOnly);
ZEND_METHOD(CAMetalLayer, drawableSize);
ZEND_METHOD(CAMetalLayer, setDrawableSize);
ZEND_METHOD(CAMetalLayer, displaySyncEnabled);
ZEND_METHOD(CAMetalLayer, setDisplaySyncEnabled);
ZEND_METHOD(CAMetalLayer, contentsScale);
ZEND_METHOD(CAMetalLayer, setContentsScale);
ZEND_METHOD(CAMetalLayer, maximumDrawableCount);
ZEND_METHOD(CAMetalLayer, setMaximumDrawableCount);
ZEND_METHOD(CAMetalLayer, nextDrawable);
ZEND_METHOD(CAMetalLayer, allowsNextDrawableTimeout);
ZEND_METHOD(CAMetalLayer, setAllowsNextDrawableTimeout);
ZEND_METHOD(CAMetalLayer, presentsWithTransaction);
ZEND_METHOD(CAMetalLayer, setPresentsWithTransaction);
ZEND_METHOD(CAMetalLayer, wantsExtendedDynamicRangeContent);
ZEND_METHOD(CAMetalLayer, setWantsExtendedDynamicRangeContent);
ZEND_METHOD(CAMetalLayer, colorspace);
ZEND_METHOD(CAMetalLayer, setColorspace);
ZEND_METHOD(CAMetalLayer, EDRMetadata);
ZEND_METHOD(CAMetalLayer, setEDRMetadata);
ZEND_METHOD(CAMetalLayer, pointer);
ZEND_METHOD(CAMetalLayer, fromPointer);
ZEND_METHOD(CAMetalDrawable, __construct);
ZEND_METHOD(CAMetalDrawable, texture);
ZEND_METHOD(CAMetalDrawable, present);
ZEND_METHOD(CAMetalDrawable, presentedTime);
ZEND_METHOD(CAMetalDrawable, drawableID);
ZEND_METHOD(CAMetalDrawable, pointer);
ZEND_METHOD(CAMetalDrawable, fromPointer);
ZEND_METHOD(CAEDRMetadata, __construct);
ZEND_METHOD(CAEDRMetadata, HDR10MetadataWithMinLuminanceMaxLuminanceOpticalOutputScale);
ZEND_METHOD(CAEDRMetadata, HLGMetadata);
ZEND_METHOD(CAEDRMetadata, pointer);
ZEND_METHOD(CAEDRMetadata, fromPointer);

static const zend_function_entry class_CGSize_methods[] = {
	ZEND_ME(CGSize, __construct, arginfo_class_CGSize___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_CAMetalLayer_methods[] = {
	ZEND_ME(CAMetalLayer, __construct, arginfo_class_CAMetalLayer___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(CAMetalLayer, layer, arginfo_class_CAMetalLayer_layer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(CAMetalLayer, device, arginfo_class_CAMetalLayer_device, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setDevice, arginfo_class_CAMetalLayer_setDevice, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, pixelFormat, arginfo_class_CAMetalLayer_pixelFormat, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setPixelFormat, arginfo_class_CAMetalLayer_setPixelFormat, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, framebufferOnly, arginfo_class_CAMetalLayer_framebufferOnly, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setFramebufferOnly, arginfo_class_CAMetalLayer_setFramebufferOnly, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, drawableSize, arginfo_class_CAMetalLayer_drawableSize, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setDrawableSize, arginfo_class_CAMetalLayer_setDrawableSize, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, displaySyncEnabled, arginfo_class_CAMetalLayer_displaySyncEnabled, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setDisplaySyncEnabled, arginfo_class_CAMetalLayer_setDisplaySyncEnabled, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, contentsScale, arginfo_class_CAMetalLayer_contentsScale, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setContentsScale, arginfo_class_CAMetalLayer_setContentsScale, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, maximumDrawableCount, arginfo_class_CAMetalLayer_maximumDrawableCount, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setMaximumDrawableCount, arginfo_class_CAMetalLayer_setMaximumDrawableCount, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, nextDrawable, arginfo_class_CAMetalLayer_nextDrawable, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, allowsNextDrawableTimeout, arginfo_class_CAMetalLayer_allowsNextDrawableTimeout, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setAllowsNextDrawableTimeout, arginfo_class_CAMetalLayer_setAllowsNextDrawableTimeout, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, presentsWithTransaction, arginfo_class_CAMetalLayer_presentsWithTransaction, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setPresentsWithTransaction, arginfo_class_CAMetalLayer_setPresentsWithTransaction, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, wantsExtendedDynamicRangeContent, arginfo_class_CAMetalLayer_wantsExtendedDynamicRangeContent, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setWantsExtendedDynamicRangeContent, arginfo_class_CAMetalLayer_setWantsExtendedDynamicRangeContent, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, colorspace, arginfo_class_CAMetalLayer_colorspace, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setColorspace, arginfo_class_CAMetalLayer_setColorspace, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, EDRMetadata, arginfo_class_CAMetalLayer_EDRMetadata, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, setEDRMetadata, arginfo_class_CAMetalLayer_setEDRMetadata, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, pointer, arginfo_class_CAMetalLayer_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalLayer, fromPointer, arginfo_class_CAMetalLayer_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_CAMetalDrawable_methods[] = {
	ZEND_ME(CAMetalDrawable, __construct, arginfo_class_CAMetalDrawable___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(CAMetalDrawable, texture, arginfo_class_CAMetalDrawable_texture, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalDrawable, present, arginfo_class_CAMetalDrawable_present, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalDrawable, presentedTime, arginfo_class_CAMetalDrawable_presentedTime, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalDrawable, drawableID, arginfo_class_CAMetalDrawable_drawableID, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalDrawable, pointer, arginfo_class_CAMetalDrawable_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(CAMetalDrawable, fromPointer, arginfo_class_CAMetalDrawable_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_CAEDRMetadata_methods[] = {
	ZEND_ME(CAEDRMetadata, __construct, arginfo_class_CAEDRMetadata___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(CAEDRMetadata, HDR10MetadataWithMinLuminanceMaxLuminanceOpticalOutputScale, arginfo_class_CAEDRMetadata_HDR10MetadataWithMinLuminanceMaxLuminanceOpticalOutputScale, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(CAEDRMetadata, HLGMetadata, arginfo_class_CAEDRMetadata_HLGMetadata, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(CAEDRMetadata, pointer, arginfo_class_CAEDRMetadata_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(CAEDRMetadata, fromPointer, arginfo_class_CAEDRMetadata_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_CGSize(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "CGSize", class_CGSize_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_width_default_value;
	ZVAL_DOUBLE(&property_width_default_value, 0.0);
	zend_string *property_width_name = zend_string_init("width", sizeof("width") - 1, 1);
	zend_declare_typed_property(class_entry, property_width_name, &property_width_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_width_name);

	zval property_height_default_value;
	ZVAL_DOUBLE(&property_height_default_value, 0.0);
	zend_string *property_height_name = zend_string_init("height", sizeof("height") - 1, 1);
	zend_declare_typed_property(class_entry, property_height_name, &property_height_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_height_name);

	return class_entry;
}

static zend_class_entry *register_class_CAMetalLayer(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "CAMetalLayer", class_CAMetalLayer_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_CAMetalDrawable(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "CAMetalDrawable", class_CAMetalDrawable_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_CAEDRMetadata(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "CAEDRMetadata", class_CAEDRMetadata_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}
