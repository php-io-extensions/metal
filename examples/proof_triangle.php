<?php
/**
 * Wave A proof: compile an MSL shader pair at runtime, build a render
 * pipeline, and draw one triangle into a 64x64 offscreen RGBA8Unorm
 * texture cleared to black — then byte-check the readback. No window, no
 * AppKit. Exit 0 = proven; exit 1 = failed.
 *
 * This exercises the whole Wave A surface end to end: the NSError**
 * pattern (newLibraryWithSourceOptionsError,
 * newRenderPipelineStateWithDescriptorError), MTLLibrary/MTLFunction,
 * MTLBuffer (bytes in, guarded read back out), the pipeline descriptor
 * family, and MTLRenderCommandEncoder's resource binding + draw calls.
 *
 * Raw enum ints are used deliberately: constants belong to jovian/metal,
 * not the ext. Every value below was read out of the CommandLineTools SDK
 * headers (file:line in the comment).
 */

use Metal\MTL\MTLDevice\MTLDevice;
use Metal\MTL\MTLTextureDescriptor\MTLTextureDescriptor;
use Metal\MTL\MTLTexture\MTLTexture;
use Metal\MTL\MTLBuffer\MTLBuffer;
use Metal\MTL\MTLLibrary\MTLLibrary;
use Metal\MTL\MTLFunction\MTLFunction;
use Metal\MTL\MTLRenderPipelineDescriptor\MTLRenderPipelineDescriptor;
use Metal\MTL\MTLRenderPipelineColorAttachmentDescriptorArray\MTLRenderPipelineColorAttachmentDescriptorArray;
use Metal\MTL\MTLRenderPipelineColorAttachmentDescriptor\MTLRenderPipelineColorAttachmentDescriptor;
use Metal\MTL\MTLRenderPipelineState\MTLRenderPipelineState;
use Metal\MTL\MTLRenderPassDescriptor\MTLRenderPassDescriptor;
use Metal\MTL\MTLRenderPassColorAttachmentDescriptorArray\MTLRenderPassColorAttachmentDescriptorArray;
use Metal\MTL\MTLRenderPassAttachmentDescriptor\MTLRenderPassAttachmentDescriptor;
use Metal\MTL\MTLRenderPassColorAttachmentDescriptor\MTLRenderPassColorAttachmentDescriptor;
use Metal\MTL\MTLCommandQueue\MTLCommandQueue;
use Metal\MTL\MTLCommandBuffer\MTLCommandBuffer;
use Metal\MTL\MTLCommandEncoder\MTLCommandEncoder;
use Metal\MTL\MTLRenderCommandEncoder\MTLRenderCommandEncoder;
use Metal\Bridge\Bridge;

const PIXEL_FORMAT_RGBA8UNORM = 70;    // MTLPixelFormatRGBA8Unorm, MTLPixelFormat.h:59
const LOAD_ACTION_CLEAR = 2;           // MTLLoadActionClear, MTLRenderPass.h:35
const STORE_ACTION_STORE = 1;          // MTLStoreActionStore, MTLRenderPass.h:40
const USAGE_RENDER_TARGET = 0x0004;    // MTLTextureUsageRenderTarget, MTLTexture.h:102
const STORAGE_MODE_SHARED = 0;         // MTLStorageModeShared, MTLResource.h:84
const RESOURCE_STORAGE_SHARED = 0;     // MTLResourceStorageModeShared = MTLStorageModeShared << 4, MTLResource.h:165,176
const STATUS_COMPLETED = 4;            // MTLCommandBufferStatusCompleted, MTLCommandBuffer.h:61
const PRIMITIVE_TYPE_TRIANGLE = 3;     // MTLPrimitiveTypeTriangle, MTLRenderCommandEncoder.h:32
const FUNCTION_TYPE_VERTEX = 1;        // MTLFunctionTypeVertex, MTLLibrary.h:75
const FUNCTION_TYPE_FRAGMENT = 2;      // MTLFunctionTypeFragment, MTLLibrary.h:76

const SIZE = 64;                       // offscreen texture edge, pixels
const BYTES_PER_ROW = SIZE * 4;        // RGBA8Unorm: 4 bytes per pixel

// The triangle's flat color, and what RGBA8Unorm rounding makes of it.
const TRI = [0.25, 0.5, 0.75, 1.0];
const TRI_BYTES = [64, 128, 191, 255]; // round(c * 255); asserted with +/-1

