<?php

/** @generate-class-entries */

/**
 * @not-serializable
 */
final class CAMetalLayer
{
    private function __construct() {}

    public static function layer(): CAMetalLayer {}

    public function device(): ?MTLDevice {}

    public function setDevice(?MTLDevice $device): void {}

    public function pixelFormat(): MTLPixelFormat {}

    public function setPixelFormat(MTLPixelFormat $pixelFormat): void {}

    public function framebufferOnly(): bool {}

    public function setFramebufferOnly(bool $framebufferOnly): void {}

    /** A CGSize, as ext-appkit's NSSize. */
    public function drawableSize(): NSSize {}

    public function setDrawableSize(NSSize $drawableSize): void {}

    public function displaySyncEnabled(): bool {}

    public function setDisplaySyncEnabled(bool $displaySyncEnabled): void {}

    public function contentsScale(): float {}

    public function setContentsScale(float $contentsScale): void {}

    public function maximumDrawableCount(): int {}

    public function setMaximumDrawableCount(int $maximumDrawableCount): void {}

    public function nextDrawable(): ?CAMetalDrawable {}

    /** When false, nextDrawable answers null at once instead of waiting up to a second for a free drawable. */
    public function allowsNextDrawableTimeout(): bool {}

    public function setAllowsNextDrawableTimeout(bool $allowsNextDrawableTimeout): void {}

    public function presentsWithTransaction(): bool {}

    public function setPresentsWithTransaction(bool $presentsWithTransaction): void {}

    public function wantsExtendedDynamicRangeContent(): bool {}

    public function setWantsExtendedDynamicRangeContent(bool $wantsExtendedDynamicRangeContent): void {}

    /** ext-appkit's CGColorSpace, or null. */
    public function colorspace(): ?CGColorSpace {}

    public function setColorspace(?CGColorSpace $colorspace): void {}

    public function EDRMetadata(): ?CAEDRMetadata {}

    public function setEDRMetadata(?CAEDRMetadata $EDRMetadata): void {}

    public function pointer(): int {}

    /** The object at $pointer (another extension's pointer()), trusted to be this class's native object; 0 is null. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * @not-serializable
 */
final class CAMetalDrawable
{
    private function __construct() {}

    public function texture(): MTLTexture {}

    public function present(): void {}

    /** MTLDrawable's presentedTime: when the drawable reached the screen, in seconds on the host clock; 0 before it has. */
    public function presentedTime(): float {}

    public function drawableID(): int {}

    public function pointer(): int {}

    /** The object at $pointer (another extension's pointer()), trusted to be this class's native object; 0 is null. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * @not-serializable
 */
final class CAEDRMetadata
{
    private function __construct() {}

    /** Luminances in nits; $opticalOutputScale is the nits of content value 1.0. */
    public static function HDR10MetadataWithMinLuminanceMaxLuminanceOpticalOutputScale(float $minNits, float $maxNits, float $opticalOutputScale): CAEDRMetadata {}

    public static function HLGMetadata(): CAEDRMetadata {}

    public function pointer(): int {}

    /** The object at $pointer (another extension's pointer()), trusted to be this class's native object; 0 is null. */
    public static function fromPointer(int $pointer): ?static {}
}
