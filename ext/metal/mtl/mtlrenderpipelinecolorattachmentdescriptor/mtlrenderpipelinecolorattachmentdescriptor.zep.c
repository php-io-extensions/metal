
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

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, sourceRGBBlendFactor)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinecolorattachmentdescriptor_source_rgb_blend_factor(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, setSourceRGBBlendFactor)
{
	zval *handle_param = NULL, *sourceRGBBlendFactor_param = NULL, _0, _1;
	zend_long handle, sourceRGBBlendFactor;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(sourceRGBBlendFactor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &sourceRGBBlendFactor_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, sourceRGBBlendFactor);
	mtl_mtlrenderpipelinecolorattachmentdescriptor_set_source_rgb_blend_factor(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, destinationRGBBlendFactor)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinecolorattachmentdescriptor_destination_rgb_blend_factor(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, setDestinationRGBBlendFactor)
{
	zval *handle_param = NULL, *destinationRGBBlendFactor_param = NULL, _0, _1;
	zend_long handle, destinationRGBBlendFactor;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(destinationRGBBlendFactor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &destinationRGBBlendFactor_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, destinationRGBBlendFactor);
	mtl_mtlrenderpipelinecolorattachmentdescriptor_set_destination_rgb_blend_factor(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, rgbBlendOperation)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinecolorattachmentdescriptor_rgb_blend_operation(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, setRgbBlendOperation)
{
	zval *handle_param = NULL, *rgbBlendOperation_param = NULL, _0, _1;
	zend_long handle, rgbBlendOperation;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(rgbBlendOperation)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &rgbBlendOperation_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, rgbBlendOperation);
	mtl_mtlrenderpipelinecolorattachmentdescriptor_set_rgb_blend_operation(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, sourceAlphaBlendFactor)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinecolorattachmentdescriptor_source_alpha_blend_factor(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, setSourceAlphaBlendFactor)
{
	zval *handle_param = NULL, *sourceAlphaBlendFactor_param = NULL, _0, _1;
	zend_long handle, sourceAlphaBlendFactor;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(sourceAlphaBlendFactor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &sourceAlphaBlendFactor_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, sourceAlphaBlendFactor);
	mtl_mtlrenderpipelinecolorattachmentdescriptor_set_source_alpha_blend_factor(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, destinationAlphaBlendFactor)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinecolorattachmentdescriptor_destination_alpha_blend_factor(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, setDestinationAlphaBlendFactor)
{
	zval *handle_param = NULL, *destinationAlphaBlendFactor_param = NULL, _0, _1;
	zend_long handle, destinationAlphaBlendFactor;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(destinationAlphaBlendFactor)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &destinationAlphaBlendFactor_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, destinationAlphaBlendFactor);
	mtl_mtlrenderpipelinecolorattachmentdescriptor_set_destination_alpha_blend_factor(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, alphaBlendOperation)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinecolorattachmentdescriptor_alpha_blend_operation(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, setAlphaBlendOperation)
{
	zval *handle_param = NULL, *alphaBlendOperation_param = NULL, _0, _1;
	zend_long handle, alphaBlendOperation;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(alphaBlendOperation)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &alphaBlendOperation_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, alphaBlendOperation);
	mtl_mtlrenderpipelinecolorattachmentdescriptor_set_alpha_blend_operation(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, writeMask)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpipelinecolorattachmentdescriptor_write_mask(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor, setWriteMask)
{
	zval *handle_param = NULL, *writeMask_param = NULL, _0, _1;
	zend_long handle, writeMask;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(writeMask)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &writeMask_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, writeMask);
	mtl_mtlrenderpipelinecolorattachmentdescriptor_set_write_mask(&_0, &_1);
}

