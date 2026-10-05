<?php

/** @generate-class-entries */

/**
 * @not-serializable
 */
final class MTLCompileOptions
{
    private function __construct() {}

    public static function new(): MTLCompileOptions {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLCompileOptions. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLLibrary
{
    private function __construct() {}

    public function newFunctionWithName(string $name): ?MTLFunction {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must conform to MTLLibrary. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLFunction
{
    private function __construct() {}

    public function name(): string {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must conform to MTLFunction. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLVertexDescriptor
{
    private function __construct() {}

    public static function vertexDescriptor(): MTLVertexDescriptor {}

    public function attributes(): MTLVertexAttributeDescriptorArray {}

    public function layouts(): MTLVertexBufferLayoutDescriptorArray {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLVertexDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLVertexAttributeDescriptorArray
{
    private function __construct() {}

    public function objectAtIndexedSubscript(int $index): MTLVertexAttributeDescriptor {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLVertexAttributeDescriptorArray. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLVertexBufferLayoutDescriptorArray
{
    private function __construct() {}

    public function objectAtIndexedSubscript(int $index): MTLVertexBufferLayoutDescriptor {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLVertexBufferLayoutDescriptorArray. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLVertexAttributeDescriptor
{
    private function __construct() {}

    public function format(): MTLVertexFormat {}

    public function setFormat(MTLVertexFormat $format): void {}

    public function offset(): int {}

    public function setOffset(int $offset): void {}

    public function bufferIndex(): int {}

    public function setBufferIndex(int $bufferIndex): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLVertexAttributeDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLVertexBufferLayoutDescriptor
{
    private function __construct() {}

    public function stride(): int {}

    public function setStride(int $stride): void {}

    public function stepFunction(): MTLVertexStepFunction {}

    public function setStepFunction(MTLVertexStepFunction $stepFunction): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLVertexBufferLayoutDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLRenderPipelineDescriptor
{
    private function __construct() {}

    public static function new(): MTLRenderPipelineDescriptor {}

    public function vertexFunction(): ?MTLFunction {}

    public function setVertexFunction(?MTLFunction $function): void {}

    public function fragmentFunction(): ?MTLFunction {}

    public function setFragmentFunction(?MTLFunction $function): void {}

    public function vertexDescriptor(): ?MTLVertexDescriptor {}

    public function setVertexDescriptor(?MTLVertexDescriptor $vertexDescriptor): void {}

    public function rasterSampleCount(): int {}

    public function setRasterSampleCount(int $rasterSampleCount): void {}

    public function depthAttachmentPixelFormat(): MTLPixelFormat {}

    public function setDepthAttachmentPixelFormat(MTLPixelFormat $pixelFormat): void {}

    public function stencilAttachmentPixelFormat(): MTLPixelFormat {}

    public function setStencilAttachmentPixelFormat(MTLPixelFormat $pixelFormat): void {}

    public function colorAttachments(): MTLRenderPipelineColorAttachmentDescriptorArray {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLRenderPipelineDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLRenderPipelineColorAttachmentDescriptorArray
{
    private function __construct() {}

    public function objectAtIndexedSubscript(int $index): MTLRenderPipelineColorAttachmentDescriptor {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLRenderPipelineColorAttachmentDescriptorArray. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLRenderPipelineColorAttachmentDescriptor
{
    private function __construct() {}

    public function pixelFormat(): MTLPixelFormat {}

    public function setPixelFormat(MTLPixelFormat $pixelFormat): void {}

    public function writeMask(): MTLColorWriteMask|int {}

    public function setWriteMask(MTLColorWriteMask|int $writeMask): void {}

    public function blendingEnabled(): bool {}

    public function setBlendingEnabled(bool $blendingEnabled): void {}

    public function rgbBlendOperation(): MTLBlendOperation {}

    public function setRgbBlendOperation(MTLBlendOperation $operation): void {}

    public function alphaBlendOperation(): MTLBlendOperation {}

    public function setAlphaBlendOperation(MTLBlendOperation $operation): void {}

    public function sourceRGBBlendFactor(): MTLBlendFactor {}

    public function setSourceRGBBlendFactor(MTLBlendFactor $factor): void {}

    public function destinationRGBBlendFactor(): MTLBlendFactor {}

    public function setDestinationRGBBlendFactor(MTLBlendFactor $factor): void {}

    public function sourceAlphaBlendFactor(): MTLBlendFactor {}

    public function setSourceAlphaBlendFactor(MTLBlendFactor $factor): void {}

    public function destinationAlphaBlendFactor(): MTLBlendFactor {}

    public function setDestinationAlphaBlendFactor(MTLBlendFactor $factor): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLRenderPipelineColorAttachmentDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLRenderPipelineState
{
    private function __construct() {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must conform to MTLRenderPipelineState. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLStencilDescriptor
{
    private function __construct() {}

    public static function new(): MTLStencilDescriptor {}

    public function stencilCompareFunction(): MTLCompareFunction {}

    public function setStencilCompareFunction(MTLCompareFunction $function): void {}

    public function stencilFailureOperation(): MTLStencilOperation {}

    public function setStencilFailureOperation(MTLStencilOperation $operation): void {}

    public function depthFailureOperation(): MTLStencilOperation {}

    public function setDepthFailureOperation(MTLStencilOperation $operation): void {}

    public function depthStencilPassOperation(): MTLStencilOperation {}

    public function setDepthStencilPassOperation(MTLStencilOperation $operation): void {}

    public function readMask(): int {}

    public function setReadMask(int $readMask): void {}

    public function writeMask(): int {}

    public function setWriteMask(int $writeMask): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLStencilDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLDepthStencilDescriptor
{
    private function __construct() {}

    public static function new(): MTLDepthStencilDescriptor {}

    public function depthCompareFunction(): MTLCompareFunction {}

    public function setDepthCompareFunction(MTLCompareFunction $function): void {}

    public function depthWriteEnabled(): bool {}

    public function setDepthWriteEnabled(bool $depthWriteEnabled): void {}

    public function frontFaceStencil(): ?MTLStencilDescriptor {}

    public function setFrontFaceStencil(?MTLStencilDescriptor $stencil): void {}

    public function backFaceStencil(): ?MTLStencilDescriptor {}

    public function setBackFaceStencil(?MTLStencilDescriptor $stencil): void {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must be an MTLDepthStencilDescriptor. */
    public static function fromPointer(int $pointer): static {}
}

/**
 * @not-serializable
 */
final class MTLDepthStencilState
{
    private function __construct() {}

    public function pointer(): int {}

    /** The address is trusted to hold an object; it must conform to MTLDepthStencilState. */
    public static function fromPointer(int $pointer): static {}
}
