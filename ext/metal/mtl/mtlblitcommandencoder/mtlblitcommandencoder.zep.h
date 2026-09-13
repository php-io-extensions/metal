
extern zend_class_entry *metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder);

PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, copyFromBufferSourceOffsetToBufferDestinationOffsetSize);
PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, fillBufferRangeValue);
PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin);
PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImage);
PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, generateMipmapsForTexture);
PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, synchronizeResource);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_copyfrombuffersourceoffsettobufferdestinationoffsetsize, 0, 6, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceBuffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceOffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationBuffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationOffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_fillbufferrangevalue, 0, 5, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, rangeLocation, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, rangeLength, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_copyfrombuffersourceoffsetsourcebytesperrowsourcebytesperimagesourcesizetotexturedestinationslicedestinationleveldestinationorigin, 0, 14, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceBuffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceOffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceBytesPerRow, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceBytesPerImage, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceSizeWidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceSizeHeight, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceSizeDepth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationTexture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationSlice, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationLevel, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationOriginX, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationOriginY, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationOriginZ, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_copyfromtexturesourceslicesourcelevelsourceoriginsourcesizetobufferdestinationoffsetdestinationbytesperrowdestinationbytesperimage, 0, 14, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceTexture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceSlice, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceLevel, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceOriginX, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceOriginY, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceOriginZ, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceSizeWidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceSizeHeight, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sourceSizeDepth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationBuffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationOffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationBytesPerRow, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, destinationBytesPerImage, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_generatemipmapsfortexture, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_synchronizeresource, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, resource_, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_method_entry) {
	PHP_ME(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, copyFromBufferSourceOffsetToBufferDestinationOffsetSize, arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_copyfrombuffersourceoffsettobufferdestinationoffsetsize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, fillBufferRangeValue, arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_fillbufferrangevalue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin, arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_copyfrombuffersourceoffsetsourcebytesperrowsourcebytesperimagesourcesizetotexturedestinationslicedestinationleveldestinationorigin, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImage, arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_copyfromtexturesourceslicesourcelevelsourceoriginsourcesizetobufferdestinationoffsetdestinationbytesperrowdestinationbytesperimage, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, generateMipmapsForTexture, arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_generatemipmapsfortexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, synchronizeResource, arginfo_metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_synchronizeresource, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
