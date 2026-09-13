
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


ZEPHIR_INIT_CLASS(Metal_MTL_MTLRenderPassColorAttachmentDescriptorArray_MTLRenderPassColorAttachmentDescriptorArray)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLRenderPassColorAttachmentDescriptorArray, MTLRenderPassColorAttachmentDescriptorArray, metal, mtl_mtlrenderpasscolorattachmentdescriptorarray_mtlrenderpasscolorattachmentdescriptorarray, metal_mtl_mtlrenderpasscolorattachmentdescriptorarray_mtlrenderpasscolorattachmentdescriptorarray_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLRenderPassColorAttachmentDescriptorArray_MTLRenderPassColorAttachmentDescriptorArray, objectAtIndexedSubscript)
{
	zval *handle_param = NULL, *attachmentIndex_param = NULL, _0, _1;
	zend_long handle, attachmentIndex;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(attachmentIndex)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &attachmentIndex_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, attachmentIndex);
	RETURN_LONG(mtl_mtlrenderpasscolorattachmentdescriptorarray_object_at_indexed_subscript(&_0, &_1));
}

PHP_METHOD(Metal_MTL_MTLRenderPassColorAttachmentDescriptorArray_MTLRenderPassColorAttachmentDescriptorArray, setObjectAtIndexedSubscript)
{
	zval *handle_param = NULL, *attachment_param = NULL, *attachmentIndex_param = NULL, _0, _1, _2;
	zend_long handle, attachment, attachmentIndex;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(attachment)
		Z_PARAM_LONG(attachmentIndex)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &handle_param, &attachment_param, &attachmentIndex_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, attachment);
	ZVAL_LONG(&_2, attachmentIndex);
	mtl_mtlrenderpasscolorattachmentdescriptorarray_set_object_at_indexed_subscript(&_0, &_1, &_2);
}

