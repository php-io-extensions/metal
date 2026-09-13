#!/usr/bin/env php
<?php
/*
 * Negative and positive controls for check-parity.php. Builds a minimal
 * package (one init binding, one setter), generates .zep/optimizers, then
 * asserts PARITY_OK on the good tree and a drift diagnostic on each known
 * failure mode: composite extra send, init with a third send, missing
 * optimizer, extra optimizer, arity mismatch, extra-sources holes, @zep
 * without a prototype, prototype without @zep.
 *
 * Ported from ../../appkit/scripts/tests/parity-guard.php (ns_ -> mtl_,
 * appkit -> metal, NS\NSSample -> MTL\MTLSample; same discipline as the
 * gen-zep.php doc-comment port). All fixture trees use a temp root, so
 * check-parity.php's auto-invoked SDK header audit (added alongside this
 * port — see check-parity.php's `$root === dirname(__DIR__)` guard) never
 * fires against them; only the "real package" run at the top exercises it.
 *
 * Prints PARITY_GUARD_OK only when every scenario behaves.
 */

declare(strict_types=1);

$scriptsDir = dirname(__DIR__);
$packageRoot = dirname($scriptsDir);
$check = $scriptsDir . '/check-parity.php';
$gen = $scriptsDir . '/gen-zep.php';
$failures = [];

function rrmdir(string $dir): void
{
    if (!is_dir($dir)) {
        return;
    }
    $it = new RecursiveIteratorIterator(
        new RecursiveDirectoryIterator($dir, FilesystemIterator::SKIP_DOTS),
        RecursiveIteratorIterator::CHILD_FIRST
    );
    foreach ($it as $file) {
        $file->isDir() ? rmdir($file->getPathname()) : unlink($file->getPathname());
    }
    rmdir($dir);
}

function runPhp(string $script, string $root): array
{
    $cmd = sprintf(
        '%s %s %s 2>&1',
        escapeshellarg(PHP_BINARY),
        escapeshellarg($script),
        escapeshellarg($root)
    );
    $output = [];
    exec($cmd, $output, $code);

    return ['code' => $code, 'text' => implode("\n", $output)];
}

function writeGood(string $tmp): void
{
    mkdir("{$tmp}/src", 0755, true);
    file_put_contents("{$tmp}/config.json", json_encode([
        'namespace' => 'metal',
        'name' => 'metal',
        'extra-sources' => ['src/mtl-sample.m'],
    ], JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES) . "\n");

    file_put_contents("{$tmp}/src/mtl-sample.h", <<<'H'
#ifndef PHP_METAL_MTL_SAMPLE_H
#define PHP_METAL_MTL_SAMPLE_H

#include "php.h"

/*@zep MTL\MTLSample initWithFrame(double x, double y, double w, double h) -> int */
zend_long mtl_mtlsample_init_with_frame(zval *x, zval *y, zval *w, zval *h);
/*@zep MTL\MTLSample setBezelStyle(int handle, int style) -> void */
void mtl_mtlsample_set_bezel_style(zval *handle, zval *style);
/*@reserved MTL\MTLSample - (void)setAttributedTitle:(NSAttributedString *)t */

#endif
H);

    file_put_contents("{$tmp}/src/mtl-sample.m", goodImpl());
}

function goodImpl(): string
{
    return <<<'M'
#include "mtl-sample.h"

zend_long mtl_mtlsample_init_with_frame(zval *x, zval *y, zval *w, zval *h)
{
    NSRect r = NSMakeRect(0, 0, 100, 24);
    id obj = [[MTLSample alloc] initWithFrame:r];
    return (zend_long) (uintptr_t) obj;
}

void mtl_mtlsample_set_bezel_style(zval *handle, zval *style)
{
    zval *argv[2];
    argv[0] = handle;
    argv[1] = style;
    char c = Z_STRVAL_P(style)[0];
    (void) c;
    id obj = (id) (uintptr_t) 0;
    [obj setBezelStyle:1];
}
M;
}

function generate(string $tmp, string $gen): void
{
    $r = runPhp($gen, $tmp);
    if ($r['code'] !== 0 || !str_contains($r['text'], 'GEN_OK')) {
        fwrite(STDERR, "fixture generator failed:\n{$r['text']}\n");
        exit(1);
    }
}

function expectOk(string $label, array $result): void
{
    global $failures;
    if ($result['code'] !== 0 || !str_contains($result['text'], 'PARITY_OK')) {
        $failures[] = "{$label}: expected PARITY_OK, got exit {$result['code']}:\n{$result['text']}";
    }
}

function expectFail(string $label, array $result, string $needle): void
{
    global $failures;
    if ($result['code'] === 0 || str_contains($result['text'], 'PARITY_OK')) {
        $failures[] = "{$label}: expected non-zero without PARITY_OK, got exit {$result['code']}:\n{$result['text']}";
        return;
    }
    if (!str_contains($result['text'], $needle)) {
        $failures[] = "{$label}: failed but diagnostic did not contain '{$needle}':\n{$result['text']}";
    }
}

function freshTree(string $gen): string
{
    $tmp = sys_get_temp_dir() . '/metal-parity-' . bin2hex(random_bytes(4));
    writeGood($tmp);
    generate($tmp, $gen);

    return $tmp;
}

