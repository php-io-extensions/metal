
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

