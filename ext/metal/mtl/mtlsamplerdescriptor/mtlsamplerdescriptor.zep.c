
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "src/mtl-sampler.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLSamplerDescriptor, MTLSamplerDescriptor, metal, mtl_mtlsamplerdescriptor_mtlsamplerdescriptor, metal_mtl_mtlsamplerdescriptor_mtlsamplerdescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, init)
{

	RETURN_LONG(mtl_mtlsamplerdescriptor_init());
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, minFilter)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlsamplerdescriptor_min_filter(&_0));
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, setMinFilter)
{
	zval *handle_param = NULL, *minFilter_param = NULL, _0, _1;
	zend_long handle, minFilter;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(minFilter)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &minFilter_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, minFilter);
	mtl_mtlsamplerdescriptor_set_min_filter(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, magFilter)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlsamplerdescriptor_mag_filter(&_0));
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, setMagFilter)
{
	zval *handle_param = NULL, *magFilter_param = NULL, _0, _1;
	zend_long handle, magFilter;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(magFilter)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &magFilter_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, magFilter);
	mtl_mtlsamplerdescriptor_set_mag_filter(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, sAddressMode)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlsamplerdescriptor_s_address_mode(&_0));
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, setSAddressMode)
{
	zval *handle_param = NULL, *sAddressMode_param = NULL, _0, _1;
	zend_long handle, sAddressMode;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(sAddressMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &sAddressMode_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, sAddressMode);
	mtl_mtlsamplerdescriptor_set_s_address_mode(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, tAddressMode)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlsamplerdescriptor_t_address_mode(&_0));
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, setTAddressMode)
{
	zval *handle_param = NULL, *tAddressMode_param = NULL, _0, _1;
	zend_long handle, tAddressMode;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(tAddressMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &tAddressMode_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, tAddressMode);
	mtl_mtlsamplerdescriptor_set_t_address_mode(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, label)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *handle_param = NULL, result, _0;
	zend_long handle;

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &handle_param);
	ZEPHIR_INIT_VAR(&result);
	ZVAL_LONG(&_0, handle);
	mtl_mtlsamplerdescriptor_label(&result, &_0);
	RETURN_CCTOR(&result);
}

PHP_METHOD(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor, setLabel)
{
	zval *handle_param = NULL, *label = NULL, label_sub, _0;
	zend_long handle;

	ZVAL_UNDEF(&label_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_ZVAL(label)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &label);
	ZVAL_LONG(&_0, handle);
	mtl_mtlsamplerdescriptor_set_label(&_0, label);
}

