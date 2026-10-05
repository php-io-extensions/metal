#include "runtime.h"
#include "../stubs/MTLTypes_arginfo.h"

static zend_long metal_long_property(zend_object *object, const char *name)
{
	zval rv;
	zval *value = zend_read_property(object->ce, object, name, strlen(name), 0, &rv);

	if (Z_TYPE_P(value) == IS_LONG) {
		return Z_LVAL_P(value);
	}

	if (Z_TYPE_P(value) == IS_DOUBLE) {
		return (zend_long) Z_DVAL_P(value);
	}

	return 0;
}

static double metal_double_property(zend_object *object, const char *name)
{
	zval rv;
	zval *value = zend_read_property(object->ce, object, name, strlen(name), 0, &rv);

	if (Z_TYPE_P(value) == IS_DOUBLE) {
		return Z_DVAL_P(value);
	}

	if (Z_TYPE_P(value) == IS_LONG) {
		return (double) Z_LVAL_P(value);
	}

	return 0.0;
}

static zend_object *metal_object_property(zend_object *object, const char *name)
{
	zval rv;
	zval *value = zend_read_property(object->ce, object, name, strlen(name), 0, &rv);

	if (Z_TYPE_P(value) != IS_OBJECT) {
		return NULL;
	}

	return Z_OBJ_P(value);
}

void metal_register_MTLTypes(void)
{
	metal_ce_MTLOrigin = register_class_MTLOrigin();
	metal_ce_MTLSize = register_class_MTLSize();
	metal_ce_MTLRegion = register_class_MTLRegion();
	metal_ce_MTLClearColor = register_class_MTLClearColor();
	metal_ce_MTLViewport = register_class_MTLViewport();
	metal_ce_MTLScissorRect = register_class_MTLScissorRect();
	metal_ce_MTLPixelFormat = register_class_MTLPixelFormat();
	metal_ce_MTLLoadAction = register_class_MTLLoadAction();
	metal_ce_MTLStoreAction = register_class_MTLStoreAction();
	metal_ce_MTLPrimitiveType = register_class_MTLPrimitiveType();
	metal_ce_MTLIndexType = register_class_MTLIndexType();
	metal_ce_MTLTextureUsage = register_class_MTLTextureUsage();
	metal_ce_MTLStorageMode = register_class_MTLStorageMode();
	metal_ce_MTLResourceOptions = register_class_MTLResourceOptions();
	metal_ce_MTLTextureType = register_class_MTLTextureType();
	metal_ce_MTLVertexFormat = register_class_MTLVertexFormat();
	metal_ce_MTLVertexStepFunction = register_class_MTLVertexStepFunction();
	metal_ce_MTLBlendFactor = register_class_MTLBlendFactor();
	metal_ce_MTLBlendOperation = register_class_MTLBlendOperation();
	metal_ce_MTLColorWriteMask = register_class_MTLColorWriteMask();
	metal_ce_MTLSamplerMinMagFilter = register_class_MTLSamplerMinMagFilter();
	metal_ce_MTLSamplerAddressMode = register_class_MTLSamplerAddressMode();
	metal_ce_MTLCompareFunction = register_class_MTLCompareFunction();
	metal_ce_MTLStencilOperation = register_class_MTLStencilOperation();
	metal_ce_MTLCullMode = register_class_MTLCullMode();
	metal_ce_MTLWinding = register_class_MTLWinding();
	metal_ce_MTLCommandBufferStatus = register_class_MTLCommandBufferStatus();
}

ZEND_METHOD(MTLOrigin, __construct)
{
	zend_long x, y, z;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(z)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_long(metal_ce_MTLOrigin, Z_OBJ_P(ZEND_THIS), "x", sizeof("x") - 1, x);
	zend_update_property_long(metal_ce_MTLOrigin, Z_OBJ_P(ZEND_THIS), "y", sizeof("y") - 1, y);
	zend_update_property_long(metal_ce_MTLOrigin, Z_OBJ_P(ZEND_THIS), "z", sizeof("z") - 1, z);
}

