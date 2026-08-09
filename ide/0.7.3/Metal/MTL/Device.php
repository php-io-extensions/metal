<?php

namespace Metal\MTL;

/**
 * MTLDevice / MTLCommandQueue handles (opaque ints).
 */
class Device
{


    /**
     * @return int Opaque MTLDevice handle, or 0
     */
    public static function createSystemDefault(): int
    {
    }

    /**
     * @param int $device
     * @return void
     */
    public static function release(int $device): void
    {
    }

    /**
     * @return int Opaque MTLCommandQueue handle, or 0
     * @param int $device
     */
    public static function newCommandQueue(int $device): int
    {
    }

    /**
     * @param int $queue
     * @return void
     */
    public static function releaseCommandQueue(int $queue): void
    {
    }

    /**
     * @param int $device
     * @return string
     */
    public static function getName(int $device): string
    {
    }
}
