<?php

declare(strict_types=1);

// Sites metal-vertex-buffer-index, metal-shader-bytes-index, metal-fragment-texture-index and
// metal-fragment-sampler-index (outcome 1): a negative index reaches Metal as NSUIntegerMax, and the
// render encoder writes its binding table at that index. An index past Metal's limit but positive
// (1000) does not crash; only the wrapped one does.

beforeEach(fn () => requireProbeBuild());

it('refuses a negative binding index, which the render encoder writes out of bounds with (SIGSEGV) without the refusal', function (string $call, string $site, string $message): void {
    $code = "\$encoder = renderEncoder(\$device);\ntry {\n    {$call};\n} finally {\n    \$encoder->endEncoding();\n}";

    $kept = metalProbe($code, null);
    $off = metalProbe($code, $site);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: '.$message)
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
})->with([
    'vertex buffer' => ['$encoder->setVertexBufferOffsetAtIndex($device->newBufferWithLengthOptions(16, MTLResourceOptions::STORAGE_MODE_SHARED), 0, -1)', 'metal-vertex-buffer-index', 'MTLRenderCommandEncoder::setVertexBufferOffsetAtIndex(): Argument #3 ($index) must be greater than or equal to 0'],
    'vertex bytes' => ['$encoder->setVertexBytesLengthAtIndex("abcd", 4, -1)', 'metal-shader-bytes-index', 'MTLRenderCommandEncoder::setVertexBytesLengthAtIndex(): Argument #3 ($index) must be greater than or equal to 0'],
    'fragment bytes' => ['$encoder->setFragmentBytesLengthAtIndex("abcd", 4, -1)', 'metal-shader-bytes-index', 'MTLRenderCommandEncoder::setFragmentBytesLengthAtIndex(): Argument #3 ($index) must be greater than or equal to 0'],
    'fragment texture' => ['$encoder->setFragmentTextureAtIndex(sharedTexture($device), -1)', 'metal-fragment-texture-index', 'MTLRenderCommandEncoder::setFragmentTextureAtIndex(): Argument #2 ($index) must be greater than or equal to 0'],
    'fragment sampler' => ['$encoder->setFragmentSamplerStateAtIndex(null, -1)', 'metal-fragment-sampler-index', 'MTLRenderCommandEncoder::setFragmentSamplerStateAtIndex(): Argument #2 ($index) must be greater than or equal to 0'],
]);
