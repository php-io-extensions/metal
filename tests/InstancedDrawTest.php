<?php

declare(strict_types=1);

/**
 * Draws the lower-left triangle into an 8×8 target with the instanced selector.
 * Zero instances leave the clear. One instance covers the same pixels the uninstanced draw covers.
 */
function drawInstances(int $instances): string
{
    $target = sharedTexture(8, 8);
    $pass = MTLRenderPassDescriptor::renderPassDescriptor();
    $color = $pass->colorAttachments()->objectAtIndexedSubscript(0);
    $color->setTexture($target);
    $color->setLoadAction(MTLLoadAction::CLEAR);
    $color->setClearColor(new MTLClearColor(0.0, 0.0, 0.0, 1.0));
    $color->setStoreAction(MTLStoreAction::STORE);

    $triangle = pack('g6', -1.0, -1.0, 1.0, -1.0, -1.0, 1.0);
    $red = pack('g4', 1.0, 0.0, 0.0, 1.0);

    $commands = device()->newCommandQueue()->commandBuffer();
    $encoder = $commands->renderCommandEncoderWithDescriptor($pass);
    $encoder->setRenderPipelineState(flatPipeline(1, MTLColorWriteMask::ALL, null));
    $encoder->setVertexBytesLengthAtIndex($triangle, strlen($triangle), 0);
    $encoder->setFragmentBytesLengthAtIndex($red, strlen($red), 0);
    $encoder->drawPrimitivesVertexStartVertexCountInstanceCount(MTLPrimitiveType::TRIANGLE, 0, 3, $instances);
    $encoder->endEncoding();
    $commands->commit();
    $commands->waitUntilCompleted();

    expect($commands->status())->toBe(MTLCommandBufferStatus::COMPLETED);

    return textureBytes($target, 32, new MTLRegion(new MTLOrigin(0, 0, 0), new MTLSize(8, 8, 1)), 0);
}

/** RGBA8 pixel at (x, y) of a tightly packed 8-wide image, as hex. */
function instancePixel(string $bytes, int $x, int $y): string
{
    return bin2hex(substr($bytes, ($y * 8 + $x) * 4, 4));
}

it('draws nothing when the instance count is zero', function (): void {
    $pixels = drawInstances(0);

    expect(instancePixel($pixels, 1, 6))->toBe('000000ff')
        ->and(instancePixel($pixels, 0, 0))->toBe('000000ff');
});

it('draws the triangle once when the instance count is one', function (): void {
    $pixels = drawInstances(1);

    expect(instancePixel($pixels, 1, 6))->toBe('ff0000ff')
        ->and(instancePixel($pixels, 6, 1))->toBe('000000ff');
});
