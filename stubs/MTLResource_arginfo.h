/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: b3b28fdeee5224d72c3fdb31e19f2bf99940c34e */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_MTLTextureDescriptor___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLTextureDescriptor_texture2DDescriptorWithPixelFormatWidthHeightMipmapped, 0, 4, MTLTextureDescriptor, 0)
	ZEND_ARG_OBJ_INFO(0, pixelFormat, MTLPixelFormat, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mipmapped, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLTextureDescriptor_new, 0, 0, MTLTextureDescriptor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLTextureDescriptor_textureType, 0, 0, MTLTextureType, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTextureDescriptor_setTextureType, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, textureType, MTLTextureType, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLTextureDescriptor_pixelFormat, 0, 0, MTLPixelFormat, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTextureDescriptor_setPixelFormat, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, pixelFormat, MTLPixelFormat, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTextureDescriptor_width, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTextureDescriptor_setWidth, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_MTLTextureDescriptor_height arginfo_class_MTLTextureDescriptor_width

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTextureDescriptor_setHeight, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_MTLTextureDescriptor_sampleCount arginfo_class_MTLTextureDescriptor_width

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTextureDescriptor_setSampleCount, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sampleCount, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(arginfo_class_MTLTextureDescriptor_usage, 0, 0, MTLTextureUsage, MAY_BE_LONG)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTextureDescriptor_setUsage, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, usage, MTLTextureUsage, MAY_BE_LONG, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLTextureDescriptor_storageMode, 0, 0, MTLStorageMode, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTextureDescriptor_setStorageMode, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, storageMode, MTLStorageMode, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_MTLTextureDescriptor_pointer arginfo_class_MTLTextureDescriptor_width

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTextureDescriptor_fromPointer, 0, 1, IS_STATIC, 0)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_MTLTexture___construct arginfo_class_MTLTextureDescriptor___construct

#define arginfo_class_MTLTexture_width arginfo_class_MTLTextureDescriptor_width

#define arginfo_class_MTLTexture_height arginfo_class_MTLTextureDescriptor_width

#define arginfo_class_MTLTexture_pixelFormat arginfo_class_MTLTextureDescriptor_pixelFormat

#define arginfo_class_MTLTexture_textureType arginfo_class_MTLTextureDescriptor_textureType

