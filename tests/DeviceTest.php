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

it('boxes the object at an address, and null for address 0', function (): void {
    expect(MTLDevice::fromPointer(device()->pointer()))->toBe(device())
        ->and(MTLDevice::fromPointer(0))->toBeNull();
});

it('cannot be constructed, cloned or serialized', function (): void {
    expect(fn () => new ReflectionClass(MTLDevice::class))->not->toThrow(Throwable::class)
        ->and((new ReflectionClass(MTLDevice::class))->getConstructor()->isPrivate())->toBeTrue()
        ->and(fn () => clone device())->toThrow(Error::class)
        ->and(fn () => serialize(device()))->toThrow(Exception::class);
});
