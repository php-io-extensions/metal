#include "runtime.h"
#include "../stubs/MTLCommand_arginfo.h"

#define THIS_ID METAL_ID(Z_OBJ_P(ZEND_THIS))

static void metal_setup_class(zend_class_entry **slot, zend_class_entry *(*register_fn)(void), Protocol *protocol, Class cls)
{
	*slot = register_fn();
	metal_object_setup(*slot);
	metal_map_native(*slot, protocol, cls);
}

void metal_register_MTLCommand(void)
{
	metal_setup_class(&metal_ce_MTLCommandQueue, register_class_MTLCommandQueue, @protocol(MTLCommandQueue), Nil);
	metal_setup_class(&metal_ce_MTLCommandBuffer, register_class_MTLCommandBuffer, @protocol(MTLCommandBuffer), Nil);
	metal_setup_class(&metal_ce_MTLRenderPassDescriptor, register_class_MTLRenderPassDescriptor, nil, [MTLRenderPassDescriptor class]);
	metal_setup_class(&metal_ce_MTLRenderPassColorAttachmentDescriptorArray, register_class_MTLRenderPassColorAttachmentDescriptorArray, nil, [MTLRenderPassColorAttachmentDescriptorArray class]);
	metal_setup_class(&metal_ce_MTLRenderPassColorAttachmentDescriptor, register_class_MTLRenderPassColorAttachmentDescriptor, nil, [MTLRenderPassColorAttachmentDescriptor class]);
	metal_setup_class(&metal_ce_MTLRenderPassDepthAttachmentDescriptor, register_class_MTLRenderPassDepthAttachmentDescriptor, nil, [MTLRenderPassDepthAttachmentDescriptor class]);
	metal_setup_class(&metal_ce_MTLRenderPassStencilAttachmentDescriptor, register_class_MTLRenderPassStencilAttachmentDescriptor, nil, [MTLRenderPassStencilAttachmentDescriptor class]);
	metal_setup_class(&metal_ce_MTLRenderCommandEncoder, register_class_MTLRenderCommandEncoder, @protocol(MTLRenderCommandEncoder), Nil);
	metal_setup_class(&metal_ce_MTLBlitCommandEncoder, register_class_MTLBlitCommandEncoder, @protocol(MTLBlitCommandEncoder), Nil);
}

static bool metal_shader_bytes(zend_string *bytes, zend_long length, zend_long index, const void **out)
{
	if (!metal_nonnegative(length, 2) || !metal_nonnegative(index, 3)) {
		return false;
	}

	if ((size_t) length > ZSTR_LEN(bytes)) {
		zend_argument_value_error(1, "must hold %zu bytes, %zu given", (size_t) length, ZSTR_LEN(bytes));
		return false;
	}

	*out = ZSTR_VAL(bytes);
	return true;
}

