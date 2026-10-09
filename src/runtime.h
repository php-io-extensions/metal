/*
 * The glue every binding shares: one PHP object per native object, retained
 * while PHP holds it. Metal's concrete classes are private, so a box uses the
 * binding's declared PHP class rather than the Objective-C class chain.
 * NSException and NSError become MetalException.
 */

#ifndef METAL_RUNTIME_H
#define METAL_RUNTIME_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "zend_enum.h"
#include "zend_exceptions.h"
#include "php_metal.h"

#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#include <objc/runtime.h>

ZEND_BEGIN_MODULE_GLOBALS(metal)
	HashTable boxes;               /* native address => zend_object*, not refcounted */
ZEND_END_MODULE_GLOBALS(metal)

ZEND_EXTERN_MODULE_GLOBALS(metal)
#define METAL_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(metal, v)

typedef struct {
	id ptr;                        /* retained, nil before boxing */
	zend_object std;
} metal_object;

static zend_always_inline metal_object *metal_object_from(zend_object *obj)
{
	return (metal_object *) ((char *) obj - XtOffsetOf(metal_object, std));
}

#define METAL_ID(zobj) (metal_object_from(zobj)->ptr)

extern zend_class_entry *metal_ce_MetalException;
extern zend_class_entry *metal_ce_MTLDevice;
extern zend_class_entry *metal_ce_MTLOrigin;
extern zend_class_entry *metal_ce_MTLSize;
extern zend_class_entry *metal_ce_MTLRegion;
extern zend_class_entry *metal_ce_MTLClearColor;
extern zend_class_entry *metal_ce_MTLViewport;
extern zend_class_entry *metal_ce_MTLScissorRect;
extern zend_class_entry *metal_ce_MTLPixelFormat;
extern zend_class_entry *metal_ce_MTLLoadAction;
extern zend_class_entry *metal_ce_MTLStoreAction;
extern zend_class_entry *metal_ce_MTLPrimitiveType;
extern zend_class_entry *metal_ce_MTLIndexType;
extern zend_class_entry *metal_ce_MTLTextureUsage;
extern zend_class_entry *metal_ce_MTLStorageMode;
extern zend_class_entry *metal_ce_MTLResourceOptions;
extern zend_class_entry *metal_ce_MTLTextureType;
extern zend_class_entry *metal_ce_MTLVertexFormat;
extern zend_class_entry *metal_ce_MTLVertexStepFunction;
extern zend_class_entry *metal_ce_MTLBlendFactor;
extern zend_class_entry *metal_ce_MTLBlendOperation;
extern zend_class_entry *metal_ce_MTLColorWriteMask;
extern zend_class_entry *metal_ce_MTLSamplerMinMagFilter;
extern zend_class_entry *metal_ce_MTLSamplerAddressMode;
extern zend_class_entry *metal_ce_MTLCompareFunction;
extern zend_class_entry *metal_ce_MTLStencilOperation;
extern zend_class_entry *metal_ce_MTLCullMode;
extern zend_class_entry *metal_ce_MTLWinding;
extern zend_class_entry *metal_ce_MTLCommandBufferStatus;
extern zend_class_entry *metal_ce_MTLTextureDescriptor;
extern zend_class_entry *metal_ce_MTLTexture;
extern zend_class_entry *metal_ce_MTLBuffer;
extern zend_class_entry *metal_ce_MTLSamplerDescriptor;
extern zend_class_entry *metal_ce_MTLSamplerState;
extern zend_class_entry *metal_ce_MTLCompileOptions;
extern zend_class_entry *metal_ce_MTLLibrary;
extern zend_class_entry *metal_ce_MTLFunction;
extern zend_class_entry *metal_ce_MTLVertexDescriptor;
extern zend_class_entry *metal_ce_MTLVertexAttributeDescriptorArray;
extern zend_class_entry *metal_ce_MTLVertexBufferLayoutDescriptorArray;
extern zend_class_entry *metal_ce_MTLVertexAttributeDescriptor;
extern zend_class_entry *metal_ce_MTLVertexBufferLayoutDescriptor;
extern zend_class_entry *metal_ce_MTLRenderPipelineDescriptor;
extern zend_class_entry *metal_ce_MTLRenderPipelineColorAttachmentDescriptorArray;
extern zend_class_entry *metal_ce_MTLRenderPipelineColorAttachmentDescriptor;
extern zend_class_entry *metal_ce_MTLRenderPipelineState;
extern zend_class_entry *metal_ce_MTLStencilDescriptor;
extern zend_class_entry *metal_ce_MTLDepthStencilDescriptor;
extern zend_class_entry *metal_ce_MTLDepthStencilState;
extern zend_class_entry *metal_ce_MTLCommandQueue;
extern zend_class_entry *metal_ce_MTLCommandBuffer;
extern zend_class_entry *metal_ce_MTLRenderPassDescriptor;
extern zend_class_entry *metal_ce_MTLRenderPassColorAttachmentDescriptorArray;
extern zend_class_entry *metal_ce_MTLRenderPassColorAttachmentDescriptor;
extern zend_class_entry *metal_ce_MTLRenderPassDepthAttachmentDescriptor;
extern zend_class_entry *metal_ce_MTLRenderPassStencilAttachmentDescriptor;
extern zend_class_entry *metal_ce_MTLRenderCommandEncoder;
extern zend_class_entry *metal_ce_MTLBlitCommandEncoder;
extern zend_class_entry *metal_ce_CGSize;
extern zend_class_entry *metal_ce_CAMetalLayer;
extern zend_class_entry *metal_ce_CAMetalDrawable;
extern zend_class_entry *metal_ce_CAEDRMetadata;

