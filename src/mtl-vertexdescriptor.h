#ifndef PHP_METAL_MTL_VERTEXDESCRIPTOR_H
#define PHP_METAL_MTL_VERTEXDESCRIPTOR_H

/*
 * Wave A partials of the MTLVertexDescriptor.h family: the descriptor
 * itself plus the attribute/layout descriptors and their subscript
 * arrays, all same-file companions.
 *
 * MTLVertexDescriptor is constructed by its own class factory
 * (+vertexDescriptor), the arrays come from attributes/layouts, and each
 * element descriptor from its array's subscript — no alloc+init anywhere
 * in this family.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLVertexDescriptor wave A: factory, attributes, layouts */

/*@zep MTL\MTLVertexDescriptor vertexDescriptor() -> int */
zend_long mtl_mtlvertexdescriptor_vertex_descriptor(void);

/*@zep MTL\MTLVertexDescriptor attributes(int handle) -> int */
zend_long mtl_mtlvertexdescriptor_attributes(zval *handle);
/*@zep MTL\MTLVertexDescriptor layouts(int handle) -> int */
zend_long mtl_mtlvertexdescriptor_layouts(zval *handle);

/*@audit partial MTL\MTLVertexAttributeDescriptorArray subscript pair */
/*@audit factory MTL\MTLVertexAttributeDescriptorArray MTLVertexDescriptor::attributes */

/*@zep MTL\MTLVertexAttributeDescriptorArray objectAtIndexedSubscript(int handle, int index) -> int */
zend_long mtl_mtlvertexattributedescriptorarray_object_at_indexed_subscript(zval *handle, zval *index);
/*@zep MTL\MTLVertexAttributeDescriptorArray setObjectAtIndexedSubscript(int handle, int attributeDesc, int index) -> void */
void mtl_mtlvertexattributedescriptorarray_set_object_at_indexed_subscript(zval *handle, zval *attributeDesc, zval *index);

/*@audit partial MTL\MTLVertexAttributeDescriptor wave A: format, offset, bufferIndex */
/*@audit factory MTL\MTLVertexAttributeDescriptor MTLVertexAttributeDescriptorArray::objectAtIndexedSubscript */

/*@zep MTL\MTLVertexAttributeDescriptor format(int handle) -> int */
zend_long mtl_mtlvertexattributedescriptor_format(zval *handle);
/*@zep MTL\MTLVertexAttributeDescriptor setFormat(int handle, int format) -> void */
void mtl_mtlvertexattributedescriptor_set_format(zval *handle, zval *format);

/*@zep MTL\MTLVertexAttributeDescriptor offset(int handle) -> int */
zend_long mtl_mtlvertexattributedescriptor_offset(zval *handle);
/*@zep MTL\MTLVertexAttributeDescriptor setOffset(int handle, int offset) -> void */
void mtl_mtlvertexattributedescriptor_set_offset(zval *handle, zval *offset);

/*@zep MTL\MTLVertexAttributeDescriptor bufferIndex(int handle) -> int */
zend_long mtl_mtlvertexattributedescriptor_buffer_index(zval *handle);
/*@zep MTL\MTLVertexAttributeDescriptor setBufferIndex(int handle, int bufferIndex) -> void */
void mtl_mtlvertexattributedescriptor_set_buffer_index(zval *handle, zval *bufferIndex);

/*@audit partial MTL\MTLVertexBufferLayoutDescriptorArray subscript pair */
/*@audit factory MTL\MTLVertexBufferLayoutDescriptorArray MTLVertexDescriptor::layouts */

/*@zep MTL\MTLVertexBufferLayoutDescriptorArray objectAtIndexedSubscript(int handle, int index) -> int */
zend_long mtl_mtlvertexbufferlayoutdescriptorarray_object_at_indexed_subscript(zval *handle, zval *index);
/*@zep MTL\MTLVertexBufferLayoutDescriptorArray setObjectAtIndexedSubscript(int handle, int bufferDesc, int index) -> void */
void mtl_mtlvertexbufferlayoutdescriptorarray_set_object_at_indexed_subscript(zval *handle, zval *bufferDesc, zval *index);

/*@audit partial MTL\MTLVertexBufferLayoutDescriptor wave A: stride, stepFunction, stepRate */
/*@audit factory MTL\MTLVertexBufferLayoutDescriptor MTLVertexBufferLayoutDescriptorArray::objectAtIndexedSubscript */

/*@zep MTL\MTLVertexBufferLayoutDescriptor stride(int handle) -> int */
zend_long mtl_mtlvertexbufferlayoutdescriptor_stride(zval *handle);
/*@zep MTL\MTLVertexBufferLayoutDescriptor setStride(int handle, int stride) -> void */
void mtl_mtlvertexbufferlayoutdescriptor_set_stride(zval *handle, zval *stride);

/*@zep MTL\MTLVertexBufferLayoutDescriptor stepFunction(int handle) -> int */
zend_long mtl_mtlvertexbufferlayoutdescriptor_step_function(zval *handle);
/*@zep MTL\MTLVertexBufferLayoutDescriptor setStepFunction(int handle, int stepFunction) -> void */
void mtl_mtlvertexbufferlayoutdescriptor_set_step_function(zval *handle, zval *stepFunction);

/*@zep MTL\MTLVertexBufferLayoutDescriptor stepRate(int handle) -> int */
zend_long mtl_mtlvertexbufferlayoutdescriptor_step_rate(zval *handle);
/*@zep MTL\MTLVertexBufferLayoutDescriptor setStepRate(int handle, int stepRate) -> void */
void mtl_mtlvertexbufferlayoutdescriptor_set_step_rate(zval *handle, zval *stepRate);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_VERTEXDESCRIPTOR_H */
