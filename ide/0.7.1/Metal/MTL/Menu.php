<?php

namespace Metal\MTL;

/**
 * macOS menu bar (NSMenu).
 */
class Menu
{


    /**
     * Install App | File | Edit | Window | Help, including Quit (Cmd+Q).
     *
     * @param string $appName
     * @return bool
     */
    public static function installDefault(string $appName): bool
    {
    }

    /**
     * Add an item under a top-level menu (created if missing).
     * actionId "quit" also terminates the app.
     *
     * @param string $menuTitle
     * @param string $itemTitle
     * @param string $keyEquivalent
     * @param string $actionId
     * @return bool
     */
    public static function addItem(string $menuTitle, string $itemTitle, string $keyEquivalent, string $actionId): bool
    {
    }

    /**
     * @return string Action id of a selected custom item, or "" if none
     */
    public static function pollAction(): string
    {
    }
}
