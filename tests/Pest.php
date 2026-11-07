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

/** The region's pixels, read through getBytes into an ext-fb buffer of $bytesPerRow × the region's height. */
function textureBytes(MTLTexture $texture, int $bytesPerRow, MTLRegion $region, int $level): string
{
    $buffer = new FbBuffer(new FbFormat(FB_LAYOUT_RGBA8888, channelOrder: FB_CHANNELS_RGBA), intdiv($bytesPerRow, 4), $region->size->height);
    $texture->getBytesBytesPerRowFromRegionMipmapLevel($buffer->pointer(), $bytesPerRow, $region, $level);

    return $buffer->bytes();
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

/** macOS signal numbers a kept refusal's probe dies by. */
const PROBE_SIGBUS = 10;
const PROBE_SIGSEGV = 11;

/**
 * Skips a tests/Probes test unless the loaded ext-metal is a probe build (--enable-metal-probes),
 * the only build where env METAL_PROBE_OFF turns a kept refusal off.
 */
function requireProbeBuild(): void
{
    if (! defined('METAL_PROBES')) {
        test()->markTestSkipped('ext-metal is not a probe build (configure --enable-metal-probes): METAL_PROBES is undefined');
    }
}

/**
 * Runs $code in a child of this PHP with only ext-metal loaded, after a prelude that defines
 * $device, sharedTexture() and renderEncoder(). $siteOff names the kept site METAL_PROBE_OFF
 * turns off, null keeps every site. $gmalloc runs the child under libgmalloc with Zend's
 * allocator off, so a native over-read of PHP memory faults at the guard page.
 *
 * @return array{signal: ?int, stdout: string}
 */
function metalProbe(string $code, ?string $siteOff, bool $gmalloc = false): array
{
    $prelude = <<<'PHP'
    $device = MTLCreateSystemDefaultDevice();
    function sharedTexture(MTLDevice $device): MTLTexture {
        $descriptor = MTLTextureDescriptor::texture2DDescriptorWithPixelFormatWidthHeightMipmapped(MTLPixelFormat::RGBA8_UNORM, 4, 2, false);
        $descriptor->setStorageMode(MTLStorageMode::SHARED);
        $descriptor->setUsage(MTLTextureUsage::SHADER_READ->value | MTLTextureUsage::RENDER_TARGET->value);
        return $device->newTextureWithDescriptor($descriptor);
    }
    function renderEncoder(MTLDevice $device): MTLRenderCommandEncoder {
        $pass = MTLRenderPassDescriptor::renderPassDescriptor();
        $pass->colorAttachments()->objectAtIndexedSubscript(0)->setTexture(sharedTexture($device));
        return $device->newCommandQueue()->commandBuffer()->renderCommandEncoderWithDescriptor($pass);
    }
    PHP;
    $script = "<?php\ndeclare(strict_types=1);\n".$prelude."\ntry {\n".$code."\n} catch (Throwable \$t) {\n    echo 'REFUSED ', get_class(\$t), ': ', \$t->getMessage(), \"\\n\";\n}\necho \"SURVIVED\\n\";\n";
    $file = tempnam(sys_get_temp_dir(), 'metal-probe');
    file_put_contents($file, $script);

    $env = getenv();
    unset($env['METAL_PROBE_OFF'], $env['DYLD_INSERT_LIBRARIES'], $env['USE_ZEND_ALLOC']);
    $env['XDEBUG_MODE'] = 'off';
    if ($siteOff !== null) {
        $env['METAL_PROBE_OFF'] = $siteOff;
    }
    if ($gmalloc) {
        $env['DYLD_INSERT_LIBRARIES'] = '/usr/lib/libgmalloc.dylib';
        $env['USE_ZEND_ALLOC'] = '0';
    }

    $command = [PHP_BINARY, '-n', '-d', 'memory_limit=128M', '-d', 'extension='.ini_get('extension_dir').'/appkit.so', '-d', 'extension='.ini_get('extension_dir').'/metal.so', $file];
    $process = proc_open($command, [0 => ['file', '/dev/null', 'r'], 1 => ['pipe', 'w'], 2 => ['file', '/dev/null', 'w']], $pipes, null, $env);
    $stdout = (string) stream_get_contents($pipes[1]);
    fclose($pipes[1]);
    do {
        $status = proc_get_status($process);
        if ($status['running']) {
            usleep(20_000);
        }
    } while ($status['running']);
    proc_close($process);
    @unlink($file);

    return ['signal' => $status['signaled'] ? $status['termsig'] : null, 'stdout' => $stdout];
}
