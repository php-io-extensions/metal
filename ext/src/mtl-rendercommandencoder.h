#ifndef PHP_METAL_MTL_RENDERCOMMANDENCODER_H
#define PHP_METAL_MTL_RENDERCOMMANDENCODER_H

/*
 * Wave A partial of the MTLRenderCommandEncoder protocol (its own
 * header). endEncoding/label stay bound on MTLCommandEncoder, where the
 * SDK declares them; handles are untyped, so a render-encoder handle
 * passes through those calls unchanged.
 *
 * Construction is MTLCommandBuffer::renderCommandEncoderWithDescriptor
 * (factory marker below). Method names are the SDK selectors flattened in
 * the house style, so setVertexBuffer:offset:atIndex: binds as
 * setVertexBufferOffsetAtIndex.
 *
 * Flattening is not injective: setVertexBufferOffset:atIndex: (and the
 * setFragmentBuffer/setFragmentBufferOffset pair, and the attributeStride
 * overloads) flatten to that same name. Per the appkit collision
 * precedent (drawKnob/drawKnobRect, postNotificationNameObject/
 * ...UserInfo), the first binding keeps the plain flattened name and
 * whichever colliding selector a later wave binds takes a distinguishing
 * suffix, chosen at bind time.
 *
 * Structs follow the house convention (components in): MTLViewport as its
 * six doubles, MTLScissorRect as its four integers.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLRenderCommandEncoder wave A: pipeline/resource binding, viewport, scissor, raster state, draws */
/*@audit factory MTL\MTLRenderCommandEncoder MTLCommandBuffer::renderCommandEncoderWithDescriptor */

/*@zep MTL\MTLRenderCommandEncoder setRenderPipelineState(int handle, int pipelineState) -> void */
void mtl_mtlrendercommandencoder_set_render_pipeline_state(zval *handle, zval *pipelineState);

/*@zep MTL\MTLRenderCommandEncoder setVertexBufferOffsetAtIndex(int handle, int buffer, int offset, int index) -> void */
void mtl_mtlrendercommandencoder_set_vertex_buffer_offset_at_index(zval *handle, zval *buffer, zval *offset, zval *index);

/*@zep MTL\MTLRenderCommandEncoder setFragmentBufferOffsetAtIndex(int handle, int buffer, int offset, int index) -> void */
void mtl_mtlrendercommandencoder_set_fragment_buffer_offset_at_index(zval *handle, zval *buffer, zval *offset, zval *index);

/*@zep MTL\MTLRenderCommandEncoder setVertexTextureAtIndex(int handle, int texture, int index) -> void */
void mtl_mtlrendercommandencoder_set_vertex_texture_at_index(zval *handle, zval *texture, zval *index);

/*@zep MTL\MTLRenderCommandEncoder setFragmentTextureAtIndex(int handle, int texture, int index) -> void */
void mtl_mtlrendercommandencoder_set_fragment_texture_at_index(zval *handle, zval *texture, zval *index);

/*@zep MTL\MTLRenderCommandEncoder setFragmentSamplerStateAtIndex(int handle, int sampler, int index) -> void */
void mtl_mtlrendercommandencoder_set_fragment_sampler_state_at_index(zval *handle, zval *sampler, zval *index);

/*@zep MTL\MTLRenderCommandEncoder setViewport(int handle, double originX, double originY, double width, double height, double znear, double zfar) -> void */
void mtl_mtlrendercommandencoder_set_viewport(zval *handle, zval *originX, zval *originY, zval *width, zval *height, zval *znear, zval *zfar);

/*@zep MTL\MTLRenderCommandEncoder setScissorRect(int handle, int x, int y, int width, int height) -> void */
void mtl_mtlrendercommandencoder_set_scissor_rect(zval *handle, zval *x, zval *y, zval *width, zval *height);

/*@zep MTL\MTLRenderCommandEncoder setCullMode(int handle, int cullMode) -> void */
void mtl_mtlrendercommandencoder_set_cull_mode(zval *handle, zval *cullMode);

/*@zep MTL\MTLRenderCommandEncoder setFrontFacingWinding(int handle, int frontFacingWinding) -> void */
void mtl_mtlrendercommandencoder_set_front_facing_winding(zval *handle, zval *frontFacingWinding);

/*@zep MTL\MTLRenderCommandEncoder setTriangleFillMode(int handle, int fillMode) -> void */
void mtl_mtlrendercommandencoder_set_triangle_fill_mode(zval *handle, zval *fillMode);

/*@zep MTL\MTLRenderCommandEncoder setDepthStencilState(int handle, int depthStencilState) -> void */
void mtl_mtlrendercommandencoder_set_depth_stencil_state(zval *handle, zval *depthStencilState);

/*@zep MTL\MTLRenderCommandEncoder drawPrimitivesVertexStartVertexCount(int handle, int primitiveType, int vertexStart, int vertexCount) -> void */
void mtl_mtlrendercommandencoder_draw_primitives_vertex_start_vertex_count(zval *handle, zval *primitiveType, zval *vertexStart, zval *vertexCount);

/*@zep MTL\MTLRenderCommandEncoder drawPrimitivesVertexStartVertexCountInstanceCount(int handle, int primitiveType, int vertexStart, int vertexCount, int instanceCount) -> void */
void mtl_mtlrendercommandencoder_draw_primitives_vertex_start_vertex_count_instance_count(zval *handle, zval *primitiveType, zval *vertexStart, zval *vertexCount, zval *instanceCount);

/*@zep MTL\MTLRenderCommandEncoder drawIndexedPrimitivesIndexCountIndexTypeIndexBufferIndexBufferOffset(int handle, int primitiveType, int indexCount, int indexType, int indexBuffer, int indexBufferOffset) -> void */
void mtl_mtlrendercommandencoder_draw_indexed_primitives_index_count_index_type_index_buffer_index_buffer_offset(zval *handle, zval *primitiveType, zval *indexCount, zval *indexType, zval *indexBuffer, zval *indexBufferOffset);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_RENDERCOMMANDENCODER_H */
