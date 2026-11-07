<?php

declare(strict_types=1);

// Sites metal-null-address and metal-destination-null-address (outcome 1): Metal reads from, or
// writes to, the address it is given. Address 0 makes it dereference NULL.

beforeEach(fn () => requireProbeBuild());

it('refuses address 0 as buffer bytes, which Metal reads (SIGSEGV) without the refusal', function (): void {
    $code = '$device->newBufferWithBytesLengthOptions(0, 64, MTLResourceOptions::STORAGE_MODE_SHARED);';

    $kept = metalProbe($code, null);
    $off = metalProbe($code, 'metal-null-address');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: MTLDevice::newBufferWithBytesLengthOptions(): Argument #1 ($bytes) must not be a null address')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});

it('refuses address 0 as texture bytes, which Metal reads (SIGSEGV) without the refusal', function (): void {
    $code = 'sharedTexture($device)->replaceRegionMipmapLevelWithBytesBytesPerRow(new MTLRegion(new MTLOrigin(0, 0, 0), new MTLSize(4, 2, 1)), 0, 0, 16);';

    $kept = metalProbe($code, null);
    $off = metalProbe($code, 'metal-null-address');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: MTLTexture::replaceRegionMipmapLevelWithBytesBytesPerRow(): Argument #3 ($bytes) must not be a null address')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});

it('refuses address 0 as the getBytes destination, which Metal writes (SIGSEGV) without the refusal', function (): void {
    $code = 'sharedTexture($device)->getBytesBytesPerRowFromRegionMipmapLevel(0, 16, new MTLRegion(new MTLOrigin(0, 0, 0), new MTLSize(4, 2, 1)), 0);';

    $kept = metalProbe($code, null);
    $off = metalProbe($code, 'metal-destination-null-address');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError: MTLTexture::getBytesBytesPerRowFromRegionMipmapLevel(): Argument #1 ($pixelBytes) must not be a null address')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});
