/*
 * metal: 1:1 bindings of Metal and CAMetalLayer, as PHP classes named after
 * their native counterparts.
 */

#include "runtime.h"
#include "ext/standard/info.h"

#include "../stubs/metal_arginfo.h"

ZEND_DECLARE_MODULE_GLOBALS(metal)

zend_class_entry *metal_ce_MetalException;
zend_class_entry *metal_ce_MTLDevice;
zend_class_entry *metal_ce_MTLOrigin;
zend_class_entry *metal_ce_MTLSize;
zend_class_entry *metal_ce_MTLRegion;
zend_class_entry *metal_ce_MTLClearColor;
zend_class_entry *metal_ce_MTLViewport;
zend_class_entry *metal_ce_MTLScissorRect;
zend_class_entry *metal_ce_MTLPixelFormat;
zend_class_entry *metal_ce_MTLLoadAction;
zend_class_entry *metal_ce_MTLStoreAction;
zend_class_entry *metal_ce_MTLPrimitiveType;
zend_class_entry *metal_ce_MTLIndexType;
zend_class_entry *metal_ce_MTLTextureUsage;
zend_class_entry *metal_ce_MTLStorageMode;
zend_class_entry *metal_ce_MTLResourceOptions;
zend_class_entry *metal_ce_MTLTextureType;
zend_class_entry *metal_ce_MTLVertexFormat;
zend_class_entry *metal_ce_MTLVertexStepFunction;
zend_class_entry *metal_ce_MTLBlendFactor;
zend_class_entry *metal_ce_MTLBlendOperation;
zend_class_entry *metal_ce_MTLColorWriteMask;
zend_class_entry *metal_ce_MTLSamplerMinMagFilter;
zend_class_entry *metal_ce_MTLSamplerAddressMode;
zend_class_entry *metal_ce_MTLCompareFunction;
zend_class_entry *metal_ce_MTLStencilOperation;
zend_class_entry *metal_ce_MTLCullMode;
zend_class_entry *metal_ce_MTLWinding;
zend_class_entry *metal_ce_MTLCommandBufferStatus;
zend_class_entry *metal_ce_MTLTextureDescriptor;
zend_class_entry *metal_ce_MTLTexture;
zend_class_entry *metal_ce_MTLBuffer;
zend_class_entry *metal_ce_MTLSamplerDescriptor;
zend_class_entry *metal_ce_MTLSamplerState;
zend_class_entry *metal_ce_MTLCompileOptions;
zend_class_entry *metal_ce_MTLLibrary;
zend_class_entry *metal_ce_MTLFunction;
zend_class_entry *metal_ce_MTLVertexDescriptor;
zend_class_entry *metal_ce_MTLVertexAttributeDescriptorArray;
zend_class_entry *metal_ce_MTLVertexBufferLayoutDescriptorArray;
zend_class_entry *metal_ce_MTLVertexAttributeDescriptor;
zend_class_entry *metal_ce_MTLVertexBufferLayoutDescriptor;
zend_class_entry *metal_ce_MTLRenderPipelineDescriptor;
zend_class_entry *metal_ce_MTLRenderPipelineColorAttachmentDescriptorArray;
zend_class_entry *metal_ce_MTLRenderPipelineColorAttachmentDescriptor;
zend_class_entry *metal_ce_MTLRenderPipelineState;
zend_class_entry *metal_ce_MTLStencilDescriptor;
zend_class_entry *metal_ce_MTLDepthStencilDescriptor;
zend_class_entry *metal_ce_MTLDepthStencilState;
zend_class_entry *metal_ce_MTLCommandQueue;
zend_class_entry *metal_ce_MTLCommandBuffer;
zend_class_entry *metal_ce_MTLRenderPassDescriptor;
zend_class_entry *metal_ce_MTLRenderPassColorAttachmentDescriptorArray;
zend_class_entry *metal_ce_MTLRenderPassColorAttachmentDescriptor;
zend_class_entry *metal_ce_MTLRenderPassDepthAttachmentDescriptor;
zend_class_entry *metal_ce_MTLRenderPassStencilAttachmentDescriptor;
zend_class_entry *metal_ce_MTLRenderCommandEncoder;
zend_class_entry *metal_ce_MTLBlitCommandEncoder;
zend_class_entry *metal_ce_CGSize;
zend_class_entry *metal_ce_CAMetalLayer;
zend_class_entry *metal_ce_CAMetalDrawable;

static PHP_GINIT_FUNCTION(metal)
{
#if defined(COMPILE_DL_METAL) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	zend_hash_init(&metal_globals->boxes, 64, NULL, NULL, 1);
}

static PHP_GSHUTDOWN_FUNCTION(metal)
{
	zend_hash_destroy(&metal_globals->boxes);
}

PHP_MINIT_FUNCTION(metal)
{
	/*
	 * Metal's descriptor validation aborts the process on a nil vertex function.
	 * Mode 1 reports that failure as an NSException, which METAL_BEGIN turns
	 * into MetalException. Leave a value the process already set alone.
	 */
	if (getenv("METAL_ERROR_MODE") == NULL) {
		setenv("METAL_ERROR_MODE", "1", 0);
	}

	metal_ce_MetalException = register_class_MetalException(zend_ce_exception);
	metal_register_MTLTypes();
	metal_register_MTLResource();
	metal_register_MTLPipeline();
	metal_register_MTLCommand();
	metal_register_CAMetalLayer();
	metal_register_MTLDevice();

	return SUCCESS;
}

PHP_RINIT_FUNCTION(metal)
{
#if defined(COMPILE_DL_METAL) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_MINFO_FUNCTION(metal)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "metal support", "enabled");
	php_info_print_table_row(2, "Version", PHP_METAL_VERSION);
	php_info_print_table_end();
}

ZEND_FUNCTION(MTLCreateSystemDefaultDevice)
{
	ZEND_PARSE_PARAMETERS_NONE();

	/* NS_RETURNS_RETAINED, and the same device object on every call. */
	METAL_BEGIN
		metal_box_owned(return_value, MTLCreateSystemDefaultDevice(), metal_ce_MTLDevice);
	METAL_END
}

zend_module_entry metal_module_entry = {
	STANDARD_MODULE_HEADER,
	"metal",
	ext_functions,
	PHP_MINIT(metal),
	NULL,
	PHP_RINIT(metal),
	NULL,
	PHP_MINFO(metal),
	PHP_METAL_VERSION,
	PHP_MODULE_GLOBALS(metal),
	PHP_GINIT(metal),
	PHP_GSHUTDOWN(metal),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_METAL
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(metal)
#endif
