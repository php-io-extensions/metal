#ifndef PHP_METAL_MTL_RENDERPIPELINE_H
#define PHP_METAL_MTL_RENDERPIPELINE_H

/*
 * Wave A partials of the MTLRenderPipeline.h family: the descriptor, its
 * color-attachment array + attachment descriptor, and the
 * MTLRenderPipelineState protocol. Same-file companions bind here.
 * MTLRenderPipelineReflection, the tile/mesh descriptors and the
 * functions descriptor are untouched this wave.
 *
 * Construction is alloc+init (sanctioned glue) for the descriptor; the
 * state comes from MTLDevice::newRenderPipelineStateWithDescriptorError
 * (the NSError** pattern). blendingEnabled's SDK getter is
 * isBlendingEnabled, so the binding keeps the property name and sends the
 * getter (house getter=isX rule).
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLRenderPipelineDescriptor wave A: functions, vertex descriptor, color attachments, raster sample count, label */

/*@zep-construct MTL\MTLRenderPipelineDescriptor init() -> int */
zend_long mtl_mtlrenderpipelinedescriptor_init(void);

/*@zep MTL\MTLRenderPipelineDescriptor vertexFunction(int handle) -> int */
zend_long mtl_mtlrenderpipelinedescriptor_vertex_function(zval *handle);
/*@zep MTL\MTLRenderPipelineDescriptor setVertexFunction(int handle, int vertexFunction) -> void */
void mtl_mtlrenderpipelinedescriptor_set_vertex_function(zval *handle, zval *vertexFunction);

/*@zep MTL\MTLRenderPipelineDescriptor fragmentFunction(int handle) -> int */
zend_long mtl_mtlrenderpipelinedescriptor_fragment_function(zval *handle);
/*@zep MTL\MTLRenderPipelineDescriptor setFragmentFunction(int handle, int fragmentFunction) -> void */
void mtl_mtlrenderpipelinedescriptor_set_fragment_function(zval *handle, zval *fragmentFunction);

/*@zep MTL\MTLRenderPipelineDescriptor vertexDescriptor(int handle) -> int */
zend_long mtl_mtlrenderpipelinedescriptor_vertex_descriptor(zval *handle);
/*@zep MTL\MTLRenderPipelineDescriptor setVertexDescriptor(int handle, int vertexDescriptor) -> void */
void mtl_mtlrenderpipelinedescriptor_set_vertex_descriptor(zval *handle, zval *vertexDescriptor);

/*@zep MTL\MTLRenderPipelineDescriptor rasterSampleCount(int handle) -> int */
zend_long mtl_mtlrenderpipelinedescriptor_raster_sample_count(zval *handle);
/*@zep MTL\MTLRenderPipelineDescriptor setRasterSampleCount(int handle, int rasterSampleCount) -> void */
void mtl_mtlrenderpipelinedescriptor_set_raster_sample_count(zval *handle, zval *rasterSampleCount);

/*@zep MTL\MTLRenderPipelineDescriptor colorAttachments(int handle) -> int */
zend_long mtl_mtlrenderpipelinedescriptor_color_attachments(zval *handle);

/*@zep MTL\MTLRenderPipelineDescriptor label(int handle) -> var */
void mtl_mtlrenderpipelinedescriptor_label(zval *return_value, zval *handle);
/*@zep MTL\MTLRenderPipelineDescriptor setLabel(int handle, var label) -> void */
void mtl_mtlrenderpipelinedescriptor_set_label(zval *handle, zval *label);

/*@audit partial MTL\MTLRenderPipelineColorAttachmentDescriptorArray subscript pair */
/*@audit factory MTL\MTLRenderPipelineColorAttachmentDescriptorArray MTLRenderPipelineDescriptor::colorAttachments */

/*@zep MTL\MTLRenderPipelineColorAttachmentDescriptorArray objectAtIndexedSubscript(int handle, int attachmentIndex) -> int */
zend_long mtl_mtlrenderpipelinecolorattachmentdescriptorarray_object_at_indexed_subscript(zval *handle, zval *attachmentIndex);
/*@zep MTL\MTLRenderPipelineColorAttachmentDescriptorArray setObjectAtIndexedSubscript(int handle, int attachment, int attachmentIndex) -> void */
void mtl_mtlrenderpipelinecolorattachmentdescriptorarray_set_object_at_indexed_subscript(zval *handle, zval *attachment, zval *attachmentIndex);

/*@audit partial MTL\MTLRenderPipelineColorAttachmentDescriptor wave A: pixelFormat, blendingEnabled */
/*@audit factory MTL\MTLRenderPipelineColorAttachmentDescriptor MTLRenderPipelineColorAttachmentDescriptorArray::objectAtIndexedSubscript */

/*@zep MTL\MTLRenderPipelineColorAttachmentDescriptor pixelFormat(int handle) -> int */
zend_long mtl_mtlrenderpipelinecolorattachmentdescriptor_pixel_format(zval *handle);
/*@zep MTL\MTLRenderPipelineColorAttachmentDescriptor setPixelFormat(int handle, int pixelFormat) -> void */
void mtl_mtlrenderpipelinecolorattachmentdescriptor_set_pixel_format(zval *handle, zval *pixelFormat);

/*@zep MTL\MTLRenderPipelineColorAttachmentDescriptor blendingEnabled(int handle) -> bool */
zend_long mtl_mtlrenderpipelinecolorattachmentdescriptor_blending_enabled(zval *handle);
/*@zep MTL\MTLRenderPipelineColorAttachmentDescriptor setBlendingEnabled(int handle, bool blendingEnabled) -> void */
void mtl_mtlrenderpipelinecolorattachmentdescriptor_set_blending_enabled(zval *handle, zval *blendingEnabled);

/*@audit partial MTL\MTLRenderPipelineState wave A: label */
/*@audit factory MTL\MTLRenderPipelineState MTLDevice::newRenderPipelineStateWithDescriptorError */

/*@zep MTL\MTLRenderPipelineState label(int handle) -> var */
void mtl_mtlrenderpipelinestate_label(zval *return_value, zval *handle);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_RENDERPIPELINE_H */