/* Boxes obj as ce (the binding's declared type), or the PHP object already holding obj. nil → null. */
void metal_box(zval *rv, id obj, zend_class_entry *ce);
/* Boxes a +1 object (alloc/init, new…) without a second retain. */
void metal_box_owned(zval *rv, id obj, zend_class_entry *ce);
void metal_object_setup(zend_class_entry *ce);
/* The protocol or class ce stands for, for fromPointer()'s check: set at registration. */
void metal_map_native(zend_class_entry *ce, Protocol *protocol, Class cls);
void metal_throw_nserror(NSError *error);
void metal_throw_nsexception(NSException *exception);
/* Copies a zend enum case's backing value, or the int given for an Enum|int parameter. */
zend_long metal_enum_or_long(zval *value);
void metal_return_enum(zval *rv, zend_class_entry *ce, zend_long value);

static zend_always_inline zend_long metal_enum_param(zend_object *case_obj, zend_long plain)
{
	zval value;

	if (case_obj != NULL) {
		ZVAL_OBJ(&value, case_obj);
	} else {
		ZVAL_LONG(&value, plain);
	}

	return metal_enum_or_long(&value);
}

/*
 * string|int bytes. A string shorter than need is a ValueError using short_format
 * (two %zu: need, given). Address 0 is a ValueError. Any other address is trusted.
 */
bool metal_resolve_bytes(zend_string *bytes, zend_long address, size_t need, uint32_t arg_num, const char *short_format, const void **out);
bool metal_nonnegative(zend_long value, uint32_t arg_num);
NSString *metal_nsstring(zend_string *str);

#define METAL_BEGIN @autoreleasepool { @try {
#define METAL_END } @catch (NSException *metal_exception) { metal_throw_nsexception(metal_exception); RETURN_THROWS(); } }

/* A handle class has no PHP constructor: alloc happens on the Metal side. */
#define METAL_REJECT_CONSTRUCT(cls) \
	ZEND_METHOD(cls, __construct) \
	{ \
		ZEND_PARSE_PARAMETERS_NONE(); \
		zend_throw_error(NULL, "%s cannot be constructed", #cls); \
	}

/* pointer() and fromPointer() for a handle class. */
#define METAL_POINTER_METHODS(cls) \
	ZEND_METHOD(cls, pointer) { ZEND_PARSE_PARAMETERS_NONE(); RETURN_LONG((zend_long) (uintptr_t) METAL_ID(Z_OBJ_P(ZEND_THIS))); } \
	ZEND_METHOD(cls, fromPointer) { metal_from_pointer(INTERNAL_FUNCTION_PARAM_PASSTHRU); }

void metal_from_pointer(INTERNAL_FUNCTION_PARAMETERS);

MTLOrigin metal_origin_from(zend_object *object);
MTLSize metal_size_from(zend_object *object);
MTLRegion metal_region_from(zend_object *object);
MTLClearColor metal_clear_color_from(zend_object *object);
MTLViewport metal_viewport_from(zend_object *object);
MTLScissorRect metal_scissor_from(zend_object *object);
void metal_region_new(zval *rv, MTLRegion region);
void metal_clear_color_new(zval *rv, MTLClearColor color);

/* Class registration, one per stub, called from MINIT. */
void metal_register_MTLDevice(void);
void metal_register_MTLTypes(void);
void metal_register_MTLResource(void);
void metal_register_MTLPipeline(void);
void metal_register_MTLCommand(void);
void metal_register_CAMetalLayer(void);

#endif