function fail(string $msg): never { fwrite(STDERR, "PROOF_FAIL: {$msg}\n"); exit(1); }

/** Unwrap the sanctioned {handle, error} return shape. */
function unwrap(array $result, string $what): int
{
    if (($result['handle'] ?? 0) > 0) {
        return (int) $result['handle'];
    }
    $error = (int) ($result['error'] ?? 0);
    $detail = $error > 0 ? (Bridge::errorDescription($error) ?? 'unreadable NSError') : 'no error object';
    fwrite(STDERR, "PROOF_FAIL: {$what} failed: {$detail}\n");
    exit(1);
}

$device = MTLDevice::createSystemDefault();
$device > 0 || fail('no system default Metal device');
echo 'device: ' . MTLDevice::name($device) . "\n";

// ---- 1. compile the shader pair from source ----------------------------

$source = <<<'METAL'
#include <metal_stdlib>
using namespace metal;

struct VertexOut {
    float4 position [[position]];
    float4 color;
};

vertex VertexOut triangle_vertex(uint vid [[vertex_id]],
                                 const device float2 *positions [[buffer(0)]])
{
    VertexOut out;
    out.position = float4(positions[vid], 0.0, 1.0);
    out.color = float4(0.25, 0.5, 0.75, 1.0);
    return out;
}

fragment float4 triangle_fragment(VertexOut in [[stage_in]])
{
    return in.color;
}
METAL;

// options = 0 is nil MTLCompileOptions (that class is not bound this wave).
$library = unwrap(MTLDevice::newLibraryWithSourceOptionsError($device, $source, 0), 'shader compile');

$names = MTLLibrary::functionNames($library);
sort($names);
$names === ['triangle_fragment', 'triangle_vertex']
    || fail('functionNames returned ' . var_export($names, true));

$vertexFn = MTLLibrary::newFunctionWithName($library, 'triangle_vertex');
$fragmentFn = MTLLibrary::newFunctionWithName($library, 'triangle_fragment');
$vertexFn > 0 && $fragmentFn > 0 || fail('shader functions not found in the compiled library');
MTLFunction::name($vertexFn) === 'triangle_vertex' || fail('vertex function name mismatch');
MTLFunction::functionType($vertexFn) === FUNCTION_TYPE_VERTEX || fail('vertex function type mismatch');
MTLFunction::functionType($fragmentFn) === FUNCTION_TYPE_FRAGMENT || fail('fragment function type mismatch');

// ---- 2. pipeline state -------------------------------------------------

$pipelineDesc = MTLRenderPipelineDescriptor::init();
MTLRenderPipelineDescriptor::setLabel($pipelineDesc, 'proof triangle');
MTLRenderPipelineDescriptor::setVertexFunction($pipelineDesc, $vertexFn);
MTLRenderPipelineDescriptor::setFragmentFunction($pipelineDesc, $fragmentFn);
$pipelineAttachments = MTLRenderPipelineDescriptor::colorAttachments($pipelineDesc);
$colorAttachment = MTLRenderPipelineColorAttachmentDescriptorArray::objectAtIndexedSubscript($pipelineAttachments, 0);
MTLRenderPipelineColorAttachmentDescriptor::setPixelFormat($colorAttachment, PIXEL_FORMAT_RGBA8UNORM);
MTLRenderPipelineColorAttachmentDescriptor::setBlendingEnabled($colorAttachment, false);

$pipeline = unwrap(
    MTLDevice::newRenderPipelineStateWithDescriptorError($device, $pipelineDesc),
    'pipeline creation'
);
MTLRenderPipelineState::label($pipeline) === 'proof triangle' || fail('pipeline label did not round-trip');

// ---- 3. vertex buffer --------------------------------------------------

// Clip space: apex top-centre, base along the bottom. The centre pixel is
// inside; every corner of the texture is outside.
$positions = [0.0, 0.9, -0.9, -0.9, 0.9, -0.9];
$vertexBytes = pack('g*', ...$positions); // 'g' = 32-bit float, little-endian
strlen($vertexBytes) === 24 || fail('expected 24 bytes of vertex data, got ' . strlen($vertexBytes));

$vertexBuffer = MTLDevice::newBufferWithBytesLengthOptions($device, $vertexBytes, RESOURCE_STORAGE_SHARED);
$vertexBuffer > 0 || fail('vertex buffer creation failed');
MTLBuffer::length($vertexBuffer) === 24 || fail('buffer length is ' . MTLBuffer::length($vertexBuffer));
MTLBuffer::contentsBytes($vertexBuffer, 0, 24) === $vertexBytes || fail('buffer contents did not round-trip');
MTLBuffer::contentsBytes($vertexBuffer, 16, 16) === '' || fail('out-of-bounds read was not refused');

