
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "metal.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *metal_mtl_app_ce;
zend_class_entry *metal_mtl_device_ce;
zend_class_entry *metal_mtl_menu_ce;
zend_class_entry *metal_mtl_window_ce;

ZEND_DECLARE_MODULE_GLOBALS(metal)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(metal)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Metal_MTL_App);
	ZEPHIR_INIT(Metal_MTL_Device);
	ZEPHIR_INIT(Metal_MTL_Menu);
	ZEPHIR_INIT(Metal_MTL_Window);
	
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(metal)
{
	
	zephir_deinitialize_memory();
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_metal_globals *metal_globals)
{
	metal_globals->initialized = 0;

	/* Cache Enabled */
	metal_globals->cache_enabled = 1;

	/* Recursive Lock */
	metal_globals->recursive_lock = 0;

	/* Static cache */
	memset(metal_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);

	
	
}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_metal_globals *metal_globals)
{
	
}

static PHP_RINIT_FUNCTION(metal)
{
	zend_metal_globals *metal_globals_ptr;
	metal_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(metal_globals_ptr);
	zephir_initialize_memory(metal_globals_ptr);

	
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(metal)
{
	
	zephir_deinitialize_memory();
	return SUCCESS;
}



static PHP_MINFO_FUNCTION(metal)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_METAL_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_METAL_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_METAL_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_METAL_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_METAL_ZEPVERSION);
	php_info_print_table_end();
	
	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(metal)
{
#if defined(COMPILE_DL_METAL) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	php_zephir_init_globals(metal_globals);
	php_zephir_init_module_globals(metal_globals);
}

static PHP_GSHUTDOWN_FUNCTION(metal)
{
	
}


zend_function_entry php_metal_functions[] = {
	ZEND_FE_END

};

static const zend_module_dep php_metal_deps[] = {
	
	ZEND_MOD_END
};

zend_module_entry metal_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	php_metal_deps,
	PHP_METAL_EXTNAME,
	php_metal_functions,
	PHP_MINIT(metal),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(metal),
#else
	NULL,
#endif
	PHP_RINIT(metal),
	PHP_RSHUTDOWN(metal),
	PHP_MINFO(metal),
	PHP_METAL_VERSION,
	ZEND_MODULE_GLOBALS(metal),
	PHP_GINIT(metal),
	PHP_GSHUTDOWN(metal),
#ifdef ZEPHIR_POST_REQUEST
	PHP_PRSHUTDOWN(metal),
#else
	NULL,
#endif
	STANDARD_MODULE_PROPERTIES_EX
};

/* implement standard "stub" routine to introduce ourselves to Zend */
#ifdef COMPILE_DL_METAL
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(metal)
#endif
