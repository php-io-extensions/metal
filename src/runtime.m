#include "runtime.h"

static zend_object_handlers metal_handlers;

typedef struct {
	zend_class_entry *ce;
	Protocol *protocol;            /* non-nil: fromPointer checks conformsToProtocol: */
	Class cls;                     /* non-Nil: fromPointer checks isKindOfClass: */
} metal_native;

/* Filled only from MINIT. One row per handle class. */
#define METAL_NATIVE_MAX 96
static metal_native metal_natives[METAL_NATIVE_MAX];
static uint32_t metal_native_count = 0;

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

void metal_map_native(zend_class_entry *ce, Protocol *protocol, Class cls)
{
	if (metal_native_count >= METAL_NATIVE_MAX) {
		zend_error_noreturn(E_ERROR, "metal: the native class map is full");
	}

	metal_natives[metal_native_count++] = (metal_native) { ce, protocol, cls };
}

static metal_native *metal_native_for(zend_class_entry *ce)
{
	for (uint32_t i = 0; i < metal_native_count; i++) {
		if (metal_natives[i].ce == ce) {
			return &metal_natives[i];
		}
	}

	return NULL;
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

	zend_class_entry *scope = zend_get_called_scope(execute_data);

	if (pointer == 0) {
		zend_throw_exception_ex(metal_ce_MetalException, 0,
			"%s::fromPointer(): must not be a null address", ZSTR_VAL(scope->name));
		RETURN_THROWS();
	}

	metal_native *native = metal_native_for(scope);

	if (native == NULL || (native->protocol == nil && native->cls == Nil)) {
		zend_throw_exception_ex(metal_ce_MetalException, 0,
			"%s::fromPointer(): has no native class", ZSTR_VAL(scope->name));
		RETURN_THROWS();
	}

	id obj = (id) (uintptr_t) pointer;

	METAL_BEGIN
		bool matches = native->protocol != nil
			? [obj conformsToProtocol:native->protocol]
			: [obj isKindOfClass:native->cls];

		if (!matches) {
			zend_throw_exception_ex(metal_ce_MetalException, 0,
				"%s::fromPointer(): the object at 0x%lx is not an %s",
				ZSTR_VAL(scope->name), (unsigned long) pointer, ZSTR_VAL(scope->name));
			RETURN_THROWS();
		}

		metal_box(return_value, obj, scope);
	METAL_END
}

void metal_throw_nserror(NSError *error)
{
	if (EG(exception) != NULL) {
		return;
	}

	if (error == nil) {
		zend_throw_exception(metal_ce_MetalException, "Metal call failed", 0);
		return;
	}

	const char *message = [[error localizedDescription] UTF8String];

	zend_throw_exception(metal_ce_MetalException, message != NULL ? message : "Metal call failed", (zend_long) [error code]);
}

void metal_throw_nsexception(NSException *exception)
{
	if (EG(exception) != NULL) {
		return;
	}

	zend_throw_exception_ex(metal_ce_MetalException, 0, "%s: %s",
		[[exception name] UTF8String] ?: "NSException",
		[[exception reason] UTF8String] ?: "(no reason)");
}

NSString *metal_nsstring(zend_string *str)
{
	return [[[NSString alloc] initWithBytes:ZSTR_VAL(str) length:ZSTR_LEN(str) encoding:NSUTF8StringEncoding] autorelease];
}

bool metal_nonnegative(zend_long value, uint32_t arg_num)
{
	if (value < 0) {
		zend_argument_value_error(arg_num, "must be greater than or equal to 0");
		return false;
	}

	return true;
}

bool metal_resolve_bytes(zend_string *bytes, zend_long address, size_t need, uint32_t arg_num, const char *short_format, const void **out)
{
	if (bytes != NULL) {
		if (ZSTR_LEN(bytes) < need) {
			zend_argument_value_error(arg_num, short_format, need, ZSTR_LEN(bytes));
			return false;
		}

		*out = ZSTR_VAL(bytes);
		return true;
	}

	if (address == 0) {
		zend_argument_value_error(arg_num, "must not be a null address");
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
