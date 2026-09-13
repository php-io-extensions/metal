
extern zend_class_entry *metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder);

PHP_METHOD(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, setComputePipelineState);
PHP_METHOD(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, setBufferOffsetAtIndex);
PHP_METHOD(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, setTextureAtIndex);
PHP_METHOD(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, dispatchThreadgroupsThreadsPerThreadgroup);
PHP_METHOD(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, dispatchThreadsThreadsPerThreadgroup);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_setcomputepipelinestate, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, state, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_setbufferoffsetatindex, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_settextureatindex, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_dispatchthreadgroupsthreadsperthreadgroup, 0, 7, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadgroupsPerGridWidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadgroupsPerGridHeight, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadgroupsPerGridDepth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadsPerThreadgroupWidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadsPerThreadgroupHeight, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadsPerThreadgroupDepth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_dispatchthreadsthreadsperthreadgroup, 0, 7, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadsPerGridWidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadsPerGridHeight, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadsPerGridDepth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadsPerThreadgroupWidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadsPerThreadgroupHeight, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, threadsPerThreadgroupDepth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_method_entry) {
	PHP_ME(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, setComputePipelineState, arginfo_metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_setcomputepipelinestate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, setBufferOffsetAtIndex, arginfo_metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_setbufferoffsetatindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, setTextureAtIndex, arginfo_metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_settextureatindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, dispatchThreadgroupsThreadsPerThreadgroup, arginfo_metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_dispatchthreadgroupsthreadsperthreadgroup, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, dispatchThreadsThreadsPerThreadgroup, arginfo_metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_dispatchthreadsthreadsperthreadgroup, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
