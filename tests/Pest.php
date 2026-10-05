<?php

declare(strict_types=1);

if (! extension_loaded('metal')) {
    throw new RuntimeException('The metal extension is not loaded; run ./install-macos.sh');
}

function device(): MTLDevice
{
    return MTLCreateSystemDefaultDevice() ?? throw new RuntimeException('This Mac has no Metal device');
}

function sharedTexture(int $width = 4, int $height = 2): MTLTexture
{
    $descriptor = MTLTextureDescriptor::texture2DDescriptorWithPixelFormatWidthHeightMipmapped(MTLPixelFormat::RGBA8_UNORM, $width, $height, false);
    $descriptor->setStorageMode(MTLStorageMode::SHARED);
    $descriptor->setUsage(MTLTextureUsage::SHADER_READ->value | MTLTextureUsage::RENDER_TARGET->value);

    return device()->newTextureWithDescriptor($descriptor);
}

/** One vertex function placing float2 points from buffer 0, one fragment function filling with the float4 in buffer 0. */
const FLAT_MSL = <<<'MSL'
#include <metal_stdlib>
using namespace metal;

struct VertexOut { float4 position [[position]]; };

vertex VertexOut flat_vertex(uint vid [[vertex_id]], constant float2 *points [[buffer(0)]])
{
    VertexOut out;
    out.position = float4(points[vid], 0.0, 1.0);
    return out;
}

fragment float4 flat_fragment(constant float4 &color [[buffer(0)]])
{
    return color;
}
MSL;

function flatPipeline(int $samples, MTLColorWriteMask|int $writeMask, ?MTLPixelFormat $stencil = MTLPixelFormat::STENCIL8): MTLRenderPipelineState
{
    $library = device()->newLibraryWithSourceOptionsError(FLAT_MSL, null);
    $descriptor = MTLRenderPipelineDescriptor::new();
    $descriptor->setVertexFunction($library->newFunctionWithName('flat_vertex'));
    $descriptor->setFragmentFunction($library->newFunctionWithName('flat_fragment'));
    $descriptor->setRasterSampleCount($samples);
    $color = $descriptor->colorAttachments()->objectAtIndexedSubscript(0);
    $color->setPixelFormat(MTLPixelFormat::RGBA8_UNORM);
    $color->setWriteMask($writeMask);
    if ($stencil !== null) {
        $descriptor->setStencilAttachmentPixelFormat($stencil);
    }

    return device()->newRenderPipelineStateWithDescriptorError($descriptor);
}

function stencilState(MTLCompareFunction $compare, MTLStencilOperation $pass): MTLDepthStencilState
{
    $stencil = MTLStencilDescriptor::new();
    $stencil->setStencilCompareFunction($compare);
    $stencil->setDepthStencilPassOperation($pass);
    $descriptor = MTLDepthStencilDescriptor::new();
    $descriptor->setFrontFaceStencil($stencil);
    $descriptor->setBackFaceStencil($stencil);

    return device()->newDepthStencilStateWithDescriptor($descriptor);
}
