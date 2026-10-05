<?php

declare(strict_types=1);

it('configures a layer for the device', function (): void {
    $layer = CAMetalLayer::layer();
    $layer->setDevice(device());
    $layer->setPixelFormat(MTLPixelFormat::BGRA8_UNORM);
    $layer->setFramebufferOnly(false);
    $layer->setDrawableSize(new CGSize(320.0, 240.0));
    $layer->setDisplaySyncEnabled(false);
    $layer->setMaximumDrawableCount(2);
    $layer->setContentsScale(2.0);

    expect($layer->device())->toBe(device())
        ->and($layer->pixelFormat())->toBe(MTLPixelFormat::BGRA8_UNORM)
        ->and($layer->framebufferOnly())->toBeFalse()
        ->and([$layer->drawableSize()->width, $layer->drawableSize()->height])->toBe([320.0, 240.0])
        ->and($layer->displaySyncEnabled())->toBeFalse()
        ->and($layer->maximumDrawableCount())->toBe(2)
        ->and($layer->contentsScale())->toBe(2.0)
        ->and(CAMetalLayer::fromPointer($layer->pointer()))->toBe($layer);
});

it('declares the drawable side for slice 8', function (): void {
    expect(method_exists(CAMetalLayer::class, 'nextDrawable'))->toBeTrue()
        ->and(method_exists(CAMetalDrawable::class, 'texture'))->toBeTrue()
        ->and(method_exists(MTLCommandBuffer::class, 'presentDrawable'))->toBeTrue();
});
