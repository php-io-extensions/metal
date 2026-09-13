<?php
/**
 * Slice-zero windowed proof: an ext-appkit NSWindow/NSView hosts a
 * CAMetalLayer created by THIS extension; we clear-and-present ~120
 * frames of an animated color. Requires ext-appkit >= the point release
 * that adds Bridge::adopt (spec §7 named prerequisite). Until then this
 * script exits 2 with a clear message — that is expected, not a failure
 * of this repo.
 */

if (!extension_loaded('appkit')) {
    fwrite(STDERR, "SKIP: ext-appkit not loaded\n");
    exit(2);
}
if (!method_exists('AppKit\\Bridge\\Bridge', 'adopt')) {
    fwrite(STDERR, "SKIP: ext-appkit has no Bridge::adopt yet (spec §7 prerequisite)\n");
    exit(2);
}

use Metal\MTL\MTLDevice\MTLDevice;
use Metal\MTL\MTLCommandQueue\MTLCommandQueue;
use Metal\MTL\MTLCommandBuffer\MTLCommandBuffer;
use Metal\MTL\MTLCommandEncoder\MTLCommandEncoder;
use Metal\MTL\MTLRenderPassDescriptor\MTLRenderPassDescriptor;
use Metal\MTL\MTLRenderPassColorAttachmentDescriptorArray\MTLRenderPassColorAttachmentDescriptorArray;
use Metal\MTL\MTLRenderPassAttachmentDescriptor\MTLRenderPassAttachmentDescriptor;
use Metal\MTL\MTLRenderPassColorAttachmentDescriptor\MTLRenderPassColorAttachmentDescriptor;
use Metal\QuartzCore\CAMetalLayer\CAMetalLayer;
use Metal\QuartzCore\CAMetalDrawable\CAMetalDrawable;
use Metal\Bridge\Bridge as MetalBridge;
use AppKit\NS\NSApplication\NSApplication;
use AppKit\NS\NSWindow\NSWindow;
use AppKit\NS\NSView\NSView;
use AppKit\Bridge\Bridge as AppKitBridge;

const PIXEL_FORMAT_BGRA8UNORM = 80; // verify per Task 8 discipline
const LOAD_ACTION_CLEAR = 2;
const STORE_ACTION_STORE = 1;

$app = NSApplication::sharedApplication();
$win = NSWindow::initWithContentRectStyleMaskBackingDefer(100.0, 100.0, 400.0, 300.0, 15, 2, false);
NSWindow::setTitle($win, 'ext-metal proof_view');
$view = NSView::initWithFrame(0.0, 0.0, 400.0, 300.0);
NSWindow::setContentView($win, $view);

$device = MTLDevice::createSystemDefault();
$layer = CAMetalLayer::init();
CAMetalLayer::setDevice($layer, $device);
CAMetalLayer::setPixelFormat($layer, PIXEL_FORMAT_BGRA8UNORM);
CAMetalLayer::setDrawableSize($layer, 800.0, 600.0);

// The seam: metal pointer bits -> appkit adoption -> NSView layer-backing.
$layerPtr = MetalBridge::pointerOf($layer);
$appkitLayer = AppKitBridge::adopt('CAMetalLayer', $layerPtr);
NSView::setWantsLayer($view, true);
NSView::setLayer($view, $appkitLayer);

NSWindow::makeKeyAndOrderFront($win, 0);

$queue = MTLDevice::newCommandQueue($device);
$skipped = 0;
const MAX_SKIPPED_FRAMES = 10;
const TOTAL_FRAMES = 120;
for ($frame = 0; $frame < TOTAL_FRAMES; $frame++) {
    $drawable = CAMetalLayer::nextDrawable($layer);
    if ($drawable === 0) { $skipped++; usleep(8000); continue; }
    $texture = CAMetalDrawable::texture($drawable);
    $pass = MTLRenderPassDescriptor::renderPassDescriptor();
    $atts = MTLRenderPassDescriptor::colorAttachments($pass);
    $att = MTLRenderPassColorAttachmentDescriptorArray::objectAtIndexedSubscript($atts, 0);
    MTLRenderPassAttachmentDescriptor::setTexture($att, $texture);
    MTLRenderPassAttachmentDescriptor::setLoadAction($att, LOAD_ACTION_CLEAR);
    MTLRenderPassAttachmentDescriptor::setStoreAction($att, STORE_ACTION_STORE);
    $t = $frame / 120.0;
    MTLRenderPassColorAttachmentDescriptor::setClearColor($att, $t, 0.2, 1.0 - $t, 1.0);
    $cb = MTLCommandQueue::commandBuffer($queue);
    $enc = MTLCommandBuffer::renderCommandEncoderWithDescriptor($cb, $pass);
    MTLCommandEncoder::endEncoding($enc);
    MTLCommandBuffer::presentDrawable($cb, $drawable);
    MTLCommandBuffer::commit($cb);
    AppKitBridge::pump(0.0);

    // Release every handle acquired this frame — a per-frame loop that
    // does not release leaks one retain per frame per handle (see
    // .okf/bridge.md's "release what you acquire in per-frame loops" note,
    // and .okf/traps/layer-pointer-seam.md for the pointer-seam half of
    // this discipline).
    MetalBridge::release($drawable);
    MetalBridge::release($texture);
    MetalBridge::release($pass);
    MetalBridge::release($atts);
    MetalBridge::release($att);
    MetalBridge::release($cb);
    MetalBridge::release($enc);

    usleep(16000);
}

if ($skipped > MAX_SKIPPED_FRAMES) {
    fwrite(STDERR, "PROOF_VIEW_FAIL: {$skipped}/" . TOTAL_FRAMES . " frames skipped (nextDrawable returned 0), exceeds the " . MAX_SKIPPED_FRAMES . "-frame budget\n");
    exit(1);
}

echo "PROOF_VIEW_OK\n";
exit(0);
