
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
#include "src/mtl-computecommandencoder.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL\\MTLComputeCommandEncoder, MTLComputeCommandEncoder, metal, mtl_mtlcomputecommandencoder_mtlcomputecommandencoder, metal_mtl_mtlcomputecommandencoder_mtlcomputecommandencoder_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, setComputePipelineState)
{
	zval *handle_param = NULL, *state_param = NULL, _0, _1;
	zend_long handle, state;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(state)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &handle_param, &state_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, state);
	mtl_mtlcomputecommandencoder_set_compute_pipeline_state(&_0, &_1);
}

PHP_METHOD(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, setBufferOffsetAtIndex)
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
	mtl_mtlcomputecommandencoder_set_buffer_offset_at_index(&_0, &_1, &_2, &_3);
}

PHP_METHOD(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, setTextureAtIndex)
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
	mtl_mtlcomputecommandencoder_set_texture_at_index(&_0, &_1, &_2);
}

PHP_METHOD(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, dispatchThreadgroupsThreadsPerThreadgroup)
{
	zval *handle_param = NULL, *threadgroupsPerGridWidth_param = NULL, *threadgroupsPerGridHeight_param = NULL, *threadgroupsPerGridDepth_param = NULL, *threadsPerThreadgroupWidth_param = NULL, *threadsPerThreadgroupHeight_param = NULL, *threadsPerThreadgroupDepth_param = NULL, _0, _1, _2, _3, _4, _5, _6;
	zend_long handle, threadgroupsPerGridWidth, threadgroupsPerGridHeight, threadgroupsPerGridDepth, threadsPerThreadgroupWidth, threadsPerThreadgroupHeight, threadsPerThreadgroupDepth;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(threadgroupsPerGridWidth)
		Z_PARAM_LONG(threadgroupsPerGridHeight)
		Z_PARAM_LONG(threadgroupsPerGridDepth)
		Z_PARAM_LONG(threadsPerThreadgroupWidth)
		Z_PARAM_LONG(threadsPerThreadgroupHeight)
		Z_PARAM_LONG(threadsPerThreadgroupDepth)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(7, 0, &handle_param, &threadgroupsPerGridWidth_param, &threadgroupsPerGridHeight_param, &threadgroupsPerGridDepth_param, &threadsPerThreadgroupWidth_param, &threadsPerThreadgroupHeight_param, &threadsPerThreadgroupDepth_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, threadgroupsPerGridWidth);
	ZVAL_LONG(&_2, threadgroupsPerGridHeight);
	ZVAL_LONG(&_3, threadgroupsPerGridDepth);
	ZVAL_LONG(&_4, threadsPerThreadgroupWidth);
	ZVAL_LONG(&_5, threadsPerThreadgroupHeight);
	ZVAL_LONG(&_6, threadsPerThreadgroupDepth);
	mtl_mtlcomputecommandencoder_dispatch_threadgroups_threads_per_threadgroup(&_0, &_1, &_2, &_3, &_4, &_5, &_6);
}

PHP_METHOD(Metal_MTL_MTLComputeCommandEncoder_MTLComputeCommandEncoder, dispatchThreadsThreadsPerThreadgroup)
{
	zval *handle_param = NULL, *threadsPerGridWidth_param = NULL, *threadsPerGridHeight_param = NULL, *threadsPerGridDepth_param = NULL, *threadsPerThreadgroupWidth_param = NULL, *threadsPerThreadgroupHeight_param = NULL, *threadsPerThreadgroupDepth_param = NULL, _0, _1, _2, _3, _4, _5, _6;
	zend_long handle, threadsPerGridWidth, threadsPerGridHeight, threadsPerGridDepth, threadsPerThreadgroupWidth, threadsPerThreadgroupHeight, threadsPerThreadgroupDepth;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZEND_PARSE_PARAMETERS_START(7, 7)
		Z_PARAM_LONG(handle)
		Z_PARAM_LONG(threadsPerGridWidth)
		Z_PARAM_LONG(threadsPerGridHeight)
		Z_PARAM_LONG(threadsPerGridDepth)
		Z_PARAM_LONG(threadsPerThreadgroupWidth)
		Z_PARAM_LONG(threadsPerThreadgroupHeight)
		Z_PARAM_LONG(threadsPerThreadgroupDepth)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(7, 0, &handle_param, &threadsPerGridWidth_param, &threadsPerGridHeight_param, &threadsPerGridDepth_param, &threadsPerThreadgroupWidth_param, &threadsPerThreadgroupHeight_param, &threadsPerThreadgroupDepth_param);
	ZVAL_LONG(&_0, handle);
	ZVAL_LONG(&_1, threadsPerGridWidth);
	ZVAL_LONG(&_2, threadsPerGridHeight);
	ZVAL_LONG(&_3, threadsPerGridDepth);
	ZVAL_LONG(&_4, threadsPerThreadgroupWidth);
	ZVAL_LONG(&_5, threadsPerThreadgroupHeight);
	ZVAL_LONG(&_6, threadsPerThreadgroupDepth);
	mtl_mtlcomputecommandencoder_dispatch_threads_threads_per_threadgroup(&_0, &_1, &_2, &_3, &_4, &_5, &_6);
}

