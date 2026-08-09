namespace Metal\MTL;

%{
#include "metal-app.h"
}%

/**
 * NSApplication lifecycle — Darwin only.
 */
class App
{
    public static function init() -> bool
    {
        bool result;
        %{
            result = mtl_app_init() == 1;
        }%
        return result;
    }

    /**
     * Drain pending AppKit events once.
     * @return bool false when quit was requested
     */
    public static function poll() -> bool
    {
        bool result;
        %{
            result = mtl_app_poll() == 1;
        }%
        return result;
    }

    public static function run() -> void
    {
        %{
            mtl_app_run();
        }%
    }

    public static function terminate() -> void
    {
        %{
            mtl_app_terminate();
        }%
    }

    public static function shouldQuit() -> bool
    {
        bool result;
        %{
            result = mtl_app_should_quit() == 1;
        }%
        return result;
    }

    public static function resetQuit() -> void
    {
        %{
            mtl_app_reset_quit();
        }%
    }
}
