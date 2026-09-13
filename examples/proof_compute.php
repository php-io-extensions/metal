<?php
/**
 * Wave B proof: compile an MSL compute kernel at runtime, dispatch it over
 * 64 uints on the GPU and byte-check every result, then exercise the blit
 * encoder — fill, buffer-to-buffer copy, the buffer/texture copy pair, and
 * mipmap generation. No window, no AppKit. Exit 0 = proven; exit 1 = failed.
 *
 * This exercises the whole Wave B surface end to end:
 * MTLDevice::newComputePipelineStateWithFunctionError (the third user of
 * the NSError** pattern), MTLComputePipelineState, MTLCommandBuffer's two
 * new encoder factories, MTLComputeCommandEncoder (both the uniform and
 * the non-uniform dispatch), and MTLBlitCommandEncoder. It also proves the
 * conformance guard lets compute and blit encoder handles through
 * MTLCommandEncoder's endEncoding/label, which they inherit.
 *
 * Raw enum ints are used deliberately: constants belong to jovian/metal,
 * not the ext. Every value below was read out of the CommandLineTools SDK
 * headers (file:line in the comment).
 */

use Metal\MTL\MTLDevice\MTLDevice;
use Metal\MTL\MTLBuffer\MTLBuffer;
use Metal\MTL\MTLLibrary\MTLLibrary;
use Metal\MTL\MTLFunction\MTLFunction;
use Metal\MTL\MTLComputePipelineState\MTLComputePipelineState;
use Metal\MTL\MTLComputeCommandEncoder\MTLComputeCommandEncoder;
use Metal\MTL\MTLBlitCommandEncoder\MTLBlitCommandEncoder;
use Metal\MTL\MTLTextureDescriptor\MTLTextureDescriptor;
use Metal\MTL\MTLCommandQueue\MTLCommandQueue;
use Metal\MTL\MTLCommandBuffer\MTLCommandBuffer;
use Metal\MTL\MTLCommandEncoder\MTLCommandEncoder;
use Metal\Bridge\Bridge;

const RESOURCE_STORAGE_SHARED = 0;  // MTLResourceStorageModeShared = MTLStorageModeShared << 4, MTLResource.h:176,165,84
const STORAGE_MODE_SHARED = 0;      // MTLStorageModeShared, MTLResource.h:84
const STATUS_COMPLETED = 4;         // MTLCommandBufferStatusCompleted, MTLCommandBuffer.h:61
const FUNCTION_TYPE_KERNEL = 3;     // MTLFunctionTypeKernel, MTLLibrary.h:77
const PIXEL_FORMAT_RGBA8UNORM = 70; // MTLPixelFormatRGBA8Unorm, MTLPixelFormat.h:59
const USAGE_SHADER_READ = 0x0001;   // MTLTextureUsageShaderRead, MTLTexture.h:100
const USAGE_RENDER_TARGET = 0x0004; // MTLTextureUsageRenderTarget, MTLTexture.h:102

const N = 64;                       // elements dispatched
const ELEM = 4;                     // bytes per uint
const BYTES = N * ELEM;             // 256
const PARTIAL_N = 50;               // non-uniform grid: deliberately not a multiple of the threadgroup size
const SENTINEL = 0xFFFFFFFF;        // prefill for the non-uniform run's tail

const TEX = 4;                      // mipmapped texture edge, pixels
const TEX_BPR = TEX * 4;            // RGBA8Unorm: 4 bytes per pixel
const TEX_BYTES = TEX * TEX_BPR;    // 64

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

function runAndWait(int $cb, string $what): void
{
    MTLCommandBuffer::commit($cb);
    MTLCommandBuffer::waitUntilCompleted($cb);
    if (MTLCommandBuffer::status($cb) !== STATUS_COMPLETED) {
        $err = MTLCommandBuffer::error($cb);
        fail("{$what}: command buffer not completed: "
            . ($err > 0 ? (Bridge::errorDescription($err) ?? 'unreadable NSError') : 'no error object'));
    }
}

