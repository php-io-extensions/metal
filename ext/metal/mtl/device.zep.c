
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"

#include "metal-device.h"
#include <stdint.h>



/**
 * MTLDevice / MTLCommandQueue handles (opaque ints).
 */
ZEPHIR_INIT_CLASS(Metal_MTL_Device)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL, Device, metal, mtl_device, metal_mtl_device_method_entry, 0);

	return SUCCESS;
}

/**
 * @return int Opaque MTLDevice handle, or 0
 */
PHP_METHOD(Metal_MTL_Device, createSystemDefault)
{
	zend_long handle = 0;
	
            handle = (zend_long) mtl_device_create_system_default();
        
	RETURN_LONG(handle);
}

PHP_METHOD(Metal_MTL_Device, release)
{
	zval *device_param = NULL;
	zend_long device;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &device_param);
	
            mtl_device_release((uintptr_t) device);
        
}

/**
 * @return int Opaque MTLCommandQueue handle, or 0
 */
PHP_METHOD(Metal_MTL_Device, newCommandQueue)
{
	zval *device_param = NULL;
	zend_long device, handle = 0;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &device_param);
	
            handle = (zend_long) mtl_device_new_command_queue((uintptr_t) device);
        
	RETURN_LONG(handle);
}

PHP_METHOD(Metal_MTL_Device, releaseCommandQueue)
{
	zval *queue_param = NULL;
	zend_long queue;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(queue)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &queue_param);
	
            mtl_command_queue_release((uintptr_t) queue);
        
}

PHP_METHOD(Metal_MTL_Device, getName)
{
	zval name;
	zval *device_param = NULL;
	zend_long device;

	ZVAL_UNDEF(&name);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(device)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &device_param);
	
            char buf[512];
            buf[0] = '\0';
            if (mtl_device_get_name((uintptr_t) device, buf, (int) sizeof(buf))) {
                ZVAL_STRING(&name, buf);
            } else {
                ZVAL_STRING(&name, "");
            }
        
	RETURN_CTORW(&name);
}

