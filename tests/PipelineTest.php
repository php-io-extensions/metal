<?php

declare(strict_types=1);

it('compiles MSL at runtime and finds its functions', function (): void {
    $library = device()->newLibraryWithSourceOptionsError(FLAT_MSL, MTLCompileOptions::new());

    expect($library->newFunctionWithName('flat_vertex')->name())->toBe('flat_vertex')
        ->and($library->newFunctionWithName('missing'))->toBeNull();
});

it('returns null and hands back the compiler\'s NSError for MSL that does not compile', function (): void {
    $library = device()->newLibraryWithSourceOptionsError('vertex float4 broken(', null, $error);

    expect($library)->toBeNull()
        ->and($error)->toBeInstanceOf(NSError::class)
        ->and($error->localizedDescription())->toContain('error');
});

it('builds multisampled pipelines with a stencil attachment, colour on and off', function (): void {
    expect(flatPipeline(4, MTLColorWriteMask::NONE))->toBeInstanceOf(MTLRenderPipelineState::class)
        ->and(flatPipeline(4, MTLColorWriteMask::ALL))->toBeInstanceOf(MTLRenderPipelineState::class)
        ->and(flatPipeline(1, MTLColorWriteMask::ALL, null))->toBeInstanceOf(MTLRenderPipelineState::class);
});

it('passes on the NSException Metal raises for a descriptor without a vertex function', function (): void {
    $descriptor = MTLRenderPipelineDescriptor::new();
    $descriptor->colorAttachments()->objectAtIndexedSubscript(0)->setPixelFormat(MTLPixelFormat::RGBA8_UNORM);

    device()->newRenderPipelineStateWithDescriptorError($descriptor, $error);
})->throws(NSException::class, 'vertexFunction');

it('keeps a descriptor\'s sub-object alive after the descriptor goes', function (): void {
    $descriptor = MTLRenderPipelineDescriptor::new();
    $color = $descriptor->colorAttachments()->objectAtIndexedSubscript(0);
    unset($descriptor);
    $color->setPixelFormat(MTLPixelFormat::BGRA8_UNORM);

    expect($color->pixelFormat())->toBe(MTLPixelFormat::BGRA8_UNORM);
});

it('describes vertex layouts and depth-stencil state', function (): void {
    $vertex = MTLVertexDescriptor::vertexDescriptor();
    $attribute = $vertex->attributes()->objectAtIndexedSubscript(0);
    $attribute->setFormat(MTLVertexFormat::FLOAT2);
    $attribute->setBufferIndex(0);
    $vertex->layouts()->objectAtIndexedSubscript(0)->setStride(8);

    expect($vertex->attributes()->objectAtIndexedSubscript(0)->format())->toBe(MTLVertexFormat::FLOAT2)
        ->and($vertex->layouts()->objectAtIndexedSubscript(0)->stride())->toBe(8)
        ->and(stencilState(MTLCompareFunction::ALWAYS, MTLStencilOperation::INVERT))->toBeInstanceOf(MTLDepthStencilState::class);
});
