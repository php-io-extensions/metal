#ifndef PHP_METAL_MTL_COMPUTECOMMANDENCODER_H
#define PHP_METAL_MTL_COMPUTECOMMANDENCODER_H

/*
 * Wave B partial of the MTLComputeCommandEncoder protocol (its own
 * header). The protocol adopts MTLCommandEncoder, so endEncoding and
 * label/setLabel stay bound where the SDK declares them and a compute
 * encoder handle satisfies the conformance guard on those calls
 * unchanged.
 *
 * Construction is MTLCommandBuffer::computeCommandEncoder (factory marker
 * below). Method names are the SDK selectors flattened in the house
 * style, so setBuffer:offset:atIndex: binds as setBufferOffsetAtIndex.
 *
 * Same collision case as the render encoder: flattening is not injective
 * and setBufferOffset:atIndex: (MTLComputeCommandEncoder.h:72) flattens to
 * that very name. Per the house convention the first binding keeps the
 * plain flattened name and whichever colliding selector a later wave binds
 * takes a distinguishing suffix, chosen at bind time. Nothing here
 * reserves the other name.
 *
 * setBytes:length:atIndex: is not bound: it is a raw pointer + length
 * pair, which is the unguarded write primitive MTLBuffer's accessors were
 * written to avoid. Callers stage small constants through a buffer.
 *
 * Structs follow the house convention (components in): both MTLSize
 * arguments of the two dispatch calls cross as their three integers.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLComputeCommandEncoder wave B: pipeline state, buffer/texture binding, uniform and non-uniform dispatch */
/*@audit factory MTL\MTLComputeCommandEncoder MTLCommandBuffer::computeCommandEncoder */

/*@zep MTL\MTLComputeCommandEncoder setComputePipelineState(int handle, int state) -> void */
void mtl_mtlcomputecommandencoder_set_compute_pipeline_state(zval *handle, zval *state);

/*@zep MTL\MTLComputeCommandEncoder setBufferOffsetAtIndex(int handle, int buffer, int offset, int index) -> void */
void mtl_mtlcomputecommandencoder_set_buffer_offset_at_index(zval *handle, zval *buffer, zval *offset, zval *index);

/*@zep MTL\MTLComputeCommandEncoder setTextureAtIndex(int handle, int texture, int index) -> void */
void mtl_mtlcomputecommandencoder_set_texture_at_index(zval *handle, zval *texture, zval *index);

/*@zep MTL\MTLComputeCommandEncoder dispatchThreadgroupsThreadsPerThreadgroup(int handle, int threadgroupsPerGridWidth, int threadgroupsPerGridHeight, int threadgroupsPerGridDepth, int threadsPerThreadgroupWidth, int threadsPerThreadgroupHeight, int threadsPerThreadgroupDepth) -> void */
void mtl_mtlcomputecommandencoder_dispatch_threadgroups_threads_per_threadgroup(zval *handle, zval *threadgroupsPerGridWidth, zval *threadgroupsPerGridHeight, zval *threadgroupsPerGridDepth, zval *threadsPerThreadgroupWidth, zval *threadsPerThreadgroupHeight, zval *threadsPerThreadgroupDepth);

/*@zep MTL\MTLComputeCommandEncoder dispatchThreadsThreadsPerThreadgroup(int handle, int threadsPerGridWidth, int threadsPerGridHeight, int threadsPerGridDepth, int threadsPerThreadgroupWidth, int threadsPerThreadgroupHeight, int threadsPerThreadgroupDepth) -> void */
void mtl_mtlcomputecommandencoder_dispatch_threads_threads_per_threadgroup(zval *handle, zval *threadsPerGridWidth, zval *threadsPerGridHeight, zval *threadsPerGridDepth, zval *threadsPerThreadgroupWidth, zval *threadsPerThreadgroupHeight, zval *threadsPerThreadgroupDepth);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_COMPUTECOMMANDENCODER_H */
