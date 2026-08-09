#ifndef PHP_METAL_MENU_H
#define PHP_METAL_MENU_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Install a standard macOS menu bar: App | File | Edit | Window | Help.
 * app_name is used for the application menu title (e.g. "Metal").
 * Includes Quit (Cmd+Q). Idempotent — replaces the main menu.
 */
int mtl_menu_install_default(const char *app_name);

/**
 * Add a menu item under an existing top-level menu (creates the menu if missing).
 * key_equivalent may be "" for none (single lowercase char typical, e.g. "n").
 * action_id is a UTF-8 token returned later by mtl_menu_poll_action when chosen.
 * Returns 1 on success.
 */
int mtl_menu_add_item(
    const char *menu_title,
    const char *item_title,
    const char *key_equivalent,
    const char *action_id
);

/**
 * If a custom menu item was activated since the last poll, copy its action_id
 * into out_action (out_action_len bytes, NUL-terminated) and return 1.
 * Otherwise return 0.
 */
int mtl_menu_poll_action(char *out_action, int out_action_len);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_MENU_H */