#define ATTACH_TEXTURE(cls, type) \
	ZEND_METHOD(cls, texture) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			metal_box(return_value, [(type *) THIS_ID texture], metal_ce_MTLTexture); \
		METAL_END \
	} \
	ZEND_METHOD(cls, setTexture) \
	{ \
		zend_object *texture = NULL; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_OBJ_OF_CLASS_OR_NULL(texture, metal_ce_MTLTexture) \
		ZEND_PARSE_PARAMETERS_END(); \
		METAL_BEGIN \
			[(type *) THIS_ID setTexture:(texture != NULL ? (id<MTLTexture>) METAL_ID(texture) : nil)]; \
		METAL_END \
	} \
	ZEND_METHOD(cls, resolveTexture) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			metal_box(return_value, [(type *) THIS_ID resolveTexture], metal_ce_MTLTexture); \
		METAL_END \
	} \
	ZEND_METHOD(cls, setResolveTexture) \
	{ \
		zend_object *texture = NULL; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_OBJ_OF_CLASS_OR_NULL(texture, metal_ce_MTLTexture) \
		ZEND_PARSE_PARAMETERS_END(); \
		METAL_BEGIN \
			[(type *) THIS_ID setResolveTexture:(texture != NULL ? (id<MTLTexture>) METAL_ID(texture) : nil)]; \
		METAL_END \
	} \
	ZEND_METHOD(cls, loadAction) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			metal_return_enum(return_value, metal_ce_MTLLoadAction, (zend_long) [(type *) THIS_ID loadAction]); \
		METAL_END \
	} \
	ZEND_METHOD(cls, setLoadAction) \
	{ \
		zend_object *action; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_OBJ_OF_CLASS(action, metal_ce_MTLLoadAction) \
		ZEND_PARSE_PARAMETERS_END(); \
		METAL_BEGIN \
			[(type *) THIS_ID setLoadAction:(MTLLoadAction) metal_enum_param(action, 0)]; \
		METAL_END \
	} \
	ZEND_METHOD(cls, storeAction) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		METAL_BEGIN \
			metal_return_enum(return_value, metal_ce_MTLStoreAction, (zend_long) [(type *) THIS_ID storeAction]); \
		METAL_END \
	} \
	ZEND_METHOD(cls, setStoreAction) \
	{ \
		zend_object *action; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			Z_PARAM_OBJ_OF_CLASS(action, metal_ce_MTLStoreAction) \
		ZEND_PARSE_PARAMETERS_END(); \
		METAL_BEGIN \
			[(type *) THIS_ID setStoreAction:(MTLStoreAction) metal_enum_param(action, 0)]; \
		METAL_END \
	}

METAL_REJECT_CONSTRUCT(MTLCommandQueue)
METAL_POINTER_METHODS(MTLCommandQueue)

ZEND_METHOD(MTLCommandQueue, commandBuffer)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(id<MTLCommandQueue>) THIS_ID commandBuffer], metal_ce_MTLCommandBuffer);
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLCommandBuffer)
METAL_POINTER_METHODS(MTLCommandBuffer)

ZEND_METHOD(MTLCommandBuffer, renderCommandEncoderWithDescriptor)
{
	zend_object *descriptor;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(descriptor, metal_ce_MTLRenderPassDescriptor)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		metal_box(return_value,
			[(id<MTLCommandBuffer>) THIS_ID renderCommandEncoderWithDescriptor:(MTLRenderPassDescriptor *) METAL_ID(descriptor)],
			metal_ce_MTLRenderCommandEncoder);
	METAL_END
}

ZEND_METHOD(MTLCommandBuffer, blitCommandEncoder)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(id<MTLCommandBuffer>) THIS_ID blitCommandEncoder], metal_ce_MTLBlitCommandEncoder);
	METAL_END
}

ZEND_METHOD(MTLCommandBuffer, presentDrawable)
{
	zend_object *drawable;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(drawable, metal_ce_CAMetalDrawable)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(id<MTLCommandBuffer>) THIS_ID presentDrawable:(id<MTLDrawable>) METAL_ID(drawable)];
	METAL_END
}

ZEND_METHOD(MTLCommandBuffer, presentDrawableAfterMinimumDuration)
{
	zend_object *drawable;
	double duration;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(drawable, metal_ce_CAMetalDrawable)
		Z_PARAM_DOUBLE(duration)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(id<MTLCommandBuffer>) THIS_ID presentDrawable:(id<MTLDrawable>) METAL_ID(drawable) afterMinimumDuration:(CFTimeInterval) duration];
	METAL_END
}

ZEND_METHOD(MTLCommandBuffer, presentDrawableAtTime)
{
	zend_object *drawable;
	double at;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS(drawable, metal_ce_CAMetalDrawable)
		Z_PARAM_DOUBLE(at)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(id<MTLCommandBuffer>) THIS_ID presentDrawable:(id<MTLDrawable>) METAL_ID(drawable) atTime:(CFTimeInterval) at];
	METAL_END
}

ZEND_METHOD(MTLCommandBuffer, commit)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		[(id<MTLCommandBuffer>) THIS_ID commit];
	METAL_END
}

