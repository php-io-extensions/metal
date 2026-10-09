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

it('sets the drawable timeout, transaction presents, EDR, colorspace and EDR metadata', function (): void {
    $layer = CAMetalLayer::layer();

    $layer->setAllowsNextDrawableTimeout(false);
    $layer->setPresentsWithTransaction(true);
    $layer->setWantsExtendedDynamicRangeContent(true);
    $layer->setEDRMetadata(CAEDRMetadata::HDR10MetadataWithMinLuminanceMaxLuminanceOpticalOutputScale(0.005, 1000.0, 100.0));

    expect($layer->allowsNextDrawableTimeout())->toBeFalse()
        ->and($layer->presentsWithTransaction())->toBeTrue()
        ->and($layer->wantsExtendedDynamicRangeContent())->toBeTrue()
        ->and($layer->EDRMetadata())->toBeInstanceOf(CAEDRMetadata::class)
        ->and(CAEDRMetadata::HLGMetadata())->toBeInstanceOf(CAEDRMetadata::class)
        ->and($layer->colorspace())->toBeNull()
        ->and(fn () => $layer->setColorspace(0))->toThrow(ValueError::class, 'must not be a null address');

    $layer->setEDRMetadata(null);
    expect($layer->EDRMetadata())->toBeNull();
});

it('takes a CGColorSpace by its address', function (): void {
    $layer = CAMetalLayer::layer();
    $space = CGColorSpace::createWithName(kCGColorSpaceSRGB);

    $layer->setColorspace($space->pointer());

    expect($layer->colorspace())->toBe($space->pointer());
    $layer->setColorspace(null);
    expect($layer->colorspace())->toBeNull();
})->skip(! class_exists(CGColorSpace::class), 'needs ext-appkit for a CGColorSpace');

it('presents a drawable after a minimum duration and reports when it reached the screen', function (): void {
    $app = NSApplication::sharedApplication();
    $app->finishLaunching();
    $app->setActivationPolicy(NSApplicationActivationPolicy::REGULAR);
    $app->activateIgnoringOtherApps(true);
    // Presentation times come back through the application's event cycle, not a bare run loop.
    $pump = function () use ($app): void {
        while ($event = $app->nextEventMatchingMaskUntilDateInModeDequeue(NSEventMask::ANY, NSDate::dateWithTimeIntervalSinceNow(0.01), NSDefaultRunLoopMode, true)) {
            $app->sendEvent($event);
        }
    };
    $window = NSWindow::initWithContentRectStyleMaskBackingDefer(new NSRect(0.0, 0.0, 160.0, 120.0), NSWindowStyleMask::TITLED->value, NSBackingStoreType::BUFFERED, false);
    $window->setReleasedWhenClosed(false);
    $device = device();
    $layer = CAMetalLayer::layer();
    $layer->setDevice($device);
    $layer->setPixelFormat(MTLPixelFormat::BGRA8_UNORM);
    $layer->setDrawableSize(new CGSize(160.0, 120.0));
    $window->contentView()->setLayer(CALayer::fromPointer($layer->pointer()));
    // Metal presents nothing to a window that is not visible: this one floats, centred, and is waited on.
    $window->setLevel(NSFloatingWindowLevel);
    $window->center();
    $window->makeKeyAndOrderFront(null);
    $until = microtime(true) + 2.0;
    while (($window->occlusionState() & NSWindowOcclusionState::VISIBLE->value) === 0 && microtime(true) < $until) {
        $pump();
    }
    expect($window->occlusionState() & NSWindowOcclusionState::VISIBLE->value)->not->toBe(0);
    $queue = $device->newCommandQueue();

    // A frame loop: each drawable waited on for at most half a second. A fresh layer's first
    // drawable is never shown, nor one presented after the layer idled a second, so plain frames
    // run first and the two timed presents come last.
    $presented = [];
    foreach (['plain', 'plain', 'plain', 'plain', 'after', 'at'] as $how) {
        $drawable = $layer->nextDrawable();
        $commands = $queue->commandBuffer();
        match ($how) {
            'after' => $commands->presentDrawableAfterMinimumDuration($drawable, 1 / 60),
            'at' => $commands->presentDrawableAtTime($drawable, 0.0),
            default => $commands->presentDrawable($drawable),
        };
        $commands->commit();
        $commands->waitUntilCompleted();
        $until = microtime(true) + 0.5;
        while ($drawable->presentedTime() === 0.0 && microtime(true) < $until) {
            $pump();
        }
        $presented[] = [$drawable->drawableID(), $drawable->presentedTime()];
    }
    [$after, $at] = array_slice($presented, -2);

    expect($after[1])->toBeGreaterThan(0.0)
        ->and($at[1])->toBeGreaterThan($after[1])
        ->and($at[0])->not->toBe($after[0]);
    $window->close();
})->skip(! class_exists(NSWindow::class), 'needs ext-appkit for an on-screen layer');
