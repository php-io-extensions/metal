#include "runtime.h"
#include "../stubs/MTLPipeline_arginfo.h"

#define THIS_ID METAL_ID(Z_OBJ_P(ZEND_THIS))

static void metal_setup_class(zend_class_entry **slot, zend_class_entry *(*register_fn)(void), Protocol *protocol, Class cls)
{
	*slot = register_fn();
	metal_object_setup(*slot);
	metal_map_native(*slot, protocol, cls);
}

void metal_register_MTLPipeline(void)
{
	metal_setup_class(&metal_ce_MTLCompileOptions, register_class_MTLCompileOptions, nil, [MTLCompileOptions class]);
	metal_setup_class(&metal_ce_MTLLibrary, register_class_MTLLibrary, @protocol(MTLLibrary), Nil);
	metal_setup_class(&metal_ce_MTLFunction, register_class_MTLFunction, @protocol(MTLFunction), Nil);
	metal_setup_class(&metal_ce_MTLVertexDescriptor, register_class_MTLVertexDescriptor, nil, [MTLVertexDescriptor class]);
	metal_setup_class(&metal_ce_MTLVertexAttributeDescriptorArray, register_class_MTLVertexAttributeDescriptorArray, nil, [MTLVertexAttributeDescriptorArray class]);
	metal_setup_class(&metal_ce_MTLVertexBufferLayoutDescriptorArray, register_class_MTLVertexBufferLayoutDescriptorArray, nil, [MTLVertexBufferLayoutDescriptorArray class]);
	metal_setup_class(&metal_ce_MTLVertexAttributeDescriptor, register_class_MTLVertexAttributeDescriptor, nil, [MTLVertexAttributeDescriptor class]);
	metal_setup_class(&metal_ce_MTLVertexBufferLayoutDescriptor, register_class_MTLVertexBufferLayoutDescriptor, nil, [MTLVertexBufferLayoutDescriptor class]);
	metal_setup_class(&metal_ce_MTLRenderPipelineDescriptor, register_class_MTLRenderPipelineDescriptor, nil, [MTLRenderPipelineDescriptor class]);
	metal_setup_class(&metal_ce_MTLRenderPipelineColorAttachmentDescriptorArray, register_class_MTLRenderPipelineColorAttachmentDescriptorArray, nil, [MTLRenderPipelineColorAttachmentDescriptorArray class]);
	metal_setup_class(&metal_ce_MTLRenderPipelineColorAttachmentDescriptor, register_class_MTLRenderPipelineColorAttachmentDescriptor, nil, [MTLRenderPipelineColorAttachmentDescriptor class]);
	metal_setup_class(&metal_ce_MTLRenderPipelineState, register_class_MTLRenderPipelineState, @protocol(MTLRenderPipelineState), Nil);
	metal_setup_class(&metal_ce_MTLStencilDescriptor, register_class_MTLStencilDescriptor, nil, [MTLStencilDescriptor class]);
	metal_setup_class(&metal_ce_MTLDepthStencilDescriptor, register_class_MTLDepthStencilDescriptor, nil, [MTLDepthStencilDescriptor class]);
	metal_setup_class(&metal_ce_MTLDepthStencilState, register_class_MTLDepthStencilState, @protocol(MTLDepthStencilState), Nil);
}

#define METAL_NEW(cls, native) \
	ZEND_METHOD(cls, new) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			metal_box_owned(return_value, [[native alloc] init], metal_ce_##cls); \
		METAL_END \
	}

#define METAL_LONG_GET(cls, method, type, sel) \
	ZEND_METHOD(cls, method) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			RETURN_LONG((zend_long) [(type *) THIS_ID sel]); \
		METAL_END \
	}

#define METAL_LONG_SET(cls, method, type, sel) \
	ZEND_METHOD(cls, method) \
	{ \
		zend_long value; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_LONG(value) \
		ZEND_PARSE_PARAMETERS_END(); \
		if (!metal_nonnegative(value, 1)) { \
			RETURN_THROWS(); \
		} \
		METAL_BEGIN \
			[(type *) THIS_ID sel:(NSUInteger) value]; \
		METAL_END \
	}

