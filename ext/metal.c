
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "metal.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *metal_bridge_bridge_ce;
zend_class_entry *metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_ce;
zend_class_entry *metal_mtl_mtlbuffer_mtlbuffer_ce;
zend_class_entry *metal_mtl_mtlcommandbuffer_mtlcommandbuffer_ce;
zend_class_entry *metal_mtl_mtlcommandencoder_mtlcommandencoder_ce;
zend_class_entry *metal_mtl_mtlcommandqueue_mtlcommandqueue_ce;
zend_class_entry *metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_ce;
zend_class_entry *metal_mtl_mtlcomputepipelinestate_mtlcomputepipelinestate_ce;
zend_class_entry *metal_mtl_mtldepthstencildescriptor_mtldepthstencildescriptor_ce;
zend_class_entry *metal_mtl_mtldepthstencilstate_mtldepthstencilstate_ce;
zend_class_entry *metal_mtl_mtldevice_mtldevice_ce;
zend_class_entry *metal_mtl_mtlfunction_mtlfunction_ce;
zend_class_entry *metal_mtl_mtllibrary_mtllibrary_ce;
zend_class_entry *metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_ce;
zend_class_entry *metal_mtl_mtlrenderpassattachmentdescriptor_mtlrenderpassattachmentdescriptor_ce;
zend_class_entry *metal_mtl_mtlrenderpasscolorattachmentdescriptor_mtlrenderpasscolorattachmentdescriptor_ce;
zend_class_entry *metal_mtl_mtlrenderpasscolorattachmentdescriptorarray_mtlrenderpasscolorattachmentdescriptorarray_ce;
zend_class_entry *metal_mtl_mtlrenderpassdepthattachmentdescriptor_mtlrenderpassdepthattachmentdescriptor_ce;
zend_class_entry *metal_mtl_mtlrenderpassdescriptor_mtlrenderpassdescriptor_ce;
zend_class_entry *metal_mtl_mtlrenderpassstencilattachmentdescriptor_mtlrenderpassstencilattachmentdescriptor_ce;
zend_class_entry *metal_mtl_mtlrenderpipelinecolorattachmentdescriptor_mtlrenderpipelinecolorattachmentdescriptor_ce;
zend_class_entry *metal_mtl_mtlrenderpipelinecolorattachmentdescriptorarray_mtlrenderpipelinecolorattachmentdescriptorarray_ce;
zend_class_entry *metal_mtl_mtlrenderpipelinedescriptor_mtlrenderpipelinedescriptor_ce;
zend_class_entry *metal_mtl_mtlrenderpipelinestate_mtlrenderpipelinestate_ce;
zend_class_entry *metal_mtl_mtlsamplerdescriptor_mtlsamplerdescriptor_ce;
zend_class_entry *metal_mtl_mtlsamplerstate_mtlsamplerstate_ce;
zend_class_entry *metal_mtl_mtltexture_mtltexture_ce;
zend_class_entry *metal_mtl_mtltexturedescriptor_mtltexturedescriptor_ce;
zend_class_entry *metal_mtl_mtlvertexattributedescriptor_mtlvertexattributedescriptor_ce;
zend_class_entry *metal_mtl_mtlvertexattributedescriptorarray_mtlvertexattributedescriptorarray_ce;
zend_class_entry *metal_mtl_mtlvertexbufferlayoutdescriptor_mtlvertexbufferlayoutdescriptor_ce;
zend_class_entry *metal_mtl_mtlvertexbufferlayoutdescriptorarray_mtlvertexbufferlayoutdescriptorarray_ce;
zend_class_entry *metal_mtl_mtlvertexdescriptor_mtlvertexdescriptor_ce;
zend_class_entry *metal_quartzcore_cametaldrawable_cametaldrawable_ce;
zend_class_entry *metal_quartzcore_cametallayer_cametallayer_ce;

