
extern zend_class_entry *metal_mtl_mtlsamplerstate_mtlsamplerstate_ce;

ZEPHIR_INIT_CLASS(Metal_MTL_MTLSamplerState_MTLSamplerState);

PHP_METHOD(Metal_MTL_MTLSamplerState_MTLSamplerState, label);

ZEND_BEGIN_ARG_INFO_EX(arginfo_metal_mtl_mtlsamplerstate_mtlsamplerstate_label, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(metal_mtl_mtlsamplerstate_mtlsamplerstate_method_entry) {
	PHP_ME(Metal_MTL_MTLSamplerState_MTLSamplerState, label, arginfo_metal_mtl_mtlsamplerstate_mtlsamplerstate_label, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
