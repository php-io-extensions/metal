
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"

#include "metal-menu.h"



/**
 * macOS menu bar (NSMenu).
 */
ZEPHIR_INIT_CLASS(Metal_MTL_Menu)
{
	ZEPHIR_REGISTER_CLASS(Metal\\MTL, Menu, metal, mtl_menu, metal_mtl_menu_method_entry, 0);

	return SUCCESS;
}

/**
 * Install App | File | Edit | Window | Help, including Quit (Cmd+Q).
 */
PHP_METHOD(Metal_MTL_Menu, installDefault)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *appName_param = NULL;
	zval appName;

	ZVAL_UNDEF(&appName);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(appName)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &appName_param);
	zephir_get_strval(&appName, appName_param);
	
            result = mtl_menu_install_default(Z_STRVAL(appName)) == 1;
        
	RETURN_MM_BOOL(result);
}

/**
 * Add an item under a top-level menu (created if missing).
 * actionId "quit" also terminates the app.
 */
PHP_METHOD(Metal_MTL_Menu, addItem)
{
	zend_bool result = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *menuTitle_param = NULL, *itemTitle_param = NULL, *keyEquivalent_param = NULL, *actionId_param = NULL;
	zval menuTitle, itemTitle, keyEquivalent, actionId;

	ZVAL_UNDEF(&menuTitle);
	ZVAL_UNDEF(&itemTitle);
	ZVAL_UNDEF(&keyEquivalent);
	ZVAL_UNDEF(&actionId);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_STR(menuTitle)
		Z_PARAM_STR(itemTitle)
		Z_PARAM_STR(keyEquivalent)
		Z_PARAM_STR(actionId)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 4, 0, &menuTitle_param, &itemTitle_param, &keyEquivalent_param, &actionId_param);
	zephir_get_strval(&menuTitle, menuTitle_param);
	zephir_get_strval(&itemTitle, itemTitle_param);
	zephir_get_strval(&keyEquivalent, keyEquivalent_param);
	zephir_get_strval(&actionId, actionId_param);
	
            result = mtl_menu_add_item(
                Z_STRVAL(menuTitle),
                Z_STRVAL(itemTitle),
                Z_STRVAL(keyEquivalent),
                Z_STRVAL(actionId)
            ) == 1;
        
	RETURN_MM_BOOL(result);
}

/**
 * @return string Action id of a selected custom item, or "" if none
 */
PHP_METHOD(Metal_MTL_Menu, pollAction)
{
	zval action;

	ZVAL_UNDEF(&action);
	
            char buf[256];
            buf[0] = '\0';
            if (mtl_menu_poll_action(buf, (int) sizeof(buf))) {
                ZVAL_STRING(&action, buf);
            } else {
                ZVAL_STRING(&action, "");
            }
        
	RETURN_CTORW(&action);
}

