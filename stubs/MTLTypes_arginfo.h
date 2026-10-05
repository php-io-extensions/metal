/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 929d6f1856d1c3d068eea17c18717c598d7431a0 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_MTLOrigin___construct, 0, 0, 3)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_MTLSize___construct, 0, 0, 3)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, depth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_MTLRegion___construct, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, origin, MTLOrigin, 0)
	ZEND_ARG_OBJ_INFO(0, size, MTLSize, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_MTLClearColor___construct, 0, 0, 4)
	ZEND_ARG_TYPE_INFO(0, red, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, green, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, blue, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_MTLViewport___construct, 0, 0, 6)
	ZEND_ARG_TYPE_INFO(0, originX, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, originY, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, znear, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, zfar, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_MTLScissorRect___construct, 0, 0, 4)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(MTLOrigin, __construct);
ZEND_METHOD(MTLSize, __construct);
ZEND_METHOD(MTLRegion, __construct);
ZEND_METHOD(MTLClearColor, __construct);
ZEND_METHOD(MTLViewport, __construct);
ZEND_METHOD(MTLScissorRect, __construct);

static const zend_function_entry class_MTLOrigin_methods[] = {
	ZEND_ME(MTLOrigin, __construct, arginfo_class_MTLOrigin___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_MTLSize_methods[] = {
	ZEND_ME(MTLSize, __construct, arginfo_class_MTLSize___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_MTLRegion_methods[] = {
	ZEND_ME(MTLRegion, __construct, arginfo_class_MTLRegion___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_MTLClearColor_methods[] = {
	ZEND_ME(MTLClearColor, __construct, arginfo_class_MTLClearColor___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_MTLViewport_methods[] = {
	ZEND_ME(MTLViewport, __construct, arginfo_class_MTLViewport___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_MTLScissorRect_methods[] = {
	ZEND_ME(MTLScissorRect, __construct, arginfo_class_MTLScissorRect___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_MTLOrigin(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLOrigin", class_MTLOrigin_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x_default_value;
	ZVAL_LONG(&property_x_default_value, 0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_LONG(&property_y_default_value, 0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y_name);

	zval property_z_default_value;
	ZVAL_LONG(&property_z_default_value, 0);
	zend_string *property_z_name = zend_string_init("z", sizeof("z") - 1, 1);
	zend_declare_typed_property(class_entry, property_z_name, &property_z_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_z_name);

	return class_entry;
}

static zend_class_entry *register_class_MTLSize(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLSize", class_MTLSize_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_width_default_value;
	ZVAL_LONG(&property_width_default_value, 0);
	zend_string *property_width_name = zend_string_init("width", sizeof("width") - 1, 1);
	zend_declare_typed_property(class_entry, property_width_name, &property_width_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_width_name);

	zval property_height_default_value;
	ZVAL_LONG(&property_height_default_value, 0);
	zend_string *property_height_name = zend_string_init("height", sizeof("height") - 1, 1);
	zend_declare_typed_property(class_entry, property_height_name, &property_height_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_height_name);

	zval property_depth_default_value;
	ZVAL_LONG(&property_depth_default_value, 0);
	zend_string *property_depth_name = zend_string_init("depth", sizeof("depth") - 1, 1);
	zend_declare_typed_property(class_entry, property_depth_name, &property_depth_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_depth_name);

	return class_entry;
}

static zend_class_entry *register_class_MTLRegion(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLRegion", class_MTLRegion_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_origin_default_value;
	ZVAL_UNDEF(&property_origin_default_value);
	zend_string *property_origin_name = zend_string_init("origin", sizeof("origin") - 1, 1);
	zend_string *property_origin_class_MTLOrigin = zend_string_init("MTLOrigin", sizeof("MTLOrigin")-1, 1);
	zend_declare_typed_property(class_entry, property_origin_name, &property_origin_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_origin_class_MTLOrigin, 0, 0));
	zend_string_release(property_origin_name);

	zval property_size_default_value;
	ZVAL_UNDEF(&property_size_default_value);
	zend_string *property_size_name = zend_string_init("size", sizeof("size") - 1, 1);
	zend_string *property_size_class_MTLSize = zend_string_init("MTLSize", sizeof("MTLSize")-1, 1);
	zend_declare_typed_property(class_entry, property_size_name, &property_size_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_size_class_MTLSize, 0, 0));
	zend_string_release(property_size_name);

	return class_entry;
}

static zend_class_entry *register_class_MTLClearColor(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLClearColor", class_MTLClearColor_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_red_default_value;
	ZVAL_DOUBLE(&property_red_default_value, 0.0);
	zend_string *property_red_name = zend_string_init("red", sizeof("red") - 1, 1);
	zend_declare_typed_property(class_entry, property_red_name, &property_red_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_red_name);

	zval property_green_default_value;
	ZVAL_DOUBLE(&property_green_default_value, 0.0);
	zend_string *property_green_name = zend_string_init("green", sizeof("green") - 1, 1);
	zend_declare_typed_property(class_entry, property_green_name, &property_green_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_green_name);

	zval property_blue_default_value;
	ZVAL_DOUBLE(&property_blue_default_value, 0.0);
	zend_string *property_blue_name = zend_string_init("blue", sizeof("blue") - 1, 1);
	zend_declare_typed_property(class_entry, property_blue_name, &property_blue_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_blue_name);

	zval property_alpha_default_value;
	ZVAL_DOUBLE(&property_alpha_default_value, 0.0);
	zend_string *property_alpha_name = zend_string_init("alpha", sizeof("alpha") - 1, 1);
	zend_declare_typed_property(class_entry, property_alpha_name, &property_alpha_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_alpha_name);

	return class_entry;
}

static zend_class_entry *register_class_MTLViewport(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLViewport", class_MTLViewport_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_originX_default_value;
	ZVAL_DOUBLE(&property_originX_default_value, 0.0);
	zend_string *property_originX_name = zend_string_init("originX", sizeof("originX") - 1, 1);
	zend_declare_typed_property(class_entry, property_originX_name, &property_originX_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_originX_name);

	zval property_originY_default_value;
	ZVAL_DOUBLE(&property_originY_default_value, 0.0);
	zend_string *property_originY_name = zend_string_init("originY", sizeof("originY") - 1, 1);
	zend_declare_typed_property(class_entry, property_originY_name, &property_originY_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_originY_name);

	zval property_width_default_value;
	ZVAL_DOUBLE(&property_width_default_value, 0.0);
	zend_string *property_width_name = zend_string_init("width", sizeof("width") - 1, 1);
	zend_declare_typed_property(class_entry, property_width_name, &property_width_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_width_name);

	zval property_height_default_value;
	ZVAL_DOUBLE(&property_height_default_value, 0.0);
	zend_string *property_height_name = zend_string_init("height", sizeof("height") - 1, 1);
	zend_declare_typed_property(class_entry, property_height_name, &property_height_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_height_name);

	zval property_znear_default_value;
	ZVAL_DOUBLE(&property_znear_default_value, 0.0);
	zend_string *property_znear_name = zend_string_init("znear", sizeof("znear") - 1, 1);
	zend_declare_typed_property(class_entry, property_znear_name, &property_znear_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_znear_name);

	zval property_zfar_default_value;
	ZVAL_DOUBLE(&property_zfar_default_value, 0.0);
	zend_string *property_zfar_name = zend_string_init("zfar", sizeof("zfar") - 1, 1);
	zend_declare_typed_property(class_entry, property_zfar_name, &property_zfar_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_zfar_name);

	return class_entry;
}

static zend_class_entry *register_class_MTLScissorRect(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "MTLScissorRect", class_MTLScissorRect_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_x_default_value;
	ZVAL_LONG(&property_x_default_value, 0);
	zend_string *property_x_name = zend_string_init("x", sizeof("x") - 1, 1);
	zend_declare_typed_property(class_entry, property_x_name, &property_x_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_x_name);

	zval property_y_default_value;
	ZVAL_LONG(&property_y_default_value, 0);
	zend_string *property_y_name = zend_string_init("y", sizeof("y") - 1, 1);
	zend_declare_typed_property(class_entry, property_y_name, &property_y_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_y_name);

	zval property_width_default_value;
	ZVAL_LONG(&property_width_default_value, 0);
	zend_string *property_width_name = zend_string_init("width", sizeof("width") - 1, 1);
	zend_declare_typed_property(class_entry, property_width_name, &property_width_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_width_name);

	zval property_height_default_value;
	ZVAL_LONG(&property_height_default_value, 0);
	zend_string *property_height_name = zend_string_init("height", sizeof("height") - 1, 1);
	zend_declare_typed_property(class_entry, property_height_name, &property_height_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_height_name);

	return class_entry;
}

static zend_class_entry *register_class_MTLPixelFormat(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLPixelFormat", IS_LONG, NULL);

	zval enum_case_INVALID_value;
	ZVAL_LONG(&enum_case_INVALID_value, 0);
	zend_enum_add_case_cstr(class_entry, "INVALID", &enum_case_INVALID_value);

	zval enum_case_A8_UNORM_value;
	ZVAL_LONG(&enum_case_A8_UNORM_value, 1);
	zend_enum_add_case_cstr(class_entry, "A8_UNORM", &enum_case_A8_UNORM_value);

	zval enum_case_R8_UNORM_value;
	ZVAL_LONG(&enum_case_R8_UNORM_value, 10);
	zend_enum_add_case_cstr(class_entry, "R8_UNORM", &enum_case_R8_UNORM_value);

	zval enum_case_R8_UNORM_SRGB_value;
	ZVAL_LONG(&enum_case_R8_UNORM_SRGB_value, 11);
	zend_enum_add_case_cstr(class_entry, "R8_UNORM_SRGB", &enum_case_R8_UNORM_SRGB_value);

	zval enum_case_R8_SNORM_value;
	ZVAL_LONG(&enum_case_R8_SNORM_value, 12);
	zend_enum_add_case_cstr(class_entry, "R8_SNORM", &enum_case_R8_SNORM_value);

	zval enum_case_R8_UINT_value;
	ZVAL_LONG(&enum_case_R8_UINT_value, 13);
	zend_enum_add_case_cstr(class_entry, "R8_UINT", &enum_case_R8_UINT_value);

	zval enum_case_R8_SINT_value;
	ZVAL_LONG(&enum_case_R8_SINT_value, 14);
	zend_enum_add_case_cstr(class_entry, "R8_SINT", &enum_case_R8_SINT_value);

	zval enum_case_R16_UNORM_value;
	ZVAL_LONG(&enum_case_R16_UNORM_value, 20);
	zend_enum_add_case_cstr(class_entry, "R16_UNORM", &enum_case_R16_UNORM_value);

	zval enum_case_R16_SNORM_value;
	ZVAL_LONG(&enum_case_R16_SNORM_value, 22);
	zend_enum_add_case_cstr(class_entry, "R16_SNORM", &enum_case_R16_SNORM_value);

	zval enum_case_R16_UINT_value;
	ZVAL_LONG(&enum_case_R16_UINT_value, 23);
	zend_enum_add_case_cstr(class_entry, "R16_UINT", &enum_case_R16_UINT_value);

	zval enum_case_R16_SINT_value;
	ZVAL_LONG(&enum_case_R16_SINT_value, 24);
	zend_enum_add_case_cstr(class_entry, "R16_SINT", &enum_case_R16_SINT_value);

	zval enum_case_R16_FLOAT_value;
	ZVAL_LONG(&enum_case_R16_FLOAT_value, 25);
	zend_enum_add_case_cstr(class_entry, "R16_FLOAT", &enum_case_R16_FLOAT_value);

	zval enum_case_RG8_UNORM_value;
	ZVAL_LONG(&enum_case_RG8_UNORM_value, 30);
	zend_enum_add_case_cstr(class_entry, "RG8_UNORM", &enum_case_RG8_UNORM_value);

	zval enum_case_RG8_UNORM_SRGB_value;
	ZVAL_LONG(&enum_case_RG8_UNORM_SRGB_value, 31);
	zend_enum_add_case_cstr(class_entry, "RG8_UNORM_SRGB", &enum_case_RG8_UNORM_SRGB_value);

	zval enum_case_RG8_SNORM_value;
	ZVAL_LONG(&enum_case_RG8_SNORM_value, 32);
	zend_enum_add_case_cstr(class_entry, "RG8_SNORM", &enum_case_RG8_SNORM_value);

	zval enum_case_RG8_UINT_value;
	ZVAL_LONG(&enum_case_RG8_UINT_value, 33);
	zend_enum_add_case_cstr(class_entry, "RG8_UINT", &enum_case_RG8_UINT_value);

	zval enum_case_RG8_SINT_value;
	ZVAL_LONG(&enum_case_RG8_SINT_value, 34);
	zend_enum_add_case_cstr(class_entry, "RG8_SINT", &enum_case_RG8_SINT_value);

	zval enum_case_B5G6R5_UNORM_value;
	ZVAL_LONG(&enum_case_B5G6R5_UNORM_value, 40);
	zend_enum_add_case_cstr(class_entry, "B5G6R5_UNORM", &enum_case_B5G6R5_UNORM_value);

	zval enum_case_A1BGR5_UNORM_value;
	ZVAL_LONG(&enum_case_A1BGR5_UNORM_value, 41);
	zend_enum_add_case_cstr(class_entry, "A1BGR5_UNORM", &enum_case_A1BGR5_UNORM_value);

	zval enum_case_ABGR4_UNORM_value;
	ZVAL_LONG(&enum_case_ABGR4_UNORM_value, 42);
	zend_enum_add_case_cstr(class_entry, "ABGR4_UNORM", &enum_case_ABGR4_UNORM_value);

	zval enum_case_BGR5A1_UNORM_value;
	ZVAL_LONG(&enum_case_BGR5A1_UNORM_value, 43);
	zend_enum_add_case_cstr(class_entry, "BGR5A1_UNORM", &enum_case_BGR5A1_UNORM_value);

	zval enum_case_R32_UINT_value;
	ZVAL_LONG(&enum_case_R32_UINT_value, 53);
	zend_enum_add_case_cstr(class_entry, "R32_UINT", &enum_case_R32_UINT_value);

	zval enum_case_R32_SINT_value;
	ZVAL_LONG(&enum_case_R32_SINT_value, 54);
	zend_enum_add_case_cstr(class_entry, "R32_SINT", &enum_case_R32_SINT_value);

	zval enum_case_R32_FLOAT_value;
	ZVAL_LONG(&enum_case_R32_FLOAT_value, 55);
	zend_enum_add_case_cstr(class_entry, "R32_FLOAT", &enum_case_R32_FLOAT_value);

	zval enum_case_RG16_UNORM_value;
	ZVAL_LONG(&enum_case_RG16_UNORM_value, 60);
	zend_enum_add_case_cstr(class_entry, "RG16_UNORM", &enum_case_RG16_UNORM_value);

	zval enum_case_RG16_SNORM_value;
	ZVAL_LONG(&enum_case_RG16_SNORM_value, 62);
	zend_enum_add_case_cstr(class_entry, "RG16_SNORM", &enum_case_RG16_SNORM_value);

	zval enum_case_RG16_UINT_value;
	ZVAL_LONG(&enum_case_RG16_UINT_value, 63);
	zend_enum_add_case_cstr(class_entry, "RG16_UINT", &enum_case_RG16_UINT_value);

	zval enum_case_RG16_SINT_value;
	ZVAL_LONG(&enum_case_RG16_SINT_value, 64);
	zend_enum_add_case_cstr(class_entry, "RG16_SINT", &enum_case_RG16_SINT_value);

	zval enum_case_RG16_FLOAT_value;
	ZVAL_LONG(&enum_case_RG16_FLOAT_value, 65);
	zend_enum_add_case_cstr(class_entry, "RG16_FLOAT", &enum_case_RG16_FLOAT_value);

	zval enum_case_RGBA8_UNORM_value;
	ZVAL_LONG(&enum_case_RGBA8_UNORM_value, 70);
	zend_enum_add_case_cstr(class_entry, "RGBA8_UNORM", &enum_case_RGBA8_UNORM_value);

	zval enum_case_RGBA8_UNORM_SRGB_value;
	ZVAL_LONG(&enum_case_RGBA8_UNORM_SRGB_value, 71);
	zend_enum_add_case_cstr(class_entry, "RGBA8_UNORM_SRGB", &enum_case_RGBA8_UNORM_SRGB_value);

	zval enum_case_RGBA8_SNORM_value;
	ZVAL_LONG(&enum_case_RGBA8_SNORM_value, 72);
	zend_enum_add_case_cstr(class_entry, "RGBA8_SNORM", &enum_case_RGBA8_SNORM_value);

	zval enum_case_RGBA8_UINT_value;
	ZVAL_LONG(&enum_case_RGBA8_UINT_value, 73);
	zend_enum_add_case_cstr(class_entry, "RGBA8_UINT", &enum_case_RGBA8_UINT_value);

	zval enum_case_RGBA8_SINT_value;
	ZVAL_LONG(&enum_case_RGBA8_SINT_value, 74);
	zend_enum_add_case_cstr(class_entry, "RGBA8_SINT", &enum_case_RGBA8_SINT_value);

	zval enum_case_BGRA8_UNORM_value;
	ZVAL_LONG(&enum_case_BGRA8_UNORM_value, 80);
	zend_enum_add_case_cstr(class_entry, "BGRA8_UNORM", &enum_case_BGRA8_UNORM_value);

	zval enum_case_BGRA8_UNORM_SRGB_value;
	ZVAL_LONG(&enum_case_BGRA8_UNORM_SRGB_value, 81);
	zend_enum_add_case_cstr(class_entry, "BGRA8_UNORM_SRGB", &enum_case_BGRA8_UNORM_SRGB_value);

	zval enum_case_RGB10A2_UNORM_value;
	ZVAL_LONG(&enum_case_RGB10A2_UNORM_value, 90);
	zend_enum_add_case_cstr(class_entry, "RGB10A2_UNORM", &enum_case_RGB10A2_UNORM_value);

	zval enum_case_RGB10A2_UINT_value;
	ZVAL_LONG(&enum_case_RGB10A2_UINT_value, 91);
	zend_enum_add_case_cstr(class_entry, "RGB10A2_UINT", &enum_case_RGB10A2_UINT_value);

	zval enum_case_RG11B10_FLOAT_value;
	ZVAL_LONG(&enum_case_RG11B10_FLOAT_value, 92);
	zend_enum_add_case_cstr(class_entry, "RG11B10_FLOAT", &enum_case_RG11B10_FLOAT_value);

	zval enum_case_RGB9E5_FLOAT_value;
	ZVAL_LONG(&enum_case_RGB9E5_FLOAT_value, 93);
	zend_enum_add_case_cstr(class_entry, "RGB9E5_FLOAT", &enum_case_RGB9E5_FLOAT_value);

	zval enum_case_BGR10A2_UNORM_value;
	ZVAL_LONG(&enum_case_BGR10A2_UNORM_value, 94);
	zend_enum_add_case_cstr(class_entry, "BGR10A2_UNORM", &enum_case_BGR10A2_UNORM_value);

	zval enum_case_BGR10_XR_value;
	ZVAL_LONG(&enum_case_BGR10_XR_value, 554);
	zend_enum_add_case_cstr(class_entry, "BGR10_XR", &enum_case_BGR10_XR_value);

	zval enum_case_BGR10_XR_SRGB_value;
	ZVAL_LONG(&enum_case_BGR10_XR_SRGB_value, 555);
	zend_enum_add_case_cstr(class_entry, "BGR10_XR_SRGB", &enum_case_BGR10_XR_SRGB_value);

	zval enum_case_RG32_UINT_value;
	ZVAL_LONG(&enum_case_RG32_UINT_value, 103);
	zend_enum_add_case_cstr(class_entry, "RG32_UINT", &enum_case_RG32_UINT_value);

	zval enum_case_RG32_SINT_value;
	ZVAL_LONG(&enum_case_RG32_SINT_value, 104);
	zend_enum_add_case_cstr(class_entry, "RG32_SINT", &enum_case_RG32_SINT_value);

	zval enum_case_RG32_FLOAT_value;
	ZVAL_LONG(&enum_case_RG32_FLOAT_value, 105);
	zend_enum_add_case_cstr(class_entry, "RG32_FLOAT", &enum_case_RG32_FLOAT_value);

	zval enum_case_RGBA16_UNORM_value;
	ZVAL_LONG(&enum_case_RGBA16_UNORM_value, 110);
	zend_enum_add_case_cstr(class_entry, "RGBA16_UNORM", &enum_case_RGBA16_UNORM_value);

	zval enum_case_RGBA16_SNORM_value;
	ZVAL_LONG(&enum_case_RGBA16_SNORM_value, 112);
	zend_enum_add_case_cstr(class_entry, "RGBA16_SNORM", &enum_case_RGBA16_SNORM_value);

	zval enum_case_RGBA16_UINT_value;
	ZVAL_LONG(&enum_case_RGBA16_UINT_value, 113);
	zend_enum_add_case_cstr(class_entry, "RGBA16_UINT", &enum_case_RGBA16_UINT_value);

	zval enum_case_RGBA16_SINT_value;
	ZVAL_LONG(&enum_case_RGBA16_SINT_value, 114);
	zend_enum_add_case_cstr(class_entry, "RGBA16_SINT", &enum_case_RGBA16_SINT_value);

	zval enum_case_RGBA16_FLOAT_value;
	ZVAL_LONG(&enum_case_RGBA16_FLOAT_value, 115);
	zend_enum_add_case_cstr(class_entry, "RGBA16_FLOAT", &enum_case_RGBA16_FLOAT_value);

	zval enum_case_BGRA10_XR_value;
	ZVAL_LONG(&enum_case_BGRA10_XR_value, 552);
	zend_enum_add_case_cstr(class_entry, "BGRA10_XR", &enum_case_BGRA10_XR_value);

	zval enum_case_BGRA10_XR_SRGB_value;
	ZVAL_LONG(&enum_case_BGRA10_XR_SRGB_value, 553);
	zend_enum_add_case_cstr(class_entry, "BGRA10_XR_SRGB", &enum_case_BGRA10_XR_SRGB_value);

	zval enum_case_RGBA32_UINT_value;
	ZVAL_LONG(&enum_case_RGBA32_UINT_value, 123);
	zend_enum_add_case_cstr(class_entry, "RGBA32_UINT", &enum_case_RGBA32_UINT_value);

	zval enum_case_RGBA32_SINT_value;
	ZVAL_LONG(&enum_case_RGBA32_SINT_value, 124);
	zend_enum_add_case_cstr(class_entry, "RGBA32_SINT", &enum_case_RGBA32_SINT_value);

	zval enum_case_RGBA32_FLOAT_value;
	ZVAL_LONG(&enum_case_RGBA32_FLOAT_value, 125);
	zend_enum_add_case_cstr(class_entry, "RGBA32_FLOAT", &enum_case_RGBA32_FLOAT_value);

	zval enum_case_BC1_RGBA_value;
	ZVAL_LONG(&enum_case_BC1_RGBA_value, 130);
	zend_enum_add_case_cstr(class_entry, "BC1_RGBA", &enum_case_BC1_RGBA_value);

	zval enum_case_BC1_RGBA_SRGB_value;
	ZVAL_LONG(&enum_case_BC1_RGBA_SRGB_value, 131);
	zend_enum_add_case_cstr(class_entry, "BC1_RGBA_SRGB", &enum_case_BC1_RGBA_SRGB_value);

	zval enum_case_BC2_RGBA_value;
	ZVAL_LONG(&enum_case_BC2_RGBA_value, 132);
	zend_enum_add_case_cstr(class_entry, "BC2_RGBA", &enum_case_BC2_RGBA_value);

	zval enum_case_BC2_RGBA_SRGB_value;
	ZVAL_LONG(&enum_case_BC2_RGBA_SRGB_value, 133);
	zend_enum_add_case_cstr(class_entry, "BC2_RGBA_SRGB", &enum_case_BC2_RGBA_SRGB_value);

	zval enum_case_BC3_RGBA_value;
	ZVAL_LONG(&enum_case_BC3_RGBA_value, 134);
	zend_enum_add_case_cstr(class_entry, "BC3_RGBA", &enum_case_BC3_RGBA_value);

	zval enum_case_BC3_RGBA_SRGB_value;
	ZVAL_LONG(&enum_case_BC3_RGBA_SRGB_value, 135);
	zend_enum_add_case_cstr(class_entry, "BC3_RGBA_SRGB", &enum_case_BC3_RGBA_SRGB_value);

	zval enum_case_BC4_RUNORM_value;
	ZVAL_LONG(&enum_case_BC4_RUNORM_value, 140);
	zend_enum_add_case_cstr(class_entry, "BC4_RUNORM", &enum_case_BC4_RUNORM_value);

	zval enum_case_BC4_RSNORM_value;
	ZVAL_LONG(&enum_case_BC4_RSNORM_value, 141);
	zend_enum_add_case_cstr(class_entry, "BC4_RSNORM", &enum_case_BC4_RSNORM_value);

	zval enum_case_BC5_RG_UNORM_value;
	ZVAL_LONG(&enum_case_BC5_RG_UNORM_value, 142);
	zend_enum_add_case_cstr(class_entry, "BC5_RG_UNORM", &enum_case_BC5_RG_UNORM_value);

	zval enum_case_BC5_RG_SNORM_value;
	ZVAL_LONG(&enum_case_BC5_RG_SNORM_value, 143);
	zend_enum_add_case_cstr(class_entry, "BC5_RG_SNORM", &enum_case_BC5_RG_SNORM_value);

	zval enum_case_BC6H_RGB_FLOAT_value;
	ZVAL_LONG(&enum_case_BC6H_RGB_FLOAT_value, 150);
	zend_enum_add_case_cstr(class_entry, "BC6H_RGB_FLOAT", &enum_case_BC6H_RGB_FLOAT_value);

	zval enum_case_BC6H_RGB_UFLOAT_value;
	ZVAL_LONG(&enum_case_BC6H_RGB_UFLOAT_value, 151);
	zend_enum_add_case_cstr(class_entry, "BC6H_RGB_UFLOAT", &enum_case_BC6H_RGB_UFLOAT_value);

	zval enum_case_BC7_RGBA_UNORM_value;
	ZVAL_LONG(&enum_case_BC7_RGBA_UNORM_value, 152);
	zend_enum_add_case_cstr(class_entry, "BC7_RGBA_UNORM", &enum_case_BC7_RGBA_UNORM_value);

	zval enum_case_BC7_RGBA_UNORM_SRGB_value;
	ZVAL_LONG(&enum_case_BC7_RGBA_UNORM_SRGB_value, 153);
	zend_enum_add_case_cstr(class_entry, "BC7_RGBA_UNORM_SRGB", &enum_case_BC7_RGBA_UNORM_SRGB_value);

	zval enum_case_PVRTC_RGB_2BPP_value;
	ZVAL_LONG(&enum_case_PVRTC_RGB_2BPP_value, 160);
	zend_enum_add_case_cstr(class_entry, "PVRTC_RGB_2BPP", &enum_case_PVRTC_RGB_2BPP_value);

	zval enum_case_PVRTC_RGB_2BPP_SRGB_value;
	ZVAL_LONG(&enum_case_PVRTC_RGB_2BPP_SRGB_value, 161);
	zend_enum_add_case_cstr(class_entry, "PVRTC_RGB_2BPP_SRGB", &enum_case_PVRTC_RGB_2BPP_SRGB_value);

	zval enum_case_PVRTC_RGB_4BPP_value;
	ZVAL_LONG(&enum_case_PVRTC_RGB_4BPP_value, 162);
	zend_enum_add_case_cstr(class_entry, "PVRTC_RGB_4BPP", &enum_case_PVRTC_RGB_4BPP_value);

	zval enum_case_PVRTC_RGB_4BPP_SRGB_value;
	ZVAL_LONG(&enum_case_PVRTC_RGB_4BPP_SRGB_value, 163);
	zend_enum_add_case_cstr(class_entry, "PVRTC_RGB_4BPP_SRGB", &enum_case_PVRTC_RGB_4BPP_SRGB_value);

	zval enum_case_PVRTC_RGBA_2BPP_value;
	ZVAL_LONG(&enum_case_PVRTC_RGBA_2BPP_value, 164);
	zend_enum_add_case_cstr(class_entry, "PVRTC_RGBA_2BPP", &enum_case_PVRTC_RGBA_2BPP_value);

	zval enum_case_PVRTC_RGBA_2BPP_SRGB_value;
	ZVAL_LONG(&enum_case_PVRTC_RGBA_2BPP_SRGB_value, 165);
	zend_enum_add_case_cstr(class_entry, "PVRTC_RGBA_2BPP_SRGB", &enum_case_PVRTC_RGBA_2BPP_SRGB_value);

	zval enum_case_PVRTC_RGBA_4BPP_value;
	ZVAL_LONG(&enum_case_PVRTC_RGBA_4BPP_value, 166);
	zend_enum_add_case_cstr(class_entry, "PVRTC_RGBA_4BPP", &enum_case_PVRTC_RGBA_4BPP_value);

	zval enum_case_PVRTC_RGBA_4BPP_SRGB_value;
	ZVAL_LONG(&enum_case_PVRTC_RGBA_4BPP_SRGB_value, 167);
	zend_enum_add_case_cstr(class_entry, "PVRTC_RGBA_4BPP_SRGB", &enum_case_PVRTC_RGBA_4BPP_SRGB_value);

	zval enum_case_EAC_R11_UNORM_value;
	ZVAL_LONG(&enum_case_EAC_R11_UNORM_value, 170);
	zend_enum_add_case_cstr(class_entry, "EAC_R11_UNORM", &enum_case_EAC_R11_UNORM_value);

	zval enum_case_EAC_R11_SNORM_value;
	ZVAL_LONG(&enum_case_EAC_R11_SNORM_value, 172);
	zend_enum_add_case_cstr(class_entry, "EAC_R11_SNORM", &enum_case_EAC_R11_SNORM_value);

	zval enum_case_EAC_RG11_UNORM_value;
	ZVAL_LONG(&enum_case_EAC_RG11_UNORM_value, 174);
	zend_enum_add_case_cstr(class_entry, "EAC_RG11_UNORM", &enum_case_EAC_RG11_UNORM_value);

	zval enum_case_EAC_RG11_SNORM_value;
	ZVAL_LONG(&enum_case_EAC_RG11_SNORM_value, 176);
	zend_enum_add_case_cstr(class_entry, "EAC_RG11_SNORM", &enum_case_EAC_RG11_SNORM_value);

	zval enum_case_EAC_RGBA8_value;
	ZVAL_LONG(&enum_case_EAC_RGBA8_value, 178);
	zend_enum_add_case_cstr(class_entry, "EAC_RGBA8", &enum_case_EAC_RGBA8_value);

	zval enum_case_EAC_RGBA8_SRGB_value;
	ZVAL_LONG(&enum_case_EAC_RGBA8_SRGB_value, 179);
	zend_enum_add_case_cstr(class_entry, "EAC_RGBA8_SRGB", &enum_case_EAC_RGBA8_SRGB_value);

	zval enum_case_ETC2_RGB8_value;
	ZVAL_LONG(&enum_case_ETC2_RGB8_value, 180);
	zend_enum_add_case_cstr(class_entry, "ETC2_RGB8", &enum_case_ETC2_RGB8_value);

	zval enum_case_ETC2_RGB8_SRGB_value;
	ZVAL_LONG(&enum_case_ETC2_RGB8_SRGB_value, 181);
	zend_enum_add_case_cstr(class_entry, "ETC2_RGB8_SRGB", &enum_case_ETC2_RGB8_SRGB_value);

	zval enum_case_ETC2_RGB8A1_value;
	ZVAL_LONG(&enum_case_ETC2_RGB8A1_value, 182);
	zend_enum_add_case_cstr(class_entry, "ETC2_RGB8A1", &enum_case_ETC2_RGB8A1_value);

	zval enum_case_ETC2_RGB8A1_SRGB_value;
	ZVAL_LONG(&enum_case_ETC2_RGB8A1_SRGB_value, 183);
	zend_enum_add_case_cstr(class_entry, "ETC2_RGB8A1_SRGB", &enum_case_ETC2_RGB8A1_SRGB_value);

	zval enum_case_ASTC_4X4_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_4X4_SRGB_value, 186);
	zend_enum_add_case_cstr(class_entry, "ASTC_4X4_SRGB", &enum_case_ASTC_4X4_SRGB_value);

	zval enum_case_ASTC_5X4_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_5X4_SRGB_value, 187);
	zend_enum_add_case_cstr(class_entry, "ASTC_5X4_SRGB", &enum_case_ASTC_5X4_SRGB_value);

	zval enum_case_ASTC_5X5_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_5X5_SRGB_value, 188);
	zend_enum_add_case_cstr(class_entry, "ASTC_5X5_SRGB", &enum_case_ASTC_5X5_SRGB_value);

	zval enum_case_ASTC_6X5_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_6X5_SRGB_value, 189);
	zend_enum_add_case_cstr(class_entry, "ASTC_6X5_SRGB", &enum_case_ASTC_6X5_SRGB_value);

	zval enum_case_ASTC_6X6_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_6X6_SRGB_value, 190);
	zend_enum_add_case_cstr(class_entry, "ASTC_6X6_SRGB", &enum_case_ASTC_6X6_SRGB_value);

	zval enum_case_ASTC_8X5_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_8X5_SRGB_value, 192);
	zend_enum_add_case_cstr(class_entry, "ASTC_8X5_SRGB", &enum_case_ASTC_8X5_SRGB_value);

	zval enum_case_ASTC_8X6_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_8X6_SRGB_value, 193);
	zend_enum_add_case_cstr(class_entry, "ASTC_8X6_SRGB", &enum_case_ASTC_8X6_SRGB_value);

	zval enum_case_ASTC_8X8_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_8X8_SRGB_value, 194);
	zend_enum_add_case_cstr(class_entry, "ASTC_8X8_SRGB", &enum_case_ASTC_8X8_SRGB_value);

	zval enum_case_ASTC_10X5_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_10X5_SRGB_value, 195);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X5_SRGB", &enum_case_ASTC_10X5_SRGB_value);

	zval enum_case_ASTC_10X6_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_10X6_SRGB_value, 196);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X6_SRGB", &enum_case_ASTC_10X6_SRGB_value);

	zval enum_case_ASTC_10X8_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_10X8_SRGB_value, 197);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X8_SRGB", &enum_case_ASTC_10X8_SRGB_value);

	zval enum_case_ASTC_10X10_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_10X10_SRGB_value, 198);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X10_SRGB", &enum_case_ASTC_10X10_SRGB_value);

	zval enum_case_ASTC_12X10_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_12X10_SRGB_value, 199);
	zend_enum_add_case_cstr(class_entry, "ASTC_12X10_SRGB", &enum_case_ASTC_12X10_SRGB_value);

	zval enum_case_ASTC_12X12_SRGB_value;
	ZVAL_LONG(&enum_case_ASTC_12X12_SRGB_value, 200);
	zend_enum_add_case_cstr(class_entry, "ASTC_12X12_SRGB", &enum_case_ASTC_12X12_SRGB_value);

	zval enum_case_ASTC_4X4_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_4X4_LDR_value, 204);
	zend_enum_add_case_cstr(class_entry, "ASTC_4X4_LDR", &enum_case_ASTC_4X4_LDR_value);

	zval enum_case_ASTC_5X4_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_5X4_LDR_value, 205);
	zend_enum_add_case_cstr(class_entry, "ASTC_5X4_LDR", &enum_case_ASTC_5X4_LDR_value);

	zval enum_case_ASTC_5X5_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_5X5_LDR_value, 206);
	zend_enum_add_case_cstr(class_entry, "ASTC_5X5_LDR", &enum_case_ASTC_5X5_LDR_value);

	zval enum_case_ASTC_6X5_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_6X5_LDR_value, 207);
	zend_enum_add_case_cstr(class_entry, "ASTC_6X5_LDR", &enum_case_ASTC_6X5_LDR_value);

	zval enum_case_ASTC_6X6_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_6X6_LDR_value, 208);
	zend_enum_add_case_cstr(class_entry, "ASTC_6X6_LDR", &enum_case_ASTC_6X6_LDR_value);

	zval enum_case_ASTC_8X5_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_8X5_LDR_value, 210);
	zend_enum_add_case_cstr(class_entry, "ASTC_8X5_LDR", &enum_case_ASTC_8X5_LDR_value);

	zval enum_case_ASTC_8X6_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_8X6_LDR_value, 211);
	zend_enum_add_case_cstr(class_entry, "ASTC_8X6_LDR", &enum_case_ASTC_8X6_LDR_value);

	zval enum_case_ASTC_8X8_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_8X8_LDR_value, 212);
	zend_enum_add_case_cstr(class_entry, "ASTC_8X8_LDR", &enum_case_ASTC_8X8_LDR_value);

	zval enum_case_ASTC_10X5_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_10X5_LDR_value, 213);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X5_LDR", &enum_case_ASTC_10X5_LDR_value);

	zval enum_case_ASTC_10X6_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_10X6_LDR_value, 214);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X6_LDR", &enum_case_ASTC_10X6_LDR_value);

	zval enum_case_ASTC_10X8_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_10X8_LDR_value, 215);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X8_LDR", &enum_case_ASTC_10X8_LDR_value);

	zval enum_case_ASTC_10X10_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_10X10_LDR_value, 216);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X10_LDR", &enum_case_ASTC_10X10_LDR_value);

	zval enum_case_ASTC_12X10_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_12X10_LDR_value, 217);
	zend_enum_add_case_cstr(class_entry, "ASTC_12X10_LDR", &enum_case_ASTC_12X10_LDR_value);

	zval enum_case_ASTC_12X12_LDR_value;
	ZVAL_LONG(&enum_case_ASTC_12X12_LDR_value, 218);
	zend_enum_add_case_cstr(class_entry, "ASTC_12X12_LDR", &enum_case_ASTC_12X12_LDR_value);

	zval enum_case_ASTC_4X4_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_4X4_HDR_value, 222);
	zend_enum_add_case_cstr(class_entry, "ASTC_4X4_HDR", &enum_case_ASTC_4X4_HDR_value);

	zval enum_case_ASTC_5X4_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_5X4_HDR_value, 223);
	zend_enum_add_case_cstr(class_entry, "ASTC_5X4_HDR", &enum_case_ASTC_5X4_HDR_value);

	zval enum_case_ASTC_5X5_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_5X5_HDR_value, 224);
	zend_enum_add_case_cstr(class_entry, "ASTC_5X5_HDR", &enum_case_ASTC_5X5_HDR_value);

	zval enum_case_ASTC_6X5_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_6X5_HDR_value, 225);
	zend_enum_add_case_cstr(class_entry, "ASTC_6X5_HDR", &enum_case_ASTC_6X5_HDR_value);

	zval enum_case_ASTC_6X6_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_6X6_HDR_value, 226);
	zend_enum_add_case_cstr(class_entry, "ASTC_6X6_HDR", &enum_case_ASTC_6X6_HDR_value);

	zval enum_case_ASTC_8X5_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_8X5_HDR_value, 228);
	zend_enum_add_case_cstr(class_entry, "ASTC_8X5_HDR", &enum_case_ASTC_8X5_HDR_value);

	zval enum_case_ASTC_8X6_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_8X6_HDR_value, 229);
	zend_enum_add_case_cstr(class_entry, "ASTC_8X6_HDR", &enum_case_ASTC_8X6_HDR_value);

	zval enum_case_ASTC_8X8_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_8X8_HDR_value, 230);
	zend_enum_add_case_cstr(class_entry, "ASTC_8X8_HDR", &enum_case_ASTC_8X8_HDR_value);

	zval enum_case_ASTC_10X5_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_10X5_HDR_value, 231);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X5_HDR", &enum_case_ASTC_10X5_HDR_value);

	zval enum_case_ASTC_10X6_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_10X6_HDR_value, 232);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X6_HDR", &enum_case_ASTC_10X6_HDR_value);

	zval enum_case_ASTC_10X8_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_10X8_HDR_value, 233);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X8_HDR", &enum_case_ASTC_10X8_HDR_value);

	zval enum_case_ASTC_10X10_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_10X10_HDR_value, 234);
	zend_enum_add_case_cstr(class_entry, "ASTC_10X10_HDR", &enum_case_ASTC_10X10_HDR_value);

	zval enum_case_ASTC_12X10_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_12X10_HDR_value, 235);
	zend_enum_add_case_cstr(class_entry, "ASTC_12X10_HDR", &enum_case_ASTC_12X10_HDR_value);

	zval enum_case_ASTC_12X12_HDR_value;
	ZVAL_LONG(&enum_case_ASTC_12X12_HDR_value, 236);
	zend_enum_add_case_cstr(class_entry, "ASTC_12X12_HDR", &enum_case_ASTC_12X12_HDR_value);

	zval enum_case_GBGR422_value;
	ZVAL_LONG(&enum_case_GBGR422_value, 240);
	zend_enum_add_case_cstr(class_entry, "GBGR422", &enum_case_GBGR422_value);

	zval enum_case_BGRG422_value;
	ZVAL_LONG(&enum_case_BGRG422_value, 241);
	zend_enum_add_case_cstr(class_entry, "BGRG422", &enum_case_BGRG422_value);

	zval enum_case_DEPTH16_UNORM_value;
	ZVAL_LONG(&enum_case_DEPTH16_UNORM_value, 250);
	zend_enum_add_case_cstr(class_entry, "DEPTH16_UNORM", &enum_case_DEPTH16_UNORM_value);

	zval enum_case_DEPTH32_FLOAT_value;
	ZVAL_LONG(&enum_case_DEPTH32_FLOAT_value, 252);
	zend_enum_add_case_cstr(class_entry, "DEPTH32_FLOAT", &enum_case_DEPTH32_FLOAT_value);

	zval enum_case_STENCIL8_value;
	ZVAL_LONG(&enum_case_STENCIL8_value, 253);
	zend_enum_add_case_cstr(class_entry, "STENCIL8", &enum_case_STENCIL8_value);

	zval enum_case_DEPTH24_UNORM_STENCIL8_value;
	ZVAL_LONG(&enum_case_DEPTH24_UNORM_STENCIL8_value, 255);
	zend_enum_add_case_cstr(class_entry, "DEPTH24_UNORM_STENCIL8", &enum_case_DEPTH24_UNORM_STENCIL8_value);

	zval enum_case_DEPTH32_FLOAT_STENCIL8_value;
	ZVAL_LONG(&enum_case_DEPTH32_FLOAT_STENCIL8_value, 260);
	zend_enum_add_case_cstr(class_entry, "DEPTH32_FLOAT_STENCIL8", &enum_case_DEPTH32_FLOAT_STENCIL8_value);

	zval enum_case_X32_STENCIL8_value;
	ZVAL_LONG(&enum_case_X32_STENCIL8_value, 261);
	zend_enum_add_case_cstr(class_entry, "X32_STENCIL8", &enum_case_X32_STENCIL8_value);

	zval enum_case_X24_STENCIL8_value;
	ZVAL_LONG(&enum_case_X24_STENCIL8_value, 262);
	zend_enum_add_case_cstr(class_entry, "X24_STENCIL8", &enum_case_X24_STENCIL8_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLLoadAction(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLLoadAction", IS_LONG, NULL);

	zval enum_case_DONT_CARE_value;
	ZVAL_LONG(&enum_case_DONT_CARE_value, 0);
	zend_enum_add_case_cstr(class_entry, "DONT_CARE", &enum_case_DONT_CARE_value);

	zval enum_case_LOAD_value;
	ZVAL_LONG(&enum_case_LOAD_value, 1);
	zend_enum_add_case_cstr(class_entry, "LOAD", &enum_case_LOAD_value);

	zval enum_case_CLEAR_value;
	ZVAL_LONG(&enum_case_CLEAR_value, 2);
	zend_enum_add_case_cstr(class_entry, "CLEAR", &enum_case_CLEAR_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLStoreAction(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLStoreAction", IS_LONG, NULL);

	zval enum_case_DONT_CARE_value;
	ZVAL_LONG(&enum_case_DONT_CARE_value, 0);
	zend_enum_add_case_cstr(class_entry, "DONT_CARE", &enum_case_DONT_CARE_value);

	zval enum_case_STORE_value;
	ZVAL_LONG(&enum_case_STORE_value, 1);
	zend_enum_add_case_cstr(class_entry, "STORE", &enum_case_STORE_value);

	zval enum_case_MULTISAMPLE_RESOLVE_value;
	ZVAL_LONG(&enum_case_MULTISAMPLE_RESOLVE_value, 2);
	zend_enum_add_case_cstr(class_entry, "MULTISAMPLE_RESOLVE", &enum_case_MULTISAMPLE_RESOLVE_value);

	zval enum_case_STORE_AND_MULTISAMPLE_RESOLVE_value;
	ZVAL_LONG(&enum_case_STORE_AND_MULTISAMPLE_RESOLVE_value, 3);
	zend_enum_add_case_cstr(class_entry, "STORE_AND_MULTISAMPLE_RESOLVE", &enum_case_STORE_AND_MULTISAMPLE_RESOLVE_value);

	zval enum_case_UNKNOWN_value;
	ZVAL_LONG(&enum_case_UNKNOWN_value, 4);
	zend_enum_add_case_cstr(class_entry, "UNKNOWN", &enum_case_UNKNOWN_value);

	zval enum_case_CUSTOM_SAMPLE_DEPTH_STORE_value;
	ZVAL_LONG(&enum_case_CUSTOM_SAMPLE_DEPTH_STORE_value, 5);
	zend_enum_add_case_cstr(class_entry, "CUSTOM_SAMPLE_DEPTH_STORE", &enum_case_CUSTOM_SAMPLE_DEPTH_STORE_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLPrimitiveType(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLPrimitiveType", IS_LONG, NULL);

	zval enum_case_POINT_value;
	ZVAL_LONG(&enum_case_POINT_value, 0);
	zend_enum_add_case_cstr(class_entry, "POINT", &enum_case_POINT_value);

	zval enum_case_LINE_value;
	ZVAL_LONG(&enum_case_LINE_value, 1);
	zend_enum_add_case_cstr(class_entry, "LINE", &enum_case_LINE_value);

	zval enum_case_LINE_STRIP_value;
	ZVAL_LONG(&enum_case_LINE_STRIP_value, 2);
	zend_enum_add_case_cstr(class_entry, "LINE_STRIP", &enum_case_LINE_STRIP_value);

	zval enum_case_TRIANGLE_value;
	ZVAL_LONG(&enum_case_TRIANGLE_value, 3);
	zend_enum_add_case_cstr(class_entry, "TRIANGLE", &enum_case_TRIANGLE_value);

	zval enum_case_TRIANGLE_STRIP_value;
	ZVAL_LONG(&enum_case_TRIANGLE_STRIP_value, 4);
	zend_enum_add_case_cstr(class_entry, "TRIANGLE_STRIP", &enum_case_TRIANGLE_STRIP_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLIndexType(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLIndexType", IS_LONG, NULL);

	zval enum_case_UINT16_value;
	ZVAL_LONG(&enum_case_UINT16_value, 0);
	zend_enum_add_case_cstr(class_entry, "UINT16", &enum_case_UINT16_value);

	zval enum_case_UINT32_value;
	ZVAL_LONG(&enum_case_UINT32_value, 1);
	zend_enum_add_case_cstr(class_entry, "UINT32", &enum_case_UINT32_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLTextureUsage(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLTextureUsage", IS_LONG, NULL);

	zval enum_case_UNKNOWN_value;
	ZVAL_LONG(&enum_case_UNKNOWN_value, 0);
	zend_enum_add_case_cstr(class_entry, "UNKNOWN", &enum_case_UNKNOWN_value);

	zval enum_case_SHADER_READ_value;
	ZVAL_LONG(&enum_case_SHADER_READ_value, 1);
	zend_enum_add_case_cstr(class_entry, "SHADER_READ", &enum_case_SHADER_READ_value);

	zval enum_case_SHADER_WRITE_value;
	ZVAL_LONG(&enum_case_SHADER_WRITE_value, 2);
	zend_enum_add_case_cstr(class_entry, "SHADER_WRITE", &enum_case_SHADER_WRITE_value);

	zval enum_case_RENDER_TARGET_value;
	ZVAL_LONG(&enum_case_RENDER_TARGET_value, 4);
	zend_enum_add_case_cstr(class_entry, "RENDER_TARGET", &enum_case_RENDER_TARGET_value);

	zval enum_case_PIXEL_FORMAT_VIEW_value;
	ZVAL_LONG(&enum_case_PIXEL_FORMAT_VIEW_value, 16);
	zend_enum_add_case_cstr(class_entry, "PIXEL_FORMAT_VIEW", &enum_case_PIXEL_FORMAT_VIEW_value);

	zval enum_case_SHADER_ATOMIC_value;
	ZVAL_LONG(&enum_case_SHADER_ATOMIC_value, 32);
	zend_enum_add_case_cstr(class_entry, "SHADER_ATOMIC", &enum_case_SHADER_ATOMIC_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLStorageMode(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLStorageMode", IS_LONG, NULL);

	zval enum_case_SHARED_value;
	ZVAL_LONG(&enum_case_SHARED_value, 0);
	zend_enum_add_case_cstr(class_entry, "SHARED", &enum_case_SHARED_value);

	zval enum_case_MANAGED_value;
	ZVAL_LONG(&enum_case_MANAGED_value, 1);
	zend_enum_add_case_cstr(class_entry, "MANAGED", &enum_case_MANAGED_value);

	zval enum_case_PRIVATE_value;
	ZVAL_LONG(&enum_case_PRIVATE_value, 2);
	zend_enum_add_case_cstr(class_entry, "PRIVATE", &enum_case_PRIVATE_value);

	zval enum_case_MEMORYLESS_value;
	ZVAL_LONG(&enum_case_MEMORYLESS_value, 3);
	zend_enum_add_case_cstr(class_entry, "MEMORYLESS", &enum_case_MEMORYLESS_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLResourceOptions(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLResourceOptions", IS_LONG, NULL);

	zval enum_case_CPU_CACHE_MODE_WRITE_COMBINED_value;
	ZVAL_LONG(&enum_case_CPU_CACHE_MODE_WRITE_COMBINED_value, 1);
	zend_enum_add_case_cstr(class_entry, "CPU_CACHE_MODE_WRITE_COMBINED", &enum_case_CPU_CACHE_MODE_WRITE_COMBINED_value);

	zval enum_case_STORAGE_MODE_SHARED_value;
	ZVAL_LONG(&enum_case_STORAGE_MODE_SHARED_value, 0);
	zend_enum_add_case_cstr(class_entry, "STORAGE_MODE_SHARED", &enum_case_STORAGE_MODE_SHARED_value);

	zval enum_case_STORAGE_MODE_MANAGED_value;
	ZVAL_LONG(&enum_case_STORAGE_MODE_MANAGED_value, 16);
	zend_enum_add_case_cstr(class_entry, "STORAGE_MODE_MANAGED", &enum_case_STORAGE_MODE_MANAGED_value);

	zval enum_case_STORAGE_MODE_PRIVATE_value;
	ZVAL_LONG(&enum_case_STORAGE_MODE_PRIVATE_value, 32);
	zend_enum_add_case_cstr(class_entry, "STORAGE_MODE_PRIVATE", &enum_case_STORAGE_MODE_PRIVATE_value);

	zval enum_case_STORAGE_MODE_MEMORYLESS_value;
	ZVAL_LONG(&enum_case_STORAGE_MODE_MEMORYLESS_value, 48);
	zend_enum_add_case_cstr(class_entry, "STORAGE_MODE_MEMORYLESS", &enum_case_STORAGE_MODE_MEMORYLESS_value);

	zval enum_case_HAZARD_TRACKING_MODE_UNTRACKED_value;
	ZVAL_LONG(&enum_case_HAZARD_TRACKING_MODE_UNTRACKED_value, 256);
	zend_enum_add_case_cstr(class_entry, "HAZARD_TRACKING_MODE_UNTRACKED", &enum_case_HAZARD_TRACKING_MODE_UNTRACKED_value);

	zval enum_case_HAZARD_TRACKING_MODE_TRACKED_value;
	ZVAL_LONG(&enum_case_HAZARD_TRACKING_MODE_TRACKED_value, 512);
	zend_enum_add_case_cstr(class_entry, "HAZARD_TRACKING_MODE_TRACKED", &enum_case_HAZARD_TRACKING_MODE_TRACKED_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLTextureType(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLTextureType", IS_LONG, NULL);

	zval enum_case_TYPE_1D_value;
	ZVAL_LONG(&enum_case_TYPE_1D_value, 0);
	zend_enum_add_case_cstr(class_entry, "TYPE_1D", &enum_case_TYPE_1D_value);

	zval enum_case_TYPE_1D_ARRAY_value;
	ZVAL_LONG(&enum_case_TYPE_1D_ARRAY_value, 1);
	zend_enum_add_case_cstr(class_entry, "TYPE_1D_ARRAY", &enum_case_TYPE_1D_ARRAY_value);

	zval enum_case_TYPE_2D_value;
	ZVAL_LONG(&enum_case_TYPE_2D_value, 2);
	zend_enum_add_case_cstr(class_entry, "TYPE_2D", &enum_case_TYPE_2D_value);

	zval enum_case_TYPE_2D_ARRAY_value;
	ZVAL_LONG(&enum_case_TYPE_2D_ARRAY_value, 3);
	zend_enum_add_case_cstr(class_entry, "TYPE_2D_ARRAY", &enum_case_TYPE_2D_ARRAY_value);

	zval enum_case_TYPE_2D_MULTISAMPLE_value;
	ZVAL_LONG(&enum_case_TYPE_2D_MULTISAMPLE_value, 4);
	zend_enum_add_case_cstr(class_entry, "TYPE_2D_MULTISAMPLE", &enum_case_TYPE_2D_MULTISAMPLE_value);

	zval enum_case_CUBE_value;
	ZVAL_LONG(&enum_case_CUBE_value, 5);
	zend_enum_add_case_cstr(class_entry, "CUBE", &enum_case_CUBE_value);

	zval enum_case_CUBE_ARRAY_value;
	ZVAL_LONG(&enum_case_CUBE_ARRAY_value, 6);
	zend_enum_add_case_cstr(class_entry, "CUBE_ARRAY", &enum_case_CUBE_ARRAY_value);

	zval enum_case_TYPE_3D_value;
	ZVAL_LONG(&enum_case_TYPE_3D_value, 7);
	zend_enum_add_case_cstr(class_entry, "TYPE_3D", &enum_case_TYPE_3D_value);

	zval enum_case_TYPE_2D_MULTISAMPLE_ARRAY_value;
	ZVAL_LONG(&enum_case_TYPE_2D_MULTISAMPLE_ARRAY_value, 8);
	zend_enum_add_case_cstr(class_entry, "TYPE_2D_MULTISAMPLE_ARRAY", &enum_case_TYPE_2D_MULTISAMPLE_ARRAY_value);

	zval enum_case_TEXTURE_BUFFER_value;
	ZVAL_LONG(&enum_case_TEXTURE_BUFFER_value, 9);
	zend_enum_add_case_cstr(class_entry, "TEXTURE_BUFFER", &enum_case_TEXTURE_BUFFER_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLVertexFormat(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLVertexFormat", IS_LONG, NULL);

	zval enum_case_INVALID_value;
	ZVAL_LONG(&enum_case_INVALID_value, 0);
	zend_enum_add_case_cstr(class_entry, "INVALID", &enum_case_INVALID_value);

	zval enum_case_UCHAR2_value;
	ZVAL_LONG(&enum_case_UCHAR2_value, 1);
	zend_enum_add_case_cstr(class_entry, "UCHAR2", &enum_case_UCHAR2_value);

	zval enum_case_UCHAR3_value;
	ZVAL_LONG(&enum_case_UCHAR3_value, 2);
	zend_enum_add_case_cstr(class_entry, "UCHAR3", &enum_case_UCHAR3_value);

	zval enum_case_UCHAR4_value;
	ZVAL_LONG(&enum_case_UCHAR4_value, 3);
	zend_enum_add_case_cstr(class_entry, "UCHAR4", &enum_case_UCHAR4_value);

	zval enum_case_CHAR2_value;
	ZVAL_LONG(&enum_case_CHAR2_value, 4);
	zend_enum_add_case_cstr(class_entry, "CHAR2", &enum_case_CHAR2_value);

	zval enum_case_CHAR3_value;
	ZVAL_LONG(&enum_case_CHAR3_value, 5);
	zend_enum_add_case_cstr(class_entry, "CHAR3", &enum_case_CHAR3_value);

	zval enum_case_CHAR4_value;
	ZVAL_LONG(&enum_case_CHAR4_value, 6);
	zend_enum_add_case_cstr(class_entry, "CHAR4", &enum_case_CHAR4_value);

	zval enum_case_UCHAR2_NORMALIZED_value;
	ZVAL_LONG(&enum_case_UCHAR2_NORMALIZED_value, 7);
	zend_enum_add_case_cstr(class_entry, "UCHAR2_NORMALIZED", &enum_case_UCHAR2_NORMALIZED_value);

	zval enum_case_UCHAR3_NORMALIZED_value;
	ZVAL_LONG(&enum_case_UCHAR3_NORMALIZED_value, 8);
	zend_enum_add_case_cstr(class_entry, "UCHAR3_NORMALIZED", &enum_case_UCHAR3_NORMALIZED_value);

	zval enum_case_UCHAR4_NORMALIZED_value;
	ZVAL_LONG(&enum_case_UCHAR4_NORMALIZED_value, 9);
	zend_enum_add_case_cstr(class_entry, "UCHAR4_NORMALIZED", &enum_case_UCHAR4_NORMALIZED_value);

	zval enum_case_CHAR2_NORMALIZED_value;
	ZVAL_LONG(&enum_case_CHAR2_NORMALIZED_value, 10);
	zend_enum_add_case_cstr(class_entry, "CHAR2_NORMALIZED", &enum_case_CHAR2_NORMALIZED_value);

	zval enum_case_CHAR3_NORMALIZED_value;
	ZVAL_LONG(&enum_case_CHAR3_NORMALIZED_value, 11);
	zend_enum_add_case_cstr(class_entry, "CHAR3_NORMALIZED", &enum_case_CHAR3_NORMALIZED_value);

	zval enum_case_CHAR4_NORMALIZED_value;
	ZVAL_LONG(&enum_case_CHAR4_NORMALIZED_value, 12);
	zend_enum_add_case_cstr(class_entry, "CHAR4_NORMALIZED", &enum_case_CHAR4_NORMALIZED_value);

	zval enum_case_USHORT2_value;
	ZVAL_LONG(&enum_case_USHORT2_value, 13);
	zend_enum_add_case_cstr(class_entry, "USHORT2", &enum_case_USHORT2_value);

	zval enum_case_USHORT3_value;
	ZVAL_LONG(&enum_case_USHORT3_value, 14);
	zend_enum_add_case_cstr(class_entry, "USHORT3", &enum_case_USHORT3_value);

	zval enum_case_USHORT4_value;
	ZVAL_LONG(&enum_case_USHORT4_value, 15);
	zend_enum_add_case_cstr(class_entry, "USHORT4", &enum_case_USHORT4_value);

	zval enum_case_SHORT2_value;
	ZVAL_LONG(&enum_case_SHORT2_value, 16);
	zend_enum_add_case_cstr(class_entry, "SHORT2", &enum_case_SHORT2_value);

	zval enum_case_SHORT3_value;
	ZVAL_LONG(&enum_case_SHORT3_value, 17);
	zend_enum_add_case_cstr(class_entry, "SHORT3", &enum_case_SHORT3_value);

	zval enum_case_SHORT4_value;
	ZVAL_LONG(&enum_case_SHORT4_value, 18);
	zend_enum_add_case_cstr(class_entry, "SHORT4", &enum_case_SHORT4_value);

	zval enum_case_USHORT2_NORMALIZED_value;
	ZVAL_LONG(&enum_case_USHORT2_NORMALIZED_value, 19);
	zend_enum_add_case_cstr(class_entry, "USHORT2_NORMALIZED", &enum_case_USHORT2_NORMALIZED_value);

	zval enum_case_USHORT3_NORMALIZED_value;
	ZVAL_LONG(&enum_case_USHORT3_NORMALIZED_value, 20);
	zend_enum_add_case_cstr(class_entry, "USHORT3_NORMALIZED", &enum_case_USHORT3_NORMALIZED_value);

	zval enum_case_USHORT4_NORMALIZED_value;
	ZVAL_LONG(&enum_case_USHORT4_NORMALIZED_value, 21);
	zend_enum_add_case_cstr(class_entry, "USHORT4_NORMALIZED", &enum_case_USHORT4_NORMALIZED_value);

	zval enum_case_SHORT2_NORMALIZED_value;
	ZVAL_LONG(&enum_case_SHORT2_NORMALIZED_value, 22);
	zend_enum_add_case_cstr(class_entry, "SHORT2_NORMALIZED", &enum_case_SHORT2_NORMALIZED_value);

	zval enum_case_SHORT3_NORMALIZED_value;
	ZVAL_LONG(&enum_case_SHORT3_NORMALIZED_value, 23);
	zend_enum_add_case_cstr(class_entry, "SHORT3_NORMALIZED", &enum_case_SHORT3_NORMALIZED_value);

	zval enum_case_SHORT4_NORMALIZED_value;
	ZVAL_LONG(&enum_case_SHORT4_NORMALIZED_value, 24);
	zend_enum_add_case_cstr(class_entry, "SHORT4_NORMALIZED", &enum_case_SHORT4_NORMALIZED_value);

	zval enum_case_HALF2_value;
	ZVAL_LONG(&enum_case_HALF2_value, 25);
	zend_enum_add_case_cstr(class_entry, "HALF2", &enum_case_HALF2_value);

	zval enum_case_HALF3_value;
	ZVAL_LONG(&enum_case_HALF3_value, 26);
	zend_enum_add_case_cstr(class_entry, "HALF3", &enum_case_HALF3_value);

	zval enum_case_HALF4_value;
	ZVAL_LONG(&enum_case_HALF4_value, 27);
	zend_enum_add_case_cstr(class_entry, "HALF4", &enum_case_HALF4_value);

	zval enum_case_FLOAT_value;
	ZVAL_LONG(&enum_case_FLOAT_value, 28);
	zend_enum_add_case_cstr(class_entry, "FLOAT", &enum_case_FLOAT_value);

	zval enum_case_FLOAT2_value;
	ZVAL_LONG(&enum_case_FLOAT2_value, 29);
	zend_enum_add_case_cstr(class_entry, "FLOAT2", &enum_case_FLOAT2_value);

	zval enum_case_FLOAT3_value;
	ZVAL_LONG(&enum_case_FLOAT3_value, 30);
	zend_enum_add_case_cstr(class_entry, "FLOAT3", &enum_case_FLOAT3_value);

	zval enum_case_FLOAT4_value;
	ZVAL_LONG(&enum_case_FLOAT4_value, 31);
	zend_enum_add_case_cstr(class_entry, "FLOAT4", &enum_case_FLOAT4_value);

	zval enum_case_INT_value;
	ZVAL_LONG(&enum_case_INT_value, 32);
	zend_enum_add_case_cstr(class_entry, "INT", &enum_case_INT_value);

	zval enum_case_INT2_value;
	ZVAL_LONG(&enum_case_INT2_value, 33);
	zend_enum_add_case_cstr(class_entry, "INT2", &enum_case_INT2_value);

	zval enum_case_INT3_value;
	ZVAL_LONG(&enum_case_INT3_value, 34);
	zend_enum_add_case_cstr(class_entry, "INT3", &enum_case_INT3_value);

	zval enum_case_INT4_value;
	ZVAL_LONG(&enum_case_INT4_value, 35);
	zend_enum_add_case_cstr(class_entry, "INT4", &enum_case_INT4_value);

	zval enum_case_UINT_value;
	ZVAL_LONG(&enum_case_UINT_value, 36);
	zend_enum_add_case_cstr(class_entry, "UINT", &enum_case_UINT_value);

	zval enum_case_UINT2_value;
	ZVAL_LONG(&enum_case_UINT2_value, 37);
	zend_enum_add_case_cstr(class_entry, "UINT2", &enum_case_UINT2_value);

	zval enum_case_UINT3_value;
	ZVAL_LONG(&enum_case_UINT3_value, 38);
	zend_enum_add_case_cstr(class_entry, "UINT3", &enum_case_UINT3_value);

	zval enum_case_UINT4_value;
	ZVAL_LONG(&enum_case_UINT4_value, 39);
	zend_enum_add_case_cstr(class_entry, "UINT4", &enum_case_UINT4_value);

	zval enum_case_INT1010102_NORMALIZED_value;
	ZVAL_LONG(&enum_case_INT1010102_NORMALIZED_value, 40);
	zend_enum_add_case_cstr(class_entry, "INT1010102_NORMALIZED", &enum_case_INT1010102_NORMALIZED_value);

	zval enum_case_UINT1010102_NORMALIZED_value;
	ZVAL_LONG(&enum_case_UINT1010102_NORMALIZED_value, 41);
	zend_enum_add_case_cstr(class_entry, "UINT1010102_NORMALIZED", &enum_case_UINT1010102_NORMALIZED_value);

	zval enum_case_UCHAR4_NORMALIZED_BGRA_value;
	ZVAL_LONG(&enum_case_UCHAR4_NORMALIZED_BGRA_value, 42);
	zend_enum_add_case_cstr(class_entry, "UCHAR4_NORMALIZED_BGRA", &enum_case_UCHAR4_NORMALIZED_BGRA_value);

	zval enum_case_UCHAR_value;
	ZVAL_LONG(&enum_case_UCHAR_value, 45);
	zend_enum_add_case_cstr(class_entry, "UCHAR", &enum_case_UCHAR_value);

	zval enum_case_CHAR_value;
	ZVAL_LONG(&enum_case_CHAR_value, 46);
	zend_enum_add_case_cstr(class_entry, "CHAR", &enum_case_CHAR_value);

	zval enum_case_UCHAR_NORMALIZED_value;
	ZVAL_LONG(&enum_case_UCHAR_NORMALIZED_value, 47);
	zend_enum_add_case_cstr(class_entry, "UCHAR_NORMALIZED", &enum_case_UCHAR_NORMALIZED_value);

	zval enum_case_CHAR_NORMALIZED_value;
	ZVAL_LONG(&enum_case_CHAR_NORMALIZED_value, 48);
	zend_enum_add_case_cstr(class_entry, "CHAR_NORMALIZED", &enum_case_CHAR_NORMALIZED_value);

	zval enum_case_USHORT_value;
	ZVAL_LONG(&enum_case_USHORT_value, 49);
	zend_enum_add_case_cstr(class_entry, "USHORT", &enum_case_USHORT_value);

	zval enum_case_SHORT_value;
	ZVAL_LONG(&enum_case_SHORT_value, 50);
	zend_enum_add_case_cstr(class_entry, "SHORT", &enum_case_SHORT_value);

	zval enum_case_USHORT_NORMALIZED_value;
	ZVAL_LONG(&enum_case_USHORT_NORMALIZED_value, 51);
	zend_enum_add_case_cstr(class_entry, "USHORT_NORMALIZED", &enum_case_USHORT_NORMALIZED_value);

	zval enum_case_SHORT_NORMALIZED_value;
	ZVAL_LONG(&enum_case_SHORT_NORMALIZED_value, 52);
	zend_enum_add_case_cstr(class_entry, "SHORT_NORMALIZED", &enum_case_SHORT_NORMALIZED_value);

	zval enum_case_HALF_value;
	ZVAL_LONG(&enum_case_HALF_value, 53);
	zend_enum_add_case_cstr(class_entry, "HALF", &enum_case_HALF_value);

	zval enum_case_FLOAT_RG11B10_value;
	ZVAL_LONG(&enum_case_FLOAT_RG11B10_value, 54);
	zend_enum_add_case_cstr(class_entry, "FLOAT_RG11B10", &enum_case_FLOAT_RG11B10_value);

	zval enum_case_FLOAT_RGB9E5_value;
	ZVAL_LONG(&enum_case_FLOAT_RGB9E5_value, 55);
	zend_enum_add_case_cstr(class_entry, "FLOAT_RGB9E5", &enum_case_FLOAT_RGB9E5_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLVertexStepFunction(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLVertexStepFunction", IS_LONG, NULL);

	zval enum_case_CONSTANT_value;
	ZVAL_LONG(&enum_case_CONSTANT_value, 0);
	zend_enum_add_case_cstr(class_entry, "CONSTANT", &enum_case_CONSTANT_value);

	zval enum_case_PER_VERTEX_value;
	ZVAL_LONG(&enum_case_PER_VERTEX_value, 1);
	zend_enum_add_case_cstr(class_entry, "PER_VERTEX", &enum_case_PER_VERTEX_value);

	zval enum_case_PER_INSTANCE_value;
	ZVAL_LONG(&enum_case_PER_INSTANCE_value, 2);
	zend_enum_add_case_cstr(class_entry, "PER_INSTANCE", &enum_case_PER_INSTANCE_value);

	zval enum_case_PER_PATCH_value;
	ZVAL_LONG(&enum_case_PER_PATCH_value, 3);
	zend_enum_add_case_cstr(class_entry, "PER_PATCH", &enum_case_PER_PATCH_value);

	zval enum_case_PER_PATCH_CONTROL_POINT_value;
	ZVAL_LONG(&enum_case_PER_PATCH_CONTROL_POINT_value, 4);
	zend_enum_add_case_cstr(class_entry, "PER_PATCH_CONTROL_POINT", &enum_case_PER_PATCH_CONTROL_POINT_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLBlendFactor(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLBlendFactor", IS_LONG, NULL);

	zval enum_case_ZERO_value;
	ZVAL_LONG(&enum_case_ZERO_value, 0);
	zend_enum_add_case_cstr(class_entry, "ZERO", &enum_case_ZERO_value);

	zval enum_case_ONE_value;
	ZVAL_LONG(&enum_case_ONE_value, 1);
	zend_enum_add_case_cstr(class_entry, "ONE", &enum_case_ONE_value);

	zval enum_case_SOURCE_COLOR_value;
	ZVAL_LONG(&enum_case_SOURCE_COLOR_value, 2);
	zend_enum_add_case_cstr(class_entry, "SOURCE_COLOR", &enum_case_SOURCE_COLOR_value);

	zval enum_case_ONE_MINUS_SOURCE_COLOR_value;
	ZVAL_LONG(&enum_case_ONE_MINUS_SOURCE_COLOR_value, 3);
	zend_enum_add_case_cstr(class_entry, "ONE_MINUS_SOURCE_COLOR", &enum_case_ONE_MINUS_SOURCE_COLOR_value);

	zval enum_case_SOURCE_ALPHA_value;
	ZVAL_LONG(&enum_case_SOURCE_ALPHA_value, 4);
	zend_enum_add_case_cstr(class_entry, "SOURCE_ALPHA", &enum_case_SOURCE_ALPHA_value);

	zval enum_case_ONE_MINUS_SOURCE_ALPHA_value;
	ZVAL_LONG(&enum_case_ONE_MINUS_SOURCE_ALPHA_value, 5);
	zend_enum_add_case_cstr(class_entry, "ONE_MINUS_SOURCE_ALPHA", &enum_case_ONE_MINUS_SOURCE_ALPHA_value);

	zval enum_case_DESTINATION_COLOR_value;
	ZVAL_LONG(&enum_case_DESTINATION_COLOR_value, 6);
	zend_enum_add_case_cstr(class_entry, "DESTINATION_COLOR", &enum_case_DESTINATION_COLOR_value);

	zval enum_case_ONE_MINUS_DESTINATION_COLOR_value;
	ZVAL_LONG(&enum_case_ONE_MINUS_DESTINATION_COLOR_value, 7);
	zend_enum_add_case_cstr(class_entry, "ONE_MINUS_DESTINATION_COLOR", &enum_case_ONE_MINUS_DESTINATION_COLOR_value);

	zval enum_case_DESTINATION_ALPHA_value;
	ZVAL_LONG(&enum_case_DESTINATION_ALPHA_value, 8);
	zend_enum_add_case_cstr(class_entry, "DESTINATION_ALPHA", &enum_case_DESTINATION_ALPHA_value);

	zval enum_case_ONE_MINUS_DESTINATION_ALPHA_value;
	ZVAL_LONG(&enum_case_ONE_MINUS_DESTINATION_ALPHA_value, 9);
	zend_enum_add_case_cstr(class_entry, "ONE_MINUS_DESTINATION_ALPHA", &enum_case_ONE_MINUS_DESTINATION_ALPHA_value);

	zval enum_case_SOURCE_ALPHA_SATURATED_value;
	ZVAL_LONG(&enum_case_SOURCE_ALPHA_SATURATED_value, 10);
	zend_enum_add_case_cstr(class_entry, "SOURCE_ALPHA_SATURATED", &enum_case_SOURCE_ALPHA_SATURATED_value);

	zval enum_case_BLEND_COLOR_value;
	ZVAL_LONG(&enum_case_BLEND_COLOR_value, 11);
	zend_enum_add_case_cstr(class_entry, "BLEND_COLOR", &enum_case_BLEND_COLOR_value);

	zval enum_case_ONE_MINUS_BLEND_COLOR_value;
	ZVAL_LONG(&enum_case_ONE_MINUS_BLEND_COLOR_value, 12);
	zend_enum_add_case_cstr(class_entry, "ONE_MINUS_BLEND_COLOR", &enum_case_ONE_MINUS_BLEND_COLOR_value);

	zval enum_case_BLEND_ALPHA_value;
	ZVAL_LONG(&enum_case_BLEND_ALPHA_value, 13);
	zend_enum_add_case_cstr(class_entry, "BLEND_ALPHA", &enum_case_BLEND_ALPHA_value);

	zval enum_case_ONE_MINUS_BLEND_ALPHA_value;
	ZVAL_LONG(&enum_case_ONE_MINUS_BLEND_ALPHA_value, 14);
	zend_enum_add_case_cstr(class_entry, "ONE_MINUS_BLEND_ALPHA", &enum_case_ONE_MINUS_BLEND_ALPHA_value);

	zval enum_case_SOURCE1_COLOR_value;
	ZVAL_LONG(&enum_case_SOURCE1_COLOR_value, 15);
	zend_enum_add_case_cstr(class_entry, "SOURCE1_COLOR", &enum_case_SOURCE1_COLOR_value);

	zval enum_case_ONE_MINUS_SOURCE1_COLOR_value;
	ZVAL_LONG(&enum_case_ONE_MINUS_SOURCE1_COLOR_value, 16);
	zend_enum_add_case_cstr(class_entry, "ONE_MINUS_SOURCE1_COLOR", &enum_case_ONE_MINUS_SOURCE1_COLOR_value);

	zval enum_case_SOURCE1_ALPHA_value;
	ZVAL_LONG(&enum_case_SOURCE1_ALPHA_value, 17);
	zend_enum_add_case_cstr(class_entry, "SOURCE1_ALPHA", &enum_case_SOURCE1_ALPHA_value);

	zval enum_case_ONE_MINUS_SOURCE1_ALPHA_value;
	ZVAL_LONG(&enum_case_ONE_MINUS_SOURCE1_ALPHA_value, 18);
	zend_enum_add_case_cstr(class_entry, "ONE_MINUS_SOURCE1_ALPHA", &enum_case_ONE_MINUS_SOURCE1_ALPHA_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLBlendOperation(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLBlendOperation", IS_LONG, NULL);

	zval enum_case_ADD_value;
	ZVAL_LONG(&enum_case_ADD_value, 0);
	zend_enum_add_case_cstr(class_entry, "ADD", &enum_case_ADD_value);

	zval enum_case_SUBTRACT_value;
	ZVAL_LONG(&enum_case_SUBTRACT_value, 1);
	zend_enum_add_case_cstr(class_entry, "SUBTRACT", &enum_case_SUBTRACT_value);

	zval enum_case_REVERSE_SUBTRACT_value;
	ZVAL_LONG(&enum_case_REVERSE_SUBTRACT_value, 2);
	zend_enum_add_case_cstr(class_entry, "REVERSE_SUBTRACT", &enum_case_REVERSE_SUBTRACT_value);

	zval enum_case_MIN_value;
	ZVAL_LONG(&enum_case_MIN_value, 3);
	zend_enum_add_case_cstr(class_entry, "MIN", &enum_case_MIN_value);

	zval enum_case_MAX_value;
	ZVAL_LONG(&enum_case_MAX_value, 4);
	zend_enum_add_case_cstr(class_entry, "MAX", &enum_case_MAX_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLColorWriteMask(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLColorWriteMask", IS_LONG, NULL);

	zval enum_case_NONE_value;
	ZVAL_LONG(&enum_case_NONE_value, 0);
	zend_enum_add_case_cstr(class_entry, "NONE", &enum_case_NONE_value);

	zval enum_case_RED_value;
	ZVAL_LONG(&enum_case_RED_value, 8);
	zend_enum_add_case_cstr(class_entry, "RED", &enum_case_RED_value);

	zval enum_case_GREEN_value;
	ZVAL_LONG(&enum_case_GREEN_value, 4);
	zend_enum_add_case_cstr(class_entry, "GREEN", &enum_case_GREEN_value);

	zval enum_case_BLUE_value;
	ZVAL_LONG(&enum_case_BLUE_value, 2);
	zend_enum_add_case_cstr(class_entry, "BLUE", &enum_case_BLUE_value);

	zval enum_case_ALPHA_value;
	ZVAL_LONG(&enum_case_ALPHA_value, 1);
	zend_enum_add_case_cstr(class_entry, "ALPHA", &enum_case_ALPHA_value);

	zval enum_case_ALL_value;
	ZVAL_LONG(&enum_case_ALL_value, 15);
	zend_enum_add_case_cstr(class_entry, "ALL", &enum_case_ALL_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLSamplerMinMagFilter(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLSamplerMinMagFilter", IS_LONG, NULL);

	zval enum_case_NEAREST_value;
	ZVAL_LONG(&enum_case_NEAREST_value, 0);
	zend_enum_add_case_cstr(class_entry, "NEAREST", &enum_case_NEAREST_value);

	zval enum_case_LINEAR_value;
	ZVAL_LONG(&enum_case_LINEAR_value, 1);
	zend_enum_add_case_cstr(class_entry, "LINEAR", &enum_case_LINEAR_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLSamplerAddressMode(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLSamplerAddressMode", IS_LONG, NULL);

	zval enum_case_CLAMP_TO_EDGE_value;
	ZVAL_LONG(&enum_case_CLAMP_TO_EDGE_value, 0);
	zend_enum_add_case_cstr(class_entry, "CLAMP_TO_EDGE", &enum_case_CLAMP_TO_EDGE_value);

	zval enum_case_MIRROR_CLAMP_TO_EDGE_value;
	ZVAL_LONG(&enum_case_MIRROR_CLAMP_TO_EDGE_value, 1);
	zend_enum_add_case_cstr(class_entry, "MIRROR_CLAMP_TO_EDGE", &enum_case_MIRROR_CLAMP_TO_EDGE_value);

	zval enum_case_REPEAT_value;
	ZVAL_LONG(&enum_case_REPEAT_value, 2);
	zend_enum_add_case_cstr(class_entry, "REPEAT", &enum_case_REPEAT_value);

	zval enum_case_MIRROR_REPEAT_value;
	ZVAL_LONG(&enum_case_MIRROR_REPEAT_value, 3);
	zend_enum_add_case_cstr(class_entry, "MIRROR_REPEAT", &enum_case_MIRROR_REPEAT_value);

	zval enum_case_CLAMP_TO_ZERO_value;
	ZVAL_LONG(&enum_case_CLAMP_TO_ZERO_value, 4);
	zend_enum_add_case_cstr(class_entry, "CLAMP_TO_ZERO", &enum_case_CLAMP_TO_ZERO_value);

	zval enum_case_CLAMP_TO_BORDER_COLOR_value;
	ZVAL_LONG(&enum_case_CLAMP_TO_BORDER_COLOR_value, 5);
	zend_enum_add_case_cstr(class_entry, "CLAMP_TO_BORDER_COLOR", &enum_case_CLAMP_TO_BORDER_COLOR_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLCompareFunction(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLCompareFunction", IS_LONG, NULL);

	zval enum_case_NEVER_value;
	ZVAL_LONG(&enum_case_NEVER_value, 0);
	zend_enum_add_case_cstr(class_entry, "NEVER", &enum_case_NEVER_value);

	zval enum_case_LESS_value;
	ZVAL_LONG(&enum_case_LESS_value, 1);
	zend_enum_add_case_cstr(class_entry, "LESS", &enum_case_LESS_value);

	zval enum_case_EQUAL_value;
	ZVAL_LONG(&enum_case_EQUAL_value, 2);
	zend_enum_add_case_cstr(class_entry, "EQUAL", &enum_case_EQUAL_value);

	zval enum_case_LESS_EQUAL_value;
	ZVAL_LONG(&enum_case_LESS_EQUAL_value, 3);
	zend_enum_add_case_cstr(class_entry, "LESS_EQUAL", &enum_case_LESS_EQUAL_value);

	zval enum_case_GREATER_value;
	ZVAL_LONG(&enum_case_GREATER_value, 4);
	zend_enum_add_case_cstr(class_entry, "GREATER", &enum_case_GREATER_value);

	zval enum_case_NOT_EQUAL_value;
	ZVAL_LONG(&enum_case_NOT_EQUAL_value, 5);
	zend_enum_add_case_cstr(class_entry, "NOT_EQUAL", &enum_case_NOT_EQUAL_value);

	zval enum_case_GREATER_EQUAL_value;
	ZVAL_LONG(&enum_case_GREATER_EQUAL_value, 6);
	zend_enum_add_case_cstr(class_entry, "GREATER_EQUAL", &enum_case_GREATER_EQUAL_value);

	zval enum_case_ALWAYS_value;
	ZVAL_LONG(&enum_case_ALWAYS_value, 7);
	zend_enum_add_case_cstr(class_entry, "ALWAYS", &enum_case_ALWAYS_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLStencilOperation(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLStencilOperation", IS_LONG, NULL);

	zval enum_case_KEEP_value;
	ZVAL_LONG(&enum_case_KEEP_value, 0);
	zend_enum_add_case_cstr(class_entry, "KEEP", &enum_case_KEEP_value);

	zval enum_case_ZERO_value;
	ZVAL_LONG(&enum_case_ZERO_value, 1);
	zend_enum_add_case_cstr(class_entry, "ZERO", &enum_case_ZERO_value);

	zval enum_case_REPLACE_value;
	ZVAL_LONG(&enum_case_REPLACE_value, 2);
	zend_enum_add_case_cstr(class_entry, "REPLACE", &enum_case_REPLACE_value);

	zval enum_case_INCREMENT_CLAMP_value;
	ZVAL_LONG(&enum_case_INCREMENT_CLAMP_value, 3);
	zend_enum_add_case_cstr(class_entry, "INCREMENT_CLAMP", &enum_case_INCREMENT_CLAMP_value);

	zval enum_case_DECREMENT_CLAMP_value;
	ZVAL_LONG(&enum_case_DECREMENT_CLAMP_value, 4);
	zend_enum_add_case_cstr(class_entry, "DECREMENT_CLAMP", &enum_case_DECREMENT_CLAMP_value);

	zval enum_case_INVERT_value;
	ZVAL_LONG(&enum_case_INVERT_value, 5);
	zend_enum_add_case_cstr(class_entry, "INVERT", &enum_case_INVERT_value);

	zval enum_case_INCREMENT_WRAP_value;
	ZVAL_LONG(&enum_case_INCREMENT_WRAP_value, 6);
	zend_enum_add_case_cstr(class_entry, "INCREMENT_WRAP", &enum_case_INCREMENT_WRAP_value);

	zval enum_case_DECREMENT_WRAP_value;
	ZVAL_LONG(&enum_case_DECREMENT_WRAP_value, 7);
	zend_enum_add_case_cstr(class_entry, "DECREMENT_WRAP", &enum_case_DECREMENT_WRAP_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLCullMode(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLCullMode", IS_LONG, NULL);

	zval enum_case_NONE_value;
	ZVAL_LONG(&enum_case_NONE_value, 0);
	zend_enum_add_case_cstr(class_entry, "NONE", &enum_case_NONE_value);

	zval enum_case_FRONT_value;
	ZVAL_LONG(&enum_case_FRONT_value, 1);
	zend_enum_add_case_cstr(class_entry, "FRONT", &enum_case_FRONT_value);

	zval enum_case_BACK_value;
	ZVAL_LONG(&enum_case_BACK_value, 2);
	zend_enum_add_case_cstr(class_entry, "BACK", &enum_case_BACK_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLWinding(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLWinding", IS_LONG, NULL);

	zval enum_case_CLOCKWISE_value;
	ZVAL_LONG(&enum_case_CLOCKWISE_value, 0);
	zend_enum_add_case_cstr(class_entry, "CLOCKWISE", &enum_case_CLOCKWISE_value);

	zval enum_case_COUNTER_CLOCKWISE_value;
	ZVAL_LONG(&enum_case_COUNTER_CLOCKWISE_value, 1);
	zend_enum_add_case_cstr(class_entry, "COUNTER_CLOCKWISE", &enum_case_COUNTER_CLOCKWISE_value);

	return class_entry;
}

static zend_class_entry *register_class_MTLCommandBufferStatus(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("MTLCommandBufferStatus", IS_LONG, NULL);

	zval enum_case_NOT_ENQUEUED_value;
	ZVAL_LONG(&enum_case_NOT_ENQUEUED_value, 0);
	zend_enum_add_case_cstr(class_entry, "NOT_ENQUEUED", &enum_case_NOT_ENQUEUED_value);

	zval enum_case_ENQUEUED_value;
	ZVAL_LONG(&enum_case_ENQUEUED_value, 1);
	zend_enum_add_case_cstr(class_entry, "ENQUEUED", &enum_case_ENQUEUED_value);

	zval enum_case_COMMITTED_value;
	ZVAL_LONG(&enum_case_COMMITTED_value, 2);
	zend_enum_add_case_cstr(class_entry, "COMMITTED", &enum_case_COMMITTED_value);

	zval enum_case_SCHEDULED_value;
	ZVAL_LONG(&enum_case_SCHEDULED_value, 3);
	zend_enum_add_case_cstr(class_entry, "SCHEDULED", &enum_case_SCHEDULED_value);

	zval enum_case_COMPLETED_value;
	ZVAL_LONG(&enum_case_COMPLETED_value, 4);
	zend_enum_add_case_cstr(class_entry, "COMPLETED", &enum_case_COMPLETED_value);

	zval enum_case_ERROR_value;
	ZVAL_LONG(&enum_case_ERROR_value, 5);
	zend_enum_add_case_cstr(class_entry, "ERROR", &enum_case_ERROR_value);

	return class_entry;
}
