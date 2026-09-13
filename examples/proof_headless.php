<?php
/**
 * Slice-zero headless proof: clear a 4x4 RGBA8Unorm texture to
 * (1.0, 0.0, 0.5, 1.0) through a real render pass and byte-check the
 * readback. No window, no AppKit — runs on any Mac with ext-metal.
 * Exit 0 = proven; exit 1 = failed.
 *
 * Raw enum ints are used deliberately: constants belong to jovian/metal,
 * not the ext. Values verified against the CommandLineTools SDK headers.
 */

use Metal\MTL\MTLDevice\MTLDevice;
use Metal\MTL\MTLTextureDescriptor\MTLTextureDescriptor;
use Metal\MTL\MTLTexture\MTLTexture;
use Metal\MTL\MTLRenderPassDescriptor\MTLRenderPassDescriptor;
use Metal\MTL\MTLRenderPassColorAttachmentDescriptorArray\MTLRenderPassColorAttachmentDescriptorArray;
use Metal\MTL\MTLRenderPassAttachmentDescriptor\MTLRenderPassAttachmentDescriptor;
use Metal\MTL\MTLRenderPassColorAttachmentDescriptor\MTLRenderPassColorAttachmentDescriptor;
use Metal\MTL\MTLCommandQueue\MTLCommandQueue;
use Metal\MTL\MTLCommandBuffer\MTLCommandBuffer;
use Metal\MTL\MTLCommandEncoder\MTLCommandEncoder;
use Metal\Bridge\Bridge;

const PIXEL_FORMAT_RGBA8UNORM = 70; // MTLPixelFormatRGBA8Unorm
const LOAD_ACTION_CLEAR = 2;        // MTLLoadActionClear
const STORE_ACTION_STORE = 1;       // MTLStoreActionStore
const USAGE_RENDER_TARGET = 0x0004; // MTLTextureUsageRenderTarget
const STORAGE_MODE_SHARED = 0;      // MTLStorageModeShared
const STATUS_COMPLETED = 4;         // MTLCommandBufferStatusCompleted

function fail(string $msg): never { fwrite(STDERR, "PROOF_FAIL: {$msg}\n"); exit(1); }

$device = MTLDevice::createSystemDefault();
$device > 0 || fail('no system default Metal device');
echo 'device: ' . MTLDevice::name($device) . "\n";

$td = MTLTextureDescriptor::texture2DDescriptorWithPixelFormatWidthHeightMipmapped(
    PIXEL_FORMAT_RGBA8UNORM, 4, 4, false
);
MTLTextureDescriptor::setUsage($td, USAGE_RENDER_TARGET);
MTLTextureDescriptor::setStorageMode($td, STORAGE_MODE_SHARED);
$texture = MTLDevice::newTextureWithDescriptor($device, $td);
$texture > 0 || fail('texture creation failed');

$pass = MTLRenderPassDescriptor::renderPassDescriptor();
$attachments = MTLRenderPassDescriptor::colorAttachments($pass);
$att = MTLRenderPassColorAttachmentDescriptorArray::objectAtIndexedSubscript($attachments, 0);
MTLRenderPassAttachmentDescriptor::setTexture($att, $texture);
MTLRenderPassAttachmentDescriptor::setLoadAction($att, LOAD_ACTION_CLEAR);
MTLRenderPassAttachmentDescriptor::setStoreAction($att, STORE_ACTION_STORE);
MTLRenderPassColorAttachmentDescriptor::setClearColor($att, 1.0, 0.0, 0.5, 1.0);

$queue = MTLDevice::newCommandQueue($device);
$cb = MTLCommandQueue::commandBuffer($queue);
$encoder = MTLCommandBuffer::renderCommandEncoderWithDescriptor($cb, $pass);
$encoder > 0 || fail('render encoder creation failed');
MTLCommandEncoder::endEncoding($encoder);
MTLCommandBuffer::commit($cb);
MTLCommandBuffer::waitUntilCompleted($cb);

if (MTLCommandBuffer::status($cb) !== STATUS_COMPLETED) {
    $err = MTLCommandBuffer::error($cb);
    fail('command buffer not completed: ' . ($err > 0 ? Bridge::errorDescription($err) : 'no error object'));
}

$bytes = MTLTexture::getBytesBytesPerRowFromRegionMipmapLevel($texture, 16, 0, 0, 0, 4, 4, 1, 0);
strlen($bytes) === 64 || fail('expected 64 bytes, got ' . strlen($bytes));

// RGBA8Unorm little-endian byte order: R, G, B, A per pixel.
// 1.0 -> 255, 0.0 -> 0, 0.5 -> 127 or 128 (rounding), 1.0 -> 255.
for ($i = 0; $i < 64; $i += 4) {
    [$r, $g, $b, $a] = array_values(unpack('C4', substr($bytes, $i, 4)));
    $r === 255 || fail("pixel {$i}: R={$r}, expected 255");
    $g === 0   || fail("pixel {$i}: G={$g}, expected 0");
    ($b === 127 || $b === 128) || fail("pixel {$i}: B={$b}, expected 127|128");
    $a === 255 || fail("pixel {$i}: A={$a}, expected 255");
}

echo "PROOF_HEADLESS_OK\n";
exit(0);
