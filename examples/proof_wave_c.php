<?php
/**
 * Wave C binding proof: the depth and stencil attachments exist on a fresh
 * render pass and carry their clear values; the pipeline takes depth/stencil
 * pixel formats and every blend property. Round-trips only — no draw; the
 * blended draw is proven typed in jovian/metal's proof_blend_typed.php.
 * Raw enum ints are cited from the SDK headers (constants live in jovian/metal).
 */

declare(strict_types=1);

use Metal\MTL\MTLRenderPassDepthAttachmentDescriptor\MTLRenderPassDepthAttachmentDescriptor;
use Metal\MTL\MTLRenderPassDescriptor\MTLRenderPassDescriptor;
use Metal\MTL\MTLRenderPassStencilAttachmentDescriptor\MTLRenderPassStencilAttachmentDescriptor;
use Metal\MTL\MTLRenderPipelineColorAttachmentDescriptor\MTLRenderPipelineColorAttachmentDescriptor;
use Metal\MTL\MTLRenderPipelineColorAttachmentDescriptorArray\MTLRenderPipelineColorAttachmentDescriptorArray;
use Metal\MTL\MTLRenderPipelineDescriptor\MTLRenderPipelineDescriptor;

function fail(string $why): never
{
    fwrite(STDERR, "PROOF_WAVE_C_FAIL: {$why}\n");
    exit(1);
}

$passA = MTLRenderPassDescriptor::renderPassDescriptor();
$depth = MTLRenderPassDescriptor::depthAttachment($passA);
$depth > 0 || fail('depthAttachment is nil');
MTLRenderPassDepthAttachmentDescriptor::setClearDepth($depth, 0.25);
abs(MTLRenderPassDepthAttachmentDescriptor::clearDepth($depth) - 0.25) < 1e-9 || fail('clearDepth did not round-trip');

$stencil = MTLRenderPassDescriptor::stencilAttachment($passA);
$stencil > 0 || fail('stencilAttachment is nil');
MTLRenderPassStencilAttachmentDescriptor::setClearStencil($stencil, 7);
MTLRenderPassStencilAttachmentDescriptor::clearStencil($stencil) === 7 || fail('clearStencil did not round-trip');

// Prove the setters across passes: a fresh pass B starts at the SDK defaults
// (clearDepth 1.0, clearStencil 0); after setting A's attachments on it, B's own
// sub-objects (the properties are `copy`) must carry A's clear values.
$passB = MTLRenderPassDescriptor::renderPassDescriptor();
abs(MTLRenderPassDepthAttachmentDescriptor::clearDepth(MTLRenderPassDescriptor::depthAttachment($passB)) - 0.25) >= 1e-9 || fail('pass B clearDepth already 0.25 before set');
MTLRenderPassStencilAttachmentDescriptor::clearStencil(MTLRenderPassDescriptor::stencilAttachment($passB)) !== 7 || fail('pass B clearStencil already 7 before set');
MTLRenderPassDescriptor::setDepthAttachment($passB, $depth);
MTLRenderPassDescriptor::setStencilAttachment($passB, $stencil);
$depthB = MTLRenderPassDescriptor::depthAttachment($passB);
$depthB > 0 || fail('pass B depthAttachment is nil after set');
abs(MTLRenderPassDepthAttachmentDescriptor::clearDepth($depthB) - 0.25) < 1e-9 || fail('setDepthAttachment did not carry clearDepth to pass B');
$stencilB = MTLRenderPassDescriptor::stencilAttachment($passB);
$stencilB > 0 || fail('pass B stencilAttachment is nil after set');
MTLRenderPassStencilAttachmentDescriptor::clearStencil($stencilB) === 7 || fail('setStencilAttachment did not carry clearStencil to pass B');

$pipe = MTLRenderPipelineDescriptor::init();
MTLRenderPipelineDescriptor::setDepthAttachmentPixelFormat($pipe, 252);    // MTLPixelFormatDepth32Float
MTLRenderPipelineDescriptor::depthAttachmentPixelFormat($pipe) === 252 || fail('depthAttachmentPixelFormat did not round-trip');
MTLRenderPipelineDescriptor::setStencilAttachmentPixelFormat($pipe, 253);  // MTLPixelFormatStencil8
MTLRenderPipelineDescriptor::stencilAttachmentPixelFormat($pipe) === 253 || fail('stencilAttachmentPixelFormat did not round-trip');

$att = MTLRenderPipelineColorAttachmentDescriptorArray::objectAtIndexedSubscript(MTLRenderPipelineDescriptor::colorAttachments($pipe), 0);
$att > 0 || fail('pipeline colour attachment 0 missing');
MTLRenderPipelineColorAttachmentDescriptor::setBlendingEnabled($att, true);

$C = MTLRenderPipelineColorAttachmentDescriptor::class;
foreach ([
    ['setSourceRGBBlendFactor', 'sourceRGBBlendFactor', 4],            // MTLBlendFactorSourceAlpha
    ['setDestinationRGBBlendFactor', 'destinationRGBBlendFactor', 5],  // MTLBlendFactorOneMinusSourceAlpha
    ['setRgbBlendOperation', 'rgbBlendOperation', 1],                  // MTLBlendOperationSubtract (non-default, so the write is proven)
    ['setSourceAlphaBlendFactor', 'sourceAlphaBlendFactor', 4],        // MTLBlendFactorSourceAlpha (non-default; SDK default is One)
    ['setDestinationAlphaBlendFactor', 'destinationAlphaBlendFactor', 5],
    ['setAlphaBlendOperation', 'alphaBlendOperation', 1],
    ['setWriteMask', 'writeMask', 0x5],                                // MTLColorWriteMaskGreen | MTLColorWriteMaskAlpha (non-default)
] as [$set, $get, $value]) {
    $C::$set($att, $value);
    $C::$get($att) === $value || fail("{$get} did not round-trip ({$value})");
}

echo "PROOF_WAVE_C_OK\n";