ZEND_METHOD(MTLSize, __construct)
{
	zend_long width, height, depth;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_LONG(depth)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_long(metal_ce_MTLSize, Z_OBJ_P(ZEND_THIS), "width", sizeof("width") - 1, width);
	zend_update_property_long(metal_ce_MTLSize, Z_OBJ_P(ZEND_THIS), "height", sizeof("height") - 1, height);
	zend_update_property_long(metal_ce_MTLSize, Z_OBJ_P(ZEND_THIS), "depth", sizeof("depth") - 1, depth);
}

ZEND_METHOD(MTLRegion, __construct)
{
	zend_object *origin, *size;
	zval origin_zv, size_zv;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(origin, metal_ce_MTLOrigin)
		Z_PARAM_OBJ_OF_CLASS(size, metal_ce_MTLSize)
	ZEND_PARSE_PARAMETERS_END();

	ZVAL_OBJ_COPY(&origin_zv, origin);
	ZVAL_OBJ_COPY(&size_zv, size);
	zend_update_property(metal_ce_MTLRegion, Z_OBJ_P(ZEND_THIS), "origin", sizeof("origin") - 1, &origin_zv);
	zend_update_property(metal_ce_MTLRegion, Z_OBJ_P(ZEND_THIS), "size", sizeof("size") - 1, &size_zv);
	zval_ptr_dtor(&origin_zv);
	zval_ptr_dtor(&size_zv);
}

ZEND_METHOD(MTLClearColor, __construct)
{
	double red, green, blue, alpha;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_DOUBLE(red)
		Z_PARAM_DOUBLE(green)
		Z_PARAM_DOUBLE(blue)
		Z_PARAM_DOUBLE(alpha)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_double(metal_ce_MTLClearColor, Z_OBJ_P(ZEND_THIS), "red", sizeof("red") - 1, red);
	zend_update_property_double(metal_ce_MTLClearColor, Z_OBJ_P(ZEND_THIS), "green", sizeof("green") - 1, green);
	zend_update_property_double(metal_ce_MTLClearColor, Z_OBJ_P(ZEND_THIS), "blue", sizeof("blue") - 1, blue);
	zend_update_property_double(metal_ce_MTLClearColor, Z_OBJ_P(ZEND_THIS), "alpha", sizeof("alpha") - 1, alpha);
}

ZEND_METHOD(MTLViewport, __construct)
{
	double origin_x, origin_y, width, height, znear, zfar;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_DOUBLE(origin_x)
		Z_PARAM_DOUBLE(origin_y)
		Z_PARAM_DOUBLE(width)
		Z_PARAM_DOUBLE(height)
		Z_PARAM_DOUBLE(znear)
		Z_PARAM_DOUBLE(zfar)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_double(metal_ce_MTLViewport, Z_OBJ_P(ZEND_THIS), "originX", sizeof("originX") - 1, origin_x);
	zend_update_property_double(metal_ce_MTLViewport, Z_OBJ_P(ZEND_THIS), "originY", sizeof("originY") - 1, origin_y);
	zend_update_property_double(metal_ce_MTLViewport, Z_OBJ_P(ZEND_THIS), "width", sizeof("width") - 1, width);
	zend_update_property_double(metal_ce_MTLViewport, Z_OBJ_P(ZEND_THIS), "height", sizeof("height") - 1, height);
	zend_update_property_double(metal_ce_MTLViewport, Z_OBJ_P(ZEND_THIS), "znear", sizeof("znear") - 1, znear);
	zend_update_property_double(metal_ce_MTLViewport, Z_OBJ_P(ZEND_THIS), "zfar", sizeof("zfar") - 1, zfar);
}

ZEND_METHOD(MTLScissorRect, __construct)
{
	zend_long x, y, width, height;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property_long(metal_ce_MTLScissorRect, Z_OBJ_P(ZEND_THIS), "x", sizeof("x") - 1, x);
	zend_update_property_long(metal_ce_MTLScissorRect, Z_OBJ_P(ZEND_THIS), "y", sizeof("y") - 1, y);
	zend_update_property_long(metal_ce_MTLScissorRect, Z_OBJ_P(ZEND_THIS), "width", sizeof("width") - 1, width);
	zend_update_property_long(metal_ce_MTLScissorRect, Z_OBJ_P(ZEND_THIS), "height", sizeof("height") - 1, height);
}

MTLOrigin metal_origin_from(zend_object *object)
{
	MTLOrigin origin = {
		.x = (NSUInteger) metal_long_property(object, "x"),
		.y = (NSUInteger) metal_long_property(object, "y"),
		.z = (NSUInteger) metal_long_property(object, "z"),
	};

	return origin;
}

