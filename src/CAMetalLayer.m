#include "runtime.h"
#include "../stubs/CAMetalLayer_arginfo.h"

#define THIS_LAYER ((CAMetalLayer *) METAL_ID(Z_OBJ_P(ZEND_THIS)))
#define THIS_DRAWABLE ((id<CAMetalDrawable>) METAL_ID(Z_OBJ_P(ZEND_THIS)))

static CGSize metal_cgsize_from(zend_object *object)
{
	zval width_rv, height_rv;
	zval *width = zend_read_property(object->ce, object, "width", sizeof("width") - 1, 0, &width_rv);
	zval *height = zend_read_property(object->ce, object, "height", sizeof("height") - 1, 0, &height_rv);
	CGSize size = { 0, 0 };

	if (Z_TYPE_P(width) == IS_DOUBLE) {
		size.width = Z_DVAL_P(width);
	} else if (Z_TYPE_P(width) == IS_LONG) {
		size.width = (CGFloat) Z_LVAL_P(width);
	}

	if (Z_TYPE_P(height) == IS_DOUBLE) {
		size.height = Z_DVAL_P(height);
	} else if (Z_TYPE_P(height) == IS_LONG) {
		size.height = (CGFloat) Z_LVAL_P(height);
	}

	return size;
}

static void metal_cgsize_new(zval *rv, CGSize size)
{
	object_init_ex(rv, metal_ce_CGSize);
	zend_update_property_double(metal_ce_CGSize, Z_OBJ_P(rv), "width", sizeof("width") - 1, size.width);
	zend_update_property_double(metal_ce_CGSize, Z_OBJ_P(rv), "height", sizeof("height") - 1, size.height);
}

void metal_register_CAMetalLayer(void)
{
	metal_ce_CGSize = register_class_CGSize();

	metal_ce_CAMetalLayer = register_class_CAMetalLayer();
	metal_object_setup(metal_ce_CAMetalLayer);
	metal_map_native(metal_ce_CAMetalLayer, nil, [CAMetalLayer class]);

	metal_ce_CAMetalDrawable = register_class_CAMetalDrawable();
	metal_object_setup(metal_ce_CAMetalDrawable);
	metal_map_native(metal_ce_CAMetalDrawable, @protocol(CAMetalDrawable), Nil);

	metal_ce_CAEDRMetadata = register_class_CAEDRMetadata();
	metal_object_setup(metal_ce_CAEDRMetadata);
	metal_map_native(metal_ce_CAEDRMetadata, nil, [CAEDRMetadata class]);
}

ZEND_METHOD(CGSize, __construct)
{
	double width, height;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_DOUBLE(width)
		Z_PARAM_DOUBLE(height)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_double(metal_ce_CGSize, Z_OBJ_P(ZEND_THIS), "width", sizeof("width") - 1, width);
	zend_update_property_double(metal_ce_CGSize, Z_OBJ_P(ZEND_THIS), "height", sizeof("height") - 1, height);
}

METAL_REJECT_CONSTRUCT(CAMetalLayer)
METAL_POINTER_METHODS(CAMetalLayer)

