namespace Metal\MTL;

%{
#include "metal-menu.h"
}%

/**
 * macOS menu bar (NSMenu).
 */
class Menu
{
    /**
     * Install App | File | Edit | Window | Help, including Quit (Cmd+Q).
     */
    public static function installDefault(string appName) -> bool
    {
        bool result;
        %{
            result = mtl_menu_install_default(Z_STRVAL(appName)) == 1;
        }%
        return result;
    }

    /**
     * Add an item under a top-level menu (created if missing).
     * actionId "quit" also terminates the app.
     */
    public static function addItem(string menuTitle, string itemTitle, string keyEquivalent, string actionId) -> bool
    {
        bool result;
        %{
            result = mtl_menu_add_item(
                Z_STRVAL(menuTitle),
                Z_STRVAL(itemTitle),
                Z_STRVAL(keyEquivalent),
                Z_STRVAL(actionId)
            ) == 1;
        }%
        return result;
    }

    /**
     * @return string Action id of a selected custom item, or "" if none
     */
    public static function pollAction() -> string
    {
        string action;
        %{
            char buf[256];
            buf[0] = '\0';
            if (mtl_menu_poll_action(buf, (int) sizeof(buf))) {
                ZVAL_STRING(&action, buf);
            } else {
                ZVAL_STRING(&action, "");
            }
        }%
        return action;
    }
}
