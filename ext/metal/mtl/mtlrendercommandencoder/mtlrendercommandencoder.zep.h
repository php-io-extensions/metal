
extern zend_class_entry *metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder);

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setRenderPipelineState);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setVertexBufferOffsetAtIndex);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFragmentBufferOffsetAtIndex);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setVertexTextureAtIndex);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFragmentTextureAtIndex);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFragmentSamplerStateAtIndex);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setViewport);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setScissorRect);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setCullMode);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFrontFacingWinding);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setTriangleFillMode);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setDepthStencilState);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, drawPrimitivesVertexStartVertexCount);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, drawPrimitivesVertexStartVertexCountInstanceCount);
PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, drawIndexedPrimitivesIndexCountIndexTypeIndexBufferIndexBufferOffset);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setrenderpipelinestate, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pipelineState, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setvertexbufferoffsetatindex, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setfragmentbufferoffsetatindex, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setvertextextureatindex, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setfragmenttextureatindex, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setfragmentsamplerstateatindex, 0, 3, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setviewport, 0, 7, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, originX, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, originY, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, znear, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, zfar, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setscissorrect, 0, 5, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setcullmode, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, cullMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setfrontfacingwinding, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, frontFacingWinding, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_settrianglefillmode, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fillMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setdepthstencilstate, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, depthStencilState, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_drawprimitivesvertexstartvertexcount, 0, 4, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, primitiveType, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, vertexStart, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, vertexCount, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_drawprimitivesvertexstartvertexcountinstancecount, 0, 5, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, primitiveType, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, vertexStart, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, vertexCount, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instanceCount, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_drawindexedprimitivesindexcountindextypeindexbufferindexbufferoffset, 0, 6, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, primitiveType, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, indexCount, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, indexType, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, indexBuffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, indexBufferOffset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_method_entry) {
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setRenderPipelineState, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setrenderpipelinestate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setVertexBufferOffsetAtIndex, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setvertexbufferoffsetatindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFragmentBufferOffsetAtIndex, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setfragmentbufferoffsetatindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setVertexTextureAtIndex, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setvertextextureatindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFragmentTextureAtIndex, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setfragmenttextureatindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFragmentSamplerStateAtIndex, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setfragmentsamplerstateatindex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setViewport, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setviewport, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setScissorRect, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setscissorrect, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setCullMode, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setcullmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFrontFacingWinding, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setfrontfacingwinding, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setTriangleFillMode, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_settrianglefillmode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setDepthStencilState, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_setdepthstencilstate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, drawPrimitivesVertexStartVertexCount, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_drawprimitivesvertexstartvertexcount, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, drawPrimitivesVertexStartVertexCountInstanceCount, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_drawprimitivesvertexstartvertexcountinstancecount, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, drawIndexedPrimitivesIndexCountIndexTypeIndexBufferIndexBufferOffset, arginfo_metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_drawindexedprimitivesindexcountindextypeindexbufferindexbufferoffset, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