/** @return list<int> */
function readUints(int $buffer, int $count): array
{
    $bytes = MTLBuffer::contentsBytes($buffer, 0, $count * ELEM);
    strlen($bytes) === $count * ELEM
        || fail('readback expected ' . ($count * ELEM) . ' bytes, got ' . strlen($bytes));

    return array_values(unpack('V*', $bytes)); // 'V' = 32-bit unsigned, little-endian
}

$device = MTLDevice::createSystemDefault();
$device > 0 || fail('no system default Metal device');
echo 'device: ' . MTLDevice::name($device) . "\n";

$queue = MTLDevice::newCommandQueue($device);
$queue > 0 || fail('command queue creation failed');

// ---- 1. compile the compute kernel from source -------------------------

$source = <<<'METAL'
#include <metal_stdlib>
using namespace metal;

kernel void double_plus_one(device const uint *in  [[buffer(0)]],
                            device uint       *out [[buffer(1)]],
                            uint gid [[thread_position_in_grid]])
{
    out[gid] = in[gid] * 2u + 1u;
}
METAL;

// options = 0 is nil MTLCompileOptions (that class is still not bound).
$library = unwrap(MTLDevice::newLibraryWithSourceOptionsError($device, $source, 0), 'kernel compile');

$kernelFn = MTLLibrary::newFunctionWithName($library, 'double_plus_one');
$kernelFn > 0 || fail('double_plus_one not found in the compiled library');
MTLFunction::functionType($kernelFn) === FUNCTION_TYPE_KERNEL
    || fail('double_plus_one is not a kernel function');

// ---- 2. compute pipeline state -----------------------------------------

$pipeline = unwrap(
    MTLDevice::newComputePipelineStateWithFunctionError($device, $kernelFn),
    'compute pipeline creation'
);

$maxThreads = MTLComputePipelineState::maxTotalThreadsPerThreadgroup($pipeline);
$execWidth = MTLComputePipelineState::threadExecutionWidth($pipeline);
$maxThreads > 0 || fail('maxTotalThreadsPerThreadgroup is ' . $maxThreads);
$execWidth > 0 || fail('threadExecutionWidth is ' . $execWidth);
$maxThreads >= $execWidth || fail("maxTotalThreadsPerThreadgroup ({$maxThreads}) < threadExecutionWidth ({$execWidth})");
// Created from a bare function, so the SDK leaves the label nil.
MTLComputePipelineState::label($pipeline) === null || fail('unnamed pipeline reported a label');
echo "pipeline: maxTotalThreadsPerThreadgroup={$maxThreads} threadExecutionWidth={$execWidth}\n";

// A threadgroup width that divides N exactly, so the uniform dispatch
// below covers the grid with no remainder.
$groupWidth = $execWidth;
while ($groupWidth > 1 && (N % $groupWidth !== 0 || $groupWidth > $maxThreads)) {
    $groupWidth = intdiv($groupWidth, 2);
}
$groups = intdiv(N, $groupWidth);

// ---- 3. input and output buffers ---------------------------------------

$inputValues = [];
for ($i = 0; $i < N; $i++) {
    $inputValues[] = $i * 7 + 3;
}
$inputBytes = pack('V*', ...$inputValues);
strlen($inputBytes) === BYTES || fail('expected ' . BYTES . ' bytes of input, got ' . strlen($inputBytes));

$inBuffer = MTLDevice::newBufferWithBytesLengthOptions($device, $inputBytes, RESOURCE_STORAGE_SHARED);
$inBuffer > 0 || fail('input buffer creation failed');
MTLBuffer::length($inBuffer) === BYTES || fail('input buffer length is ' . MTLBuffer::length($inBuffer));

$outBuffer = MTLDevice::newBufferWithLengthOptions($device, BYTES, RESOURCE_STORAGE_SHARED);
$outBuffer > 0 || fail('output buffer creation failed');

// ---- 4. uniform dispatch over all 64 elements --------------------------

$cb = MTLCommandQueue::commandBuffer($queue);
$encoder = MTLCommandBuffer::computeCommandEncoder($cb);
$encoder > 0 || fail('compute encoder creation failed');

// The compute encoder conforms to MTLCommandEncoder, so the untyped handle
// passes that protocol's conformance-guarded calls.
MTLCommandEncoder::setLabel($encoder, 'proof compute');
MTLCommandEncoder::label($encoder) === 'proof compute' || fail('compute encoder label did not round-trip');