ZEND_METHOD(CAMetalLayer, layer)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [CAMetalLayer layer], metal_ce_CAMetalLayer);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, device)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [THIS_LAYER device], metal_ce_MTLDevice);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setDevice)
{
	zend_object *device = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(device, metal_ce_MTLDevice)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_LAYER setDevice:(device != NULL ? (id<MTLDevice>) METAL_ID(device) : nil)];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, pixelFormat)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_return_enum(return_value, metal_ce_MTLPixelFormat, (zend_long) [THIS_LAYER pixelFormat]);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setPixelFormat)
{
	zend_object *format;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(format, metal_ce_MTLPixelFormat)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_LAYER setPixelFormat:(MTLPixelFormat) metal_enum_param(format, 0)];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, framebufferOnly)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_BOOL([THIS_LAYER framebufferOnly]);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setFramebufferOnly)
{
	bool value;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(value)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_LAYER setFramebufferOnly:value];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, drawableSize)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_cgsize_new(return_value, [THIS_LAYER drawableSize]);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setDrawableSize)
{
	zend_object *size;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(size, metal_ce_CGSize)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_LAYER setDrawableSize:metal_cgsize_from(size)];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, displaySyncEnabled)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_BOOL([THIS_LAYER displaySyncEnabled]);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setDisplaySyncEnabled)
{
	bool value;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(value)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_LAYER setDisplaySyncEnabled:value];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, contentsScale)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_DOUBLE([THIS_LAYER contentsScale]);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setContentsScale)
{
	double scale;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_DOUBLE(scale)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_LAYER setContentsScale:scale];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, maximumDrawableCount)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_LONG((zend_long) [THIS_LAYER maximumDrawableCount]);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setMaximumDrawableCount)
{
	zend_long count;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(count, 1)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[THIS_LAYER setMaximumDrawableCount:(NSUInteger) count];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, allowsNextDrawableTimeout)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_BOOL([THIS_LAYER allowsNextDrawableTimeout]);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setAllowsNextDrawableTimeout)
{
	bool value;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(value)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_LAYER setAllowsNextDrawableTimeout:value];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, presentsWithTransaction)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_BOOL([THIS_LAYER presentsWithTransaction]);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setPresentsWithTransaction)
{
	bool value;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(value)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_LAYER setPresentsWithTransaction:value];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, wantsExtendedDynamicRangeContent)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_BOOL([THIS_LAYER wantsExtendedDynamicRangeContent]);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setWantsExtendedDynamicRangeContent)
{
	bool value;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_BOOL(value)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_LAYER setWantsExtendedDynamicRangeContent:value];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, colorspace)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		CGColorSpaceRef space = [THIS_LAYER colorspace];
		if (space == NULL) {
			RETURN_NULL();
		}
		RETURN_LONG((zend_long) (uintptr_t) space);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setColorspace)
{
	zend_long address;
	bool is_null = true;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG_OR_NULL(address, is_null)
	ZEND_PARSE_PARAMETERS_END();

	if (!is_null && address == 0) {
		zend_argument_value_error(1, "must not be a null address");
		RETURN_THROWS();
	}

	METAL_BEGIN
		[THIS_LAYER setColorspace:is_null ? NULL : (CGColorSpaceRef) (uintptr_t) address];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, EDRMetadata)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [THIS_LAYER EDRMetadata], metal_ce_CAEDRMetadata);
	METAL_END
}

ZEND_METHOD(CAMetalLayer, setEDRMetadata)
{
	zend_object *metadata = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(metadata, metal_ce_CAEDRMetadata)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_LAYER setEDRMetadata:metadata == NULL ? nil : (CAEDRMetadata *) METAL_ID(metadata)];
	METAL_END
}

ZEND_METHOD(CAMetalLayer, nextDrawable)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [THIS_LAYER nextDrawable], metal_ce_CAMetalDrawable);
	METAL_END
}

METAL_REJECT_CONSTRUCT(CAMetalDrawable)
METAL_POINTER_METHODS(CAMetalDrawable)

ZEND_METHOD(CAMetalDrawable, texture)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [THIS_DRAWABLE texture], metal_ce_MTLTexture);
	METAL_END
}

ZEND_METHOD(CAMetalDrawable, presentedTime)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_DOUBLE([THIS_DRAWABLE presentedTime]);
	METAL_END
}

ZEND_METHOD(CAMetalDrawable, drawableID)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_LONG((zend_long) [THIS_DRAWABLE drawableID]);
	METAL_END
}

METAL_REJECT_CONSTRUCT(CAEDRMetadata)
METAL_POINTER_METHODS(CAEDRMetadata)

ZEND_METHOD(CAEDRMetadata, HDR10MetadataWithMinLuminanceMaxLuminanceOpticalOutputScale)
{
	double min_nits, max_nits, scale;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_DOUBLE(min_nits)
		Z_PARAM_DOUBLE(max_nits)
		Z_PARAM_DOUBLE(scale)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		metal_box(return_value, [CAEDRMetadata HDR10MetadataWithMinLuminance:(float) min_nits maxLuminance:(float) max_nits opticalOutputScale:(float) scale], metal_ce_CAEDRMetadata);
	METAL_END
}

ZEND_METHOD(CAEDRMetadata, HLGMetadata)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [CAEDRMetadata HLGMetadata], metal_ce_CAEDRMetadata);
	METAL_END
}

ZEND_METHOD(CAMetalDrawable, present)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		[THIS_DRAWABLE present];
	METAL_END
}
