<?php

declare(strict_types=1);

it('clears a texture in a render pass and reads the pixel back', function (): void {
    $texture = sharedTexture(2, 2);
    $pass = MTLRenderPassDescriptor::renderPassDescriptor();
    $color = $pass->colorAttachments()->objectAtIndexedSubscript(0);
    $color->setTexture($texture);
    $color->setLoadAction(MTLLoadAction::CLEAR);
    $color->setClearColor(new MTLClearColor(0.0, 1.0, 0.0, 1.0));
    $color->setStoreAction(MTLStoreAction::STORE);

    $commands = device()->newCommandQueue()->commandBuffer();
    $commands->renderCommandEncoderWithDescriptor($pass)->endEncoding();
    $commands->commit();
    $commands->waitUntilCompleted();

    expect($commands->status())->toBe(MTLCommandBufferStatus::COMPLETED)
        ->and($commands->error())->toBeNull()
        ->and(bin2hex($texture->getBytesBytesPerRowFromRegionMipmapLevel(null, 4, new MTLRegion(new MTLOrigin(1, 1, 0), new MTLSize(1, 1, 1)), 0)))->toBe('00ff00ff');
});

it('refuses vertex bytes shorter than the length given', function (): void {
    $texture = sharedTexture(2, 2);
    $pass = MTLRenderPassDescriptor::renderPassDescriptor();
    $pass->colorAttachments()->objectAtIndexedSubscript(0)->setTexture($texture);
    $encoder = device()->newCommandQueue()->commandBuffer()->renderCommandEncoderWithDescriptor($pass);

    try {
        expect(fn () => $encoder->setVertexBytesLengthAtIndex('abc', 8, 0))->toThrow(ValueError::class, 'must hold');
    } finally {
        $encoder->endEncoding();
    }
});

it('copies a texture through a buffer and back', function (): void {
    $source = sharedTexture(4, 2);
    $bytes = random_bytes(32);
    $region = new MTLRegion(new MTLOrigin(0, 0, 0), new MTLSize(4, 2, 1));
    $source->replaceRegionMipmapLevelWithBytesBytesPerRow($region, 0, $bytes, 16);
    $buffer = device()->newBufferWithLengthOptions(32, MTLResourceOptions::STORAGE_MODE_SHARED);
    $copy = sharedTexture(4, 2);

    $commands = device()->newCommandQueue()->commandBuffer();
    $blit = $commands->blitCommandEncoder();
    $blit->copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImage($source, 0, 0, new MTLOrigin(0, 0, 0), new MTLSize(4, 2, 1), $buffer, 0, 16, 32);
    $blit->copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin($buffer, 0, 16, 32, new MTLSize(4, 2, 1), $copy, 0, 0, new MTLOrigin(0, 0, 0));
    $blit->endEncoding();
    $commands->commit();
    $commands->waitUntilCompleted();

    expect($copy->getBytesBytesPerRowFromRegionMipmapLevel(null, 16, $region, 0))->toBe($bytes);
});
