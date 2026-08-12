<?php

namespace Metal\MTL;

/**
 * Keyboard / mouse / gamepad queries over AppKit + GameController (0.7.2+).
 * Call App::poll() each frame so scroll deltas reset and events drain.
 */
class Input
{


    /**
     * @param int $keycode
     * @return bool true if macOS virtual key code is currently down
     */
    public static function keyDown(int $keycode): bool
    {
    }

    /**
     * Mouse button: 0=left, 1=right, 2=middle.
     *
     * @param int $button
     * @return bool
     */
    public static function mouseButtonDown(int $button): bool
    {
    }

    /**
     * Mouse position as [x, y].
     * window=0 → screen coords; otherwise content-view local for that window handle.
     * Y grows upward (AppKit). Empty array on failure.
     *
     * @param int $window
     * @return array
     */
    public static function mousePosition(int $window = 0): array
    {
    }

    /**
     * Scroll deltas since the last App::poll() begin as [dx, dy].
     *
     * @return array
     */
    public static function mouseScrollDelta(): array
    {
    }

    /**
     * @return int
     */
    public static function gamepadCount(): int
    {
    }

    /**
     * @param int $index
     * @return string Product / vendor name, or "" if missing
     */
    public static function gamepadName(int $index): string
    {
    }

    /**
     * Gamepad digital button (see metal-input.h layout).
     *
     * @param int $index
     * @param int $button
     * @return bool
     */
    public static function gamepadButtonDown(int $index, int $button): bool
    {
    }

    /**
     * Gamepad axis (sticks -1..1, triggers 0..1).
     *
     * @param int $index
     * @param int $axis
     * @return float
     */
    public static function gamepadAxis(int $index, int $axis): float
    {
    }

    /**
     * Snapshot: ["name" => string, "buttons" => int[15], "axes" => float[6]] or [] if missing.
     *
     * @param int $index
     * @return array
     */
    public static function gamepadState(int $index): array
    {
    }
}
