
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
#include "src/mtl-renderpipeline.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLRenderPipelineColorAttachmentDescriptor, MTLRenderPipelineColorAttachmentDescriptor, metal, mtl_mtlrenderpipelinecolorattachmentdescriptor_mtlrenderpipelinecolorattachmentdescriptor, metal_mtl_mtlrenderpipelinecolorattachmentdescriptor_mtlrenderpipelinecolorattachmentdescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, pixelFormat)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinecolorattachmentdescriptor_pixel_format(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, setPixelFormat)
{
	zval *handle_param = NULL, *pixelFormat_param = NULL, _0, _1;
	zend_long handle, pixelFormat;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(pixelFormat)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &pixelFormat_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, pixelFormat);
	mtl_mtlrenderpipelinecolorattachmentdescriptor_set_pixel_format(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, blendingEnabled)
{
	zval *handle_param = NULL, _0;
	zend_long handle, r = 0;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	r = mtl_mtlrenderpipelinecolorattachmentdescriptor_blending_enabled(&_0);
	RETURN_BOOL(r == 1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, setBlendingEnabled)
{
	zend_bool blendingEnabled;
	zval *handle_param = NULL, *blendingEnabled_param = NULL, _0, _1;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_BOOL(blendingEnabled)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &blendingEnabled_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_BOOL(&_1, (blendingEnabled ? 1 : 0));
	mtl_mtlrenderpipelinecolorattachmentdescriptor_set_blending_enabled(&_0, &_1);
}

