
extern zend_class_entry *metal_mtl_mtldevice_mtldevice_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_MTLDevice_MTLDevice);

PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, createSystemDefault);
PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, name);
PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newCommandQueue);
PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newTextureWithDescriptor);
PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newBufferWithLengthOptions);
PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newBufferWithBytesLengthOptions);
PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newLibraryWithSourceOptionsError);
PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newRenderPipelineStateWithDescriptorError);
PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newComputePipelineStateWithFunctionError);
PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newDepthStencilStateWithDescriptor);
PHP_METHOD(Metal_MTL_MTLDevice_MTLDevice, newSamplerStateWithDescriptor);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_createsystemdefault, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_name, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_newcommandqueue, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_newtexturewithdescriptor, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, descriptor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_newbufferwithlengthoptions, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_newbufferwithbyteslengthoptions, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bytes, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_newlibrarywithsourceoptionserror, 0, 3, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, source, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_newrenderpipelinestatewithdescriptorerror, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, descriptor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_newcomputepipelinestatewithfunctionerror, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, computeFunction, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_newdepthstencilstatewithdescriptor, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, descriptor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtldevice_mtldevice_newsamplerstatewithdescriptor, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, descriptor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_mtldevice_mtldevice_method_entry) {
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, createSystemDefault, arginfo_metal_mtl_mtldevice_mtldevice_createsystemdefault, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, name, arginfo_metal_mtl_mtldevice_mtldevice_name, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, newCommandQueue, arginfo_metal_mtl_mtldevice_mtldevice_newcommandqueue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, newTextureWithDescriptor, arginfo_metal_mtl_mtldevice_mtldevice_newtexturewithdescriptor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, newBufferWithLengthOptions, arginfo_metal_mtl_mtldevice_mtldevice_newbufferwithlengthoptions, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, newBufferWithBytesLengthOptions, arginfo_metal_mtl_mtldevice_mtldevice_newbufferwithbyteslengthoptions, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, newLibraryWithSourceOptionsError, arginfo_metal_mtl_mtldevice_mtldevice_newlibrarywithsourceoptionserror, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, newRenderPipelineStateWithDescriptorError, arginfo_metal_mtl_mtldevice_mtldevice_newrenderpipelinestatewithdescriptorerror, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, newComputePipelineStateWithFunctionError, arginfo_metal_mtl_mtldevice_mtldevice_newcomputepipelinestatewithfunctionerror, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, newDepthStencilStateWithDescriptor, arginfo_metal_mtl_mtldevice_mtldevice_newdepthstencilstatewithdescriptor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLDevice_MTLDevice, newSamplerStateWithDescriptor, arginfo_metal_mtl_mtldevice_mtldevice_newsamplerstatewithdescriptor, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
