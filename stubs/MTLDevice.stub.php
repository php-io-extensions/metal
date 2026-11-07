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

    /** The object at $pointer (another extension's pointer()), trusted to be this class's native object; 0 is null. */
    public static function fromPointer(int $pointer): ?static {}

    public function newTextureWithDescriptor(MTLTextureDescriptor $descriptor): ?MTLTexture {}

    public function newBufferWithLengthOptions(int $length, MTLResourceOptions|int $options): ?MTLBuffer {}

    /** $bytes is a string of at least $length bytes, or an address trusted to hold $length bytes. 0 is refused. */
    public function newBufferWithBytesLengthOptions(string|int $bytes, int $length, MTLResourceOptions|int $options): ?MTLBuffer {}

    public function newSamplerStateWithDescriptor(MTLSamplerDescriptor $descriptor): ?MTLSamplerState {}

    public function supportsTextureSampleCount(int $sampleCount): bool {}

    /** $error receives the NSError (ext-appkit's) Metal reports: the compiler log, also with a library when it only warns. */
    public function newLibraryWithSourceOptionsError(string $source, ?MTLCompileOptions $options, ?NSError &$error = null): ?MTLLibrary {}

    public function newRenderPipelineStateWithDescriptorError(MTLRenderPipelineDescriptor $descriptor, ?NSError &$error = null): ?MTLRenderPipelineState {}

    public function newDepthStencilStateWithDescriptor(MTLDepthStencilDescriptor $descriptor): ?MTLDepthStencilState {}

    public function newCommandQueue(): ?MTLCommandQueue {}
}