// ---- 4. render pass into a 64x64 offscreen texture ---------------------

$td = MTLTextureDescriptor::texture2DDescriptorWithPixelFormatWidthHeightMipmapped(
    PIXEL_FORMAT_RGBA8UNORM, SIZE, SIZE, false
);
MTLTextureDescriptor::setUsage($td, USAGE_RENDER_TARGET);
MTLTextureDescriptor::setStorageMode($td, STORAGE_MODE_SHARED);
$texture = MTLDevice::newTextureWithDescriptor($device, $td);
$texture > 0 || fail('texture creation failed');

$pass = MTLRenderPassDescriptor::renderPassDescriptor();
$passAttachments = MTLRenderPassDescriptor::colorAttachments($pass);
$att = MTLRenderPassColorAttachmentDescriptorArray::objectAtIndexedSubscript($passAttachments, 0);
MTLRenderPassAttachmentDescriptor::setTexture($att, $texture);
MTLRenderPassAttachmentDescriptor::setLoadAction($att, LOAD_ACTION_CLEAR);
MTLRenderPassAttachmentDescriptor::setStoreAction($att, STORE_ACTION_STORE);
MTLRenderPassColorAttachmentDescriptor::setClearColor($att, 0.0, 0.0, 0.0, 1.0);

$queue = MTLDevice::newCommandQueue($device);
$cb = MTLCommandQueue::commandBuffer($queue);
$encoder = MTLCommandBuffer::renderCommandEncoderWithDescriptor($cb, $pass);
$encoder > 0 || fail('render encoder creation failed');

MTLRenderCommandEncoder::setRenderPipelineState($encoder, $pipeline);
MTLRenderCommandEncoder::setViewport($encoder, 0.0, 0.0, (float) SIZE, (float) SIZE, 0.0, 1.0);
MTLRenderCommandEncoder::setScissorRect($encoder, 0, 0, SIZE, SIZE);
MTLRenderCommandEncoder::setVertexBufferOffsetAtIndex($encoder, $vertexBuffer, 0, 0);
MTLRenderCommandEncoder::drawPrimitivesVertexStartVertexCount($encoder, PRIMITIVE_TYPE_TRIANGLE, 0, 3);
MTLCommandEncoder::endEncoding($encoder);
MTLCommandBuffer::commit($cb);
MTLCommandBuffer::waitUntilCompleted($cb);

if (MTLCommandBuffer::status($cb) !== STATUS_COMPLETED) {
    $err = MTLCommandBuffer::error($cb);
    fail('command buffer not completed: ' . ($err > 0 ? Bridge::errorDescription($err) : 'no error object'));
}

// ---- 5. read the pixels back and check them ---------------------------

$bytes = MTLTexture::getBytesBytesPerRowFromRegionMipmapLevel(
    $texture, BYTES_PER_ROW, 0, 0, 0, SIZE, SIZE, 1, 0
);
strlen($bytes) === SIZE * BYTES_PER_ROW
    || fail('expected ' . (SIZE * BYTES_PER_ROW) . ' bytes, got ' . strlen($bytes));

/** @return array{0:int,1:int,2:int,3:int} */
function pixel(string $bytes, int $x, int $y): array
{
    return array_values(unpack('C4', substr($bytes, ($y * SIZE + $x) * 4, 4)));
}

$centre = pixel($bytes, SIZE >> 1, SIZE >> 1);
foreach (TRI_BYTES as $i => $want) {
    abs($centre[$i] - $want) <= 1
        || fail("centre pixel channel {$i} = {$centre[$i]}, expected {$want} (+/-1); got " . implode(',', $centre));
}

foreach ([[0, 0], [SIZE - 1, 0]] as [$x, $y]) {
    $corner = pixel($bytes, $x, $y);
    ($corner[0] === 0 && $corner[1] === 0 && $corner[2] === 0 && $corner[3] === 255)
        || fail("corner pixel ({$x},{$y}) = " . implode(',', $corner) . ', expected the black clear');
}

echo 'centre: ' . implode(',', $centre) . ' corner: ' . implode(',', pixel($bytes, 0, 0)) . "\n";
echo "PROOF_TRIANGLE_OK\n";
exit(0);
