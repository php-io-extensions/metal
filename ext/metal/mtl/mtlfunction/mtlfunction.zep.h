
extern zend_class_entry *metal_mtl_mtlfunction_mtlfunction_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_MTLFunction_MTLFunction);

PHP_METHOD(Metal_MTL_MTLFunction_MTLFunction, name);
PHP_METHOD(Metal_MTL_MTLFunction_MTLFunction, functionType);
PHP_METHOD(Metal_MTL_MTLFunction_MTLFunction, label);
PHP_METHOD(Metal_MTL_MTLFunction_MTLFunction, setLabel);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlfunction_mtlfunction_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlfunction_mtlfunction_functiontype, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_metal_mtl_mtlfunction_mtlfunction_label, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_metal_mtl_mtlfunction_mtlfunction_setlabel, 0, 2, IS_VOID, 0)

	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_INFO(0, label)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_mtlfunction_mtlfunction_method_entry) {
	PHP_ME(Metal_MTL_MTLFunction_MTLFunction, name, arginfo_metal_mtl_mtlfunction_mtlfunction_name, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLFunction_MTLFunction, functionType, arginfo_metal_mtl_mtlfunction_mtlfunction_functiontype, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLFunction_MTLFunction, label, arginfo_metal_mtl_mtlfunction_mtlfunction_label, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Metal_MTL_MTLFunction_MTLFunction, setLabel, arginfo_metal_mtl_mtlfunction_mtlfunction_setlabel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
