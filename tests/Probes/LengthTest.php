<?php

declare(strict_types=1);

// Sites metal-bytes-length and metal-shader-bytes-length (outcome 1): Metal copies the length the
// caller gives. A length past the string makes it read past the end of PHP's memory. The child runs
// under libgmalloc, so the over-read faults at the guard page.

beforeEach(fn () => requireProbeBuild());

it('refuses buffer bytes shorter than the length, which Metal reads past (SIGSEGV) without the refusal', function (): void {
    $code = '$device->newBufferWithBytesLengthOptions("ab", 1 << 24, MTLResourceOptions::STORAGE_MODE_SHARED);';

    $kept = metalProbe($code, null, gmalloc: true);
    $off = metalProbe($code, 'metal-bytes-length', gmalloc: true);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: MTLDevice::newBufferWithBytesLengthOptions(): Argument #1 ($bytes) must hold 16777216 bytes, 2 given')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});

it('refuses texture bytes shorter than the region, which Metal reads past (SIGSEGV) without the refusal', function (): void {
    $code = 'sharedTexture($device)->replaceRegionMipmapLevelWithBytesBytesPerRow(new MTLRegion(new MTLOrigin(0, 0, 0), new MTLSize(4, 2, 1)), 0, "xx", 16);';

    $kept = metalProbe($code, null, gmalloc: true);
    $off = metalProbe($code, 'metal-bytes-length', gmalloc: true);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});

it('refuses vertex and fragment bytes shorter than the length, which Metal reads past (SIGSEGV) without the refusal', function (string $method): void {
    $code = "\$encoder = renderEncoder(\$device);\ntry {\n    \$encoder->{$method}('ab', 4096, 0);\n} finally {\n    \$encoder->endEncoding();\n}";

    $kept = metalProbe($code, null, gmalloc: true);
    $off = metalProbe($code, 'metal-shader-bytes-length', gmalloc: true);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('must hold 4096 bytes, 2 given')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
})->with(['setVertexBytesLengthAtIndex', 'setFragmentBytesLengthAtIndex']);
