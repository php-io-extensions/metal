
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
#include "src/mtl-rendercommandencoder.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLRenderCommandEncoder, MTLRenderCommandEncoder, metal, mtl_mtlrendercommandencoder_mtlrendercommandencoder, metal_mtl_mtlrendercommandencoder_mtlrendercommandencoder_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setRenderPipelineState)
{
	zval *handle_param = NULL, *pipelineState_param = NULL, _0, _1;
	zend_long handle, pipelineState;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(pipelineState)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &pipelineState_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, pipelineState);
	mtl_mtlrendercommandencoder_set_render_pipeline_state(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setVertexBufferOffsetAtIndex)
{
	zval *handle_param = NULL, *buffer_param = NULL, *offset_param = NULL, *index_param = NULL, _0, _1, _2, _3;
	zend_long handle, buffer, offset, index;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(buffer)
		Z_PARAM_LONG(offset)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &handle_param, &buffer_param, &offset_param, &index_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, buffer);
	ZVAL_LONG(&_2, offset);
	ZVAL_LONG(&_3, index);
	mtl_mtlrendercommandencoder_set_vertex_buffer_offset_at_index(&_0, &_1, &_2, &_3);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFragmentBufferOffsetAtIndex)
{
	zval *handle_param = NULL, *buffer_param = NULL, *offset_param = NULL, *index_param = NULL, _0, _1, _2, _3;
	zend_long handle, buffer, offset, index;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(buffer)
		Z_PARAM_LONG(offset)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &handle_param, &buffer_param, &offset_param, &index_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, buffer);
	ZVAL_LONG(&_2, offset);
	ZVAL_LONG(&_3, index);
	mtl_mtlrendercommandencoder_set_fragment_buffer_offset_at_index(&_0, &_1, &_2, &_3);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setVertexTextureAtIndex)
{
	zval *handle_param = NULL, *texture_param = NULL, *index_param = NULL, _0, _1, _2;
	zend_long handle, texture, index;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &handle_param, &texture_param, &index_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, texture);
	ZVAL_LONG(&_2, index);
	mtl_mtlrendercommandencoder_set_vertex_texture_at_index(&_0, &_1, &_2);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFragmentTextureAtIndex)
{
	zval *handle_param = NULL, *texture_param = NULL, *index_param = NULL, _0, _1, _2;
	zend_long handle, texture, index;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(texture)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &handle_param, &texture_param, &index_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, texture);
	ZVAL_LONG(&_2, index);
	mtl_mtlrendercommandencoder_set_fragment_texture_at_index(&_0, &_1, &_2);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFragmentSamplerStateAtIndex)
{
	zval *handle_param = NULL, *sampler_param = NULL, *index_param = NULL, _0, _1, _2;
	zend_long handle, sampler, index;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(sampler)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &handle_param, &sampler_param, &index_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, sampler);
	ZVAL_LONG(&_2, index);
	mtl_mtlrendercommandencoder_set_fragment_sampler_state_at_index(&_0, &_1, &_2);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setViewport)
{
	double originX, originY, width, height, znear, zfar;
	zval *handle_param = NULL, *originX_param = NULL, *originY_param = NULL, *width_param = NULL, *height_param = NULL, *znear_param = NULL, *zfar_param = NULL, _0, _1, _2, _3, _4, _5, _6;
	zend_long handle;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_LONG(handle)
		Z_PARAM_ZVAL(originX)
		Z_PARAM_ZVAL(originY)
		Z_PARAM_ZVAL(width)
		Z_PARAM_ZVAL(height)
		Z_PARAM_ZVAL(znear)
		Z_PARAM_ZVAL(zfar)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(7, 0, &handle_param, &originX_param, &originY_param, &width_param, &height_param, &znear_param, &zfar_param);
	originX = zephir_get_doubleval(originX_param);
	originY = zephir_get_doubleval(originY_param);
	width = zephir_get_doubleval(width_param);
	height = zephir_get_doubleval(height_param);
	znear = zephir_get_doubleval(znear_param);
	zfar = zephir_get_doubleval(zfar_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_DOUBLE(&_1, originX);
	ZVAL_DOUBLE(&_2, originY);
	ZVAL_DOUBLE(&_3, width);
	ZVAL_DOUBLE(&_4, height);
	ZVAL_DOUBLE(&_5, znear);
	ZVAL_DOUBLE(&_6, zfar);
	mtl_mtlrendercommandencoder_set_viewport(&_0, &_1, &_2, &_3, &_4, &_5, &_6);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setScissorRect)
{
	zval *handle_param = NULL, *x_param = NULL, *y_param = NULL, *width_param = NULL, *height_param = NULL, _0, _1, _2, _3, _4;
	zend_long handle, x, y, width, height;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(width)
		Z_PARAM_LONG(height)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &handle_param, &x_param, &y_param, &width_param, &height_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, x);
	ZVAL_LONG(&_2, y);
	ZVAL_LONG(&_3, width);
	ZVAL_LONG(&_4, height);
	mtl_mtlrendercommandencoder_set_scissor_rect(&_0, &_1, &_2, &_3, &_4);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setCullMode)
{
	zval *handle_param = NULL, *cullMode_param = NULL, _0, _1;
	zend_long handle, cullMode;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(cullMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &cullMode_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, cullMode);
	mtl_mtlrendercommandencoder_set_cull_mode(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setFrontFacingWinding)
{
	zval *handle_param = NULL, *frontFacingWinding_param = NULL, _0, _1;
	zend_long handle, frontFacingWinding;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(frontFacingWinding)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &frontFacingWinding_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, frontFacingWinding);
	mtl_mtlrendercommandencoder_set_front_facing_winding(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setTriangleFillMode)
{
	zval *handle_param = NULL, *fillMode_param = NULL, _0, _1;
	zend_long handle, fillMode;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(fillMode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &fillMode_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, fillMode);
	mtl_mtlrendercommandencoder_set_triangle_fill_mode(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, setDepthStencilState)
{
	zval *handle_param = NULL, *depthStencilState_param = NULL, _0, _1;
	zend_long handle, depthStencilState;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(depthStencilState)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &depthStencilState_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, depthStencilState);
	mtl_mtlrendercommandencoder_set_depth_stencil_state(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, drawPrimitivesVertexStartVertexCount)
{
	zval *handle_param = NULL, *primitiveType_param = NULL, *vertexStart_param = NULL, *vertexCount_param = NULL, _0, _1, _2, _3;
	zend_long handle, primitiveType, vertexStart, vertexCount;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(primitiveType)
		Z_PARAM_LONG(vertexStart)
		Z_PARAM_LONG(vertexCount)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &handle_param, &primitiveType_param, &vertexStart_param, &vertexCount_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, primitiveType);
	ZVAL_LONG(&_2, vertexStart);
	ZVAL_LONG(&_3, vertexCount);
	mtl_mtlrendercommandencoder_draw_primitives_vertex_start_vertex_count(&_0, &_1, &_2, &_3);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, drawPrimitivesVertexStartVertexCountInstanceCount)
{
	zval *handle_param = NULL, *primitiveType_param = NULL, *vertexStart_param = NULL, *vertexCount_param = NULL, *instanceCount_param = NULL, _0, _1, _2, _3, _4;
	zend_long handle, primitiveType, vertexStart, vertexCount, instanceCount;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(primitiveType)
		Z_PARAM_LONG(vertexStart)
		Z_PARAM_LONG(vertexCount)
		Z_PARAM_LONG(instanceCount)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &handle_param, &primitiveType_param, &vertexStart_param, &vertexCount_param, &instanceCount_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, primitiveType);
	ZVAL_LONG(&_2, vertexStart);
	ZVAL_LONG(&_3, vertexCount);
	ZVAL_LONG(&_4, instanceCount);
	mtl_mtlrendercommandencoder_draw_primitives_vertex_start_vertex_count_instance_count(&_0, &_1, &_2, &_3, &_4);
}

