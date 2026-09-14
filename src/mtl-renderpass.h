#ifndef PHP_METAL_MTL_RENDERPASS_H
#define PHP_METAL_MTL_RENDERPASS_H

/*
 * Slice-zero + Wave C partials of the MTLRenderPass.h family. All six types
 * are same-file companions and bind here. Inherited attachment members
 * (texture/loadAction/storeAction) bind once on their declaring class,
 * MTLRenderPassAttachmentDescriptor — handles are untyped, so calls work
 * on color, depth and stencil attachment instances. clearColor is
 * MTLClearColor: four doubles in, assoc array {red, green, blue, alpha} out.
 * Wave C: depth and stencil attachments and their clear values; resolve
 * filters are MSAA policy and are not bound.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLRenderPassDescriptor slice zero + wave C: factory, color/depth/stencil attachments */

/*@zep MTL\MTLRenderPassDescriptor renderPassDescriptor() -> int */
zend_long mtl_mtlrenderpassdescriptor_render_pass_descriptor(void);
/*@zep MTL\MTLRenderPassDescriptor colorAttachments(int handle) -> int */
zend_long mtl_mtlrenderpassdescriptor_color_attachments(zval *handle);
/*@zep MTL\MTLRenderPassDescriptor depthAttachment(int handle) -> int */
zend_long mtl_mtlrenderpassdescriptor_depth_attachment(zval *handle);
/*@zep MTL\MTLRenderPassDescriptor setDepthAttachment(int handle, int depthAttachment) -> void */
void mtl_mtlrenderpassdescriptor_set_depth_attachment(zval *handle, zval *depthAttachment);
/*@zep MTL\MTLRenderPassDescriptor stencilAttachment(int handle) -> int */
zend_long mtl_mtlrenderpassdescriptor_stencil_attachment(zval *handle);
/*@zep MTL\MTLRenderPassDescriptor setStencilAttachment(int handle, int stencilAttachment) -> void */
void mtl_mtlrenderpassdescriptor_set_stencil_attachment(zval *handle, zval *stencilAttachment);

/*@audit partial MTL\MTLRenderPassAttachmentDescriptor slice zero: texture, loadAction, storeAction */
/*@audit factory MTL\MTLRenderPassAttachmentDescriptor MTLRenderPassColorAttachmentDescriptorArray::objectAtIndexedSubscript */

/*@zep MTL\MTLRenderPassAttachmentDescriptor texture(int handle) -> int */
zend_long mtl_mtlrenderpassattachmentdescriptor_texture(zval *handle);
/*@zep MTL\MTLRenderPassAttachmentDescriptor setTexture(int handle, int texture) -> void */
void mtl_mtlrenderpassattachmentdescriptor_set_texture(zval *handle, zval *texture);
/*@zep MTL\MTLRenderPassAttachmentDescriptor loadAction(int handle) -> int */
zend_long mtl_mtlrenderpassattachmentdescriptor_load_action(zval *handle);
/*@zep MTL\MTLRenderPassAttachmentDescriptor setLoadAction(int handle, int loadAction) -> void */
void mtl_mtlrenderpassattachmentdescriptor_set_load_action(zval *handle, zval *loadAction);
/*@zep MTL\MTLRenderPassAttachmentDescriptor storeAction(int handle) -> int */
zend_long mtl_mtlrenderpassattachmentdescriptor_store_action(zval *handle);
/*@zep MTL\MTLRenderPassAttachmentDescriptor setStoreAction(int handle, int storeAction) -> void */
void mtl_mtlrenderpassattachmentdescriptor_set_store_action(zval *handle, zval *storeAction);

/*@audit partial MTL\MTLRenderPassColorAttachmentDescriptor slice zero: clearColor */
/*@audit factory MTL\MTLRenderPassColorAttachmentDescriptor MTLRenderPassColorAttachmentDescriptorArray::objectAtIndexedSubscript */

/*@zep MTL\MTLRenderPassColorAttachmentDescriptor clearColor(int handle) -> array */
void mtl_mtlrenderpasscolorattachmentdescriptor_clear_color(zval *return_value, zval *handle);
/*@zep MTL\MTLRenderPassColorAttachmentDescriptor setClearColor(int handle, double red, double green, double blue, double alpha) -> void */
void mtl_mtlrenderpasscolorattachmentdescriptor_set_clear_color(zval *handle, zval *red, zval *green, zval *blue, zval *alpha);

/*@audit partial MTL\MTLRenderPassColorAttachmentDescriptorArray subscript pair */
/*@audit factory MTL\MTLRenderPassColorAttachmentDescriptorArray MTLRenderPassDescriptor::colorAttachments */

/*@zep MTL\MTLRenderPassColorAttachmentDescriptorArray objectAtIndexedSubscript(int handle, int attachmentIndex) -> int */
zend_long mtl_mtlrenderpasscolorattachmentdescriptorarray_object_at_indexed_subscript(zval *handle, zval *attachmentIndex);
/*@zep MTL\MTLRenderPassColorAttachmentDescriptorArray setObjectAtIndexedSubscript(int handle, int attachment, int attachmentIndex) -> void */
void mtl_mtlrenderpasscolorattachmentdescriptorarray_set_object_at_indexed_subscript(zval *handle, zval *attachment, zval *attachmentIndex);

/*@audit partial MTL\MTLRenderPassDepthAttachmentDescriptor wave C: clearDepth (depthResolveFilter not bound: MSAA policy) */
/*@audit factory MTL\MTLRenderPassDepthAttachmentDescriptor MTLRenderPassDescriptor::depthAttachment */

/*@zep MTL\MTLRenderPassDepthAttachmentDescriptor clearDepth(int handle) -> double */
double mtl_mtlrenderpassdepthattachmentdescriptor_clear_depth(zval *handle);
/*@zep MTL\MTLRenderPassDepthAttachmentDescriptor setClearDepth(int handle, double clearDepth) -> void */
void mtl_mtlrenderpassdepthattachmentdescriptor_set_clear_depth(zval *handle, zval *clearDepth);

/*@audit partial MTL\MTLRenderPassStencilAttachmentDescriptor wave C: clearStencil (stencilResolveFilter not bound: MSAA policy) */
/*@audit factory MTL\MTLRenderPassStencilAttachmentDescriptor MTLRenderPassDescriptor::stencilAttachment */

/*@zep MTL\MTLRenderPassStencilAttachmentDescriptor clearStencil(int handle) -> int */
zend_long mtl_mtlrenderpassstencilattachmentdescriptor_clear_stencil(zval *handle);
/*@zep MTL\MTLRenderPassStencilAttachmentDescriptor setClearStencil(int handle, int clearStencil) -> void */
void mtl_mtlrenderpassstencilattachmentdescriptor_set_clear_stencil(zval *handle, zval *clearStencil);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_RENDERPASS_H */
