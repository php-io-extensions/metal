#include "runtime.h"
#include "../stubs/MTLDevice_arginfo.h"

void metal_register_MTLDevice(void)
{
	metal_ce_MTLDevice = register_class_MTLDevice();
	metal_object_setup(metal_ce_MTLDevice);
	metal_map_native(metal_ce_MTLDevice, @protocol(MTLDevice), Nil);
}

METAL_REJECT_CONSTRUCT(MTLDevice)
METAL_POINTER_METHODS(MTLDevice)

ZEND_METHOD(MTLDevice, name)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		const char *name = [[METAL_ID(Z_OBJ_P(ZEND_THIS)) name] UTF8String];

		RETURN_STRING(name != NULL ? name : "");
	METAL_END
}

ZEND_METHOD(MTLDevice, newTextureWithDescriptor)
{
	zend_object *descriptor;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(descriptor, metal_ce_MTLTextureDescriptor)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		metal_box_owned(return_value, [METAL_ID(Z_OBJ_P(ZEND_THIS)) newTextureWithDescriptor:METAL_ID(descriptor)], metal_ce_MTLTexture);
	METAL_END
}

ZEND_METHOD(MTLDevice, newBufferWithLengthOptions)
{
	zend_long length;
	zend_object *options_case = NULL;
	zend_long options_long = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(length)
		Z_PARAM_OBJ_OF_CLASS_OR_LONG(options_case, metal_ce_MTLResourceOptions, options_long)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(length, 1)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		metal_box_owned(return_value,
			[METAL_ID(Z_OBJ_P(ZEND_THIS)) newBufferWithLength:(NSUInteger) length
				options:(MTLResourceOptions) metal_enum_param(options_case, options_long)],
			metal_ce_MTLBuffer);
	METAL_END
}

ZEND_METHOD(MTLDevice, newBufferWithBytesLengthOptions)
{
	zend_string *bytes = NULL;
	zend_long address = 0, length;
	zend_object *options_case = NULL;
	zend_long options_long = 0;
	const void *pointer;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR_OR_LONG(bytes, address)
		Z_PARAM_LONG(length)
		Z_PARAM_OBJ_OF_CLASS_OR_LONG(options_case, metal_ce_MTLResourceOptions, options_long)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(length, 2)) {
		RETURN_THROWS();
	}

	if (!metal_resolve_bytes(bytes, address, (size_t) length, 1, "must hold %zu bytes, %zu given", &pointer)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		metal_box_owned(return_value,
			[METAL_ID(Z_OBJ_P(ZEND_THIS)) newBufferWithBytes:pointer
				length:(NSUInteger) length
				options:(MTLResourceOptions) metal_enum_param(options_case, options_long)],
			metal_ce_MTLBuffer);
	METAL_END
}

ZEND_METHOD(MTLDevice, newSamplerStateWithDescriptor)
{
	zend_object *descriptor;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(descriptor, metal_ce_MTLSamplerDescriptor)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		metal_box_owned(return_value, [METAL_ID(Z_OBJ_P(ZEND_THIS)) newSamplerStateWithDescriptor:METAL_ID(descriptor)], metal_ce_MTLSamplerState);
	METAL_END
}

ZEND_METHOD(MTLDevice, newCommandQueue)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box_owned(return_value, [METAL_ID(Z_OBJ_P(ZEND_THIS)) newCommandQueue], metal_ce_MTLCommandQueue);
	METAL_END
}

ZEND_METHOD(MTLDevice, newLibraryWithSourceOptionsError)
{
	zend_string *source;
	zend_object *options = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(source)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(options, metal_ce_MTLCompileOptions)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		NSError *error = nil;
		id<MTLLibrary> library = [METAL_ID(Z_OBJ_P(ZEND_THIS)) newLibraryWithSource:metal_nsstring(source)
			options:(options != NULL ? (MTLCompileOptions *) METAL_ID(options) : nil)
			error:&error];

		if (library == nil) {
			metal_throw_nserror(error);
			RETURN_THROWS();
		}

		metal_box_owned(return_value, library, metal_ce_MTLLibrary);
	METAL_END
}

ZEND_METHOD(MTLDevice, newRenderPipelineStateWithDescriptorError)
{
	zend_object *descriptor;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(descriptor, metal_ce_MTLRenderPipelineDescriptor)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		NSError *error = nil;
		id<MTLRenderPipelineState> state = [METAL_ID(Z_OBJ_P(ZEND_THIS)) newRenderPipelineStateWithDescriptor:(MTLRenderPipelineDescriptor *) METAL_ID(descriptor) error:&error];

		if (state == nil) {
			metal_throw_nserror(error);
			RETURN_THROWS();
		}

		metal_box_owned(return_value, state, metal_ce_MTLRenderPipelineState);
	METAL_END
}

ZEND_METHOD(MTLDevice, newDepthStencilStateWithDescriptor)
{
	zend_object *descriptor;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(descriptor, metal_ce_MTLDepthStencilDescriptor)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		metal_box_owned(return_value,
			[METAL_ID(Z_OBJ_P(ZEND_THIS)) newDepthStencilStateWithDescriptor:(MTLDepthStencilDescriptor *) METAL_ID(descriptor)],
			metal_ce_MTLDepthStencilState);
	METAL_END
}

ZEND_METHOD(MTLDevice, supportsTextureSampleCount)
{
	zend_long sample_count;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(sample_count)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(sample_count, 1)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		RETURN_BOOL([METAL_ID(Z_OBJ_P(ZEND_THIS)) supportsTextureSampleCount:(NSUInteger) sample_count]);
	METAL_END
}