#define METAL_ENUM_GET(cls, method, type, sel, ce) \
	ZEND_METHOD(cls, method) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			metal_return_enum(return_value, ce, (zend_long) [(type *) THIS_ID sel]); \
		METAL_END \
	}

#define METAL_ENUM_SET(cls, method, type, sel, ce, native) \
	ZEND_METHOD(cls, method) \
	{ \
		zend_object *case_obj; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_OBJ_OF_CLASS(case_obj, ce) \
		ZEND_PARSE_PARAMETERS_END(); \
		METAL_BEGIN \
			[(type *) THIS_ID sel:(native) metal_enum_param(case_obj, 0)]; \
		METAL_END \
	}

#define METAL_ENUM_OR_INT_GET(cls, method, type, sel, ce) \
	ZEND_METHOD(cls, method) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			metal_return_enum(return_value, ce, (zend_long) [(type *) THIS_ID sel]); \
		METAL_END \
	}

#define METAL_ENUM_OR_INT_SET(cls, method, type, sel, ce, native) \
	ZEND_METHOD(cls, method) \
	{ \
		zend_object *case_obj = NULL; \
		zend_long plain = 0; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_OBJ_OF_CLASS_OR_LONG(case_obj, ce, plain) \
		ZEND_PARSE_PARAMETERS_END(); \
		METAL_BEGIN \
			[(type *) THIS_ID sel:(native) metal_enum_param(case_obj, plain)]; \
		METAL_END \
	}

#define METAL_BOOL_GET(cls, method, type, sel) \
	ZEND_METHOD(cls, method) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			RETURN_BOOL([(type *) THIS_ID sel]); \
		METAL_END \
	}

#define METAL_BOOL_SET(cls, method, type, sel) \
	ZEND_METHOD(cls, method) \
	{ \
		bool value; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_BOOL(value) \
		ZEND_PARSE_PARAMETERS_END(); \
		METAL_BEGIN \
			[(type *) THIS_ID sel:value]; \
		METAL_END \
	}

METAL_REJECT_CONSTRUCT(MTLCompileOptions)
METAL_POINTER_METHODS(MTLCompileOptions)
METAL_NEW(MTLCompileOptions, MTLCompileOptions)

METAL_REJECT_CONSTRUCT(MTLLibrary)
METAL_POINTER_METHODS(MTLLibrary)

ZEND_METHOD(MTLLibrary, newFunctionWithName)
{
	zend_string *name;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(name)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		metal_box_owned(return_value, [(id<MTLLibrary>) THIS_ID newFunctionWithName:metal_nsstring(name)], metal_ce_MTLFunction);
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLFunction)
METAL_POINTER_METHODS(MTLFunction)

ZEND_METHOD(MTLFunction, name)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		const char *name = [[(id<MTLFunction>) THIS_ID name] UTF8String];

		RETURN_STRING(name != NULL ? name : "");
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLVertexDescriptor)
METAL_POINTER_METHODS(MTLVertexDescriptor)

ZEND_METHOD(MTLVertexDescriptor, vertexDescriptor)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [MTLVertexDescriptor vertexDescriptor], metal_ce_MTLVertexDescriptor);
	METAL_END
}

ZEND_METHOD(MTLVertexDescriptor, attributes)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLVertexDescriptor *) THIS_ID attributes], metal_ce_MTLVertexAttributeDescriptorArray);
	METAL_END
}

ZEND_METHOD(MTLVertexDescriptor, layouts)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLVertexDescriptor *) THIS_ID layouts], metal_ce_MTLVertexBufferLayoutDescriptorArray);
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLVertexAttributeDescriptorArray)
METAL_POINTER_METHODS(MTLVertexAttributeDescriptorArray)

ZEND_METHOD(MTLVertexAttributeDescriptorArray, objectAtIndexedSubscript)
{
	zend_long index;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(index, 1)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		metal_box(return_value, [(MTLVertexAttributeDescriptorArray *) THIS_ID objectAtIndexedSubscript:(NSUInteger) index], metal_ce_MTLVertexAttributeDescriptor);
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLVertexBufferLayoutDescriptorArray)
METAL_POINTER_METHODS(MTLVertexBufferLayoutDescriptorArray)