#define arginfo_class_MTLTexture_sampleCount arginfo_class_MTLTextureDescriptor_width

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTexture_replaceRegionMipmapLevelWithBytesBytesPerRow, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, region, MTLRegion, 0)
	ZEND_ARG_TYPE_INFO(0, mipmapLevel, IS_LONG, 0)
	ZEND_ARG_TYPE_MASK(0, bytes, MAY_BE_STRING|MAY_BE_LONG, NULL)
	ZEND_ARG_TYPE_INFO(0, bytesPerRow, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLTexture_getBytesBytesPerRowFromRegionMipmapLevel, 0, 4, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, pixelBytes, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(0, bytesPerRow, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, region, MTLRegion, 0)
	ZEND_ARG_TYPE_INFO(0, mipmapLevel, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_MTLTexture_pointer arginfo_class_MTLTextureDescriptor_width

#define arginfo_class_MTLTexture_fromPointer arginfo_class_MTLTextureDescriptor_fromPointer

#define arginfo_class_MTLBuffer___construct arginfo_class_MTLTextureDescriptor___construct

#define arginfo_class_MTLBuffer_length arginfo_class_MTLTextureDescriptor_width

#define arginfo_class_MTLBuffer_contents arginfo_class_MTLTextureDescriptor_width

#define arginfo_class_MTLBuffer_pointer arginfo_class_MTLTextureDescriptor_width

#define arginfo_class_MTLBuffer_fromPointer arginfo_class_MTLTextureDescriptor_fromPointer

#define arginfo_class_MTLSamplerDescriptor___construct arginfo_class_MTLTextureDescriptor___construct

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLSamplerDescriptor_new, 0, 0, MTLSamplerDescriptor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLSamplerDescriptor_minFilter, 0, 0, MTLSamplerMinMagFilter, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLSamplerDescriptor_setMinFilter, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, minFilter, MTLSamplerMinMagFilter, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_MTLSamplerDescriptor_magFilter arginfo_class_MTLSamplerDescriptor_minFilter

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLSamplerDescriptor_setMagFilter, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, magFilter, MTLSamplerMinMagFilter, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_MTLSamplerDescriptor_sAddressMode, 0, 0, MTLSamplerAddressMode, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLSamplerDescriptor_setSAddressMode, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, sAddressMode, MTLSamplerAddressMode, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_MTLSamplerDescriptor_tAddressMode arginfo_class_MTLSamplerDescriptor_sAddressMode

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_MTLSamplerDescriptor_setTAddressMode, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, tAddressMode, MTLSamplerAddressMode, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_MTLSamplerDescriptor_pointer arginfo_class_MTLTextureDescriptor_width

#define arginfo_class_MTLSamplerDescriptor_fromPointer arginfo_class_MTLTextureDescriptor_fromPointer

#define arginfo_class_MTLSamplerState___construct arginfo_class_MTLTextureDescriptor___construct

#define arginfo_class_MTLSamplerState_pointer arginfo_class_MTLTextureDescriptor_width

#define arginfo_class_MTLSamplerState_fromPointer arginfo_class_MTLTextureDescriptor_fromPointer

ZEND_METHOD(MTLTextureDescriptor, __construct);
ZEND_METHOD(MTLTextureDescriptor, texture2DDescriptorWithPixelFormatWidthHeightMipmapped);
ZEND_METHOD(MTLTextureDescriptor, new);
ZEND_METHOD(MTLTextureDescriptor, textureType);
ZEND_METHOD(MTLTextureDescriptor, setTextureType);
ZEND_METHOD(MTLTextureDescriptor, pixelFormat);
ZEND_METHOD(MTLTextureDescriptor, setPixelFormat);
ZEND_METHOD(MTLTextureDescriptor, width);
ZEND_METHOD(MTLTextureDescriptor, setWidth);
ZEND_METHOD(MTLTextureDescriptor, height);
ZEND_METHOD(MTLTextureDescriptor, setHeight);
ZEND_METHOD(MTLTextureDescriptor, sampleCount);
ZEND_METHOD(MTLTextureDescriptor, setSampleCount);
ZEND_METHOD(MTLTextureDescriptor, usage);
ZEND_METHOD(MTLTextureDescriptor, setUsage);
ZEND_METHOD(MTLTextureDescriptor, storageMode);
ZEND_METHOD(MTLTextureDescriptor, setStorageMode);
ZEND_METHOD(MTLTextureDescriptor, pointer);
ZEND_METHOD(MTLTextureDescriptor, fromPointer);
ZEND_METHOD(MTLTexture, __construct);
ZEND_METHOD(MTLTexture, width);
ZEND_METHOD(MTLTexture, height);
ZEND_METHOD(MTLTexture, pixelFormat);
ZEND_METHOD(MTLTexture, textureType);
ZEND_METHOD(MTLTexture, sampleCount);
ZEND_METHOD(MTLTexture, replaceRegionMipmapLevelWithBytesBytesPerRow);
ZEND_METHOD(MTLTexture, getBytesBytesPerRowFromRegionMipmapLevel);
ZEND_METHOD(MTLTexture, pointer);
ZEND_METHOD(MTLTexture, fromPointer);
ZEND_METHOD(MTLBuffer, __construct);
ZEND_METHOD(MTLBuffer, length);
ZEND_METHOD(MTLBuffer, contents);
ZEND_METHOD(MTLBuffer, pointer);
ZEND_METHOD(MTLBuffer, fromPointer);
ZEND_METHOD(MTLSamplerDescriptor, __construct);
ZEND_METHOD(MTLSamplerDescriptor, new);
ZEND_METHOD(MTLSamplerDescriptor, minFilter);
ZEND_METHOD(MTLSamplerDescriptor, setMinFilter);
ZEND_METHOD(MTLSamplerDescriptor, magFilter);
ZEND_METHOD(MTLSamplerDescriptor, setMagFilter);
ZEND_METHOD(MTLSamplerDescriptor, sAddressMode);
ZEND_METHOD(MTLSamplerDescriptor, setSAddressMode);
ZEND_METHOD(MTLSamplerDescriptor, tAddressMode);
ZEND_METHOD(MTLSamplerDescriptor, setTAddressMode);
ZEND_METHOD(MTLSamplerDescriptor, pointer);
ZEND_METHOD(MTLSamplerDescriptor, fromPointer);
ZEND_METHOD(MTLSamplerState, __construct);
ZEND_METHOD(MTLSamplerState, pointer);
ZEND_METHOD(MTLSamplerState, fromPointer);

static const zend_function_entry class_MTLTextureDescriptor_methods[] = {
	ZEND_ME(MTLTextureDescriptor, __construct, arginfo_class_MTLTextureDescriptor___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(MTLTextureDescriptor, texture2DDescriptorWithPixelFormatWidthHeightMipmapped, arginfo_class_MTLTextureDescriptor_texture2DDescriptorWithPixelFormatWidthHeightMipmapped, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(MTLTextureDescriptor, new, arginfo_class_MTLTextureDescriptor_new, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(MTLTextureDescriptor, textureType, arginfo_class_MTLTextureDescriptor_textureType, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, setTextureType, arginfo_class_MTLTextureDescriptor_setTextureType, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, pixelFormat, arginfo_class_MTLTextureDescriptor_pixelFormat, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, setPixelFormat, arginfo_class_MTLTextureDescriptor_setPixelFormat, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, width, arginfo_class_MTLTextureDescriptor_width, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, setWidth, arginfo_class_MTLTextureDescriptor_setWidth, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, height, arginfo_class_MTLTextureDescriptor_height, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, setHeight, arginfo_class_MTLTextureDescriptor_setHeight, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, sampleCount, arginfo_class_MTLTextureDescriptor_sampleCount, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, setSampleCount, arginfo_class_MTLTextureDescriptor_setSampleCount, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, usage, arginfo_class_MTLTextureDescriptor_usage, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, setUsage, arginfo_class_MTLTextureDescriptor_setUsage, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, storageMode, arginfo_class_MTLTextureDescriptor_storageMode, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, setStorageMode, arginfo_class_MTLTextureDescriptor_setStorageMode, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, pointer, arginfo_class_MTLTextureDescriptor_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTextureDescriptor, fromPointer, arginfo_class_MTLTextureDescriptor_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_MTLTexture_methods[] = {
	ZEND_ME(MTLTexture, __construct, arginfo_class_MTLTexture___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(MTLTexture, width, arginfo_class_MTLTexture_width, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTexture, height, arginfo_class_MTLTexture_height, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTexture, pixelFormat, arginfo_class_MTLTexture_pixelFormat, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTexture, textureType, arginfo_class_MTLTexture_textureType, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTexture, sampleCount, arginfo_class_MTLTexture_sampleCount, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTexture, replaceRegionMipmapLevelWithBytesBytesPerRow, arginfo_class_MTLTexture_replaceRegionMipmapLevelWithBytesBytesPerRow, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTexture, getBytesBytesPerRowFromRegionMipmapLevel, arginfo_class_MTLTexture_getBytesBytesPerRowFromRegionMipmapLevel, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTexture, pointer, arginfo_class_MTLTexture_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLTexture, fromPointer, arginfo_class_MTLTexture_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_MTLBuffer_methods[] = {
	ZEND_ME(MTLBuffer, __construct, arginfo_class_MTLBuffer___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(MTLBuffer, length, arginfo_class_MTLBuffer_length, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLBuffer, contents, arginfo_class_MTLBuffer_contents, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLBuffer, pointer, arginfo_class_MTLBuffer_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLBuffer, fromPointer, arginfo_class_MTLBuffer_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_MTLSamplerDescriptor_methods[] = {
	ZEND_ME(MTLSamplerDescriptor, __construct, arginfo_class_MTLSamplerDescriptor___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(MTLSamplerDescriptor, new, arginfo_class_MTLSamplerDescriptor_new, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(MTLSamplerDescriptor, minFilter, arginfo_class_MTLSamplerDescriptor_minFilter, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLSamplerDescriptor, setMinFilter, arginfo_class_MTLSamplerDescriptor_setMinFilter, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLSamplerDescriptor, magFilter, arginfo_class_MTLSamplerDescriptor_magFilter, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLSamplerDescriptor, setMagFilter, arginfo_class_MTLSamplerDescriptor_setMagFilter, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLSamplerDescriptor, sAddressMode, arginfo_class_MTLSamplerDescriptor_sAddressMode, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLSamplerDescriptor, setSAddressMode, arginfo_class_MTLSamplerDescriptor_setSAddressMode, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLSamplerDescriptor, tAddressMode, arginfo_class_MTLSamplerDescriptor_tAddressMode, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLSamplerDescriptor, setTAddressMode, arginfo_class_MTLSamplerDescriptor_setTAddressMode, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLSamplerDescriptor, pointer, arginfo_class_MTLSamplerDescriptor_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLSamplerDescriptor, fromPointer, arginfo_class_MTLSamplerDescriptor_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_MTLSamplerState_methods[] = {
	ZEND_ME(MTLSamplerState, __construct, arginfo_class_MTLSamplerState___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(MTLSamplerState, pointer, arginfo_class_MTLSamplerState_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(MTLSamplerState, fromPointer, arginfo_class_MTLSamplerState_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_MTLTextureDescriptor(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLTextureDescriptor", class_MTLTextureDescriptor_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_MTLTexture(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLTexture", class_MTLTexture_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_MTLBuffer(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLBuffer", class_MTLBuffer_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_MTLSamplerDescriptor(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLSamplerDescriptor", class_MTLSamplerDescriptor_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_MTLSamplerState(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLSamplerState", class_MTLSamplerState_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}
