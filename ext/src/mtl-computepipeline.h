#ifndef PHP_METAL_MTL_COMPUTEPIPELINE_H
#define PHP_METAL_MTL_COMPUTEPIPELINE_H

/*
 * Wave B partial of the MTLComputePipelineState protocol, which the SDK
 * declares in MTLComputePipeline.h alongside MTLComputePipelineDescriptor
 * (not bound this wave — the descriptor path is only needed for the
 * options/reflection overloads, and the plain function factory is enough
 * to dispatch a kernel).
 *
 * Construction is MTLDevice::newComputePipelineStateWithFunctionError
 * (factory marker below), the sanctioned NSError** pattern: it returns
 * {handle: int, error: int}, exactly one of them non-zero whenever the
 * send happened, both zero when the binding refused to send at all.
 *
 * maxTotalThreadsPerThreadgroup and threadExecutionWidth are the two
 * numbers a caller needs to pick a legal threadgroup size for
 * MTLComputeCommandEncoder's dispatch calls; the ext reports them and
 * takes no position on what to do with them.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLComputePipelineState wave B: label, threadgroup sizing */
/*@audit factory MTL\MTLComputePipelineState MTLDevice::newComputePipelineStateWithFunctionError */

/*@zep MTL\MTLComputePipelineState label(int handle) -> var */
void mtl_mtlcomputepipelinestate_label(zval *return_value, zval *handle);

/*@zep MTL\MTLComputePipelineState maxTotalThreadsPerThreadgroup(int handle) -> int */
zend_long mtl_mtlcomputepipelinestate_max_total_threads_per_threadgroup(zval *handle);

/*@zep MTL\MTLComputePipelineState threadExecutionWidth(int handle) -> int */
zend_long mtl_mtlcomputepipelinestate_thread_execution_width(zval *handle);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_COMPUTEPIPELINE_H */
