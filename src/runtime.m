#include "runtime.h"

static zend_object_handlers metal_handlers;

static zend_object *metal_create_object(zend_class_entry *ce)
{
	metal_object *intern = zend_object_alloc(sizeof(metal_object), ce);

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);
	intern->std.handlers = &metal_handlers;

	return &intern->std;
}

static void metal_free_object(zend_object *object)
{
	metal_object *intern = metal_object_from(object);

	if (intern->ptr != nil) {
		zend_hash_index_del(&METAL_G(boxes), (zend_ulong) (uintptr_t) intern->ptr);

		@autoreleasepool {
			[intern->ptr release];
		}

		intern->ptr = nil;
	}

	zend_object_std_dtor(object);
}

void metal_object_setup(zend_class_entry *ce)
{
	static bool handlers_ready = false;

	if (!handlers_ready) {
		memcpy(&metal_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
		metal_handlers.offset = XtOffsetOf(metal_object, std);
		metal_handlers.free_obj = metal_free_object;
		metal_handlers.clone_obj = NULL;
		metal_handlers.compare = zend_objects_not_comparable;
		handlers_ready = true;
	}

	ce->create_object = metal_create_object;
	ce->default_object_handlers = &metal_handlers;
	ce->ce_flags |= ZEND_ACC_NOT_SERIALIZABLE | ZEND_ACC_FINAL;
}

static bool metal_box_existing(zval *rv, id obj)
{
	zend_object *existing = zend_hash_index_find_ptr(&METAL_G(boxes), (zend_ulong) (uintptr_t) obj);

	if (existing == NULL) {
		return false;
	}

	ZVAL_OBJ_COPY(rv, existing);
	return true;
}

static void metal_box_new(zval *rv, id retained, zend_class_entry *ce)
{
	object_init_ex(rv, ce);
	metal_object_from(Z_OBJ_P(rv))->ptr = retained;
	zend_hash_index_add_new_ptr(&METAL_G(boxes), (zend_ulong) (uintptr_t) retained, Z_OBJ_P(rv));
}

void metal_box(zval *rv, id obj, zend_class_entry *ce)
{
	if (obj == nil) {
		ZVAL_NULL(rv);
		return;
	}

	if (metal_box_existing(rv, obj)) {
		return;
	}

	metal_box_new(rv, [obj retain], ce);
}

void metal_box_owned(zval *rv, id obj, zend_class_entry *ce)
{
	if (obj == nil) {
		ZVAL_NULL(rv);
		return;
	}

	if (metal_box_existing(rv, obj)) {
		@autoreleasepool {
			[obj release];
		}
		return;
	}

	metal_box_new(rv, obj, ce);
}

void metal_from_pointer(INTERNAL_FUNCTION_PARAMETERS)
{
	zend_long pointer;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(pointer)
	ZEND_PARSE_PARAMETERS_END();

	/* The address is trusted to hold the class's native object; 0 is nil, which boxes as null. */
	METAL_BEGIN
		metal_box(return_value, (id) (uintptr_t) pointer, zend_get_called_scope(execute_data));
	METAL_END
}

#ifdef METAL_PROBES
bool metal_probe_off(const char *id)
{
	const char *off = getenv("METAL_PROBE_OFF");

	return off != NULL && strcmp(off, id) == 0;
}
#endif

static void metal_appkit_from_pointer(zval *rv, zend_class_entry *ce, uintptr_t address)
{
	zval arg;

	ZVAL_LONG(&arg, (zend_long) address);
	zend_call_method_with_1_params(NULL, ce, NULL, "frompointer", rv, &arg);
}

void metal_nserror_new(zval *rv, NSError *error)
{
	if (error == nil) {
		ZVAL_NULL(rv);
		return;
	}

	metal_appkit_from_pointer(rv, metal_ce_NSObject, (uintptr_t) error);
}

void metal_nserror_out(zval *ref, NSError *error)
{
	if (ref == NULL) {
		return;
	}

	zval value;

	metal_nserror_new(&value, error);
	ZEND_TRY_ASSIGN_REF_TMP(ref, &value);
}

void metal_cftype_new(zval *rv, CFTypeRef ref)
{
	metal_appkit_from_pointer(rv, metal_ce_CFType, (uintptr_t) ref);
}

CFTypeRef metal_cftype_from(zend_object *object)
{
	zval rv;

	zend_call_method_with_0_params(object, object->ce, NULL, "pointer", &rv);

	return (CFTypeRef) (uintptr_t) (Z_TYPE(rv) == IS_LONG ? Z_LVAL(rv) : 0);
}

void metal_nssize_new(zval *rv, CGSize size)
{
	object_init_ex(rv, metal_ce_NSSize);
	zend_update_property_double(metal_ce_NSSize, Z_OBJ_P(rv), "width", sizeof("width") - 1, size.width);
	zend_update_property_double(metal_ce_NSSize, Z_OBJ_P(rv), "height", sizeof("height") - 1, size.height);
}

CGSize metal_nssize_from(zend_object *object)
{
	zval width_rv, height_rv;
	zval *width = zend_read_property(object->ce, object, "width", sizeof("width") - 1, 0, &width_rv);
	zval *height = zend_read_property(object->ce, object, "height", sizeof("height") - 1, 0, &height_rv);

	return CGSizeMake(zval_get_double(width), zval_get_double(height));
}

void metal_throw_nsexception(NSException *exception)
{
	if (EG(exception) != NULL) {
		return;
	}

	zend_throw_exception_ex(metal_ce_NSException, 0, "%s: %s",
		[[exception name] UTF8String] ?: "NSException",
		[[exception reason] UTF8String] ?: "(no reason)");
}

NSString *metal_nsstring(zend_string *str)
{
	return [[[NSString alloc] initWithBytes:ZSTR_VAL(str) length:ZSTR_LEN(str) encoding:NSUTF8StringEncoding] autorelease];
}

bool metal_resolve_bytes(zend_string *bytes, zend_long address, size_t need, uint32_t arg_num, const char *short_format, const void **out)
{
	if (bytes != NULL) {
		if (!METAL_PROBE_OFF("metal-bytes-length") && (ZSTR_LEN(bytes) < need)) {
			zend_argument_value_error(arg_num, short_format, need, ZSTR_LEN(bytes)); /* binding:metal-bytes-length */
			return false;
		}

		*out = ZSTR_VAL(bytes);
		return true;
	}

	if (!METAL_PROBE_OFF("metal-null-address") && (address == 0)) {
		zend_argument_value_error(arg_num, "must not be a null address"); /* binding:metal-null-address */
		return false;
	}

	*out = (const void *) (uintptr_t) address;
	return true;
}

zend_long metal_enum_or_long(zval *value)
{
	if (Z_TYPE_P(value) == IS_OBJECT) {
		return Z_LVAL_P(zend_enum_fetch_case_value(Z_OBJ_P(value)));
	}

	return Z_LVAL_P(value);
}

void metal_return_enum(zval *rv, zend_class_entry *ce, zend_long value)
{
	zend_object *case_obj = NULL;

	if (zend_enum_get_case_by_value(&case_obj, ce, value, NULL, true) == SUCCESS && case_obj != NULL) {
		ZVAL_OBJ_COPY(rv, case_obj);
		return;
	}

	ZVAL_LONG(rv, value);
}
