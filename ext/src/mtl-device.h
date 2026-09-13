#ifndef PHP_METAL_MTL_DEVICE_H
#define PHP_METAL_MTL_DEVICE_H

/*
 * Partial of the MTLDevice protocol: creation, identity, and the
 * factories the bound waves need. MTLCreateSystemDefaultDevice is a
 * C function bound as a static factory per spec §5.2. The rest of
 * MTLDevice.h is sanctioned partial.
 *
 * Wave A adds the resource/shader/pipeline factories. Two of them use
 * the sanctioned NSError** pattern: the selector's trailing error:
 * out-param is flattened into the binding name and the call returns
 * {handle: int, error: int}. Exactly one member is non-zero whenever the
 * send happened; both are zero when the binding refused to send at all
 * (nil device, or a descriptor/source argument that did not resolve).
 * The error is an NSError registry handle readable through
 * Bridge::errorDescription.
 *
 * newBufferWithBytesLengthOptions takes the PHP string only — the
 * selector's length: argument is the string's own byte length, which is
 * the one value that cannot read past the buffer PHP handed us.
 *
 * MTLCompileOptions is not bound this wave: newLibraryWithSourceOptionsError
 * takes a nullable options object and 0 means nil, which is enough to
 * compile MSL from source. Callers that need compile options wait for the
 * wave that binds that class.
 *
 * Wave B adds newComputePipelineStateWithFunctionError, the third user of
 * the NSError** pattern. Only the plain function overload binds: the
 * options:reflection: overload writes through an out-parameter and the
 * completionHandler: overloads are blocks.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLDevice wave A+B: create, name, queue/texture/buffer/library/render- and compute-pipeline/depth-stencil/sampler factories */

/*@zep MTL\MTLDevice createSystemDefault() -> int */
zend_long mtl_mtldevice_create_system_default(void);

/*@zep MTL\MTLDevice name(int handle) -> var */
void mtl_mtldevice_name(zval *return_value, zval *handle);

/*@zep MTL\MTLDevice newCommandQueue(int handle) -> int */
zend_long mtl_mtldevice_new_command_queue(zval *handle);

/*@zep MTL\MTLDevice newTextureWithDescriptor(int handle, int descriptor) -> int */
zend_long mtl_mtldevice_new_texture_with_descriptor(zval *handle, zval *descriptor);

/*@zep MTL\MTLDevice newBufferWithLengthOptions(int handle, int length, int options) -> int */
zend_long mtl_mtldevice_new_buffer_with_length_options(zval *handle, zval *length, zval *options);

/*@zep MTL\MTLDevice newBufferWithBytesLengthOptions(int handle, string bytes, int options) -> int */
zend_long mtl_mtldevice_new_buffer_with_bytes_length_options(zval *handle, zval *bytes, zval *options);

/*@zep MTL\MTLDevice newLibraryWithSourceOptionsError(int handle, string source, int options) -> array */
void mtl_mtldevice_new_library_with_source_options_error(zval *return_value, zval *handle, zval *source, zval *options);

/*@zep MTL\MTLDevice newRenderPipelineStateWithDescriptorError(int handle, int descriptor) -> array */
void mtl_mtldevice_new_render_pipeline_state_with_descriptor_error(zval *return_value, zval *handle, zval *descriptor);

/*@zep MTL\MTLDevice newComputePipelineStateWithFunctionError(int handle, int computeFunction) -> array */
void mtl_mtldevice_new_compute_pipeline_state_with_function_error(zval *return_value, zval *handle, zval *computeFunction);

/*@zep MTL\MTLDevice newDepthStencilStateWithDescriptor(int handle, int descriptor) -> int */
zend_long mtl_mtldevice_new_depth_stencil_state_with_descriptor(zval *handle, zval *descriptor);

/*@zep MTL\MTLDevice newSamplerStateWithDescriptor(int handle, int descriptor) -> int */
zend_long mtl_mtldevice_new_sampler_state_with_descriptor(zval *handle, zval *descriptor);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_DEVICE_H */
