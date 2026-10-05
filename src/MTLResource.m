#include "runtime.h"
#include "../stubs/MTLResource_arginfo.h"

#define THIS_TEXDESC ((MTLTextureDescriptor *) METAL_ID(Z_OBJ_P(ZEND_THIS)))
#define THIS_TEXTURE ((id<MTLTexture>) METAL_ID(Z_OBJ_P(ZEND_THIS)))
#define THIS_BUFFER ((id<MTLBuffer>) METAL_ID(Z_OBJ_P(ZEND_THIS)))
#define THIS_SAMPDESC ((MTLSamplerDescriptor *) METAL_ID(Z_OBJ_P(ZEND_THIS)))

void metal_register_MTLResource(void)
{
	metal_ce_MTLTextureDescriptor = register_class_MTLTextureDescriptor();
	metal_object_setup(metal_ce_MTLTextureDescriptor);
	metal_map_native(metal_ce_MTLTextureDescriptor, nil, [MTLTextureDescriptor class]);

	metal_ce_MTLTexture = register_class_MTLTexture();
	metal_object_setup(metal_ce_MTLTexture);
	metal_map_native(metal_ce_MTLTexture, @protocol(MTLTexture), Nil);

	metal_ce_MTLBuffer = register_class_MTLBuffer();
	metal_object_setup(metal_ce_MTLBuffer);
	metal_map_native(metal_ce_MTLBuffer, @protocol(MTLBuffer), Nil);

	metal_ce_MTLSamplerDescriptor = register_class_MTLSamplerDescriptor();
	metal_object_setup(metal_ce_MTLSamplerDescriptor);
	metal_map_native(metal_ce_MTLSamplerDescriptor, nil, [MTLSamplerDescriptor class]);

	metal_ce_MTLSamplerState = register_class_MTLSamplerState();
	metal_object_setup(metal_ce_MTLSamplerState);
	metal_map_native(metal_ce_MTLSamplerState, @protocol(MTLSamplerState), Nil);
}

static bool metal_region_span(zend_object *region, zend_long bytes_per_row, uint32_t row_arg, size_t *need)
{
	zval size_rv, height_rv;
	zval *size = zend_read_property(region->ce, region, "size", sizeof("size") - 1, 0, &size_rv);

	if (Z_TYPE_P(size) != IS_OBJECT) {
		zend_argument_value_error(1, "must have a size");
		return false;
	}

	zval *height_zv = zend_read_property(Z_OBJCE_P(size), Z_OBJ_P(size), "height", sizeof("height") - 1, 0, &height_rv);

	if (Z_TYPE_P(height_zv) != IS_LONG || Z_LVAL_P(height_zv) < 0) {
		zend_argument_value_error(1, "height must be greater than or equal to 0");
		return false;
	}

	zend_long height = Z_LVAL_P(height_zv);

	if (height > 0 && (size_t) bytes_per_row > SIZE_MAX / (size_t) height) {
		zend_argument_value_error(row_arg, "times the region height overflows");
		return false;
	}

	*need = (size_t) bytes_per_row * (size_t) height;
	return true;
}

METAL_REJECT_CONSTRUCT(MTLTextureDescriptor)
METAL_POINTER_METHODS(MTLTextureDescriptor)

ZEND_METHOD(MTLTextureDescriptor, texture2DDescriptorWithPixelFormatWidthHeightMipmapped)
{
	zend_object *format;
	zend_long width, height;
	bool mipmapped;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJ_OF_CLASS(format, metal_ce_MTLPixelFormat)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
		Z_PARAM_BOOL(mipmapped)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(width, 2) || !metal_nonnegative(height, 3)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		metal_box(return_value,
			[MTLTextureDescriptor texture2DDescriptorWithPixelFormat:(MTLPixelFormat) metal_enum_param(format, 0)
				width:(NSUInteger) width
				height:(NSUInteger) height
				mipmapped:mipmapped],
			metal_ce_MTLTextureDescriptor);
	METAL_END
}

ZEND_METHOD(MTLTextureDescriptor, new)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box_owned(return_value, [[MTLTextureDescriptor alloc] init], metal_ce_MTLTextureDescriptor);
	METAL_END
}

#define METAL_TEXDESC_ENUM_GET(method, sel, ce) \
	ZEND_METHOD(MTLTextureDescriptor, method) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			metal_return_enum(return_value, ce, (zend_long) [THIS_TEXDESC sel]); \
		METAL_END \
	}

