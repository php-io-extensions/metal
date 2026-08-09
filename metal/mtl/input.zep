namespace Metal\MTL;

%{
#include "metal-input.h"
#include <stdint.h>
}%

/**
 * Keyboard / mouse / gamepad queries over AppKit + GameController (0.7.2+).
 * Call App::poll() each frame so scroll deltas reset and events drain.
 */
class Input
{
    /**
     * @return bool true if macOS virtual key code is currently down
     */
    public static function keyDown(int keycode) -> bool
    {
        bool result;
        %{
            result = mtl_input_key_down((int) keycode) == 1;
        }%
        return result;
    }

    /**
     * Mouse button: 0=left, 1=right, 2=middle.
     */
    public static function mouseButtonDown(int button) -> bool
    {
        bool result;
        %{
            result = mtl_input_mouse_button_down((int) button) == 1;
        }%
        return result;
    }

    /**
     * Mouse position as [x, y].
     * window=0 → screen coords; otherwise content-view local for that window handle.
     * Y grows upward (AppKit). Empty array on failure.
     */
    public static function mousePosition(int window = 0) -> array
    {
        array out = [];
        %{
            double x = 0.0, y = 0.0;
            if (mtl_input_mouse_position((uintptr_t) window, &x, &y)) {
                array_init(&out);
                add_next_index_double(&out, x);
                add_next_index_double(&out, y);
            } else {
                array_init(&out);
            }
        }%
        return out;
    }

    /**
     * Scroll deltas since the last App::poll() begin as [dx, dy].
     */
    public static function mouseScrollDelta() -> array
    {
        array out = [];
        %{
            double dx = 0.0, dy = 0.0;
            mtl_input_mouse_scroll_delta(&dx, &dy);
            array_init(&out);
            add_next_index_double(&out, dx);
            add_next_index_double(&out, dy);
        }%
        return out;
    }

    public static function gamepadCount() -> int
    {
        int n;
        %{
            n = mtl_input_gamepad_count();
        }%
        return n;
    }

    /**
     * @return string Product / vendor name, or "" if missing
     */
    public static function gamepadName(int index) -> string
    {
        string name;
        %{
            char buf[256];
            buf[0] = '\0';
            if (mtl_input_gamepad_name((int) index, buf, (int) sizeof(buf))) {
                ZVAL_STRING(&name, buf);
            } else {
                ZVAL_STRING(&name, "");
            }
        }%
        return name;
    }

    /**
     * Gamepad digital button (see metal-input.h layout).
     */
    public static function gamepadButtonDown(int index, int button) -> bool
    {
        bool result;
        %{
            result = mtl_input_gamepad_button_down((int) index, (int) button) == 1;
        }%
        return result;
    }

    /**
     * Gamepad axis (sticks -1..1, triggers 0..1).
     */
    public static function gamepadAxis(int index, int axis) -> double
    {
        double value;
        %{
            value = (double) mtl_input_gamepad_axis((int) index, (int) axis);
        }%
        return value;
    }

    /**
     * Snapshot: ["name" => string, "buttons" => int[15], "axes" => float[6]] or [] if missing.
     */
    public static function gamepadState(int index) -> array
    {
        array out = [];
        %{
            char buf[256];
            buf[0] = '\0';
            if (!mtl_input_gamepad_name((int) index, buf, (int) sizeof(buf))) {
                array_init(&out);
            } else {
                zval buttons, axes;
                int i;
                array_init(&out);
                add_assoc_string(&out, "name", buf);
                array_init(&buttons);
                for (i = 0; i < 15; i++) {
                    add_next_index_long(&buttons, mtl_input_gamepad_button_down((int) index, i) ? 1 : 0);
                }
                add_assoc_zval(&out, "buttons", &buttons);
                array_init(&axes);
                for (i = 0; i < 6; i++) {
                    add_next_index_double(&axes, (double) mtl_input_gamepad_axis((int) index, i));
                }
                add_assoc_zval(&out, "axes", &axes);
            }
        }%
        return out;
    }
}