ZEND_METHOD(MTLCommandBuffer, waitUntilCompleted)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		[(id<MTLCommandBuffer>) THIS_ID waitUntilCompleted];
	METAL_END
}

ZEND_METHOD(MTLCommandBuffer, status)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_return_enum(return_value, metal_ce_MTLCommandBufferStatus, (zend_long) [(id<MTLCommandBuffer>) THIS_ID status]);
	METAL_END
}

ZEND_METHOD(MTLCommandBuffer, error)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		NSError *error = [(id<MTLCommandBuffer>) THIS_ID error];

		if (error == nil) {
			RETURN_NULL();
		}

		const char *message = [[error localizedDescription] UTF8String];
		RETURN_STRING(message != NULL ? message : "");
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLRenderPassDescriptor)
METAL_POINTER_METHODS(MTLRenderPassDescriptor)

ZEND_METHOD(MTLRenderPassDescriptor, renderPassDescriptor)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [MTLRenderPassDescriptor renderPassDescriptor], metal_ce_MTLRenderPassDescriptor);
	METAL_END
}

ZEND_METHOD(MTLRenderPassDescriptor, colorAttachments)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLRenderPassDescriptor *) THIS_ID colorAttachments], metal_ce_MTLRenderPassColorAttachmentDescriptorArray);
	METAL_END
}

ZEND_METHOD(MTLRenderPassDescriptor, depthAttachment)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLRenderPassDescriptor *) THIS_ID depthAttachment], metal_ce_MTLRenderPassDepthAttachmentDescriptor);
	METAL_END
}

ZEND_METHOD(MTLRenderPassDescriptor, stencilAttachment)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_box(return_value, [(MTLRenderPassDescriptor *) THIS_ID stencilAttachment], metal_ce_MTLRenderPassStencilAttachmentDescriptor);
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLRenderPassColorAttachmentDescriptorArray)
METAL_POINTER_METHODS(MTLRenderPassColorAttachmentDescriptorArray)

ZEND_METHOD(MTLRenderPassColorAttachmentDescriptorArray, objectAtIndexedSubscript)
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
			[(MTLRenderPassColorAttachmentDescriptorArray *) THIS_ID objectAtIndexedSubscript:(NSUInteger) index],
			metal_ce_MTLRenderPassColorAttachmentDescriptor);
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLRenderPassColorAttachmentDescriptor)
METAL_POINTER_METHODS(MTLRenderPassColorAttachmentDescriptor)
ATTACH_TEXTURE(MTLRenderPassColorAttachmentDescriptor, MTLRenderPassColorAttachmentDescriptor)

ZEND_METHOD(MTLRenderPassColorAttachmentDescriptor, clearColor)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		metal_clear_color_new(return_value, [(MTLRenderPassColorAttachmentDescriptor *) THIS_ID clearColor]);
	METAL_END
}

ZEND_METHOD(MTLRenderPassColorAttachmentDescriptor, setClearColor)
{
	zend_object *color;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(color, metal_ce_MTLClearColor)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(MTLRenderPassColorAttachmentDescriptor *) THIS_ID setClearColor:metal_clear_color_from(color)];
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLRenderPassDepthAttachmentDescriptor)
METAL_POINTER_METHODS(MTLRenderPassDepthAttachmentDescriptor)
ATTACH_TEXTURE(MTLRenderPassDepthAttachmentDescriptor, MTLRenderPassDepthAttachmentDescriptor)

ZEND_METHOD(MTLRenderPassDepthAttachmentDescriptor, clearDepth)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_DOUBLE([(MTLRenderPassDepthAttachmentDescriptor *) THIS_ID clearDepth]);
	METAL_END
}

ZEND_METHOD(MTLRenderPassDepthAttachmentDescriptor, setClearDepth)
{
	double depth;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_DOUBLE(depth)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(MTLRenderPassDepthAttachmentDescriptor *) THIS_ID setClearDepth:depth];
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLRenderPassStencilAttachmentDescriptor)
METAL_POINTER_METHODS(MTLRenderPassStencilAttachmentDescriptor)
ATTACH_TEXTURE(MTLRenderPassStencilAttachmentDescriptor, MTLRenderPassStencilAttachmentDescriptor)

