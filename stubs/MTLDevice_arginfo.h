/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: aaa96dc8df5f69c193dd6204da212ef2b9c9c2ea */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_MTLDevice___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLDevice_name, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLDevice_pointer, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLDevice_fromPointer, 0, 1, IS_STATIC, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLDevice_newTextureWithDescriptor, 0, 1, MTLTexture, 1)
	ZEND_ARG_OBJ_INFO(0, descriptor, MTLTextureDescriptor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLDevice_newBufferWithLengthOptions, 0, 2, MTLBuffer, 1)
	ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, options, MTLResourceOptions, MAY_BE_LONG, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLDevice_newBufferWithBytesLengthOptions, 0, 3, MTLBuffer, 1)
	ZEND_ARG_TYPE_MASK(0, bytes, MAY_BE_STRING|MAY_BE_LONG, NULL)
	ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, options, MTLResourceOptions, MAY_BE_LONG, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLDevice_newSamplerStateWithDescriptor, 0, 1, MTLSamplerState, 1)
	ZEND_ARG_OBJ_INFO(0, descriptor, MTLSamplerDescriptor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLDevice_supportsTextureSampleCount, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, sampleCount, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLDevice_newLibraryWithSourceOptionsError, 0, 2, MTLLibrary, 0)
	ZEND_ARG_TYPE_INFO(0, source, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, options, MTLCompileOptions, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLDevice_newRenderPipelineStateWithDescriptorError, 0, 1, MTLRenderPipelineState, 0)
	ZEND_ARG_OBJ_INFO(0, descriptor, MTLRenderPipelineDescriptor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLDevice_newDepthStencilStateWithDescriptor, 0, 1, MTLDepthStencilState, 1)
	ZEND_ARG_OBJ_INFO(0, descriptor, MTLDepthStencilDescriptor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLDevice_newCommandQueue, 0, 0, MTLCommandQueue, 1)
ZEND_END_ARG_INFO()

ZEND_METHOD(MTLDevice, __construct);
ZEND_METHOD(MTLDevice, name);
ZEND_METHOD(MTLDevice, pointer);
ZEND_METHOD(MTLDevice, fromPointer);
ZEND_METHOD(MTLDevice, newTextureWithDescriptor);
ZEND_METHOD(MTLDevice, newBufferWithLengthOptions);
ZEND_METHOD(MTLDevice, newBufferWithBytesLengthOptions);
ZEND_METHOD(MTLDevice, newSamplerStateWithDescriptor);
ZEND_METHOD(MTLDevice, supportsTextureSampleCount);
ZEND_METHOD(MTLDevice, newLibraryWithSourceOptionsError);
ZEND_METHOD(MTLDevice, newRenderPipelineStateWithDescriptorError);
ZEND_METHOD(MTLDevice, newDepthStencilStateWithDescriptor);
ZEND_METHOD(MTLDevice, newCommandQueue);

static const zend_function_entry class_MTLDevice_methods[] = {
	ZEND_ME(MTLDevice, __construct, arginfo_class_MTLDevice___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(MTLDevice, name, arginfo_class_MTLDevice_name, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLDevice, pointer, arginfo_class_MTLDevice_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLDevice, fromPointer, arginfo_class_MTLDevice_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(MTLDevice, newTextureWithDescriptor, arginfo_class_MTLDevice_newTextureWithDescriptor, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLDevice, newBufferWithLengthOptions, arginfo_class_MTLDevice_newBufferWithLengthOptions, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLDevice, newBufferWithBytesLengthOptions, arginfo_class_MTLDevice_newBufferWithBytesLengthOptions, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLDevice, newSamplerStateWithDescriptor, arginfo_class_MTLDevice_newSamplerStateWithDescriptor, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLDevice, supportsTextureSampleCount, arginfo_class_MTLDevice_supportsTextureSampleCount, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLDevice, newLibraryWithSourceOptionsError, arginfo_class_MTLDevice_newLibraryWithSourceOptionsError, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLDevice, newRenderPipelineStateWithDescriptorError, arginfo_class_MTLDevice_newRenderPipelineStateWithDescriptorError, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLDevice, newDepthStencilStateWithDescriptor, arginfo_class_MTLDevice_newDepthStencilStateWithDescriptor, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLDevice, newCommandQueue, arginfo_class_MTLDevice_newCommandQueue, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_MTLDevice(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLDevice", class_MTLDevice_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}