#define METAL_TEXDESC_ENUM_SET(method, sel, ce, native) \
	ZEND_METHOD(MTLTextureDescriptor, method) \
	{ \
		zend_object *case_obj; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_OBJ_OF_CLASS(case_obj, ce) \
		ZEND_PARSE_PARAMETERS_END(); \
		METAL_BEGIN \
			[THIS_TEXDESC sel:(native) metal_enum_param(case_obj, 0)]; \
		METAL_END \
	}

#define METAL_TEXDESC_LONG_GET(method, sel) \
	ZEND_METHOD(MTLTextureDescriptor, method) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			RETURN_LONG((zend_long) [THIS_TEXDESC sel]); \
		METAL_END \
	}

#define METAL_TEXDESC_LONG_SET(method, sel) \
	ZEND_METHOD(MTLTextureDescriptor, method) \
	{ \
		zend_long value; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_LONG(value) \
		ZEND_PARSE_PARAMETERS_END(); \
		if (!metal_nonnegative(value, 1)) { \
			RETURN_THROWS(); \
		} \
		METAL_BEGIN \
			[THIS_TEXDESC sel:(NSUInteger) value]; \
		METAL_END \
	}

METAL_TEXDESC_ENUM_GET(textureType, textureType, metal_ce_MTLTextureType)
METAL_TEXDESC_ENUM_SET(setTextureType, setTextureType, metal_ce_MTLTextureType, MTLTextureType)
METAL_TEXDESC_ENUM_GET(pixelFormat, pixelFormat, metal_ce_MTLPixelFormat)
METAL_TEXDESC_ENUM_SET(setPixelFormat, setPixelFormat, metal_ce_MTLPixelFormat, MTLPixelFormat)
METAL_TEXDESC_LONG_GET(width, width)
METAL_TEXDESC_LONG_SET(setWidth, setWidth)
METAL_TEXDESC_LONG_GET(height, height)
METAL_TEXDESC_LONG_SET(setHeight, setHeight)
METAL_TEXDESC_LONG_GET(sampleCount, sampleCount)
METAL_TEXDESC_LONG_SET(setSampleCount, setSampleCount)
METAL_TEXDESC_ENUM_GET(storageMode, storageMode, metal_ce_MTLStorageMode)
METAL_TEXDESC_ENUM_SET(setStorageMode, setStorageMode, metal_ce_MTLStorageMode, MTLStorageMode)

ZEND_METHOD(MTLTextureDescriptor, usage)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_return_enum(return_value, metal_ce_MTLTextureUsage, (zend_long) [THIS_TEXDESC usage]);
	METAL_END
}

ZEND_METHOD(MTLTextureDescriptor, setUsage)
{
	zend_object *case_obj = NULL;
	zend_long plain = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_LONG(case_obj, metal_ce_MTLTextureUsage, plain)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[THIS_TEXDESC setUsage:(MTLTextureUsage) metal_enum_param(case_obj, plain)];
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLTexture)
METAL_POINTER_METHODS(MTLTexture)

ZEND_METHOD(MTLTexture, width)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_LONG((zend_long) [THIS_TEXTURE width]);
	METAL_END
}

ZEND_METHOD(MTLTexture, height)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_LONG((zend_long) [THIS_TEXTURE height]);
	METAL_END
}

ZEND_METHOD(MTLTexture, pixelFormat)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_return_enum(return_value, metal_ce_MTLPixelFormat, (zend_long) [THIS_TEXTURE pixelFormat]);
	METAL_END
}

ZEND_METHOD(MTLTexture, textureType)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_return_enum(return_value, metal_ce_MTLTextureType, (zend_long) [THIS_TEXTURE textureType]);
	METAL_END
}

ZEND_METHOD(MTLTexture, sampleCount)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_LONG((zend_long) [THIS_TEXTURE sampleCount]);
	METAL_END
}

ZEND_METHOD(MTLTexture, replaceRegionMipmapLevelWithBytesBytesPerRow)
{
	zend_object *region_obj;
	zend_long level, bytes_per_row;
	zend_string *bytes = NULL;
	zend_long address = 0;
	const void *pointer;
	size_t need;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJ_OF_CLASS(region_obj, metal_ce_MTLRegion)
		Z_PARAM_LONG(level)
		Z_PARAM_STR_OR_LONG(bytes, address)
		Z_PARAM_LONG(bytes_per_row)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(level, 2) || !metal_nonnegative(bytes_per_row, 4)) {
		RETURN_THROWS();
	}

	if (!metal_region_span(region_obj, bytes_per_row, 4, &need)) {
		RETURN_THROWS();
	}

	if (!metal_resolve_bytes(bytes, address, need, 3, "must hold bytesPerRow × height (%zu bytes), %zu given", &pointer)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[THIS_TEXTURE replaceRegion:metal_region_from(region_obj)
			mipmapLevel:(NSUInteger) level
			withBytes:pointer
			bytesPerRow:(NSUInteger) bytes_per_row];
	METAL_END
}