MTLComputeCommandEncoder::setComputePipelineState($encoder, $pipeline);
MTLComputeCommandEncoder::setBufferOffsetAtIndex($encoder, $inBuffer, 0, 0);
MTLComputeCommandEncoder::setBufferOffsetAtIndex($encoder, $outBuffer, 0, 1);
MTLComputeCommandEncoder::dispatchThreadgroupsThreadsPerThreadgroup(
    $encoder, $groups, 1, 1, $groupWidth, 1, 1
);
MTLCommandEncoder::endEncoding($encoder);
runAndWait($cb, 'uniform dispatch');

$results = readUints($outBuffer, N);
foreach ($inputValues as $i => $v) {
    $want = ($v * 2 + 1) & 0xFFFFFFFF;
    $results[$i] === $want || fail("element {$i}: got {$results[$i]}, expected {$want}");
}
echo "uniform dispatch: {$groups} threadgroup(s) x {$groupWidth} threads, all " . N . " elements exact\n";

// ---- 5. non-uniform dispatch over a partial grid ------------------------

// Prefilled with a sentinel so the untouched tail is provable, not assumed.
$sentinelBytes = pack('V*', ...array_fill(0, N, SENTINEL));
$partialBuffer = MTLDevice::newBufferWithBytesLengthOptions($device, $sentinelBytes, RESOURCE_STORAGE_SHARED);
$partialBuffer > 0 || fail('partial output buffer creation failed');

$cb = MTLCommandQueue::commandBuffer($queue);
$encoder = MTLCommandBuffer::computeCommandEncoder($cb);
$encoder > 0 || fail('second compute encoder creation failed');
MTLComputeCommandEncoder::setComputePipelineState($encoder, $pipeline);
MTLComputeCommandEncoder::setBufferOffsetAtIndex($encoder, $inBuffer, 0, 0);
MTLComputeCommandEncoder::setBufferOffsetAtIndex($encoder, $partialBuffer, 0, 1);
// PARTIAL_N is deliberately not a multiple of $groupWidth: this is the
// non-uniform threadgroup path, which Metal splits into a remainder group.
MTLComputeCommandEncoder::dispatchThreadsThreadsPerThreadgroup(
    $encoder, PARTIAL_N, 1, 1, $groupWidth, 1, 1
);
MTLCommandEncoder::endEncoding($encoder);
runAndWait($cb, 'non-uniform dispatch');

$partial = readUints($partialBuffer, N);
for ($i = 0; $i < N; $i++) {
    $want = $i < PARTIAL_N ? (($inputValues[$i] * 2 + 1) & 0xFFFFFFFF) : SENTINEL;
    $partial[$i] === $want || fail("non-uniform element {$i}: got {$partial[$i]}, expected {$want}");
}
echo 'non-uniform dispatch: ' . PARTIAL_N . " of " . N . " elements written, tail untouched\n";

// ---- 6. blit: fill, copy, and the refused guards ------------------------

$fillBuffer = MTLDevice::newBufferWithLengthOptions($device, TEX_BYTES, RESOURCE_STORAGE_SHARED);
$copyBuffer = MTLDevice::newBufferWithLengthOptions($device, TEX_BYTES, RESOURCE_STORAGE_SHARED);
$guardBuffer = MTLDevice::newBufferWithBytesLengthOptions($device, str_repeat("\x00", TEX_BYTES), RESOURCE_STORAGE_SHARED);
$fillBuffer > 0 && $copyBuffer > 0 && $guardBuffer > 0 || fail('blit buffer creation failed');

$cb = MTLCommandQueue::commandBuffer($queue);
$blit = MTLCommandBuffer::blitCommandEncoder($cb);
$blit > 0 || fail('blit encoder creation failed');
MTLCommandEncoder::setLabel($blit, 'proof blit');
MTLCommandEncoder::label($blit) === 'proof blit' || fail('blit encoder label did not round-trip');

MTLBlitCommandEncoder::fillBufferRangeValue($blit, $fillBuffer, 0, TEX_BYTES, 0xAB);
MTLBlitCommandEncoder::copyFromBufferSourceOffsetToBufferDestinationOffsetSize(
    $blit, $fillBuffer, 0, $copyBuffer, 0, TEX_BYTES
);
// Shared storage needs no sync, but the call must still be a clean no-op.
MTLBlitCommandEncoder::synchronizeResource($blit, $copyBuffer);

