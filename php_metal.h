#ifndef PHP_METAL_H
#define PHP_METAL_H

extern zend_module_entry metal_module_entry;
#define phpext_metal_ptr &metal_module_entry

#define PHP_METAL_VERSION "0.10.0"

#if defined(ZTS) && defined(COMPILE_DL_METAL)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif
