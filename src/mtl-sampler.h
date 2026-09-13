#ifndef PHP_METAL_MTL_SAMPLER_H
#define PHP_METAL_MTL_SAMPLER_H

/*
 * Wave A partials of Metal's MTLSampler.h: MTLSamplerDescriptor
 * (alloc+init construction glue) and the MTLSamplerState protocol,
 * produced by MTLDevice::newSamplerStateWithDescriptor. The remaining
 * descriptor properties (mip/lod/anisotropy/compare/border) and the
 * state's device + gpuResourceID accessors are untouched this wave.
 */

#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

/*@audit partial MTL\MTLSamplerDescriptor wave A: min/mag filter, s/t address mode, label */

/*@zep-construct MTL\MTLSamplerDescriptor init() -> int */
zend_long mtl_mtlsamplerdescriptor_init(void);

/*@zep MTL\MTLSamplerDescriptor minFilter(int handle) -> int */
zend_long mtl_mtlsamplerdescriptor_min_filter(zval *handle);
/*@zep MTL\MTLSamplerDescriptor setMinFilter(int handle, int minFilter) -> void */
void mtl_mtlsamplerdescriptor_set_min_filter(zval *handle, zval *minFilter);

/*@zep MTL\MTLSamplerDescriptor magFilter(int handle) -> int */
zend_long mtl_mtlsamplerdescriptor_mag_filter(zval *handle);
/*@zep MTL\MTLSamplerDescriptor setMagFilter(int handle, int magFilter) -> void */
void mtl_mtlsamplerdescriptor_set_mag_filter(zval *handle, zval *magFilter);

/*@zep MTL\MTLSamplerDescriptor sAddressMode(int handle) -> int */
zend_long mtl_mtlsamplerdescriptor_s_address_mode(zval *handle);
/*@zep MTL\MTLSamplerDescriptor setSAddressMode(int handle, int sAddressMode) -> void */
void mtl_mtlsamplerdescriptor_set_s_address_mode(zval *handle, zval *sAddressMode);

/*@zep MTL\MTLSamplerDescriptor tAddressMode(int handle) -> int */
zend_long mtl_mtlsamplerdescriptor_t_address_mode(zval *handle);
/*@zep MTL\MTLSamplerDescriptor setTAddressMode(int handle, int tAddressMode) -> void */
void mtl_mtlsamplerdescriptor_set_t_address_mode(zval *handle, zval *tAddressMode);

/*@zep MTL\MTLSamplerDescriptor label(int handle) -> var */
void mtl_mtlsamplerdescriptor_label(zval *return_value, zval *handle);
/*@zep MTL\MTLSamplerDescriptor setLabel(int handle, var label) -> void */
void mtl_mtlsamplerdescriptor_set_label(zval *handle, zval *label);

/*@audit partial MTL\MTLSamplerState wave A: label */
/*@audit factory MTL\MTLSamplerState MTLDevice::newSamplerStateWithDescriptor */

/*@zep MTL\MTLSamplerState label(int handle) -> var */
void mtl_mtlsamplerstate_label(zval *return_value, zval *handle);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MTL_SAMPLER_H */
