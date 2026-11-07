/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: a84adb2c6d9142407bef2a50398fbafb53938324 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_MTLCreateSystemDefaultDevice, 0, 0, MTLDevice, 1)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(MTLCreateSystemDefaultDevice);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(MTLCreateSystemDefaultDevice, arginfo_MTLCreateSystemDefaultDevice)
	ZEND_FE_END
};

static zend_class_entry *register_class_NSException(zend_class_entry *class_entry_Exception)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "NSException", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Exception, ZEND_ACC_FINAL);

	return class_entry;
}