ZEND_METHOD(MTLVertexBufferLayoutDescriptorArray, objectAtIndexedSubscript)
{
	zend_long index;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(index, 1)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		metal_box(return_value, [(MTLVertexBufferLayoutDescriptorArray *) THIS_ID objectAtIndexedSubscript:(NSUInteger) index], metal_ce_MTLVertexBufferLayoutDescriptor);
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLVertexAttributeDescriptor)
METAL_POINTER_METHODS(MTLVertexAttributeDescriptor)
METAL_ENUM_GET(MTLVertexAttributeDescriptor, format, MTLVertexAttributeDescriptor, format, metal_ce_MTLVertexFormat)
METAL_ENUM_SET(MTLVertexAttributeDescriptor, setFormat, MTLVertexAttributeDescriptor, setFormat, metal_ce_MTLVertexFormat, MTLVertexFormat)
METAL_LONG_GET(MTLVertexAttributeDescriptor, offset, MTLVertexAttributeDescriptor, offset)
METAL_LONG_SET(MTLVertexAttributeDescriptor, setOffset, MTLVertexAttributeDescriptor, setOffset)
METAL_LONG_GET(MTLVertexAttributeDescriptor, bufferIndex, MTLVertexAttributeDescriptor, bufferIndex)
METAL_LONG_SET(MTLVertexAttributeDescriptor, setBufferIndex, MTLVertexAttributeDescriptor, setBufferIndex)

METAL_REJECT_CONSTRUCT(MTLVertexBufferLayoutDescriptor)
METAL_POINTER_METHODS(MTLVertexBufferLayoutDescriptor)
METAL_LONG_GET(MTLVertexBufferLayoutDescriptor, stride, MTLVertexBufferLayoutDescriptor, stride)
METAL_LONG_SET(MTLVertexBufferLayoutDescriptor, setStride, MTLVertexBufferLayoutDescriptor, setStride)
METAL_ENUM_GET(MTLVertexBufferLayoutDescriptor, stepFunction, MTLVertexBufferLayoutDescriptor, stepFunction, metal_ce_MTLVertexStepFunction)
METAL_ENUM_SET(MTLVertexBufferLayoutDescriptor, setStepFunction, MTLVertexBufferLayoutDescriptor, setStepFunction, metal_ce_MTLVertexStepFunction, MTLVertexStepFunction)

METAL_REJECT_CONSTRUCT(MTLRenderPipelineDescriptor)
METAL_POINTER_METHODS(MTLRenderPipelineDescriptor)
METAL_NEW(MTLRenderPipelineDescriptor, MTLRenderPipelineDescriptor)

ZEND_METHOD(MTLRenderPipelineDescriptor, vertexFunction)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLRenderPipelineDescriptor *) THIS_ID vertexFunction], metal_ce_MTLFunction);
	METAL_END
}

ZEND_METHOD(MTLRenderPipelineDescriptor, setVertexFunction)
{
	zend_object *function = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(function, metal_ce_MTLFunction)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(MTLRenderPipelineDescriptor *) THIS_ID setVertexFunction:(function != NULL ? (id<MTLFunction>) METAL_ID(function) : nil)];
	METAL_END
}

ZEND_METHOD(MTLRenderPipelineDescriptor, fragmentFunction)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLRenderPipelineDescriptor *) THIS_ID fragmentFunction], metal_ce_MTLFunction);
	METAL_END
}

ZEND_METHOD(MTLRenderPipelineDescriptor, setFragmentFunction)
{
	zend_object *function = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(function, metal_ce_MTLFunction)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(MTLRenderPipelineDescriptor *) THIS_ID setFragmentFunction:(function != NULL ? (id<MTLFunction>) METAL_ID(function) : nil)];
	METAL_END
}

