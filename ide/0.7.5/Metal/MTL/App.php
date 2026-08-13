<?php

namespace Metal\MTL;

/**
 * NSApplication lifecycle — Darwin only.
 */
class App
{


    /**
     * @return bool
     */
    public static function init(): bool
    {
    }

    /**
     * Drain pending AppKit events once.
     *
     * @return bool false when quit was requested
     */
    public static function poll(): bool
    {
    }

    /**
     * @return void
     */
    public static function run(): void
    {
    }

    /**
     * @return void
     */
    public static function terminate(): void
    {
    }

    /**
     * @return bool
     */
    public static function shouldQuit(): bool
    {
    }

    /**
     * @return void
     */
    public static function resetQuit(): void
    {
    }
}
