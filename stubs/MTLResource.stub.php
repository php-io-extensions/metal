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

    /** The MTLTextureDescriptor at $pointer. The address is trusted to hold an object; it must be an MTLTextureDescriptor. */
    public static function fromPointer(int $pointer): static {}
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

    /**
     * Null reads the region into a string of bytesPerRow × height bytes.
     * An address is trusted to have room for that many bytes, and the method returns null.
     * 0 is refused.
     */
    public function getBytesBytesPerRowFromRegionMipmapLevel(?int $pixelBytes, int $bytesPerRow, MTLRegion $region, int $mipmapLevel): ?string {}

    /** The object's address, for handing it to another extension. */
    public function pointer(): int {}

    /** The MTLTexture at $pointer. The address is trusted to hold an object; it must conform to MTLTexture. */
    public static function fromPointer(int $pointer): static {}
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

    /** The MTLBuffer at $pointer. The address is trusted to hold an object; it must conform to MTLBuffer. */
    public static function fromPointer(int $pointer): static {}
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

    /** The MTLSamplerDescriptor at $pointer. The address is trusted to hold an object; it must be an MTLSamplerDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLSamplerState
{
    private function __construct() {}

    /** The object's address, for handing it to another extension. */
    public function pointer(): int {}

    /** The MTLSamplerState at $pointer. The address is trusted to hold an object; it must conform to MTLSamplerState. */
    public static function fromPointer(int $pointer): static {}
}