ZEND_METHOD(MTLRenderPipelineDescriptor, vertexDescriptor)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLRenderPipelineDescriptor *) THIS_ID vertexDescriptor], metal_ce_MTLVertexDescriptor);
	METAL_END
}

ZEND_METHOD(MTLRenderPipelineDescriptor, setVertexDescriptor)
{
	zend_object *descriptor = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(descriptor, metal_ce_MTLVertexDescriptor)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(MTLRenderPipelineDescriptor *) THIS_ID setVertexDescriptor:(descriptor != NULL ? (MTLVertexDescriptor *) METAL_ID(descriptor) : nil)];
	METAL_END
}

METAL_LONG_GET(MTLRenderPipelineDescriptor, rasterSampleCount, MTLRenderPipelineDescriptor, rasterSampleCount)
METAL_LONG_SET(MTLRenderPipelineDescriptor, setRasterSampleCount, MTLRenderPipelineDescriptor, setRasterSampleCount)
METAL_ENUM_GET(MTLRenderPipelineDescriptor, depthAttachmentPixelFormat, MTLRenderPipelineDescriptor, depthAttachmentPixelFormat, metal_ce_MTLPixelFormat)
METAL_ENUM_SET(MTLRenderPipelineDescriptor, setDepthAttachmentPixelFormat, MTLRenderPipelineDescriptor, setDepthAttachmentPixelFormat, metal_ce_MTLPixelFormat, MTLPixelFormat)
METAL_ENUM_GET(MTLRenderPipelineDescriptor, stencilAttachmentPixelFormat, MTLRenderPipelineDescriptor, stencilAttachmentPixelFormat, metal_ce_MTLPixelFormat)
METAL_ENUM_SET(MTLRenderPipelineDescriptor, setStencilAttachmentPixelFormat, MTLRenderPipelineDescriptor, setStencilAttachmentPixelFormat, metal_ce_MTLPixelFormat, MTLPixelFormat)

ZEND_METHOD(MTLRenderPipelineDescriptor, colorAttachments)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLRenderPipelineDescriptor *) THIS_ID colorAttachments], metal_ce_MTLRenderPipelineColorAttachmentDescriptorArray);
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLRenderPipelineColorAttachmentDescriptorArray)
METAL_POINTER_METHODS(MTLRenderPipelineColorAttachmentDescriptorArray)

