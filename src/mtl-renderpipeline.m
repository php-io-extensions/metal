#include "mtl-renderpipeline.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtlrenderpipelinedescriptor_init(void)
{
    @autoreleasepool {
        return mtl_handle_for([[MTLRenderPipelineDescriptor alloc] init]);
    }
}

zend_long mtl_mtlrenderpipelinedescriptor_vertex_function(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        r = d != nil ? mtl_handle_for([d vertexFunction]) : 0;
    }
    return r;
}

void mtl_mtlrenderpipelinedescriptor_set_vertex_function(zval *handle, zval *vertexFunction)
{
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        if (d == nil) return;
        [d setVertexFunction:MTL_ARG_PROTO(MTLFunction, vertexFunction)];
    }
}

zend_long mtl_mtlrenderpipelinedescriptor_fragment_function(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        r = d != nil ? mtl_handle_for([d fragmentFunction]) : 0;
    }
    return r;
}

void mtl_mtlrenderpipelinedescriptor_set_fragment_function(zval *handle, zval *fragmentFunction)
{
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        if (d == nil) return;
        [d setFragmentFunction:MTL_ARG_PROTO(MTLFunction, fragmentFunction)];
    }
}

zend_long mtl_mtlrenderpipelinedescriptor_vertex_descriptor(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        r = d != nil ? mtl_handle_for([d vertexDescriptor]) : 0;
    }
    return r;
}

void mtl_mtlrenderpipelinedescriptor_set_vertex_descriptor(zval *handle, zval *vertexDescriptor)
{
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        if (d == nil) return;
        [d setVertexDescriptor:MTL_ARG_AS(MTLVertexDescriptor, vertexDescriptor)];
    }
}

zend_long mtl_mtlrenderpipelinedescriptor_raster_sample_count(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        r = d != nil ? (zend_long) [d rasterSampleCount] : 0;
    }
    return r;
}

void mtl_mtlrenderpipelinedescriptor_set_raster_sample_count(zval *handle, zval *rasterSampleCount)
{
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        if (d == nil) return;
        [d setRasterSampleCount:(NSUInteger) mtl_arg_long(rasterSampleCount)];
    }
}

zend_long mtl_mtlrenderpipelinedescriptor_color_attachments(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        r = d != nil ? mtl_handle_for([d colorAttachments]) : 0;
    }
    return r;
}

void mtl_mtlrenderpipelinedescriptor_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        NSString *s = d != nil ? [d label] : nil;
        if (s == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, s);
    }
}

void mtl_mtlrenderpipelinedescriptor_set_label(zval *handle, zval *label)
{
    @autoreleasepool {
        MTLRenderPipelineDescriptor *d = MTL_ARG_AS(MTLRenderPipelineDescriptor, handle);
        if (d == nil) return;
        [d setLabel:(Z_TYPE_P(label) == IS_NULL ? nil : mtl_arg_string(label))];
    }
}

zend_long mtl_mtlrenderpipelinecolorattachmentdescriptorarray_object_at_indexed_subscript(zval *handle, zval *attachmentIndex)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPipelineColorAttachmentDescriptorArray *arr =
            MTL_ARG_AS(MTLRenderPipelineColorAttachmentDescriptorArray, handle);
        r = arr != nil ? mtl_handle_for([arr objectAtIndexedSubscript:(NSUInteger) mtl_arg_long(attachmentIndex)]) : 0;
    }
    return r;
}

void mtl_mtlrenderpipelinecolorattachmentdescriptorarray_set_object_at_indexed_subscript(zval *handle, zval *attachment, zval *attachmentIndex)
{
    @autoreleasepool {
        MTLRenderPipelineColorAttachmentDescriptorArray *arr =
            MTL_ARG_AS(MTLRenderPipelineColorAttachmentDescriptorArray, handle);
        if (arr == nil) return;
        [arr setObject:MTL_ARG_AS(MTLRenderPipelineColorAttachmentDescriptor, attachment)
    atIndexedSubscript:(NSUInteger) mtl_arg_long(attachmentIndex)];
    }
}

zend_long mtl_mtlrenderpipelinecolorattachmentdescriptor_pixel_format(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPipelineColorAttachmentDescriptor *a =
            MTL_ARG_AS(MTLRenderPipelineColorAttachmentDescriptor, handle);
        r = a != nil ? (zend_long) [a pixelFormat] : 0;
    }
    return r;
}

void mtl_mtlrenderpipelinecolorattachmentdescriptor_set_pixel_format(zval *handle, zval *pixelFormat)
{
    @autoreleasepool {
        MTLRenderPipelineColorAttachmentDescriptor *a =
            MTL_ARG_AS(MTLRenderPipelineColorAttachmentDescriptor, handle);
        if (a == nil) return;
        [a setPixelFormat:(MTLPixelFormat) mtl_arg_long(pixelFormat)];
    }
}

zend_long mtl_mtlrenderpipelinecolorattachmentdescriptor_blending_enabled(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPipelineColorAttachmentDescriptor *a =
            MTL_ARG_AS(MTLRenderPipelineColorAttachmentDescriptor, handle);
        r = (a != nil && [a isBlendingEnabled]) ? 1 : 0;
    }
    return r;
}

void mtl_mtlrenderpipelinecolorattachmentdescriptor_set_blending_enabled(zval *handle, zval *blendingEnabled)
{
    @autoreleasepool {
        MTLRenderPipelineColorAttachmentDescriptor *a =
            MTL_ARG_AS(MTLRenderPipelineColorAttachmentDescriptor, handle);
        if (a == nil) return;
        [a setBlendingEnabled:mtl_arg_bool(blendingEnabled)];
    }
}

void mtl_mtlrenderpipelinestate_label(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id<MTLRenderPipelineState> s = MTL_ARG_PROTO(MTLRenderPipelineState, handle);
        NSString *l = s != nil ? [s label] : nil;
        if (l == nil) { ZVAL_NULL(return_value); return; }
        mtl_ret_string(return_value, l);
    }
}
