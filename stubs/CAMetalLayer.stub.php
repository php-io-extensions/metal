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

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must conform to CAMetalDrawable. */
    public static function fromPointer(int $pointer): static {}
}
