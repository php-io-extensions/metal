#!/usr/bin/env php
<?php
/**
 * Surgical patches for Zephir's generated ext/config.m4.
 *
 * Zephir lists extra-sources (including *.m) in metal_sources and feeds
 * extra-libs through PHP_EVAL_LIBLINE. PHP_ADD_SOURCES_X has no *.m case,
 * so an Objective-C file gets an empty compile recipe. PHP_EVAL_LIBLINE
 * only understands -l / -L / -pthread, so -framework flags are dropped.
 *
 * This rewriter, given the generated config.m4 and the staged ext/src/*.m
 * files:
 *
 *   1. strips *.m from the metal_sources assignment
 *   2. appends their .lo names to shared_objects_metal after PHP_NEW_EXTENSION
 *   3. inserts PHP_ADD_BUILD_DIR([$ext_builddir/src]) if missing
 *   4. inserts PHP_ADD_MAKEFILE_FRAGMENT if missing
 *   5. replaces PHP_EVAL_LIBLINE(-framework …) with METAL_SHARED_LIBADD=
 *
 * Each patch is verified after the write. Exits non-zero on any miss.
 * Idempotent: a second pass on an already-patched file is a no-op success.
 *
 * Usage: php patch-config-m4.php <ext/config.m4> <ext/src>
 */

declare(strict_types=1);

if ($argc < 3) {
    fwrite(STDERR, "usage: patch-config-m4.php <ext/config.m4> <ext/src>\n");
    exit(2);
}

$m4Path = $argv[1];
$srcDir = rtrim($argv[2], '/');

if (!is_file($m4Path)) {
    fwrite(STDERR, "patch-config-m4: missing {$m4Path}\n");
    exit(1);
}
if (!is_dir($srcDir)) {
    fwrite(STDERR, "patch-config-m4: missing src dir {$srcDir}\n");
    exit(1);
}

$mFiles = glob("{$srcDir}/*.m") ?: [];
sort($mFiles);
$loNames = [];
foreach ($mFiles as $mFile) {
    $loNames[] = 'src/' . basename($mFile, '.m') . '.lo';
}

$content = (string) file_get_contents($m4Path);
$errors = [];
$applied = [];

function fail(string $msg): never
{
    fwrite(STDERR, "patch-config-m4: {$msg}\n");
    exit(1);
}

function note(string $patch, string $status): void
{
    echo "patch-config-m4: {$patch} {$status}\n";
}

/* ------------------------------------------------------------------ 1. strip .m from metal_sources */

if (!preg_match('/^([ \t]*metal_sources=")([^"]*)(")/m', $content, $srcMatch)) {
    fail('metal_sources assignment not found');
}

$sources = $srcMatch[2];
$stripped = preg_replace('/(?:[ \t]*\n[ \t]*|[ \t]+)[^\s"]+\.m\b/', '', $sources);
if (!is_string($stripped)) {
    fail('failed to strip .m tokens from metal_sources');
}
if (preg_match('/\.m\b/', $stripped)) {
    fail("metal_sources still contains .m after strip: {$stripped}");
}

$newAssignment = $srcMatch[1] . $stripped . $srcMatch[3];
$content = preg_replace(
    '/^[ \t]*metal_sources="[^"]*"/m',
    $newAssignment,
    $content,
    1,
    $stripCount
);
if ($stripCount !== 1) {
    fail('could not rewrite metal_sources assignment');
}
$applied[] = 'strip-m';
note('strip-m', $sources === $stripped ? 'already-clean' : 'applied');

/* ------------------------------------------------------------------ 2. append .lo to shared_objects_metal */

if ($loNames !== []) {
    $loLine = "\tshared_objects_metal=\"\$shared_objects_metal " . implode(' ', $loNames) . "\"\n";
    if (!str_contains($content, 'shared_objects_metal=')) {
        if (!preg_match('/^[ \t]*PHP_NEW_EXTENSION\(metal,[^\n]*\n/m', $content, $newExt, PREG_OFFSET_CAPTURE)) {
            fail('PHP_NEW_EXTENSION(metal, …) not found');
        }
        $insertAt = $newExt[0][1] + strlen($newExt[0][0]);
        $content = substr($content, 0, $insertAt) . $loLine . substr($content, $insertAt);
        note('shared_objects', 'applied');
    } else {
        foreach ($loNames as $lo) {
            if (!str_contains($content, $lo)) {
                fail("shared_objects_metal assignment exists but is missing {$lo}");
            }
        }
        note('shared_objects', 'already-present');
    }
    $applied[] = 'shared_objects';
} else {
    note('shared_objects', 'skipped-no-m-files');
}

/* ------------------------------------------------------------------ 3. PHP_ADD_BUILD_DIR for src */

$buildDirNeedle = 'PHP_ADD_BUILD_DIR([$ext_builddir/src])';
if (!str_contains($content, $buildDirNeedle)) {
    $buildDirLine = "\t{$buildDirNeedle}\n";
    if (preg_match('/^[ \t]*PHP_SUBST\(METAL_SHARED_LIBADD\)/m', $content, $subst, PREG_OFFSET_CAPTURE)) {
        $content = substr($content, 0, $subst[0][1]) . $buildDirLine . substr($content, $subst[0][1]);
    } elseif (preg_match('/^[ \t]*PHP_NEW_EXTENSION\(metal,[^\n]*\n/m', $content, $newExt, PREG_OFFSET_CAPTURE)) {
        $insertAt = $newExt[0][1] + strlen($newExt[0][0]);
        $content = substr($content, 0, $insertAt) . $buildDirLine . substr($content, $insertAt);
    } else {
        fail('no insertion point for PHP_ADD_BUILD_DIR(src)');
    }
    note('build-dir-src', 'applied');
} else {
    note('build-dir-src', 'already-present');
}
$applied[] = 'build-dir-src';