ZEND_METHOD(MTLRenderPassStencilAttachmentDescriptor, clearStencil)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		RETURN_LONG((zend_long) [(MTLRenderPassStencilAttachmentDescriptor *) THIS_ID clearStencil]);
	METAL_END
}

ZEND_METHOD(MTLRenderPassStencilAttachmentDescriptor, setClearStencil)
{
	zend_long value;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(value, 1)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(MTLRenderPassStencilAttachmentDescriptor *) THIS_ID setClearStencil:(uint32_t) value];
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLRenderCommandEncoder)
METAL_POINTER_METHODS(MTLRenderCommandEncoder)

ZEND_METHOD(MTLRenderCommandEncoder, setRenderPipelineState)
{
	zend_object *state;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(state, metal_ce_MTLRenderPipelineState)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setRenderPipelineState:(id<MTLRenderPipelineState>) METAL_ID(state)];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setDepthStencilState)
{
	zend_object *state = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(state, metal_ce_MTLDepthStencilState)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setDepthStencilState:(state != NULL ? (id<MTLDepthStencilState>) METAL_ID(state) : nil)];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setStencilReferenceValue)
{
	zend_long value;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(value, 1)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setStencilReferenceValue:(uint32_t) value];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setCullMode)
{
	zend_object *mode;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(mode, metal_ce_MTLCullMode)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setCullMode:(MTLCullMode) metal_enum_param(mode, 0)];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setFrontFacingWinding)
{
	zend_object *winding;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(winding, metal_ce_MTLWinding)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setFrontFacingWinding:(MTLWinding) metal_enum_param(winding, 0)];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setVertexBufferOffsetAtIndex)
{
	zend_object *buffer = NULL;
	zend_long offset, index;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(buffer, metal_ce_MTLBuffer)
		Z_PARAM_LONG(offset)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(offset, 2) || !metal_nonnegative(index, 3)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setVertexBuffer:(buffer != NULL ? (id<MTLBuffer>) METAL_ID(buffer) : nil)
			offset:(NSUInteger) offset
			atIndex:(NSUInteger) index];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setVertexBytesLengthAtIndex)
{
	zend_string *bytes;
	zend_long length, index;
	const void *pointer;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(bytes)
		Z_PARAM_LONG(length)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_shader_bytes(bytes, length, index, &pointer)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setVertexBytes:pointer length:(NSUInteger) length atIndex:(NSUInteger) index];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setFragmentBytesLengthAtIndex)
{
	zend_string *bytes;
	zend_long length, index;
	const void *pointer;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_STR(bytes)
		Z_PARAM_LONG(length)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_shader_bytes(bytes, length, index, &pointer)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setFragmentBytes:pointer length:(NSUInteger) length atIndex:(NSUInteger) index];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setFragmentTextureAtIndex)
{
	zend_object *texture = NULL;
	zend_long index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(texture, metal_ce_MTLTexture)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(index, 2)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setFragmentTexture:(texture != NULL ? (id<MTLTexture>) METAL_ID(texture) : nil) atIndex:(NSUInteger) index];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setFragmentSamplerStateAtIndex)
{
	zend_object *sampler = NULL;
	zend_long index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJ_OF_CLASS_OR_NULL(sampler, metal_ce_MTLSamplerState)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(index, 2)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setFragmentSamplerState:(sampler != NULL ? (id<MTLSamplerState>) METAL_ID(sampler) : nil) atIndex:(NSUInteger) index];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setViewport)
{
	zend_object *viewport;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(viewport, metal_ce_MTLViewport)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setViewport:metal_viewport_from(viewport)];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, setScissorRect)
{
	zend_object *rect;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(rect, metal_ce_MTLScissorRect)
	ZEND_PARSE_PARAMETERS_END();

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID setScissorRect:metal_scissor_from(rect)];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, drawPrimitivesVertexStartVertexCount)
{
	zend_object *primitive;
	zend_long start, count;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJ_OF_CLASS(primitive, metal_ce_MTLPrimitiveType)
		Z_PARAM_LONG(start)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(start, 2) || !metal_nonnegative(count, 3)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID drawPrimitives:(MTLPrimitiveType) metal_enum_param(primitive, 0)
			vertexStart:(NSUInteger) start
			vertexCount:(NSUInteger) count];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, drawIndexedPrimitivesIndexCountIndexTypeIndexBufferIndexBufferOffset)
{
	zend_object *primitive, *index_type, *buffer;
	zend_long count, offset;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJ_OF_CLASS(primitive, metal_ce_MTLPrimitiveType)
		Z_PARAM_LONG(count)
		Z_PARAM_OBJ_OF_CLASS(index_type, metal_ce_MTLIndexType)
		Z_PARAM_OBJ_OF_CLASS(buffer, metal_ce_MTLBuffer)
		Z_PARAM_LONG(offset)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(count, 2) || !metal_nonnegative(offset, 5)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID drawIndexedPrimitives:(MTLPrimitiveType) metal_enum_param(primitive, 0)
			indexCount:(NSUInteger) count
			indexType:(MTLIndexType) metal_enum_param(index_type, 0)
			indexBuffer:(id<MTLBuffer>) METAL_ID(buffer)
			indexBufferOffset:(NSUInteger) offset];
	METAL_END
}

