<?php

/** @generate-class-entries */

/**
 * @not-serializable
 */
final class MTLCommandQueue
{
    private function __construct() {}

    public function commandBuffer(): ?MTLCommandBuffer {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must conform to MTLCommandQueue. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLCommandBuffer
{
    private function __construct() {}

    public function renderCommandEncoderWithDescriptor(MTLRenderPassDescriptor $descriptor): ?MTLRenderCommandEncoder {}

    public function blitCommandEncoder(): ?MTLBlitCommandEncoder {}

    public function presentDrawable(CAMetalDrawable $drawable): void {}

    /** Shown no sooner than $duration seconds after the drawable before it. */
    public function presentDrawableAfterMinimumDuration(CAMetalDrawable $drawable, float $duration): void {}

    /** Shown at $presentationTime, seconds on the host clock (CACurrentMediaTime). */
    public function presentDrawableAtTime(CAMetalDrawable $drawable, float $presentationTime): void {}

    public function commit(): void {}

    public function waitUntilCompleted(): void {}

    public function status(): MTLCommandBufferStatus {}

    /** The command buffer's NSError localizedDescription, or null. */
    public function error(): ?string {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must conform to MTLCommandBuffer. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLRenderPassDescriptor
{
    private function __construct() {}

    public static function renderPassDescriptor(): MTLRenderPassDescriptor {}

    public function colorAttachments(): MTLRenderPassColorAttachmentDescriptorArray {}

    public function depthAttachment(): MTLRenderPassDepthAttachmentDescriptor {}

    public function stencilAttachment(): MTLRenderPassStencilAttachmentDescriptor {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLRenderPassDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLRenderPassColorAttachmentDescriptorArray
{
    private function __construct() {}

    public function objectAtIndexedSubscript(int $index): MTLRenderPassColorAttachmentDescriptor {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLRenderPassColorAttachmentDescriptorArray. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLRenderPassColorAttachmentDescriptor
{
    private function __construct() {}

    public function texture(): ?MTLTexture {}

    public function setTexture(?MTLTexture $texture): void {}

    public function resolveTexture(): ?MTLTexture {}

    public function setResolveTexture(?MTLTexture $texture): void {}

    public function loadAction(): MTLLoadAction {}

    public function setLoadAction(MTLLoadAction $loadAction): void {}

    public function storeAction(): MTLStoreAction {}

    public function setStoreAction(MTLStoreAction $storeAction): void {}

    public function clearColor(): MTLClearColor {}

    public function setClearColor(MTLClearColor $clearColor): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLRenderPassColorAttachmentDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLRenderPassDepthAttachmentDescriptor
{
    private function __construct() {}

    public function texture(): ?MTLTexture {}

    public function setTexture(?MTLTexture $texture): void {}

    public function resolveTexture(): ?MTLTexture {}

    public function setResolveTexture(?MTLTexture $texture): void {}

    public function loadAction(): MTLLoadAction {}

    public function setLoadAction(MTLLoadAction $loadAction): void {}

    public function storeAction(): MTLStoreAction {}

    public function setStoreAction(MTLStoreAction $storeAction): void {}

    public function clearDepth(): float {}

    public function setClearDepth(float $clearDepth): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLRenderPassDepthAttachmentDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLRenderPassStencilAttachmentDescriptor
{
    private function __construct() {}

    public function texture(): ?MTLTexture {}

    public function setTexture(?MTLTexture $texture): void {}

    public function resolveTexture(): ?MTLTexture {}

    public function setResolveTexture(?MTLTexture $texture): void {}

    public function loadAction(): MTLLoadAction {}

    public function setLoadAction(MTLLoadAction $loadAction): void {}

    public function storeAction(): MTLStoreAction {}

    public function setStoreAction(MTLStoreAction $storeAction): void {}

    public function clearStencil(): int {}

    public function setClearStencil(int $clearStencil): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLRenderPassStencilAttachmentDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLRenderCommandEncoder
{
    private function __construct() {}

    public function setRenderPipelineState(MTLRenderPipelineState $state): void {}

    public function setDepthStencilState(?MTLDepthStencilState $state): void {}

    public function setStencilReferenceValue(int $value): void {}

    public function setCullMode(MTLCullMode $cullMode): void {}

    public function setFrontFacingWinding(MTLWinding $winding): void {}

    public function setVertexBufferOffsetAtIndex(?MTLBuffer $buffer, int $offset, int $index): void {}

    /** $bytes must hold $length bytes. */
    public function setVertexBytesLengthAtIndex(string $bytes, int $length, int $index): void {}

    /** $bytes must hold $length bytes. */
    public function setFragmentBytesLengthAtIndex(string $bytes, int $length, int $index): void {}

    public function setFragmentTextureAtIndex(?MTLTexture $texture, int $index): void {}

    public function setFragmentSamplerStateAtIndex(?MTLSamplerState $sampler, int $index): void {}

    public function setViewport(MTLViewport $viewport): void {}

    public function setScissorRect(MTLScissorRect $rect): void {}

    public function drawPrimitivesVertexStartVertexCount(MTLPrimitiveType $primitiveType, int $vertexStart, int $vertexCount): void {}

    public function drawIndexedPrimitivesIndexCountIndexTypeIndexBufferIndexBufferOffset(MTLPrimitiveType $primitiveType, int $indexCount, MTLIndexType $indexType, MTLBuffer $indexBuffer, int $indexBufferOffset): void {}

    public function endEncoding(): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must conform to MTLRenderCommandEncoder. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLBlitCommandEncoder
{
    private function __construct() {}

    public function copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin(MTLTexture $sourceTexture, int $sourceSlice, int $sourceLevel, MTLOrigin $sourceOrigin, MTLSize $sourceSize, MTLTexture $destinationTexture, int $destinationSlice, int $destinationLevel, MTLOrigin $destinationOrigin): void {}

    public function copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImage(MTLTexture $sourceTexture, int $sourceSlice, int $sourceLevel, MTLOrigin $sourceOrigin, MTLSize $sourceSize, MTLBuffer $destinationBuffer, int $destinationOffset, int $destinationBytesPerRow, int $destinationBytesPerImage): void {}

    public function copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin(MTLBuffer $sourceBuffer, int $sourceOffset, int $sourceBytesPerRow, int $sourceBytesPerImage, MTLSize $sourceSize, MTLTexture $destinationTexture, int $destinationSlice, int $destinationLevel, MTLOrigin $destinationOrigin): void {}

    public function synchronizeResource(MTLTexture|MTLBuffer $resource): void {}

    public function endEncoding(): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must conform to MTLBlitCommandEncoder. */
    public static function fromPointer(int $pointer): static {}
}
