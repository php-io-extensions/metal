
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_METAL_H
#define PHP_METAL_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_METAL_NAME        "metal"
#define PHP_METAL_VERSION     "0.7.2"
#define PHP_METAL_EXTNAME     "metal"
#define PHP_METAL_AUTHOR      "Project Saturn Studios, LLC"
#define PHP_METAL_ZEPVERSION  "0.19.0-$Id$"
#define PHP_METAL_DESCRIPTION "PHP-Controllable Darwin Metal + AppKit Extension"



ZEND_BEGIN_MODULE_GLOBALS(metal)

	int initialized;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(metal)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(metal)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(metal, v)
#else
	#define ZEPHIR_GLOBAL(v) (metal_globals.v)
#endif

#ifdef ZTS
	ZEND_TSRMLS_CACHE_EXTERN()
	#define ZEPHIR_VGLOBAL ((zend_metal_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(metal_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(metal_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def metal_globals
#define zend_zephir_globals_def zend_metal_globals

extern zend_module_entry metal_module_entry;
#define phpext_metal_ptr &metal_module_entry

#endif
