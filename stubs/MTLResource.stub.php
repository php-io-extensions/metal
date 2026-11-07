<?php

/** @generate-class-entries */

/**
 * @not-serializable
 */
final class MTLTextureDescriptor
{
    private function __construct() {}

    public static function texture2DDescriptorWithPixelFormatWidthHeightMipmapped(MTLPixelFormat $pixelFormat, int $width, int $height, bool $mipmapped): MTLTextureDescriptor {}

    public static function new(): MTLTextureDescriptor {}

    public function textureType(): MTLTextureType {}

    public function setTextureType(MTLTextureType $textureType): void {}

    public function pixelFormat(): MTLPixelFormat {}

    public function setPixelFormat(MTLPixelFormat $pixelFormat): void {}

    public function width(): int {}

    public function setWidth(int $width): void {}

    public function height(): int {}

    public function setHeight(int $height): void {}

    public function sampleCount(): int {}

    public function setSampleCount(int $sampleCount): void {}

    public function usage(): MTLTextureUsage|int {}

    public function setUsage(MTLTextureUsage|int $usage): void {}

    public function storageMode(): MTLStorageMode {}

    public function setStorageMode(MTLStorageMode $storageMode): void {}

    /** The object's address, for handing it to another extension. */
    public function pointer(): int {}

    /** The object at $pointer (another extension's pointer()), trusted to be this class's native object; 0 is null. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * @not-serializable
 */
final class MTLTexture
{
    private function __construct() {}

    public function width(): int {}

    public function height(): int {}

    public function pixelFormat(): MTLPixelFormat {}

    public function textureType(): MTLTextureType {}

    public function sampleCount(): int {}

    /**
     * $bytes is a string that must hold bytesPerRow × height bytes, or an address
     * trusted to hold that many. 0 is refused.
     */
    public function replaceRegionMipmapLevelWithBytesBytesPerRow(MTLRegion $region, int $mipmapLevel, string|int $bytes, int $bytesPerRow): void {}

    /** $pixelBytes is an address trusted to have room for bytesPerRow × the region's height. 0 is refused. */
    public function getBytesBytesPerRowFromRegionMipmapLevel(int $pixelBytes, int $bytesPerRow, MTLRegion $region, int $mipmapLevel): void {}

    /** The object's address, for handing it to another extension. */
    public function pointer(): int {}

    /** The object at $pointer (another extension's pointer()), trusted to be this class's native object; 0 is null. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * @not-serializable
 */
final class MTLBuffer
{
    private function __construct() {}

    public function length(): int {}

    /** The address contents returns, or 0 when that pointer is nil. */
    public function contents(): int {}

    /** The object's address, for handing it to another extension. */
    public function pointer(): int {}

    /** The object at $pointer (another extension's pointer()), trusted to be this class's native object; 0 is null. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * @not-serializable
 */
final class MTLSamplerDescriptor
{
    private function __construct() {}

    public static function new(): MTLSamplerDescriptor {}

    public function minFilter(): MTLSamplerMinMagFilter {}

    public function setMinFilter(MTLSamplerMinMagFilter $minFilter): void {}

    public function magFilter(): MTLSamplerMinMagFilter {}

    public function setMagFilter(MTLSamplerMinMagFilter $magFilter): void {}

    public function sAddressMode(): MTLSamplerAddressMode {}

    public function setSAddressMode(MTLSamplerAddressMode $sAddressMode): void {}

    public function tAddressMode(): MTLSamplerAddressMode {}

    public function setTAddressMode(MTLSamplerAddressMode $tAddressMode): void {}

    /** The object's address, for handing it to another extension. */
    public function pointer(): int {}

    /** The object at $pointer (another extension's pointer()), trusted to be this class's native object; 0 is null. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * @not-serializable
 */
final class MTLSamplerState
{
    private function __construct() {}

    /** The object's address, for handing it to another extension. */
    public function pointer(): int {}

    /** The object at $pointer (another extension's pointer()), trusted to be this class's native object; 0 is null. */
    public static function fromPointer(int $pointer): ?static {}
}