ZEND_DECLARE_MODULE_GLOBALS(metal)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(metal)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Metal_Bridge_Bridge);
	ZEPHIR_INIT(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder);
	ZEPHIR_INIT(Metal_MTL_MTLBuffer_MTLBuffer);
	ZEPHIR_INIT(Metal_MTL_MTLCommandBuffer_MTLCommandBuffer);
	ZEPHIR_INIT(Metal_MTL_MTLCommandEncoder_MTLCommandEncoder);
	ZEPHIR_INIT(Metal_MTL_MTLCommandQueue_MTLCommandQueue);
	ZEPHIR_INIT(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder);
	ZEPHIR_INIT(Metal_MTL_MTLComputePipelineState_MTLComputePipelineState);
	ZEPHIR_INIT(Metal_MTL_MTLDepthStencilDescriptor_MTLDepthStencilDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLDepthStencilState_MTLDepthStencilState);
	ZEPHIR_INIT(Metal_MTL_MTLDevice_MTLDevice);
	ZEPHIR_INIT(Metal_MTL_MTLFunction_MTLFunction);
	ZEPHIR_INIT(Metal_MTL_MTLLibrary_MTLLibrary);
	ZEPHIR_INIT(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder);
	ZEPHIR_INIT(Metal_MTL_MTLRenderPassAttachmentDescriptor_MTLRenderPassAttachmentDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLRenderPassColorAttachmentDescriptorArray_MTLRenderPassColorAttachmentDescriptorArray);
	ZEPHIR_INIT(Metal_MTL_MTLRenderPassColorAttachmentDescriptor_MTLRenderPassColorAttachmentDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLRenderPassDepthAttachmentDescriptor_MTLRenderPassDepthAttachmentDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLRenderPassDescriptor_MTLRenderPassDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLRenderPassStencilAttachmentDescriptor_MTLRenderPassStencilAttachmentDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptorArray_MTLRenderPipelineColorAttachmentDescriptorArray);
	ZEPHIR_INIT(Metal_MTL_MTLRenderPipelineColorAttachmentDescriptor_MTLRenderPipelineColorAttachmentDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLRenderPipelineDescriptor_MTLRenderPipelineDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLRenderPipelineState_MTLRenderPipelineState);
	ZEPHIR_INIT(Metal_MTL_MTLSamplerDescriptor_MTLSamplerDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLSamplerState_MTLSamplerState);
	ZEPHIR_INIT(Metal_MTL_MTLTextureDescriptor_MTLTextureDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLTexture_MTLTexture);
	ZEPHIR_INIT(Metal_MTL_MTLVertexAttributeDescriptorArray_MTLVertexAttributeDescriptorArray);
	ZEPHIR_INIT(Metal_MTL_MTLVertexAttributeDescriptor_MTLVertexAttributeDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLVertexBufferLayoutDescriptorArray_MTLVertexBufferLayoutDescriptorArray);
	ZEPHIR_INIT(Metal_MTL_MTLVertexBufferLayoutDescriptor_MTLVertexBufferLayoutDescriptor);
	ZEPHIR_INIT(Metal_MTL_MTLVertexDescriptor_MTLVertexDescriptor);
	ZEPHIR_INIT(Metal_QuartzCore_CAMetalDrawable_CAMetalDrawable);
	ZEPHIR_INIT(Metal_QuartzCore_CAMetalLayer_CAMetalLayer);
	
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(metal)
{
	
	zephir_deinitialize_memory();
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_metal_globals *metal_globals)
{
	metal_globals->initialized = 0;

	/* Cache Enabled */
	metal_globals->cache_enabled = 1;

	/* Recursive Lock */
	metal_globals->recursive_lock = 0;

	/* Static cache */
	memset(metal_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);

	
	
}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_metal_globals *metal_globals)
{
	
}

static PHP_RINIT_FUNCTION(metal)
{
	zend_metal_globals *metal_globals_ptr;
	metal_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(metal_globals_ptr);
	zephir_initialize_memory(metal_globals_ptr);

	
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(metal)
{
	
	zephir_deinitialize_memory();
	return SUCCESS;
}



static PHP_MINFO_FUNCTION(metal)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_METAL_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_METAL_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_METAL_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_METAL_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_METAL_ZEPVERSION);
	php_info_print_table_end();
	
	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(metal)
{
#if defined(COMPILE_DL_METAL) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	php_zephir_init_globals(metal_globals);
	php_zephir_init_module_globals(metal_globals);
}

static PHP_GSHUTDOWN_FUNCTION(metal)
{
	
}


zend_function_entry php_metal_functions[] = {
	ZEND_FE_END

};

static const zend_module_dep php_metal_deps[] = {
	
	ZEND_MOD_END
};

zend_module_entry metal_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	php_metal_deps,
	PHP_METAL_EXTNAME,
	php_metal_functions,
	PHP_MINIT(metal),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(metal),
#else
	NULL,
#endif
	PHP_RINIT(metal),
	PHP_RSHUTDOWN(metal),
	PHP_MINFO(metal),
	PHP_METAL_VERSION,
	ZEND_MODULE_GLOBALS(metal),
	PHP_GINIT(metal),
	PHP_GSHUTDOWN(metal),
#ifdef ZEPHIR_POST_REQUEST
	PHP_PRSHUTDOWN(metal),
#else
	NULL,
#endif
	STANDARD_MODULE_PROPERTIES_EX
};

/* implement standard "stub" routine to introduce ourselves to Zend */
#ifdef COMPILE_DL_METAL
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(metal)
#endif