ZEND_METHOD(MTLRenderPipelineColorAttachmentDescriptorArray, objectAtIndexedSubscript)
{
	zend_long index;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(index, 1)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		metal_box(return_value,
			[(MTLRenderPipelineColorAttachmentDescriptorArray *) THIS_ID objectAtIndexedSubscript:(NSUInteger) index],
			metal_ce_MTLRenderPipelineColorAttachmentDescriptor);
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLRenderPipelineColorAttachmentDescriptor)
METAL_POINTER_METHODS(MTLRenderPipelineColorAttachmentDescriptor)
METAL_ENUM_GET(MTLRenderPipelineColorAttachmentDescriptor, pixelFormat, MTLRenderPipelineColorAttachmentDescriptor, pixelFormat, metal_ce_MTLPixelFormat)
METAL_ENUM_SET(MTLRenderPipelineColorAttachmentDescriptor, setPixelFormat, MTLRenderPipelineColorAttachmentDescriptor, setPixelFormat, metal_ce_MTLPixelFormat, MTLPixelFormat)
METAL_ENUM_OR_INT_GET(MTLRenderPipelineColorAttachmentDescriptor, writeMask, MTLRenderPipelineColorAttachmentDescriptor, writeMask, metal_ce_MTLColorWriteMask)
METAL_ENUM_OR_INT_SET(MTLRenderPipelineColorAttachmentDescriptor, setWriteMask, MTLRenderPipelineColorAttachmentDescriptor, setWriteMask, metal_ce_MTLColorWriteMask, MTLColorWriteMask)
METAL_BOOL_GET(MTLRenderPipelineColorAttachmentDescriptor, blendingEnabled, MTLRenderPipelineColorAttachmentDescriptor, isBlendingEnabled)
METAL_BOOL_SET(MTLRenderPipelineColorAttachmentDescriptor, setBlendingEnabled, MTLRenderPipelineColorAttachmentDescriptor, setBlendingEnabled)
METAL_ENUM_GET(MTLRenderPipelineColorAttachmentDescriptor, rgbBlendOperation, MTLRenderPipelineColorAttachmentDescriptor, rgbBlendOperation, metal_ce_MTLBlendOperation)
METAL_ENUM_SET(MTLRenderPipelineColorAttachmentDescriptor, setRgbBlendOperation, MTLRenderPipelineColorAttachmentDescriptor, setRgbBlendOperation, metal_ce_MTLBlendOperation, MTLBlendOperation)
METAL_ENUM_GET(MTLRenderPipelineColorAttachmentDescriptor, alphaBlendOperation, MTLRenderPipelineColorAttachmentDescriptor, alphaBlendOperation, metal_ce_MTLBlendOperation)
METAL_ENUM_SET(MTLRenderPipelineColorAttachmentDescriptor, setAlphaBlendOperation, MTLRenderPipelineColorAttachmentDescriptor, setAlphaBlendOperation, metal_ce_MTLBlendOperation, MTLBlendOperation)
METAL_ENUM_GET(MTLRenderPipelineColorAttachmentDescriptor, sourceRGBBlendFactor, MTLRenderPipelineColorAttachmentDescriptor, sourceRGBBlendFactor, metal_ce_MTLBlendFactor)
METAL_ENUM_SET(MTLRenderPipelineColorAttachmentDescriptor, setSourceRGBBlendFactor, MTLRenderPipelineColorAttachmentDescriptor, setSourceRGBBlendFactor, metal_ce_MTLBlendFactor, MTLBlendFactor)
METAL_ENUM_GET(MTLRenderPipelineColorAttachmentDescriptor, destinationRGBBlendFactor, MTLRenderPipelineColorAttachmentDescriptor, destinationRGBBlendFactor, metal_ce_MTLBlendFactor)
METAL_ENUM_SET(MTLRenderPipelineColorAttachmentDescriptor, setDestinationRGBBlendFactor, MTLRenderPipelineColorAttachmentDescriptor, setDestinationRGBBlendFactor, metal_ce_MTLBlendFactor, MTLBlendFactor)
METAL_ENUM_GET(MTLRenderPipelineColorAttachmentDescriptor, sourceAlphaBlendFactor, MTLRenderPipelineColorAttachmentDescriptor, sourceAlphaBlendFactor, metal_ce_MTLBlendFactor)
METAL_ENUM_SET(MTLRenderPipelineColorAttachmentDescriptor, setSourceAlphaBlendFactor, MTLRenderPipelineColorAttachmentDescriptor, setSourceAlphaBlendFactor, metal_ce_MTLBlendFactor, MTLBlendFactor)
METAL_ENUM_GET(MTLRenderPipelineColorAttachmentDescriptor, destinationAlphaBlendFactor, MTLRenderPipelineColorAttachmentDescriptor, destinationAlphaBlendFactor, metal_ce_MTLBlendFactor)
METAL_ENUM_SET(MTLRenderPipelineColorAttachmentDescriptor, setDestinationAlphaBlendFactor, MTLRenderPipelineColorAttachmentDescriptor, setDestinationAlphaBlendFactor, metal_ce_MTLBlendFactor, MTLBlendFactor)

METAL_REJECT_CONSTRUCT(MTLRenderPipelineState)
METAL_POINTER_METHODS(MTLRenderPipelineState)