// 0. The real package must already be green (parity AND, since this root is
// the real package root, the auto-invoked audit-headers.php too).
$real = runPhp($check, $packageRoot);
expectOk('real package', $real);

$trees = [];

// 1. Minimal alloc+init + single-send setter (C subscripts must not count).
$good = freshTree($gen);
$trees[] = $good;
expectOk('good fixture', runPhp($check, $good));

// 2. Extra message send on a non-init binding.
$composite = freshTree($gen);
$trees[] = $composite;
file_put_contents("{$composite}/src/mtl-sample.m", str_replace(
    '[obj setBezelStyle:1];',
    "[obj setBezelStyle:1];\n    [obj setEnabled:YES];",
    goodImpl()
));
expectFail('composite extra send', runPhp($check, $composite), 'setEnabled');

// 3. Init binding with a third send (alloc+init+set).
$initExtra = freshTree($gen);
$trees[] = $initExtra;
file_put_contents("{$initExtra}/src/mtl-sample.m", str_replace(
    'id obj = [[MTLSample alloc] initWithFrame:r];',
    "id obj = [[MTLSample alloc] initWithFrame:r];\n    [obj setEnabled:YES];",
    goodImpl()
));
expectFail('init composite', runPhp($check, $initExtra), 'alloc+init');

// 4. Missing optimizer.
$missingOpt = freshTree($gen);
$trees[] = $missingOpt;
$optFile = glob("{$missingOpt}/optimizers/*SetBezelStyleOptimizer.php")[0] ?? null;
if (is_null($optFile)) {
    $failures[] = 'missing-optimizer: could not find generated SetBezelStyle optimizer';
} else {
    unlink($optFile);
    expectFail('missing optimizer', runPhp($check, $missingOpt), 'no optimizer');
}

// 5. Extra optimizer with no zep call.
$extraOpt = freshTree($gen);
$trees[] = $extraOpt;
$donor = glob("{$extraOpt}/optimizers/*Optimizer.php")[0];
$extraSrc = (string) file_get_contents($donor);
$extraSrc = str_replace('mtl_mtlsample_init_with_frame', 'mtl_mtlsample_ghost', $extraSrc);
$extraSrc = str_replace('MtlsampleInitWithFrameOptimizer', 'MtlsampleGhostOptimizer', $extraSrc);
$extraSrc = str_replace('mtlsample_init_with_frame', 'mtlsample_ghost', $extraSrc);
file_put_contents("{$extraOpt}/optimizers/MtlsampleGhostOptimizer.php", $extraSrc);
expectFail('extra optimizer', runPhp($check, $extraOpt), 'no zep call');

// 6. Optimizer arity disagrees with the C prototype.
$arity = freshTree($gen);
$trees[] = $arity;
$optFile = glob("{$arity}/optimizers/*SetBezelStyleOptimizer.php")[0];
$src = (string) file_get_contents($optFile);
$src = preg_replace('/!== 2/', '!== 99', $src, 1);
file_put_contents($optFile, $src);
expectFail('arity mismatch', runPhp($check, $arity), 'arity');

// 7. src/*.m not listed in extra-sources.
$missingSrc = freshTree($gen);
$trees[] = $missingSrc;
file_put_contents("{$missingSrc}/config.json", json_encode([
    'namespace' => 'metal',
    'name' => 'metal',
    'extra-sources' => [],
], JSON_PRETTY_PRINT) . "\n");
expectFail('extra-sources hole', runPhp($check, $missingSrc), 'not in config.json extra-sources');

// 8. extra-sources lists a file that does not exist.
$phantom = freshTree($gen);
$trees[] = $phantom;
file_put_contents("{$phantom}/config.json", json_encode([
    'namespace' => 'metal',
    'name' => 'metal',
    'extra-sources' => ['src/mtl-sample.m', 'src/mtl-ghost.m'],
], JSON_PRETTY_PRINT) . "\n");
expectFail('extra-sources phantom', runPhp($check, $phantom), 'does not exist');

// 9. Prototype with no preceding @zep.
$noZep = freshTree($gen);
$trees[] = $noZep;
$h = (string) file_get_contents("{$noZep}/src/mtl-sample.h");
$h = str_replace(
    "/*@reserved MTL\\MTLSample - (void)setAttributedTitle:(NSAttributedString *)t */\n",
    "void mtl_mtlsample_ghost(zval *handle);\n",
    $h
);
file_put_contents("{$noZep}/src/mtl-sample.h", $h);
expectFail('prototype without @zep', runPhp($check, $noZep), 'no preceding @zep');

// 10. @zep with no following prototype.
$noProto = freshTree($gen);
$trees[] = $noProto;
$h = (string) file_get_contents("{$noProto}/src/mtl-sample.h");
$h = str_replace(
    "/*@reserved MTL\\MTLSample - (void)setAttributedTitle:(NSAttributedString *)t */\n",
    "/*@zep MTL\\MTLSample ghost(int handle) -> void */\n",
    $h
);
file_put_contents("{$noProto}/src/mtl-sample.h", $h);
expectFail('zep without prototype', runPhp($check, $noProto), 'not followed by a parseable C prototype');

foreach ($trees as $dir) {
    rrmdir($dir);
}

if ($failures !== []) {
    foreach ($failures as $f) {
        fwrite(STDERR, "parity-guard: {$f}\n\n");
    }
    exit(1);
}

echo "PARITY_GUARD_OK\n";
