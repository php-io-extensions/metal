<?php

declare(strict_types=1);

function multisampleTarget(MTLPixelFormat $format): MTLTexture
{
    $descriptor = MTLTextureDescriptor::new();
    $descriptor->setTextureType(MTLTextureType::TYPE_2D_MULTISAMPLE);
    $descriptor->setPixelFormat($format);
    $descriptor->setWidth(8);
    $descriptor->setHeight(8);
    $descriptor->setSampleCount(4);
    $descriptor->setUsage(MTLTextureUsage::RENDER_TARGET);
    $descriptor->setStorageMode(MTLStorageMode::PRIVATE);

    return device()->newTextureWithDescriptor($descriptor);
}

/** RGBA8 pixel at (x, y) of a tightly packed 8-wide image, as hex. */
function pixelAt(string $bytes, int $x, int $y): string
{
    return bin2hex(substr($bytes, ($y * 8 + $x) * 4, 4));
}

it('fills a triangle by stencil-then-cover into a 4x target, resolves, and reads it back through a buffer', function (): void {
    $resolved = sharedTexture(8, 8);
    $pass = MTLRenderPassDescriptor::renderPassDescriptor();
    $color = $pass->colorAttachments()->objectAtIndexedSubscript(0);
    $color->setTexture(multisampleTarget(MTLPixelFormat::RGBA8_UNORM));
    $color->setResolveTexture($resolved);
    $color->setLoadAction(MTLLoadAction::CLEAR);
    $color->setClearColor(new MTLClearColor(0.0, 0.0, 0.0, 1.0));
    $color->setStoreAction(MTLStoreAction::MULTISAMPLE_RESOLVE);
    $stencil = $pass->stencilAttachment();
    $stencil->setTexture(multisampleTarget(MTLPixelFormat::STENCIL8));
    $stencil->setLoadAction(MTLLoadAction::CLEAR);
    $stencil->setClearStencil(0);
    $stencil->setStoreAction(MTLStoreAction::DONT_CARE);

    // The lower-left half of the target in clip space: (-1,-1), (1,-1), (-1,1).
    $triangle = pack('g6', -1.0, -1.0, 1.0, -1.0, -1.0, 1.0);
    $cover = pack('g12', -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0);
    $red = pack('g4', 1.0, 0.0, 0.0, 1.0);

    $queue = device()->newCommandQueue();
    $commands = $queue->commandBuffer();
    $encoder = $commands->renderCommandEncoderWithDescriptor($pass);
    // Stencil: invert where the triangle covers, no colour written.
    $encoder->setRenderPipelineState(flatPipeline(4, MTLColorWriteMask::NONE));
    $encoder->setDepthStencilState(stencilState(MTLCompareFunction::ALWAYS, MTLStencilOperation::INVERT));
    $encoder->setVertexBytesLengthAtIndex($triangle, strlen($triangle), 0);
    $encoder->drawPrimitivesVertexStartVertexCount(MTLPrimitiveType::TRIANGLE, 0, 3);
    // Cover: red where the stencil is not 0, and the stencil back to 0.
    $encoder->setRenderPipelineState(flatPipeline(4, MTLColorWriteMask::ALL));
    $encoder->setDepthStencilState(stencilState(MTLCompareFunction::NOT_EQUAL, MTLStencilOperation::ZERO));
    $encoder->setStencilReferenceValue(0);
    $encoder->setVertexBytesLengthAtIndex($cover, strlen($cover), 0);
    $encoder->setFragmentBytesLengthAtIndex($red, strlen($red), 0);
    $encoder->drawPrimitivesVertexStartVertexCount(MTLPrimitiveType::TRIANGLE, 0, 6);
    $encoder->endEncoding();

    $buffer = device()->newBufferWithLengthOptions(256, MTLResourceOptions::STORAGE_MODE_SHARED);
    $copy = sharedTexture(8, 8);
    $blit = $commands->blitCommandEncoder();
    $blit->copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImage($resolved, 0, 0, new MTLOrigin(0, 0, 0), new MTLSize(8, 8, 1), $buffer, 0, 32, 256);
    $blit->copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin($buffer, 0, 32, 256, new MTLSize(8, 8, 1), $copy, 0, 0, new MTLOrigin(0, 0, 0));
    $blit->endEncoding();
    $commands->commit();
    $commands->waitUntilCompleted();

    $whole = new MTLRegion(new MTLOrigin(0, 0, 0), new MTLSize(8, 8, 1));
    $pixels = $copy->getBytesBytesPerRowFromRegionMipmapLevel(null, 32, $whole, 0);

    expect($commands->status())->toBe(MTLCommandBufferStatus::COMPLETED)
        ->and($pixels)->toBe($resolved->getBytesBytesPerRowFromRegionMipmapLevel(null, 32, $whole, 0))
        // Texture row 0 is the top. (0,0) is the triangle's top-left vertex: on this
        // M1 a 4x resolve covers 2 of 4 samples (800000ff). The pixel one row inside is solid.
        ->and(pixelAt($pixels, 1, 6))->toBe('ff0000ff')
        ->and(pixelAt($pixels, 0, 0))->toBe('800000ff')
        ->and(pixelAt($pixels, 0, 1))->toBe('ff0000ff')
        ->and(pixelAt($pixels, 6, 1))->toBe('000000ff')
        ->and(pixelAt($pixels, 7, 7))->not->toBe('ff0000ff')
        // The hypotenuse runs top-left to bottom-right, (i, i). The anti-diagonal
        // (i, 7-i) lands on pixel centres (solid red or solid black). Every pixel
        // on (i, i) resolves to two of the four samples.
        ->and(array_unique(array_map(fn (int $i): string => pixelAt($pixels, $i, $i), range(0, 7))))->toBe(['800000ff']);
});
