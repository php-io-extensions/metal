#ifndef PHP_METAL_MTL_COMMANDBUFFER_H
#define PHP_METAL_MTL_COMMANDBUFFER_H

/*
 * Slice-zero partial of the MTLCommandBuffer protocol. Sync paths only:
 * commit + waitUntilCompleted. addCompletedHandler and friends are
 * blocks and stay reserved for a future Bridge pattern. error supports
 * the NSError reader on Bridge.
 *
 * Wave B adds the compute and blit encoder factories. Only the
 * no-argument forms bind: computeCommandEncoderWithDescriptor: and
 * blitCommandEncoderWithDescriptor: need MTLComputePassDescriptor /
 * MTLBlitPassDescriptor, which are not bound this wave, and
 * computeCommandEncoderWithDispatchType: is a concurrency opinion this
 * extension does not take for the caller.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLCommandBuffer slice zero + wave B: render/compute/blit encoder factories, present, commit, wait, status, error */
/*@audit factory MTL\MTLCommandBuffer MTLCommandQueue::commandBuffer */

/*@zep MTL\MTLCommandBuffer renderCommandEncoderWithDescriptor(int handle, int descriptor) -> int */
zend_long mtl_mtlcommandbuffer_render_command_encoder_with_descriptor(zval *handle, zval *descriptor);

/*@zep MTL\MTLCommandBuffer computeCommandEncoder(int handle) -> int */
zend_long mtl_mtlcommandbuffer_compute_command_encoder(zval *handle);

/*@zep MTL\MTLCommandBuffer blitCommandEncoder(int handle) -> int */
zend_long mtl_mtlcommandbuffer_blit_command_encoder(zval *handle);

/*@zep MTL\MTLCommandBuffer presentDrawable(int handle, int drawable) -> void */
void mtl_mtlcommandbuffer_present_drawable(zval *handle, zval *drawable);

/*@zep MTL\MTLCommandBuffer commit(int handle) -> void */
void mtl_mtlcommandbuffer_commit(zval *handle);

/*@zep MTL\MTLCommandBuffer waitUntilCompleted(int handle) -> void */
void mtl_mtlcommandbuffer_wait_until_completed(zval *handle);

/*@zep MTL\MTLCommandBuffer status(int handle) -> int */
zend_long mtl_mtlcommandbuffer_status(zval *handle);

/*@zep MTL\MTLCommandBuffer error(int handle) -> int */
zend_long mtl_mtlcommandbuffer_error(zval *handle);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_COMMANDBUFFER_H */