METAL_REJECT_CONSTRUCT(MTLStencilDescriptor)
METAL_POINTER_METHODS(MTLStencilDescriptor)
METAL_NEW(MTLStencilDescriptor, MTLStencilDescriptor)
METAL_ENUM_GET(MTLStencilDescriptor, stencilCompareFunction, MTLStencilDescriptor, stencilCompareFunction, metal_ce_MTLCompareFunction)
METAL_ENUM_SET(MTLStencilDescriptor, setStencilCompareFunction, MTLStencilDescriptor, setStencilCompareFunction, metal_ce_MTLCompareFunction, MTLCompareFunction)
METAL_ENUM_GET(MTLStencilDescriptor, stencilFailureOperation, MTLStencilDescriptor, stencilFailureOperation, metal_ce_MTLStencilOperation)
METAL_ENUM_SET(MTLStencilDescriptor, setStencilFailureOperation, MTLStencilDescriptor, setStencilFailureOperation, metal_ce_MTLStencilOperation, MTLStencilOperation)
METAL_ENUM_GET(MTLStencilDescriptor, depthFailureOperation, MTLStencilDescriptor, depthFailureOperation, metal_ce_MTLStencilOperation)
METAL_ENUM_SET(MTLStencilDescriptor, setDepthFailureOperation, MTLStencilDescriptor, setDepthFailureOperation, metal_ce_MTLStencilOperation, MTLStencilOperation)
METAL_ENUM_GET(MTLStencilDescriptor, depthStencilPassOperation, MTLStencilDescriptor, depthStencilPassOperation, metal_ce_MTLStencilOperation)
METAL_ENUM_SET(MTLStencilDescriptor, setDepthStencilPassOperation, MTLStencilDescriptor, setDepthStencilPassOperation, metal_ce_MTLStencilOperation, MTLStencilOperation)
METAL_LONG_GET(MTLStencilDescriptor, readMask, MTLStencilDescriptor, readMask)
METAL_LONG_SET(MTLStencilDescriptor, setReadMask, MTLStencilDescriptor, setReadMask)
METAL_LONG_GET(MTLStencilDescriptor, writeMask, MTLStencilDescriptor, writeMask)
METAL_LONG_SET(MTLStencilDescriptor, setWriteMask, MTLStencilDescriptor, setWriteMask)

METAL_REJECT_CONSTRUCT(MTLDepthStencilDescriptor)
METAL_POINTER_METHODS(MTLDepthStencilDescriptor)
METAL_NEW(MTLDepthStencilDescriptor, MTLDepthStencilDescriptor)
METAL_ENUM_GET(MTLDepthStencilDescriptor, depthCompareFunction, MTLDepthStencilDescriptor, depthCompareFunction, metal_ce_MTLCompareFunction)
METAL_ENUM_SET(MTLDepthStencilDescriptor, setDepthCompareFunction, MTLDepthStencilDescriptor, setDepthCompareFunction, metal_ce_MTLCompareFunction, MTLCompareFunction)
METAL_BOOL_GET(MTLDepthStencilDescriptor, depthWriteEnabled, MTLDepthStencilDescriptor, isDepthWriteEnabled)
METAL_BOOL_SET(MTLDepthStencilDescriptor, setDepthWriteEnabled, MTLDepthStencilDescriptor, setDepthWriteEnabled)

ZEND_METHOD(MTLDepthStencilDescriptor, frontFaceStencil)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLDepthStencilDescriptor *) THIS_ID frontFaceStencil], metal_ce_MTLStencilDescriptor);
	METAL_END
}

ZEND_METHOD(MTLDepthStencilDescriptor, setFrontFaceStencil)
{
	zend_object *stencil = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(stencil, metal_ce_MTLStencilDescriptor)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(MTLDepthStencilDescriptor *) THIS_ID setFrontFaceStencil:(stencil != NULL ? (MTLStencilDescriptor *) METAL_ID(stencil) : nil)];
	METAL_END
}

ZEND_METHOD(MTLDepthStencilDescriptor, backFaceStencil)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLDepthStencilDescriptor *) THIS_ID backFaceStencil], metal_ce_MTLStencilDescriptor);
	METAL_END
}

ZEND_METHOD(MTLDepthStencilDescriptor, setBackFaceStencil)
{
	zend_object *stencil = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(stencil, metal_ce_MTLStencilDescriptor)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(MTLDepthStencilDescriptor *) THIS_ID setBackFaceStencil:(stencil != NULL ? (MTLStencilDescriptor *) METAL_ID(stencil) : nil)];
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLDepthStencilState)
METAL_POINTER_METHODS(MTLDepthStencilState)
