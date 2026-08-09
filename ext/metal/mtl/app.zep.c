
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

#include "metal-app.h"



/**
 * NSApplication lifecycle — Darwin only.
 */
ZEPHIR_INIT_CLASS(Metal_MTL_App)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL, App, metal, mtl_app, metal_mtl_app_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Metal_MTL_App, init)
{
	zend_bool result = 0;
	
            result = mtl_app_init() == 1;
        
	RETURN_BOOL(result);
}

/**
 * Drain pending AppKit events once.
 * @return bool false when quit was requested
 */
PHP_METHOD(Metal_MTL_App, poll)
{
	zend_bool result = 0;
	
            result = mtl_app_poll() == 1;
        
	RETURN_BOOL(result);
}

PHP_METHOD(Metal_MTL_App, run)
{

	
            mtl_app_run();
        
}

PHP_METHOD(Metal_MTL_App, terminate)
{

	
            mtl_app_terminate();
        
}

PHP_METHOD(Metal_MTL_App, shouldQuit)
{
	zend_bool result = 0;
	
            result = mtl_app_should_quit() == 1;
        
	RETURN_BOOL(result);
}

PHP_METHOD(Metal_MTL_App, resetQuit)
{

	
            mtl_app_reset_quit();
        
}

