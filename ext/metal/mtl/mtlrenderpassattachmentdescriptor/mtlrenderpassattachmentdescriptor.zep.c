
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


ZEPHIR_INIT_CLASS(Metal_MTL_MTLRenderPassAttachmentDescriptor_MTLRenderPassAttachmentDescriptor)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLRenderPassAttachmentDescriptor, MTLRenderPassAttachmentDescriptor, metal, mtl_mtlrenderpassattachmentdescriptor_mtlrenderpassattachmentdescriptor, metal_mtl_mtlrenderpassattachmentdescriptor_mtlrenderpassattachmentdescriptor_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLRenderPassAttachmentDescriptor_MTLRenderPassAttachmentDescriptor, texture)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpassattachmentdescriptor_texture(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPassAttachmentDescriptor_MTLRenderPassAttachmentDescriptor, setTexture)
{
	zval *handle_param = NULL, *texture_param = NULL, _0, _1;
	zend_long handle, texture;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(texture)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &texture_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, texture);
	mtl_mtlrenderpassattachmentdescriptor_set_texture(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPassAttachmentDescriptor_MTLRenderPassAttachmentDescriptor, loadAction)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpassattachmentdescriptor_load_action(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPassAttachmentDescriptor_MTLRenderPassAttachmentDescriptor, setLoadAction)
{
	zval *handle_param = NULL, *loadAction_param = NULL, _0, _1;
	zend_long handle, loadAction;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(loadAction)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &loadAction_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, loadAction);
	mtl_mtlrenderpassattachmentdescriptor_set_load_action(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderPassAttachmentDescriptor_MTLRenderPassAttachmentDescriptor, storeAction)
{
	zval *handle_param = NULL, _0;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(handle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &handle_param);
	ZVAL_LONG(&_0, handle);
	RETURN_LONG(mtl_mtlrenderpassattachmentdescriptor_store_action(&_0));
}

PHP_METHOD(Metal_MTL_MTLRenderPassAttachmentDescriptor_MTLRenderPassAttachmentDescriptor, setStoreAction)
{
	zval *handle_param = NULL, *storeAction_param = NULL, _0, _1;
	zend_long handle, storeAction;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(storeAction)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &storeAction_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, storeAction);
	mtl_mtlrenderpassattachmentdescriptor_set_store_action(&_0, &_1);
}

