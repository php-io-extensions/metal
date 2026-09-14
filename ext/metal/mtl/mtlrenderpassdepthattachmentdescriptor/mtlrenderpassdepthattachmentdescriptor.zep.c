
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


ZEPHIR_INIT_CLASS(Metal_MTL_MTLRenderPassDepthAttachmentDescriptor_MTLRenderPassDepthAttachmentDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLRenderPassDepthAttachmentDescriptor, MTLRenderPassDepthAttachmentDescriptor, metal, mtl_mtlrenderpassdepthattachmentdescriptor_mtlrenderpassdepthattachmentdescriptor, metal_mtl_mtlrenderpassdepthattachmentdescriptor_mtlrenderpassdepthattachmentdescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLRenderPassDepthAttachmentDescriptor_MTLRenderPassDepthAttachmentDescriptor, clearDepth)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_DOUBLE(mtl_mtlrenderpassdepthattachmentdescriptor_clear_depth(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPassDepthAttachmentDescriptor_MTLRenderPassDepthAttachmentDescriptor, setClearDepth)
{
	double clearDepth;
	zval *handle_param = NULL, *clearDepth_param = NULL, _0, _1;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_ZVAL(clearDepth)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &clearDepth_param);
	clearDepth = zephir_get_doubleval(clearDepth_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_DOUBLE(&_1, clearDepth);
	mtl_mtlrenderpassdepthattachmentdescriptor_set_clear_depth(&_0, &_1);
}

