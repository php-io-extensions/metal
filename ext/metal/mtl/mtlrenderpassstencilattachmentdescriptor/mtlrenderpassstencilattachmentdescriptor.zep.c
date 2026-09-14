
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLRenderPassStencilAttachmentDescriptor_MTLRenderPassStencilAttachmentDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLRenderPassStencilAttachmentDescriptor, MTLRenderPassStencilAttachmentDescriptor, metal, mtl_mtlrenderpassstencilattachmentdescriptor_mtlrenderpassstencilattachmentdescriptor, metal_mtl_mtlrenderpassstencilattachmentdescriptor_mtlrenderpassstencilattachmentdescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLRenderPassStencilAttachmentDescriptor_MTLRenderPassStencilAttachmentDescriptor, clearStencil)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpassstencilattachmentdescriptor_clear_stencil(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPassStencilAttachmentDescriptor_MTLRenderPassStencilAttachmentDescriptor, setClearStencil)
{
	zval *handle_param = NULL, *clearStencil_param = NULL, _0, _1;
	zend_long handle, clearStencil;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(clearStencil)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &clearStencil_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, clearStencil);
	mtl_mtlrenderpassstencilattachmentdescriptor_set_clear_stencil(&_0, &_1);
}