MTLSize metal_size_from(zend_object *object)
{
	MTLSize size = {
		.width = (NSUInteger) metal_long_property(object, "width"),
		.height = (NSUInteger) metal_long_property(object, "height"),
		.depth = (NSUInteger) metal_long_property(object, "depth"),
	};

	return size;
}

MTLRegion metal_region_from(zend_object *object)
{
	zend_object *origin = metal_object_property(object, "origin");
	zend_object *size = metal_object_property(object, "size");
	MTLRegion region = { 0 };

	if (origin != NULL) {
		region.origin = metal_origin_from(origin);
	}
	if (size != NULL) {
		region.size = metal_size_from(size);
	}

	return region;
}

MTLClearColor metal_clear_color_from(zend_object *object)
{
	MTLClearColor color = {
		.red = metal_double_property(object, "red"),
		.green = metal_double_property(object, "green"),
		.blue = metal_double_property(object, "blue"),
		.alpha = metal_double_property(object, "alpha"),
	};

	return color;
}

MTLViewport metal_viewport_from(zend_object *object)
{
	MTLViewport viewport = {
		.originX = metal_double_property(object, "originX"),
		.originY = metal_double_property(object, "originY"),
		.width = metal_double_property(object, "width"),
		.height = metal_double_property(object, "height"),
		.znear = metal_double_property(object, "znear"),
		.zfar = metal_double_property(object, "zfar"),
	};

	return viewport;
}

MTLScissorRect metal_scissor_from(zend_object *object)
{
	MTLScissorRect rect = {
		.x = (NSUInteger) metal_long_property(object, "x"),
		.y = (NSUInteger) metal_long_property(object, "y"),
		.width = (NSUInteger) metal_long_property(object, "width"),
		.height = (NSUInteger) metal_long_property(object, "height"),
	};

	return rect;
}

void metal_clear_color_new(zval *rv, MTLClearColor color)
{
	object_init_ex(rv, metal_ce_MTLClearColor);
	zend_update_property_double(metal_ce_MTLClearColor, Z_OBJ_P(rv), "red", sizeof("red") - 1, color.red);
	zend_update_property_double(metal_ce_MTLClearColor, Z_OBJ_P(rv), "green", sizeof("green") - 1, color.green);
	zend_update_property_double(metal_ce_MTLClearColor, Z_OBJ_P(rv), "blue", sizeof("blue") - 1, color.blue);
	zend_update_property_double(metal_ce_MTLClearColor, Z_OBJ_P(rv), "alpha", sizeof("alpha") - 1, color.alpha);
}

void metal_region_new(zval *rv, MTLRegion region)
{
	zval origin, size;

	object_init_ex(&origin, metal_ce_MTLOrigin);
	zend_update_property_long(metal_ce_MTLOrigin, Z_OBJ(origin), "x", sizeof("x") - 1, (zend_long) region.origin.x);
	zend_update_property_long(metal_ce_MTLOrigin, Z_OBJ(origin), "y", sizeof("y") - 1, (zend_long) region.origin.y);
	zend_update_property_long(metal_ce_MTLOrigin, Z_OBJ(origin), "z", sizeof("z") - 1, (zend_long) region.origin.z);

	object_init_ex(&size, metal_ce_MTLSize);
	zend_update_property_long(metal_ce_MTLSize, Z_OBJ(size), "width", sizeof("width") - 1, (zend_long) region.size.width);
	zend_update_property_long(metal_ce_MTLSize, Z_OBJ(size), "height", sizeof("height") - 1, (zend_long) region.size.height);
	zend_update_property_long(metal_ce_MTLSize, Z_OBJ(size), "depth", sizeof("depth") - 1, (zend_long) region.size.depth);

	object_init_ex(rv, metal_ce_MTLRegion);
	zend_update_property(metal_ce_MTLRegion, Z_OBJ_P(rv), "origin", sizeof("origin") - 1, &origin);
	zend_update_property(metal_ce_MTLRegion, Z_OBJ_P(rv), "size", sizeof("size") - 1, &size);
	zval_ptr_dtor(&origin);
	zval_ptr_dtor(&size);
}
