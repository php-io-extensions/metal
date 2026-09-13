#include "mtl-rendercommandencoder.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

void mtl_mtlrendercommandencoder_set_render_pipeline_state(zval *handle, zval *pipelineState)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        id<MTLRenderPipelineState> p = MTL_ARG_PROTO(MTLRenderPipelineState, pipelineState);
        /* The SDK declares pipelineState nonnull; a nil send would trap
           inside Metal's validation layer, so an unresolvable handle is a
           no-op here. */
        if (e == nil || p == nil) return;
        [e setRenderPipelineState:p];
    }
}

void mtl_mtlrendercommandencoder_set_vertex_buffer_offset_at_index(zval *handle, zval *buffer, zval *offset, zval *index)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        if (e == nil) return;
        [e setVertexBuffer:MTL_ARG_PROTO(MTLBuffer, buffer)
                    offset:(NSUInteger) mtl_arg_long(offset)
                   atIndex:(NSUInteger) mtl_arg_long(index)];
    }
}

void mtl_mtlrendercommandencoder_set_fragment_buffer_offset_at_index(zval *handle, zval *buffer, zval *offset, zval *index)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        if (e == nil) return;
        [e setFragmentBuffer:MTL_ARG_PROTO(MTLBuffer, buffer)
                      offset:(NSUInteger) mtl_arg_long(offset)
                     atIndex:(NSUInteger) mtl_arg_long(index)];
    }
}

void mtl_mtlrendercommandencoder_set_vertex_texture_at_index(zval *handle, zval *texture, zval *index)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        if (e == nil) return;
        [e setVertexTexture:MTL_ARG_PROTO(MTLTexture, texture)
                    atIndex:(NSUInteger) mtl_arg_long(index)];
    }
}

void mtl_mtlrendercommandencoder_set_fragment_texture_at_index(zval *handle, zval *texture, zval *index)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        if (e == nil) return;
        [e setFragmentTexture:MTL_ARG_PROTO(MTLTexture, texture)
                      atIndex:(NSUInteger) mtl_arg_long(index)];
    }
}

void mtl_mtlrendercommandencoder_set_fragment_sampler_state_at_index(zval *handle, zval *sampler, zval *index)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        if (e == nil) return;
        [e setFragmentSamplerState:MTL_ARG_PROTO(MTLSamplerState, sampler)
                           atIndex:(NSUInteger) mtl_arg_long(index)];
    }
}

void mtl_mtlrendercommandencoder_set_viewport(zval *handle, zval *originX, zval *originY, zval *width, zval *height, zval *znear, zval *zfar)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        if (e == nil) return;
        MTLViewport vp;
        vp.originX = mtl_arg_double(originX);
        vp.originY = mtl_arg_double(originY);
        vp.width = mtl_arg_double(width);
        vp.height = mtl_arg_double(height);
        vp.znear = mtl_arg_double(znear);
        vp.zfar = mtl_arg_double(zfar);
        [e setViewport:vp];
    }
}

void mtl_mtlrendercommandencoder_set_scissor_rect(zval *handle, zval *x, zval *y, zval *width, zval *height)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        zend_long xx = mtl_arg_long(x);
        zend_long yy = mtl_arg_long(y);
        zend_long w = mtl_arg_long(width);
        zend_long h = mtl_arg_long(height);
        /* MTLScissorRect is four NSUIntegers; a negative component would
           wrap to an enormous unsigned value and fail Metal's own
           validation, so it is rejected in glue instead. */
        if (e == nil || xx < 0 || yy < 0 || w < 0 || h < 0) return;
        MTLScissorRect rect;
        rect.x = (NSUInteger) xx;
        rect.y = (NSUInteger) yy;
        rect.width = (NSUInteger) w;
        rect.height = (NSUInteger) h;
        [e setScissorRect:rect];
    }
}

void mtl_mtlrendercommandencoder_set_cull_mode(zval *handle, zval *cullMode)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        if (e == nil) return;
        [e setCullMode:(MTLCullMode) mtl_arg_long(cullMode)];
    }
}

void mtl_mtlrendercommandencoder_set_front_facing_winding(zval *handle, zval *frontFacingWinding)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        if (e == nil) return;
        [e setFrontFacingWinding:(MTLWinding) mtl_arg_long(frontFacingWinding)];
    }
}

void mtl_mtlrendercommandencoder_set_triangle_fill_mode(zval *handle, zval *fillMode)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        if (e == nil) return;
        [e setTriangleFillMode:(MTLTriangleFillMode) mtl_arg_long(fillMode)];
    }
}

void mtl_mtlrendercommandencoder_set_depth_stencil_state(zval *handle, zval *depthStencilState)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        if (e == nil) return;
        [e setDepthStencilState:MTL_ARG_PROTO(MTLDepthStencilState, depthStencilState)];
    }
}

void mtl_mtlrendercommandencoder_draw_primitives_vertex_start_vertex_count(zval *handle, zval *primitiveType, zval *vertexStart, zval *vertexCount)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        zend_long start = mtl_arg_long(vertexStart);
        zend_long count = mtl_arg_long(vertexCount);
        if (e == nil || start < 0 || count < 0) return;
        [e drawPrimitives:(MTLPrimitiveType) mtl_arg_long(primitiveType)
              vertexStart:(NSUInteger) start
              vertexCount:(NSUInteger) count];
    }
}

void mtl_mtlrendercommandencoder_draw_primitives_vertex_start_vertex_count_instance_count(zval *handle, zval *primitiveType, zval *vertexStart, zval *vertexCount, zval *instanceCount)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        zend_long start = mtl_arg_long(vertexStart);
        zend_long count = mtl_arg_long(vertexCount);
        zend_long instances = mtl_arg_long(instanceCount);
        if (e == nil || start < 0 || count < 0 || instances < 0) return;
        [e drawPrimitives:(MTLPrimitiveType) mtl_arg_long(primitiveType)
              vertexStart:(NSUInteger) start
              vertexCount:(NSUInteger) count
            instanceCount:(NSUInteger) instances];
    }
}

void mtl_mtlrendercommandencoder_draw_indexed_primitives_index_count_index_type_index_buffer_index_buffer_offset(zval *handle, zval *primitiveType, zval *indexCount, zval *indexType, zval *indexBuffer, zval *indexBufferOffset)
{
    @autoreleasepool {
        id<MTLRenderCommandEncoder> e = MTL_ARG_PROTO(MTLRenderCommandEncoder, handle);
        id<MTLBuffer> ib = MTL_ARG_PROTO(MTLBuffer, indexBuffer);
        zend_long count = mtl_arg_long(indexCount);
        zend_long offset = mtl_arg_long(indexBufferOffset);
        /* indexBuffer is nonnull in the SDK: an unresolvable handle is a
           no-op rather than a nil send. */
        if (e == nil || ib == nil || count < 0 || offset < 0) return;
        [e drawIndexedPrimitives:(MTLPrimitiveType) mtl_arg_long(primitiveType)
                      indexCount:(NSUInteger) count
                       indexType:(MTLIndexType) mtl_arg_long(indexType)
                     indexBuffer:ib
               indexBufferOffset:(NSUInteger) offset];
    }
}