/* ------------------------------------------------------------------ 4. PHP_ADD_MAKEFILE_FRAGMENT */

if (!preg_match('/^[ \t]*PHP_ADD_MAKEFILE_FRAGMENT\b/m', $content)) {
    if (str_contains($content, $buildDirNeedle)) {
        $content = str_replace(
            $buildDirNeedle,
            $buildDirNeedle . "\n\tPHP_ADD_MAKEFILE_FRAGMENT",
            $content
        );
    } elseif (preg_match('/^[ \t]*PHP_SUBST\(METAL_SHARED_LIBADD\)/m', $content, $subst, PREG_OFFSET_CAPTURE)) {
        $content = substr($content, 0, $subst[0][1]) . "\tPHP_ADD_MAKEFILE_FRAGMENT\n" . substr($content, $subst[0][1]);
    } else {
        fail('no insertion point for PHP_ADD_MAKEFILE_FRAGMENT');
    }
    note('makefile-fragment', 'applied');
} else {
    note('makefile-fragment', 'already-present');
}
$applied[] = 'makefile-fragment';

/* ------------------------------------------------------------------ 5. PHP_EVAL_LIBLINE(-framework) → METAL_SHARED_LIBADD= */

$frameworkAssign = null;
if (preg_match(
    '/PHP_EVAL_LIBLINE\((-framework[^,)]+),\s*METAL_SHARED_LIBADD\)/',
    $content,
    $evalMatch
)) {
    $libs = trim($evalMatch[1]);
    $frameworkAssign = "\tMETAL_SHARED_LIBADD=\"\$METAL_SHARED_LIBADD {$libs}\"\n";

    $block = preg_replace(
        '/^[ \t]*if ! test "x-framework[^"]*" = "x"; then\n[ \t]*PHP_EVAL_LIBLINE\(-framework[^)]+\)\n[ \t]*fi\n/m',
        $frameworkAssign,
        $content,
        1,
        $blockCount
    );
    if (is_string($block) && $blockCount === 1) {
        $content = $block;
    } else {
        $line = preg_replace(
            '/^[ \t]*PHP_EVAL_LIBLINE\(-framework[^)]+\)\n/m',
            $frameworkAssign,
            $content,
            1,
            $lineCount
        );
        if (!is_string($line) || $lineCount !== 1) {
            fail('found PHP_EVAL_LIBLINE(-framework …) but could not replace it');
        }
        $content = $line;
    }
    note('framework-libadd', 'applied');
    $applied[] = 'framework-libadd';
} elseif (preg_match('/METAL_SHARED_LIBADD="\$METAL_SHARED_LIBADD -framework/', $content)) {
    note('framework-libadd', 'already-present');
    $applied[] = 'framework-libadd';
} else {
    fail('no PHP_EVAL_LIBLINE(-framework …) and no METAL_SHARED_LIBADD= framework assignment');
}

/* ------------------------------------------------------------------ write, then verify each patch */

if (file_put_contents($m4Path, $content) === false) {
    fail("could not write {$m4Path}");
}

$written = (string) file_get_contents($m4Path);

if (!preg_match('/^[ \t]*metal_sources="([^"]*)"/m', $written, $verifySrc)) {
    $errors[] = 'verify strip-m: metal_sources assignment missing after write';
} elseif (preg_match('/\.m\b/', $verifySrc[1])) {
    $errors[] = 'verify strip-m: metal_sources still lists a .m file';
}

if ($loNames !== []) {
    if (!preg_match('/shared_objects_metal=/', $written)) {
        $errors[] = 'verify shared_objects: assignment missing';
    } else {
        foreach ($loNames as $lo) {
            if (!str_contains($written, $lo)) {
                $errors[] = "verify shared_objects: missing {$lo}";
            }
        }
    }
}

if (!str_contains($written, 'PHP_ADD_BUILD_DIR([$ext_builddir/src])')) {
    $errors[] = 'verify build-dir-src: PHP_ADD_BUILD_DIR([$ext_builddir/src]) missing';
}

if (!preg_match('/^[ \t]*PHP_ADD_MAKEFILE_FRAGMENT\b/m', $written)) {
    $errors[] = 'verify makefile-fragment: PHP_ADD_MAKEFILE_FRAGMENT missing';
}

if (preg_match('/PHP_EVAL_LIBLINE\([^)]*-framework/', $written)) {
    $errors[] = 'verify framework-libadd: PHP_EVAL_LIBLINE still receives -framework';
}
if (!preg_match('/METAL_SHARED_LIBADD="\$METAL_SHARED_LIBADD -framework/', $written)) {
    $errors[] = 'verify framework-libadd: METAL_SHARED_LIBADD= assignment missing -framework';
}

if ($errors !== []) {
    foreach ($errors as $e) {
        fwrite(STDERR, "patch-config-m4: {$e}\n");
    }
    exit(1);
}

echo 'PATCHES_OK ' . implode(',', $applied) . "\n";
