#ifndef PHP_METAL_MTL_RENDERPASS_H
#define PHP_METAL_MTL_RENDERPASS_H

/*
 * Slice-zero partials of the MTLRenderPass.h family. All four types are
 * same-file companions and bind here. Inherited attachment members
 * (texture/loadAction/storeAction) bind once on their declaring class,
 * MTLRenderPassAttachmentDescriptor — handles are untyped, so calls work
 * on color-attachment instances. clearColor is MTLClearColor: four
 * doubles in, assoc array {red, green, blue, alpha} out.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLRenderPassDescriptor slice zero: factory + colorAttachments */

/*@zep MTL\MTLRenderPassDescriptor renderPassDescriptor() -> int */
zend_long mtl_mtlrenderpassdescriptor_render_pass_descriptor(void);
/*@zep MTL\MTLRenderPassDescriptor colorAttachments(int handle) -> int */
zend_long mtl_mtlrenderpassdescriptor_color_attachments(zval *handle);

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

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_RENDERPASS_H */
