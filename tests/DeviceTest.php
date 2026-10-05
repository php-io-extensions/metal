<?php

declare(strict_types=1);

it('answers the system default device, the same object every time', function (): void {
    $device = device();

    expect($device)->toBeInstanceOf(MTLDevice::class)
        ->and($device->name())->not->toBe('')
        ->and(MTLCreateSystemDefaultDevice())->toBe($device);
});

it('hands a device to another extension by address and takes it back', function (): void {
    $device = device();

    expect($device->pointer())->toBeGreaterThan(0)
        ->and(MTLDevice::fromPointer($device->pointer()))->toBe($device);
});

it('refuses a null address and an address that is not a device', function (): void {
    expect(fn () => MTLDevice::fromPointer(0))->toThrow(MetalException::class, 'null address')
        ->and(fn () => MTLDevice::fromPointer(device()->newCommandQueue()->pointer()))->toThrow(MetalException::class, 'not an MTLDevice');
});

it('cannot be constructed, cloned or serialized', function (): void {
    expect(fn () => new ReflectionClass(MTLDevice::class))->not->toThrow(Throwable::class)
        ->and((new ReflectionClass(MTLDevice::class))->getConstructor()->isPrivate())->toBeTrue()
        ->and(fn () => clone device())->toThrow(Error::class)
        ->and(fn () => serialize(device()))->toThrow(Exception::class);
});
