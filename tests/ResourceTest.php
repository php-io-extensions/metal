<?php

declare(strict_types=1);

it('makes a texture its descriptor describes', function (): void {
    $texture = sharedTexture();

    expect([$texture->width(), $texture->height(), $texture->pixelFormat(), $texture->textureType(), $texture->sampleCount()])
        ->toBe([4, 2, MTLPixelFormat::RGBA8_UNORM, MTLTextureType::TYPE_2D, 1]);
});

it('writes bytes into a texture and reads them back', function (): void {
    $texture = sharedTexture();
    $bytes = implode('', array_map(fn (int $i): string => pack('N', 0x11223300 | $i), range(0, 7)));
    $region = new MTLRegion(new MTLOrigin(0, 0, 0), new MTLSize(4, 2, 1));

    $texture->replaceRegionMipmapLevelWithBytesBytesPerRow($region, 0, $bytes, 16);

    expect($texture->getBytesBytesPerRowFromRegionMipmapLevel(null, 16, $region, 0))->toBe($bytes)
        ->and($texture->getBytesBytesPerRowFromRegionMipmapLevel(null, 4, new MTLRegion(new MTLOrigin(2, 1, 0), new MTLSize(1, 1, 1)), 0))->toBe(substr($bytes, 24, 4));
});

it('writes from an address and reads into one', function (): void {
    $source = new FbBuffer(new FbFormat(FB_LAYOUT_RGBA8888, channelOrder: FB_CHANNELS_RGBA), 4, 2);
    $source->fill(0xAABBCCDD);
    $target = new FbBuffer(new FbFormat(FB_LAYOUT_RGBA8888, channelOrder: FB_CHANNELS_RGBA), 4, 2);
    $texture = sharedTexture();
    $region = new MTLRegion(new MTLOrigin(0, 0, 0), new MTLSize(4, 2, 1));

    $texture->replaceRegionMipmapLevelWithBytesBytesPerRow($region, 0, $source->pointer(), 16);

    expect($texture->getBytesBytesPerRowFromRegionMipmapLevel($target->pointer(), 16, $region, 0))->toBeNull()
        ->and($target->bytes())->toBe($source->bytes());
})->skip(! class_exists(FbBuffer::class), 'needs ext-fb for native addresses');

it('refuses bytes that do not hold the region, and a null address', function (Closure $call, string $message): void {
    expect($call)->toThrow(ValueError::class, $message);
})->with([
    'short string' => [fn () => sharedTexture()->replaceRegionMipmapLevelWithBytesBytesPerRow(new MTLRegion(new MTLOrigin(0, 0, 0), new MTLSize(4, 2, 1)), 0, str_repeat("\0", 31), 16), 'must hold'],
    'null address' => [fn () => sharedTexture()->replaceRegionMipmapLevelWithBytesBytesPerRow(new MTLRegion(new MTLOrigin(0, 0, 0), new MTLSize(4, 2, 1)), 0, 0, 16), 'null address'],
    'short buffer bytes' => [fn () => device()->newBufferWithBytesLengthOptions('abc', 4, MTLResourceOptions::STORAGE_MODE_SHARED), 'must hold'],
]);

it('makes buffers, shared ones with an address', function (): void {
    $shared = device()->newBufferWithLengthOptions(256, MTLResourceOptions::STORAGE_MODE_SHARED);
    $private = device()->newBufferWithLengthOptions(256, MTLResourceOptions::STORAGE_MODE_PRIVATE);

    // Ledger: on this M1, MTLStorageModePrivate still returns a contents pointer
    // (native check: storage mode 2, contents non-NULL). Nil contents is 0.
    expect([$shared->length(), $private->length()])->toBe([256, 256])
        ->and($shared->contents())->toBeGreaterThan(0)
        ->and($private->contents())->toBeGreaterThan(0)
        ->and(device()->newBufferWithBytesLengthOptions('abcd', 4, MTLResourceOptions::STORAGE_MODE_SHARED)->length())->toBe(4);
});

it('makes a sampler and says which sample counts the device takes', function (): void {
    $descriptor = MTLSamplerDescriptor::new();
    $descriptor->setMinFilter(MTLSamplerMinMagFilter::NEAREST);
    $descriptor->setMagFilter(MTLSamplerMinMagFilter::LINEAR);

    expect($descriptor->magFilter())->toBe(MTLSamplerMinMagFilter::LINEAR)
        ->and(device()->newSamplerStateWithDescriptor($descriptor))->toBeInstanceOf(MTLSamplerState::class)
        ->and(device()->supportsTextureSampleCount(4))->toBeTrue();
});
