#!/usr/bin/env php
<?php
declare(strict_types=1);
// Negative-control test for protocol counting + @audit factory.
// Runs audit-headers.php against fixtures; exits non-zero on any failure.

$root = dirname(__DIR__, 2);
$fixtures = __DIR__ . '/fixtures';

function runAudit(string $srcDir, string $frameworks): array
{
    global $root;
    $cmd = sprintf(
        'php %s %s --frameworks %s 2>&1',
        escapeshellarg("$root/scripts/audit-headers.php"),
        escapeshellarg($srcDir),
        escapeshellarg($frameworks)
    );
    exec($cmd, $out, $code);
    return [$code, implode("\n", $out)];
}

function runCount(string $header, string $class): array
{
    global $root;
    $cmd = sprintf(
        'php %s --count %s %s 2>&1',
        escapeshellarg("$root/scripts/audit-headers.php"),
        escapeshellarg($header),
        escapeshellarg($class)
    );
    exec($cmd, $out, $code);
    return [$code, implode("\n", $out)];
}

// Fixture framework dir: fixtures/Frameworks/Fake.framework/Headers/FakeProto.h
$fw = "$fixtures/Frameworks";
$fakeProtoHeader = "$fw/Fake.framework/Headers/FakeProto.h";

// Regression: bare forward declarations (`@protocol FakeQueue;`,
// `@protocol FakeChild, FakeSibling;`, `@class FakeMaker;`) sit immediately
// before the real blocks in the fixture header, mirroring MTLCommandQueue.h
// (forward decls right before the real @protocol). classBlocks() must not
// treat those as block openers — a self-referencing forward decl is the
// worst case, since it matches the audited class name and can swallow the
// real block that follows.
[$code, $out] = runCount($fakeProtoHeader, 'FakeQueue');
if ($code !== 0 || !str_contains($out, 'expected=4')) {
    fwrite(STDERR, "FAIL: forward declarations corrupted FakeQueue's count, got:\n$out\n");
    exit(1);
}
[$code, $out] = runCount($fakeProtoHeader, 'FakeMaker');
if ($code !== 0 || !str_contains($out, 'expected=1')) {
    fwrite(STDERR, "FAIL: forward declarations corrupted FakeMaker's count, got:\n$out\n");
    exit(1);
}

// 1. Good src: protocol fully bound+reserved, factory marker present -> PASS
[$code, $out] = runAudit("$fixtures/src-good", $fw);
if ($code !== 0) {
    fwrite(STDERR, "FAIL: good fixture should pass, got:\n$out\n");
    exit(1);
}
if (!str_contains($out, 'FakeQueue')) {
    fwrite(STDERR, "FAIL: audit did not report the protocol class\n$out\n");
    exit(1);
}
// Companion resolution must skip headers that only forward-declare the
// class. FakeAliases.h holds nothing but `@protocol FakeQueue;` and sorts
// before FakeProto.h, mirroring MTLFunction (forward-declared in
// MTLComputeCommandEncoder.h, really declared in MTLLibrary.h). Resolving
// to the forward-decl header would audit FakeQueue against header=0.
if (!preg_match('/FakeQueue\s+header=4\b/', $out)) {
    fwrite(STDERR, "FAIL: FakeQueue resolved to a forward-declaration-only header, got:\n$out\n");
    exit(1);
}

// 2. Bad src: same binding but no @audit factory and no init -> FAIL expected
[$code, $out] = runAudit("$fixtures/src-bad-nofactory", $fw);
if ($code === 0) {
    fwrite(STDERR, "FAIL: missing-construction fixture should fail\n$out\n");
    exit(1);
}

// 3. A factory marker may name an NSError**-pattern producer (selector ends
// in `Error`, returns the {handle, error} array) — that still yields the
// class's handle, and it is the only construction path MTLLibrary and
// MTLRenderPipelineState have.
[$code, $out] = runAudit("$fixtures/src-good-errorfactory", $fw);
if ($code !== 0) {
    fwrite(STDERR, "FAIL: NSError**-pattern factory marker should satisfy construction, got:\n$out\n");
    exit(1);
}

// 4. ...but any *other* array-returning producer must not. A plain list
// (functionNames and friends) yields no handle of the audited class, and
// before the acceptance was narrowed to `…Error` selectors such a marker
// passed silently.
[$code, $out] = runAudit("$fixtures/src-bad-arrayfactory", $fw);
if ($code === 0) {
    fwrite(STDERR, "FAIL: non-Error array producer should not satisfy a factory marker\n$out\n");
    exit(1);
}
if (!str_contains($out, 'FakeMaker::queueNames')) {
    fwrite(STDERR, "FAIL: array-factory rejection did not name the offending producer, got:\n$out\n");
    exit(1);
}

echo "AUDIT_PROTOCOL_OK\n";
