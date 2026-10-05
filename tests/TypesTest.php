<?php

declare(strict_types=1);

it('holds struct values in properties named as in C', function (): void {
    $region = new MTLRegion(new MTLOrigin(1, 2, 0), new MTLSize(8, 4, 1));
    $viewport = new MTLViewport(0.0, 0.0, 8.0, 8.0, 0.0, 1.0);

    expect([$region->origin->x, $region->origin->y, $region->size->width, $region->size->depth])->toBe([1, 2, 8, 1])
        ->and([$viewport->width, $viewport->zfar])->toBe([8.0, 1.0])
        ->and((new MTLClearColor(1.0, 0.0, 0.0, 1.0))->red)->toBe(1.0)
        ->and((new MTLScissorRect(0, 0, 4, 4))->height)->toBe(4);
});

it('carries the SDK values for the enums', function (MTLPixelFormat|MTLLoadAction|MTLStoreAction|MTLStorageMode|MTLTextureUsage|MTLTextureType|MTLPrimitiveType|MTLCompareFunction|MTLStencilOperation|MTLColorWriteMask|MTLVertexFormat|MTLResourceOptions|MTLCommandBufferStatus $case, int $value): void {
    expect($case->value)->toBe($value);
})->with([
    [MTLPixelFormat::RGBA8_UNORM, 70],
    [MTLPixelFormat::BGRA8_UNORM, 80],
    [MTLPixelFormat::DEPTH32_FLOAT, 252],
    [MTLPixelFormat::STENCIL8, 253],
    [MTLPixelFormat::DEPTH32_FLOAT_STENCIL8, 260],
    [MTLLoadAction::CLEAR, 2],
    [MTLStoreAction::MULTISAMPLE_RESOLVE, 2],
    [MTLStorageMode::SHARED, 0],
    [MTLStorageMode::PRIVATE, 2],
    [MTLTextureUsage::RENDER_TARGET, 4],
    [MTLTextureType::TYPE_2D_MULTISAMPLE, 4],
    [MTLPrimitiveType::TRIANGLE, 3],
    [MTLCompareFunction::NOT_EQUAL, 5],
    [MTLStencilOperation::INVERT, 5],
    [MTLColorWriteMask::ALL, 15],
    [MTLVertexFormat::FLOAT2, 29],
    [MTLResourceOptions::STORAGE_MODE_PRIVATE, 32],
    [MTLCommandBufferStatus::COMPLETED, 4],
]);

it('refuses a region without both halves', function (): void {
    expect(fn () => new MTLRegion(new MTLOrigin(0, 0, 0), null))->toThrow(TypeError::class);
});
