
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
#include "src/mtl-renderpass.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLRenderPassDescriptor_MTLRenderPassDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLRenderPassDescriptor, MTLRenderPassDescriptor, metal, mtl_mtlrenderpassdescriptor_mtlrenderpassdescriptor, metal_mtl_mtlrenderpassdescriptor_mtlrenderpassdescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLRenderPassDescriptor_MTLRenderPassDescriptor, renderPassDescriptor)
{

	RETURN_LONG(mtl_mtlrenderpassdescriptor_render_pass_descriptor());
}

PHP_METHOD(Metal_MTL_MTLRenderPassDescriptor_MTLRenderPassDescriptor, colorAttachments)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpassdescriptor_color_attachments(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPassDescriptor_MTLRenderPassDescriptor, depthAttachment)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpassdescriptor_depth_attachment(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPassDescriptor_MTLRenderPassDescriptor, setDepthAttachment)
{
	zval *handle_param = NULL, *depthAttachment_param = NULL, _0, _1;
	zend_long handle, depthAttachment;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(depthAttachment)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &depthAttachment_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, depthAttachment);
	mtl_mtlrenderpassdescriptor_set_depth_attachment(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPassDescriptor_MTLRenderPassDescriptor, stencilAttachment)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpassdescriptor_stencil_attachment(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPassDescriptor_MTLRenderPassDescriptor, setStencilAttachment)
{
	zval *handle_param = NULL, *stencilAttachment_param = NULL, _0, _1;
	zend_long handle, stencilAttachment;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(stencilAttachment)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &stencilAttachment_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, stencilAttachment);
	mtl_mtlrenderpassdescriptor_set_stencil_attachment(&_0, &_1);
}