ZEND_METHOD(MTLTexture, getBytesBytesPerRowFromRegionMipmapLevel)
{
	zend_long destination = 0, bytes_per_row, level;
	bool destination_null;
	zend_object *region_obj;
	size_t need;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG_OR_NULL(destination, destination_null)
		Z_PARAM_LONG(bytes_per_row)
		Z_PARAM_OBJ_OF_CLASS(region_obj, metal_ce_MTLRegion)
		Z_PARAM_LONG(level)
	ZEND_PARSE_PARAMETERS_END();

	if (!destination_null && destination == 0) {
		zend_argument_value_error(1, "must not be a null address");
		RETURN_THROWS();
	}

	if (!metal_nonnegative(bytes_per_row, 2) || !metal_nonnegative(level, 4)) {
		RETURN_THROWS();
	}

	if (!metal_region_span(region_obj, bytes_per_row, 2, &need)) {
		RETURN_THROWS();
	}

	if (destination_null) {
		zend_string *out = zend_string_alloc(need, 0);

		@autoreleasepool {
			@try {
				[THIS_TEXTURE getBytes:ZSTR_VAL(out)
					bytesPerRow:(NSUInteger) bytes_per_row
					fromRegion:metal_region_from(region_obj)
					mipmapLevel:(NSUInteger) level];
				ZSTR_VAL(out)[need] = '\0';
				RETURN_NEW_STR(out);
			} @catch (NSException *metal_exception) {
				zend_string_release(out);
				metal_throw_nsexception(metal_exception);
				RETURN_THROWS();
			}
		}

		return;
	}

	METAL_BEGIN
		[THIS_TEXTURE getBytes:(void *) (uintptr_t) destination
			bytesPerRow:(NSUInteger) bytes_per_row
			fromRegion:metal_region_from(region_obj)
			mipmapLevel:(NSUInteger) level];
		RETURN_NULL();
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLBuffer)
METAL_POINTER_METHODS(MTLBuffer)

ZEND_METHOD(MTLBuffer, length)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_LONG((zend_long) [THIS_BUFFER length]);
	METAL_END
}

ZEND_METHOD(MTLBuffer, contents)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_LONG((zend_long) (uintptr_t) [THIS_BUFFER contents]);
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLSamplerDescriptor)
METAL_POINTER_METHODS(MTLSamplerDescriptor)

ZEND_METHOD(MTLSamplerDescriptor, new)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box_owned(return_value, [[MTLSamplerDescriptor alloc] init], metal_ce_MTLSamplerDescriptor);
	METAL_END
}

#define METAL_SAMP_ENUM_GET(method, sel, ce) \
	ZEND_METHOD(MTLSamplerDescriptor, method) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			metal_return_enum(return_value, ce, (zend_long) [THIS_SAMPDESC sel]); \
		METAL_END \
	}

#define METAL_SAMP_ENUM_SET(method, sel, ce, native) \
	ZEND_METHOD(MTLSamplerDescriptor, method) \
	{ \
		zend_object *case_obj; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_OBJ_OF_CLASS(case_obj, ce) \
		ZEND_PARSE_PARAMETERS_END(); \
		METAL_BEGIN \
			[THIS_SAMPDESC sel:(native) metal_enum_param(case_obj, 0)]; \
		METAL_END \
	}

METAL_SAMP_ENUM_GET(minFilter, minFilter, metal_ce_MTLSamplerMinMagFilter)
METAL_SAMP_ENUM_SET(setMinFilter, setMinFilter, metal_ce_MTLSamplerMinMagFilter, MTLSamplerMinMagFilter)
METAL_SAMP_ENUM_GET(magFilter, magFilter, metal_ce_MTLSamplerMinMagFilter)
METAL_SAMP_ENUM_SET(setMagFilter, setMagFilter, metal_ce_MTLSamplerMinMagFilter, MTLSamplerMinMagFilter)
METAL_SAMP_ENUM_GET(sAddressMode, sAddressMode, metal_ce_MTLSamplerAddressMode)
METAL_SAMP_ENUM_SET(setSAddressMode, setSAddressMode, metal_ce_MTLSamplerAddressMode, MTLSamplerAddressMode)
METAL_SAMP_ENUM_GET(tAddressMode, tAddressMode, metal_ce_MTLSamplerAddressMode)
METAL_SAMP_ENUM_SET(setTAddressMode, setTAddressMode, metal_ce_MTLSamplerAddressMode, MTLSamplerAddressMode)

METAL_REJECT_CONSTRUCT(MTLSamplerState)
METAL_POINTER_METHODS(MTLSamplerState)
