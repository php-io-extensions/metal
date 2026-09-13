
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
#include "src/mtl-blitcommandencoder.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLBlitCommandEncoder, MTLBlitCommandEncoder, metal, mtl_mtlblitcommandencoder_mtlblitcommandencoder, metal_mtl_mtlblitcommandencoder_mtlblitcommandencoder_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, copyFromBufferSourceOffsetToBufferDestinationOffsetSize)
{
	zval *handle_param = NULL, *sourceBuffer_param = NULL, *sourceOffset_param = NULL, *destinationBuffer_param = NULL, *destinationOffset_param = NULL, *size_param = NULL, _0, _1, _2, _3, _4, _5;
	zend_long handle, sourceBuffer, sourceOffset, destinationBuffer, destinationOffset, size;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(sourceBuffer)
		Z_PARAM_LONG(sourceOffset)
		Z_PARAM_LONG(destinationBuffer)
		Z_PARAM_LONG(destinationOffset)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(6, 0, &handle_param, &sourceBuffer_param, &sourceOffset_param, &destinationBuffer_param, &destinationOffset_param, &size_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, sourceBuffer);
	ZVAL_LONG(&_2, sourceOffset);
	ZVAL_LONG(&_3, destinationBuffer);
	ZVAL_LONG(&_4, destinationOffset);
	ZVAL_LONG(&_5, size);
	mtl_mtlblitcommandencoder_copy_from_buffer_source_offset_to_buffer_destination_offset_size(&_0, &_1, &_2, &_3, &_4, &_5);
}

PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, fillBufferRangeValue)
{
	zval *handle_param = NULL, *buffer_param = NULL, *rangeLocation_param = NULL, *rangeLength_param = NULL, *value_param = NULL, _0, _1, _2, _3, _4;
	zend_long handle, buffer, rangeLocation, rangeLength, value;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(buffer)
		Z_PARAM_LONG(rangeLocation)
		Z_PARAM_LONG(rangeLength)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &handle_param, &buffer_param, &rangeLocation_param, &rangeLength_param, &value_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, buffer);
	ZVAL_LONG(&_2, rangeLocation);
	ZVAL_LONG(&_3, rangeLength);
	ZVAL_LONG(&_4, value);
	mtl_mtlblitcommandencoder_fill_buffer_range_value(&_0, &_1, &_2, &_3, &_4);
}

PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin)
{
	zval *handle_param = NULL, *sourceBuffer_param = NULL, *sourceOffset_param = NULL, *sourceBytesPerRow_param = NULL, *sourceBytesPerImage_param = NULL, *sourceSizeWidth_param = NULL, *sourceSizeHeight_param = NULL, *sourceSizeDepth_param = NULL, *destinationTexture_param = NULL, *destinationSlice_param = NULL, *destinationLevel_param = NULL, *destinationOriginX_param = NULL, *destinationOriginY_param = NULL, *destinationOriginZ_param = NULL, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13;
	zend_long handle, sourceBuffer, sourceOffset, sourceBytesPerRow, sourceBytesPerImage, sourceSizeWidth, sourceSizeHeight, sourceSizeDepth, destinationTexture, destinationSlice, destinationLevel, destinationOriginX, destinationOriginY, destinationOriginZ;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZEND_PARSE_PARAMETERS_START(14, 14)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(sourceBuffer)
		Z_PARAM_LONG(sourceOffset)
		Z_PARAM_LONG(sourceBytesPerRow)
		Z_PARAM_LONG(sourceBytesPerImage)
		Z_PARAM_LONG(sourceSizeWidth)
		Z_PARAM_LONG(sourceSizeHeight)
		Z_PARAM_LONG(sourceSizeDepth)
		Z_PARAM_LONG(destinationTexture)
		Z_PARAM_LONG(destinationSlice)
		Z_PARAM_LONG(destinationLevel)
		Z_PARAM_LONG(destinationOriginX)
		Z_PARAM_LONG(destinationOriginY)
		Z_PARAM_LONG(destinationOriginZ)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(14, 0, &handle_param, &sourceBuffer_param, &sourceOffset_param, &sourceBytesPerRow_param, &sourceBytesPerImage_param, &sourceSizeWidth_param, &sourceSizeHeight_param, &sourceSizeDepth_param, &destinationTexture_param, &destinationSlice_param, &destinationLevel_param, &destinationOriginX_param, &destinationOriginY_param, &destinationOriginZ_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, sourceBuffer);
	ZVAL_LONG(&_2, sourceOffset);
	ZVAL_LONG(&_3, sourceBytesPerRow);
	ZVAL_LONG(&_4, sourceBytesPerImage);
	ZVAL_LONG(&_5, sourceSizeWidth);
	ZVAL_LONG(&_6, sourceSizeHeight);
	ZVAL_LONG(&_7, sourceSizeDepth);
	ZVAL_LONG(&_8, destinationTexture);
	ZVAL_LONG(&_9, destinationSlice);
	ZVAL_LONG(&_10, destinationLevel);
	ZVAL_LONG(&_11, destinationOriginX);
	ZVAL_LONG(&_12, destinationOriginY);
	ZVAL_LONG(&_13, destinationOriginZ);
	mtl_mtlblitcommandencoder_copy_from_buffer_source_offset_source_bytes_per_row_source_bytes_per_image_source_size_to_texture_destination_slice_destination_level_destination_origin(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13);
}

PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImage)
{
	zval *handle_param = NULL, *sourceTexture_param = NULL, *sourceSlice_param = NULL, *sourceLevel_param = NULL, *sourceOriginX_param = NULL, *sourceOriginY_param = NULL, *sourceOriginZ_param = NULL, *sourceSizeWidth_param = NULL, *sourceSizeHeight_param = NULL, *sourceSizeDepth_param = NULL, *destinationBuffer_param = NULL, *destinationOffset_param = NULL, *destinationBytesPerRow_param = NULL, *destinationBytesPerImage_param = NULL, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13;
	zend_long handle, sourceTexture, sourceSlice, sourceLevel, sourceOriginX, sourceOriginY, sourceOriginZ, sourceSizeWidth, sourceSizeHeight, sourceSizeDepth, destinationBuffer, destinationOffset, destinationBytesPerRow, destinationBytesPerImage;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZEND_PARSE_PARAMETERS_START(14, 14)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(sourceTexture)
		Z_PARAM_LONG(sourceSlice)
		Z_PARAM_LONG(sourceLevel)
		Z_PARAM_LONG(sourceOriginX)
		Z_PARAM_LONG(sourceOriginY)
		Z_PARAM_LONG(sourceOriginZ)
		Z_PARAM_LONG(sourceSizeWidth)
		Z_PARAM_LONG(sourceSizeHeight)
		Z_PARAM_LONG(sourceSizeDepth)
		Z_PARAM_LONG(destinationBuffer)
		Z_PARAM_LONG(destinationOffset)
		Z_PARAM_LONG(destinationBytesPerRow)
		Z_PARAM_LONG(destinationBytesPerImage)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(14, 0, &handle_param, &sourceTexture_param, &sourceSlice_param, &sourceLevel_param, &sourceOriginX_param, &sourceOriginY_param, &sourceOriginZ_param, &sourceSizeWidth_param, &sourceSizeHeight_param, &sourceSizeDepth_param, &destinationBuffer_param, &destinationOffset_param, &destinationBytesPerRow_param, &destinationBytesPerImage_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, sourceTexture);
	ZVAL_LONG(&_2, sourceSlice);
	ZVAL_LONG(&_3, sourceLevel);
	ZVAL_LONG(&_4, sourceOriginX);
	ZVAL_LONG(&_5, sourceOriginY);
	ZVAL_LONG(&_6, sourceOriginZ);
	ZVAL_LONG(&_7, sourceSizeWidth);
	ZVAL_LONG(&_8, sourceSizeHeight);
	ZVAL_LONG(&_9, sourceSizeDepth);
	ZVAL_LONG(&_10, destinationBuffer);
	ZVAL_LONG(&_11, destinationOffset);
	ZVAL_LONG(&_12, destinationBytesPerRow);
	ZVAL_LONG(&_13, destinationBytesPerImage);
	mtl_mtlblitcommandencoder_copy_from_texture_source_slice_source_level_source_origin_source_size_to_buffer_destination_offset_destination_bytes_per_row_destination_bytes_per_image(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13);
}

PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, generateMipmapsForTexture)
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
	mtl_mtlblitcommandencoder_generate_mipmaps_for_texture(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLBlitCommandEncoder_MTLBlitCommandEncoder, synchronizeResource)
{
	zval *handle_param = NULL, *resource__param = NULL, _0, _1;
	zend_long handle, resource_;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(resource_)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &resource__param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, resource_);
	mtl_mtlblitcommandencoder_synchronize_resource(&_0, &_1);
}

