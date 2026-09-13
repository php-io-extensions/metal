#include "mtl-renderpass.h"
#include "mtl-value.h"
#import <Metal/Metal.h>

zend_long mtl_mtlrenderpassdescriptor_render_pass_descriptor(void)
{
    @autoreleasepool {
        return mtl_handle_for([MTLRenderPassDescriptor renderPassDescriptor]);
    }
}

zend_long mtl_mtlrenderpassdescriptor_color_attachments(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPassDescriptor *rp = MTL_ARG_AS(MTLRenderPassDescriptor, handle);
        r = rp != nil ? mtl_handle_for([rp colorAttachments]) : 0;
    }
    return r;
}

zend_long mtl_mtlrenderpassattachmentdescriptor_texture(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPassAttachmentDescriptor *a = MTL_ARG_AS(MTLRenderPassAttachmentDescriptor, handle);
        r = a != nil ? mtl_handle_for([a texture]) : 0;
    }
    return r;
}

void mtl_mtlrenderpassattachmentdescriptor_set_texture(zval *handle, zval *texture)
{
    @autoreleasepool {
        MTLRenderPassAttachmentDescriptor *a = MTL_ARG_AS(MTLRenderPassAttachmentDescriptor, handle);
        if (a == nil) return;
        [a setTexture:MTL_ARG_PROTO(MTLTexture, texture)];
    }
}

zend_long mtl_mtlrenderpassattachmentdescriptor_load_action(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPassAttachmentDescriptor *a = MTL_ARG_AS(MTLRenderPassAttachmentDescriptor, handle);
        r = a != nil ? (zend_long) [a loadAction] : 0;
    }
    return r;
}

void mtl_mtlrenderpassattachmentdescriptor_set_load_action(zval *handle, zval *loadAction)
{
    @autoreleasepool {
        MTLRenderPassAttachmentDescriptor *a = MTL_ARG_AS(MTLRenderPassAttachmentDescriptor, handle);
        if (a == nil) return;
        [a setLoadAction:(MTLLoadAction) mtl_arg_long(loadAction)];
    }
}

zend_long mtl_mtlrenderpassattachmentdescriptor_store_action(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPassAttachmentDescriptor *a = MTL_ARG_AS(MTLRenderPassAttachmentDescriptor, handle);
        r = a != nil ? (zend_long) [a storeAction] : 0;
    }
    return r;
}

void mtl_mtlrenderpassattachmentdescriptor_set_store_action(zval *handle, zval *storeAction)
{
    @autoreleasepool {
        MTLRenderPassAttachmentDescriptor *a = MTL_ARG_AS(MTLRenderPassAttachmentDescriptor, handle);
        if (a == nil) return;
        [a setStoreAction:(MTLStoreAction) mtl_arg_long(storeAction)];
    }
}

void mtl_mtlrenderpasscolorattachmentdescriptor_clear_color(zval *return_value, zval *handle)
{
    @autoreleasepool {
        MTLRenderPassColorAttachmentDescriptor *a = MTL_ARG_AS(MTLRenderPassColorAttachmentDescriptor, handle);
        if (a == nil) { array_init(return_value); return; }
        mtl_ret_clearcolor(return_value, [a clearColor]);
    }
}

void mtl_mtlrenderpasscolorattachmentdescriptor_set_clear_color(zval *handle, zval *red, zval *green, zval *blue, zval *alpha)
{
    @autoreleasepool {
        MTLRenderPassColorAttachmentDescriptor *a = MTL_ARG_AS(MTLRenderPassColorAttachmentDescriptor, handle);
        if (a == nil) return;
        [a setClearColor:MTLClearColorMake(mtl_arg_double(red), mtl_arg_double(green), mtl_arg_double(blue), mtl_arg_double(alpha))];
    }
}

zend_long mtl_mtlrenderpasscolorattachmentdescriptorarray_object_at_indexed_subscript(zval *handle, zval *attachmentIndex)
{
    zend_long r = 0;
    @autoreleasepool {
        MTLRenderPassColorAttachmentDescriptorArray *arr = MTL_ARG_AS(MTLRenderPassColorAttachmentDescriptorArray, handle);
        r = arr != nil ? mtl_handle_for([arr objectAtIndexedSubscript:(NSUInteger) mtl_arg_long(attachmentIndex)]) : 0;
    }
    return r;
}

void mtl_mtlrenderpasscolorattachmentdescriptorarray_set_object_at_indexed_subscript(zval *handle, zval *attachment, zval *attachmentIndex)
{
    @autoreleasepool {
        MTLRenderPassColorAttachmentDescriptorArray *arr = MTL_ARG_AS(MTLRenderPassColorAttachmentDescriptorArray, handle);
        if (arr == nil) return;
        [arr setObject:MTL_ARG_AS(MTLRenderPassColorAttachmentDescriptor, attachment)
   atIndexedSubscript:(NSUInteger) mtl_arg_long(attachmentIndex)];
    }
}
