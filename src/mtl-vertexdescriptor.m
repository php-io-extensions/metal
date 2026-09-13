#include "mtl-vertexdescriptor.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtlvertexdescriptor_vertex_descriptor(void)
{
    @autoreleasepool {
        return mtl_handle_for([MTLVertexDescriptor vertexDescriptor]);
    }
}

zend_long mtl_mtlvertexdescriptor_attributes(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLVertexDescriptor *d = MTL_ARG_AS(MTLVertexDescriptor, handle);
        r = d != nil ? mtl_handle_for([d attributes]) : 0;
    }
    return r;
}

zend_long mtl_mtlvertexdescriptor_layouts(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLVertexDescriptor *d = MTL_ARG_AS(MTLVertexDescriptor, handle);
        r = d != nil ? mtl_handle_for([d layouts]) : 0;
    }
    return r;
}

zend_long mtl_mtlvertexattributedescriptorarray_object_at_indexed_subscript(zval *handle, zval *index)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLVertexAttributeDescriptorArray *arr = MTL_ARG_AS(MTLVertexAttributeDescriptorArray, handle);
        r = arr != nil ? mtl_handle_for([arr objectAtIndexedSubscript:(NSUInteger) mtl_arg_long(index)]) : 0;
    }
    return r;
}

void mtl_mtlvertexattributedescriptorarray_set_object_at_indexed_subscript(zval *handle, zval *attributeDesc, zval *index)
{
    @autoreleasepool {
        MTLVertexAttributeDescriptorArray *arr = MTL_ARG_AS(MTLVertexAttributeDescriptorArray, handle);
        if (arr == nil) return;
        [arr setObject:MTL_ARG_AS(MTLVertexAttributeDescriptor, attributeDesc)
    atIndexedSubscript:(NSUInteger) mtl_arg_long(index)];
    }
}

zend_long mtl_mtlvertexattributedescriptor_format(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLVertexAttributeDescriptor *a = MTL_ARG_AS(MTLVertexAttributeDescriptor, handle);
        r = a != nil ? (zend_long) [a format] : 0;
    }
    return r;
}

void mtl_mtlvertexattributedescriptor_set_format(zval *handle, zval *format)
{
    @autoreleasepool {
        MTLVertexAttributeDescriptor *a = MTL_ARG_AS(MTLVertexAttributeDescriptor, handle);
        if (a == nil) return;
        [a setFormat:(MTLVertexFormat) mtl_arg_long(format)];
    }
}

zend_long mtl_mtlvertexattributedescriptor_offset(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLVertexAttributeDescriptor *a = MTL_ARG_AS(MTLVertexAttributeDescriptor, handle);
        r = a != nil ? (zend_long) [a offset] : 0;
    }
    return r;
}

void mtl_mtlvertexattributedescriptor_set_offset(zval *handle, zval *offset)
{
    @autoreleasepool {
        MTLVertexAttributeDescriptor *a = MTL_ARG_AS(MTLVertexAttributeDescriptor, handle);
        if (a == nil) return;
        [a setOffset:(NSUInteger) mtl_arg_long(offset)];
    }
}

zend_long mtl_mtlvertexattributedescriptor_buffer_index(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLVertexAttributeDescriptor *a = MTL_ARG_AS(MTLVertexAttributeDescriptor, handle);
        r = a != nil ? (zend_long) [a bufferIndex] : 0;
    }
    return r;
}

void mtl_mtlvertexattributedescriptor_set_buffer_index(zval *handle, zval *bufferIndex)
{
    @autoreleasepool {
        MTLVertexAttributeDescriptor *a = MTL_ARG_AS(MTLVertexAttributeDescriptor, handle);
        if (a == nil) return;
        [a setBufferIndex:(NSUInteger) mtl_arg_long(bufferIndex)];
    }
}

zend_long mtl_mtlvertexbufferlayoutdescriptorarray_object_at_indexed_subscript(zval *handle, zval *index)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLVertexBufferLayoutDescriptorArray *arr = MTL_ARG_AS(MTLVertexBufferLayoutDescriptorArray, handle);
        r = arr != nil ? mtl_handle_for([arr objectAtIndexedSubscript:(NSUInteger) mtl_arg_long(index)]) : 0;
    }
    return r;
}

void mtl_mtlvertexbufferlayoutdescriptorarray_set_object_at_indexed_subscript(zval *handle, zval *bufferDesc, zval *index)
{
    @autoreleasepool {
        MTLVertexBufferLayoutDescriptorArray *arr = MTL_ARG_AS(MTLVertexBufferLayoutDescriptorArray, handle);
        if (arr == nil) return;
        [arr setObject:MTL_ARG_AS(MTLVertexBufferLayoutDescriptor, bufferDesc)
    atIndexedSubscript:(NSUInteger) mtl_arg_long(index)];
    }
}

zend_long mtl_mtlvertexbufferlayoutdescriptor_stride(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLVertexBufferLayoutDescriptor *l = MTL_ARG_AS(MTLVertexBufferLayoutDescriptor, handle);
        r = l != nil ? (zend_long) [l stride] : 0;
    }
    return r;
}

void mtl_mtlvertexbufferlayoutdescriptor_set_stride(zval *handle, zval *stride)
{
    @autoreleasepool {
        MTLVertexBufferLayoutDescriptor *l = MTL_ARG_AS(MTLVertexBufferLayoutDescriptor, handle);
        if (l == nil) return;
        [l setStride:(NSUInteger) mtl_arg_long(stride)];
    }
}

zend_long mtl_mtlvertexbufferlayoutdescriptor_step_function(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLVertexBufferLayoutDescriptor *l = MTL_ARG_AS(MTLVertexBufferLayoutDescriptor, handle);
        r = l != nil ? (zend_long) [l stepFunction] : 0;
    }
    return r;
}

void mtl_mtlvertexbufferlayoutdescriptor_set_step_function(zval *handle, zval *stepFunction)
{
    @autoreleasepool {
        MTLVertexBufferLayoutDescriptor *l = MTL_ARG_AS(MTLVertexBufferLayoutDescriptor, handle);
        if (l == nil) return;
        [l setStepFunction:(MTLVertexStepFunction) mtl_arg_long(stepFunction)];
    }
}

zend_long mtl_mtlvertexbufferlayoutdescriptor_step_rate(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLVertexBufferLayoutDescriptor *l = MTL_ARG_AS(MTLVertexBufferLayoutDescriptor, handle);
        r = l != nil ? (zend_long) [l stepRate] : 0;
    }
    return r;
}

void mtl_mtlvertexbufferlayoutdescriptor_set_step_rate(zval *handle, zval *stepRate)
{
    @autoreleasepool {
        MTLVertexBufferLayoutDescriptor *l = MTL_ARG_AS(MTLVertexBufferLayoutDescriptor, handle);
        if (l == nil) return;
        [l setStepRate:(NSUInteger) mtl_arg_long(stepRate)];
    }
}
