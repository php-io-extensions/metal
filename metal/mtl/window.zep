namespace Metal\MTL;

%{
#include "metal-window.h"
#include <stdint.h>
}%

/**
 * NSWindow + CAMetalLayer surface.
 * Handles are opaque ints owned by the caller until destroy().
 */
class Window
{
    /**
     * @return int Opaque window handle, or 0 on failure
     */
    public static function create(string title, int width, int height) -> int
    {
        int handle;
        %{
            handle = (zend_long) mtl_window_create(Z_STRVAL(title), (int) width, (int) height);
        }%
        return handle;
    }

    public static function destroy(int window) -> void
    {
        %{
            mtl_window_destroy((uintptr_t) window);
        }%
    }

    public static function setTitle(int window, string title) -> void
    {
        %{
            mtl_window_set_title((uintptr_t) window, Z_STRVAL(title));
        }%
    }

    public static function show(int window) -> void
    {
        %{
            mtl_window_show((uintptr_t) window);
        }%
    }

    public static function hide(int window) -> void
    {
        %{
            mtl_window_hide((uintptr_t) window);
        }%
    }

    public static function shouldClose(int window) -> bool
    {
        bool result;
        %{
            result = mtl_window_should_close((uintptr_t) window) == 1;
        }%
        return result;
    }

    public static function getWidth(int window) -> int
    {
        int value;
        %{
            value = (zend_long) mtl_window_get_width((uintptr_t) window);
        }%
        return value;
    }

    public static function getHeight(int window) -> int
    {
        int value;
        %{
            value = (zend_long) mtl_window_get_height((uintptr_t) window);
        }%
        return value;
    }

    public static function attachDevice(int window, int device) -> bool
    {
        bool result;
        %{
            result = mtl_window_attach_device((uintptr_t) window, (uintptr_t) device) == 1;
        }%
        return result;
    }

    /**
     * @return int Opaque CAMetalLayer pointer, or 0
     */
    public static function getLayer(int window) -> int
    {
        int handle;
        %{
            handle = (zend_long) mtl_window_get_layer((uintptr_t) window);
        }%
        return handle;
    }

    /**
     * Clear the drawable to RGBA (0..255 components) and present.
     */
    public static function clear(int window, int r, int g, int b, int a = 255) -> bool
    {
        bool result;
        %{
            result = mtl_window_clear(
                (uintptr_t) window,
                ((float) r) / 255.0f,
                ((float) g) / 255.0f,
                ((float) b) / 255.0f,
                ((float) a) / 255.0f
            ) == 1;
        }%
        return result;
    }

    /**
     * @return int Borrowed MTLDevice handle attached to the window, or 0
     */
    public static function getDevice(int window) -> int
    {
        int handle;
        %{
            handle = (zend_long) mtl_window_get_device((uintptr_t) window);
        }%
        return handle;
    }

    /**
     * Blit an offscreen RGBA8 texture to the window drawable and present.
     */
    public static function presentTexture(int window, int texture) -> bool
    {
        bool result;
        %{
            result = mtl_window_present_texture((uintptr_t) window, (uintptr_t) texture) == 1;
        }%
        return result;
    }
}
