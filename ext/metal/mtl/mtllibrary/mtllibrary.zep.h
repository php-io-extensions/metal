
extern zend_class_entry *metal_mtl_mtllibrary_mtllibrary_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_MTLLibrary_MTLLibrary);

PHP_METHOD(Metal_MTL_MTLLibrary_MTLLibrary, newFunctionWithName);
PHP_METHOD(Metal_MTL_MTLLibrary_MTLLibrary, functionNames);
PHP_METHOD(Metal_MTL_MTLLibrary_MTLLibrary, label);
PHP_METHOD(Metal_MTL_MTLLibrary_MTLLibrary, setLabel);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtllibrary_mtllibrary_newfunctionwithname, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, functionName, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtllibrary_mtllibrary_functionnames, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_metal_mtl_mtllibrary_mtllibrary_label, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtllibrary_mtllibrary_setlabel, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_INFO(0, label)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_mtllibrary_mtllibrary_method_entry) {
	PHP_ME(Metal_MTL_MTLLibrary_MTLLibrary, newFunctionWithName, arginfo_metal_mtl_mtllibrary_mtllibrary_newfunctionwithname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLLibrary_MTLLibrary, functionNames, arginfo_metal_mtl_mtllibrary_mtllibrary_functionnames, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLLibrary_MTLLibrary, label, arginfo_metal_mtl_mtllibrary_mtllibrary_label, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLLibrary_MTLLibrary, setLabel, arginfo_metal_mtl_mtllibrary_mtllibrary_setlabel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