ZEND_METHOD(MTLRenderCommandEncoder, endEncoding)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		[(id<MTLRenderCommandEncoder>) THIS_ID endEncoding];
	METAL_END
}

METAL_REJECT_CONSTRUCT(MTLBlitCommandEncoder)
METAL_POINTER_METHODS(MTLBlitCommandEncoder)

ZEND_METHOD(MTLBlitCommandEncoder, copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin)
{
	zend_object *source, *source_origin, *source_size, *destination, *destination_origin;
	zend_long source_slice, source_level, destination_slice, destination_level;

	ZEND_PARSE_PARAMETERS_START(9, 9)
		Z_PARAM_OBJ_OF_CLASS(source, metal_ce_MTLTexture)
		Z_PARAM_LONG(source_slice)
		Z_PARAM_LONG(source_level)
		Z_PARAM_OBJ_OF_CLASS(source_origin, metal_ce_MTLOrigin)
		Z_PARAM_OBJ_OF_CLASS(source_size, metal_ce_MTLSize)
		Z_PARAM_OBJ_OF_CLASS(destination, metal_ce_MTLTexture)
		Z_PARAM_LONG(destination_slice)
		Z_PARAM_LONG(destination_level)
		Z_PARAM_OBJ_OF_CLASS(destination_origin, metal_ce_MTLOrigin)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(source_slice, 2) || !metal_nonnegative(source_level, 3) || !metal_nonnegative(destination_slice, 7) || !metal_nonnegative(destination_level, 8)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLBlitCommandEncoder>) THIS_ID copyFromTexture:(id<MTLTexture>) METAL_ID(source)
			sourceSlice:(NSUInteger) source_slice
			sourceLevel:(NSUInteger) source_level
			sourceOrigin:metal_origin_from(source_origin)
			sourceSize:metal_size_from(source_size)
			toTexture:(id<MTLTexture>) METAL_ID(destination)
			destinationSlice:(NSUInteger) destination_slice
			destinationLevel:(NSUInteger) destination_level
			destinationOrigin:metal_origin_from(destination_origin)];
	METAL_END
}

ZEND_METHOD(MTLBlitCommandEncoder, copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImage)
{
	zend_object *source, *origin, *size, *buffer;
	zend_long slice, level, offset, bytes_per_row, bytes_per_image;

	ZEND_PARSE_PARAMETERS_START(9, 9)
		Z_PARAM_OBJ_OF_CLASS(source, metal_ce_MTLTexture)
		Z_PARAM_LONG(slice)
		Z_PARAM_LONG(level)
		Z_PARAM_OBJ_OF_CLASS(origin, metal_ce_MTLOrigin)
		Z_PARAM_OBJ_OF_CLASS(size, metal_ce_MTLSize)
		Z_PARAM_OBJ_OF_CLASS(buffer, metal_ce_MTLBuffer)
		Z_PARAM_LONG(offset)
		Z_PARAM_LONG(bytes_per_row)
		Z_PARAM_LONG(bytes_per_image)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(slice, 2) || !metal_nonnegative(level, 3) || !metal_nonnegative(offset, 7) || !metal_nonnegative(bytes_per_row, 8) || !metal_nonnegative(bytes_per_image, 9)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLBlitCommandEncoder>) THIS_ID copyFromTexture:(id<MTLTexture>) METAL_ID(source)
			sourceSlice:(NSUInteger) slice
			sourceLevel:(NSUInteger) level
			sourceOrigin:metal_origin_from(origin)
			sourceSize:metal_size_from(size)
			toBuffer:(id<MTLBuffer>) METAL_ID(buffer)
			destinationOffset:(NSUInteger) offset
			destinationBytesPerRow:(NSUInteger) bytes_per_row
			destinationBytesPerImage:(NSUInteger) bytes_per_image];
	METAL_END
}

ZEND_METHOD(MTLBlitCommandEncoder, copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin)
{
	zend_object *buffer, *size, *texture, *origin;
	zend_long offset, bytes_per_row, bytes_per_image, slice, level;

	ZEND_PARSE_PARAMETERS_START(9, 9)
		Z_PARAM_OBJ_OF_CLASS(buffer, metal_ce_MTLBuffer)
		Z_PARAM_LONG(offset)
		Z_PARAM_LONG(bytes_per_row)
		Z_PARAM_LONG(bytes_per_image)
		Z_PARAM_OBJ_OF_CLASS(size, metal_ce_MTLSize)
		Z_PARAM_OBJ_OF_CLASS(texture, metal_ce_MTLTexture)
		Z_PARAM_LONG(slice)
		Z_PARAM_LONG(level)
		Z_PARAM_OBJ_OF_CLASS(origin, metal_ce_MTLOrigin)
	ZEND_PARSE_PARAMETERS_END();

	if (!metal_nonnegative(offset, 2) || !metal_nonnegative(bytes_per_row, 3) || !metal_nonnegative(bytes_per_image, 4) || !metal_nonnegative(slice, 7) || !metal_nonnegative(level, 8)) {
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLBlitCommandEncoder>) THIS_ID copyFromBuffer:(id<MTLBuffer>) METAL_ID(buffer)
			sourceOffset:(NSUInteger) offset
			sourceBytesPerRow:(NSUInteger) bytes_per_row
			sourceBytesPerImage:(NSUInteger) bytes_per_image
			sourceSize:metal_size_from(size)
			toTexture:(id<MTLTexture>) METAL_ID(texture)
			destinationSlice:(NSUInteger) slice
			destinationLevel:(NSUInteger) level
			destinationOrigin:metal_origin_from(origin)];
	METAL_END
}

ZEND_METHOD(MTLBlitCommandEncoder, synchronizeResource)
{
	zend_object *resource;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ(resource)
	ZEND_PARSE_PARAMETERS_END();

	if (!instanceof_function(resource->ce, metal_ce_MTLTexture) && !instanceof_function(resource->ce, metal_ce_MTLBuffer)) {
		zend_argument_type_error(1, "must be of type MTLTexture|MTLBuffer, %s given", ZSTR_VAL(resource->ce->name));
		RETURN_THROWS();
	}

	METAL_BEGIN
		[(id<MTLBlitCommandEncoder>) THIS_ID synchronizeResource:(id<MTLResource>) METAL_ID(resource)];
	METAL_END
}

ZEND_METHOD(MTLBlitCommandEncoder, endEncoding)
{
	ZEND_PARSE_PARAMETERS_NONE();

	METAL_BEGIN
		[(id<MTLBlitCommandEncoder>) THIS_ID endEncoding];
	METAL_END
}
