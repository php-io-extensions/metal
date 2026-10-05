<?php

/** @generate-class-entries */

/**
 * @not-serializable
 */
final class MTLDevice
{
    private function __construct() {}

    public function name(): string {}

    /** The object's address, for handing it to another extension. */
    public function pointer(): int {}

    /** The MTLDevice at $pointer (another extension's pointer()). The address is trusted to hold an object; it must conform to MTLDevice. */
    public static function fromPointer(int $pointer): static {}

    public function newTextureWithDescriptor(MTLTextureDescriptor $descriptor): ?MTLTexture {}

    public function newBufferWithLengthOptions(int $length, MTLResourceOptions|int $options): ?MTLBuffer {}

    /** $bytes is a string of at least $length bytes, or an address trusted to hold $length bytes. 0 is refused. */
    public function newBufferWithBytesLengthOptions(string|int $bytes, int $length, MTLResourceOptions|int $options): ?MTLBuffer {}

    public function newSamplerStateWithDescriptor(MTLSamplerDescriptor $descriptor): ?MTLSamplerState {}

    public function supportsTextureSampleCount(int $sampleCount): bool {}

    /** Throws MetalException with the compiler log when $source does not compile. A warning-only NSError is returned, not thrown. */
    public function newLibraryWithSourceOptionsError(string $source, ?MTLCompileOptions $options): MTLLibrary {}

    /** Throws MetalException when $descriptor is rejected. */
    public function newRenderPipelineStateWithDescriptorError(MTLRenderPipelineDescriptor $descriptor): MTLRenderPipelineState {}

    public function newDepthStencilStateWithDescriptor(MTLDepthStencilDescriptor $descriptor): ?MTLDepthStencilState {}

    public function newCommandQueue(): ?MTLCommandQueue {}
}
