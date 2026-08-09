<?php

namespace Metal\MTL;

/**
 * NSWindow + CAMetalLayer surface.
 * Handles are opaque ints owned by the caller until destroy().
 */
class Window
{


    /**
     * @return int Opaque window handle, or 0 on failure
     * @param string $title
     * @param int $width
     * @param int $height
     */
    public static function create(string $title, int $width, int $height): int
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function destroy(int $window): void
    {
    }

    /**
     * @param int $window
     * @param string $title
     * @return void
     */
    public static function setTitle(int $window, string $title): void
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function show(int $window): void
    {
    }

    /**
     * @param int $window
     * @return void
     */
    public static function hide(int $window): void
    {
    }

    /**
     * @param int $window
     * @return bool
     */
    public static function shouldClose(int $window): bool
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function getWidth(int $window): int
    {
    }

    /**
     * @param int $window
     * @return int
     */
    public static function getHeight(int $window): int
    {
    }

    /**
     * @param int $window
     * @param int $device
     * @return bool
     */
    public static function attachDevice(int $window, int $device): bool
    {
    }

    /**
     * @return int Opaque CAMetalLayer pointer, or 0
     * @param int $window
     */
    public static function getLayer(int $window): int
    {
    }

    /**
     * Clear the drawable to RGBA (0..255 components) and present.
     *
     * @param int $window
     * @param int $r
     * @param int $g
     * @param int $b
     * @param int $a
     * @return bool
     */
    public static function clear(int $window, int $r, int $g, int $b, int $a = 255): bool
    {
    }
}