PHP_METHOD(Metal_MTL_MTLRenderCommandEncoder_MTLRenderCommandEncoder, drawIndexedPrimitivesIndexCountIndexTypeIndexBufferIndexBufferOffset)
{
	zval *handle_param = NULL, *primitiveType_param = NULL, *indexCount_param = NULL, *indexType_param = NULL, *indexBuffer_param = NULL, *indexBufferOffset_param = NULL, _0, _1, _2, _3, _4, _5;
	zend_long handle, primitiveType, indexCount, indexType, indexBuffer, indexBufferOffset;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(primitiveType)
		Z_PARAM_LONG(indexCount)
		Z_PARAM_LONG(indexType)
		Z_PARAM_LONG(indexBuffer)
		Z_PARAM_LONG(indexBufferOffset)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(6, 0, &handle_param, &primitiveType_param, &indexCount_param, &indexType_param, &indexBuffer_param, &indexBufferOffset_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, primitiveType);
	ZVAL_LONG(&_2, indexCount);
	ZVAL_LONG(&_3, indexType);
	ZVAL_LONG(&_4, indexBuffer);
	ZVAL_LONG(&_5, indexBufferOffset);
	mtl_mtlrendercommandencoder_draw_indexed_primitives_index_count_index_type_index_buffer_index_buffer_offset(&_0, &_1, &_2, &_3, &_4, &_5);
}

