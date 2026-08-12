<?php

namespace Metal\MTL;

/**
 * Offscreen MTLTexture (RGBA8Unorm) — headless render targets for engines/UIs.
 * Handles are opaque ints owned by the caller until release().
 */
class Texture
{
    /**
     * @return int Opaque texture handle, or 0 on failure
     */
    public static function create(int $device, int $width, int $height): int
    {
    }

    public static function release(int $texture): void
    {
    }

    public static function getWidth(int $texture): int
    {
    }

    public static function getHeight(int $texture): int
    {
    }

    /**
     * GPU clear. RGBA components are integers 0..255.
     */
    public static function clear(int $texture, int $queue, int $r, int $g, int $b, int $a = 255): bool
    {
    }

    /**
     * CPU write one RGBA8 pixel (0..255).
     */
    public static function writePixel(int $texture, int $x, int $y, int $r, int $g, int $b, int $a = 255): bool
    {
    }

    /**
     * CPU fill an axis-aligned rect with one solid RGBA8 color (0..255).
     * One replaceRegion for the whole rect — use this instead of writePixel loops.
     */
    public static function fillRect(int $texture, int $x, int $y, int $width, int $height, int $r, int $g, int $b, int $a = 255): bool
    {
    }

    /**
     * CPU read one RGBA8 pixel as [r, g, b, a] ints 0..255, or empty array on failure.
     * @return array<int, int>
     */
    public static function readPixel(int $texture, int $queue, int $x, int $y): array
    {
    }

    /**
     * Full RGBA8888 tightly packed bytes (row-major), or "" on failure.
     */
    public static function readPixels(int $texture, int $queue): string
    {
    }
}