// Guards: a value outside uint8_t and a range past the end of the buffer
// are both refused in glue, so nothing is encoded and $guardBuffer stays
// zeroed.
MTLBlitCommandEncoder::fillBufferRangeValue($blit, $guardBuffer, 0, TEX_BYTES, 0x100);
MTLBlitCommandEncoder::fillBufferRangeValue($blit, $guardBuffer, 0, TEX_BYTES + 1, 0x5A);
MTLBlitCommandEncoder::fillBufferRangeValue($blit, $guardBuffer, -1, TEX_BYTES, 0x5A);

MTLCommandEncoder::endEncoding($blit);
runAndWait($cb, 'blit fill and copy');

$filled = MTLBuffer::contentsBytes($fillBuffer, 0, TEX_BYTES);
$copied = MTLBuffer::contentsBytes($copyBuffer, 0, TEX_BYTES);
$expected = str_repeat(chr(0xAB), TEX_BYTES);
$filled === $expected || fail('fillBufferRangeValue did not write 0xAB across the buffer');
$copied === $expected || fail('copyFromBuffer...Size did not reproduce all ' . TEX_BYTES . ' bytes of 0xAB');
MTLBuffer::contentsBytes($guardBuffer, 0, TEX_BYTES) === str_repeat("\x00", TEX_BYTES)
    || fail('a refused fillBufferRangeValue reached the GPU');
echo 'blit: ' . TEX_BYTES . " bytes filled with 0xAB and copied; three bad fills refused in glue\n";

// ---- 7. blit: buffer -> texture -> buffer, and mipmap generation --------

$td = MTLTextureDescriptor::texture2DDescriptorWithPixelFormatWidthHeightMipmapped(
    PIXEL_FORMAT_RGBA8UNORM, TEX, TEX, true
);
MTLTextureDescriptor::setUsage($td, USAGE_SHADER_READ | USAGE_RENDER_TARGET);
MTLTextureDescriptor::setStorageMode($td, STORAGE_MODE_SHARED);
$texture = MTLDevice::newTextureWithDescriptor($device, $td);
$texture > 0 || fail('mipmapped texture creation failed');

// A recognisable, non-uniform payload so a wrong stride or origin shows up.
$payload = '';
for ($i = 0; $i < TEX_BYTES; $i++) {
    $payload .= chr(($i * 5 + 17) & 0xFF);
}
$sourceBuffer = MTLDevice::newBufferWithBytesLengthOptions($device, $payload, RESOURCE_STORAGE_SHARED);
$readbackBuffer = MTLDevice::newBufferWithLengthOptions($device, TEX_BYTES, RESOURCE_STORAGE_SHARED);
$sourceBuffer > 0 && $readbackBuffer > 0 || fail('texture-copy buffer creation failed');

$cb = MTLCommandQueue::commandBuffer($queue);
$blit = MTLCommandBuffer::blitCommandEncoder($cb);
$blit > 0 || fail('second blit encoder creation failed');

MTLBlitCommandEncoder::copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin(
    $blit, $sourceBuffer, 0, TEX_BPR, TEX_BYTES, TEX, TEX, 1, $texture, 0, 0, 0, 0, 0
);
MTLBlitCommandEncoder::copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImage(
    $blit, $texture, 0, 0, 0, 0, 0, TEX, TEX, 1, $readbackBuffer, 0, TEX_BPR, TEX_BYTES
);
MTLBlitCommandEncoder::generateMipmapsForTexture($blit, $texture);
MTLCommandEncoder::endEncoding($blit);
runAndWait($cb, 'buffer/texture blit');

MTLBuffer::contentsBytes($readbackBuffer, 0, TEX_BYTES) === $payload
    || fail('buffer -> texture -> buffer round trip did not reproduce the payload');
echo 'blit: ' . TEX_BYTES . " bytes round-tripped buffer -> texture -> buffer; mipmaps generated\n";

echo "PROOF_COMPUTE_OK\n";
exit(0);
