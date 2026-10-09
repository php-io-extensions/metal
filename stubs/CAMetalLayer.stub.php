<?php

/** @generate-class-entries */

final class CGSize
{
    public float $width = 0.0;

    public float $height = 0.0;

    public function __construct(float $width, float $height) {}
}

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

    public function drawableSize(): CGSize {}

    public function setDrawableSize(CGSize $drawableSize): void {}

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

    /** The CGColorSpaceRef's address, or null. */
    public function colorspace(): ?int {}

    /** $colorspace is a CGColorSpaceRef's address (ext-appkit's CGColorSpace::pointer()), trusted; null clears it. */
    public function setColorspace(?int $colorspace): void {}

    public function EDRMetadata(): ?CAEDRMetadata {}

    public function setEDRMetadata(?CAEDRMetadata $EDRMetadata): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be a CAMetalLayer. */
    public static function fromPointer(int $pointer): static {}
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

    /** The address is trusted to hold an object; it must conform to CAMetalDrawable. */
    public static function fromPointer(int $pointer): static {}
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

    /** The address is trusted to hold an object; it must be a CAEDRMetadata. */
    public static function fromPointer(int $pointer): static {}
}
