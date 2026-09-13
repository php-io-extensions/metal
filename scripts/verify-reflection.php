<?php
/*
 * Verifies the *installed* extension against the annotations it was generated
 * from. check-parity.php compares source artefacts to each other and
 * audit-headers.php compares them to the SDK headers; neither loads the .so.
 * This script reflects every class in the loaded extension and asserts the
 * exposed method count equals the @zep + @zep-construct count for that class.
 *
 * Run: php scripts/verify-reflection.php   (extension must be enabled)
 */

declare(strict_types=1);

$root = dirname(__DIR__);

if (!extension_loaded('metal')) {
    fwrite(STDERR, "verify-reflection: the metal extension is not loaded\n");
    exit(1);
}

/* ---- expected counts: one entry per class, from the .h annotations ---- */
$expected = [];
foreach (glob($root . '/src/*.h') as $header) {
    foreach (file($header) as $line) {
        if (preg_match('#/\*\s*@zep(?:-construct)?\s+([A-Za-z0-9_\\\\]+)\s+\w+\s*\(#', $line, $m)) {
            $expected[$m[1]] = ($expected[$m[1]] ?? 0) + 1;
        }
    }
}

if ($expected === []) {
    fwrite(STDERR, "verify-reflection: no @zep annotations found under src/\n");
    exit(1);
}

/* ---- class paths map to FQNs via the generated .zep namespace + class ---- */
$fqnFor = [];
$zepFiles = new RecursiveIteratorIterator(new RecursiveDirectoryIterator($root . '/metal'));
foreach ($zepFiles as $file) {
    if ($file->getExtension() !== 'zep') {
        continue;
    }
    $src = file_get_contents($file->getPathname());
    if (preg_match('/namespace\s+([A-Za-z0-9_\\\\]+);/', $src, $ns)
        && preg_match('/^class\s+(\w+)/m', $src, $cls)) {
        // NS\NSButton\NSButton and Bridge\Bridge both annotate as
        // <path>\<class>, but the .zep namespace repeats the class only for
        // the NS\* classes, so register the path with and without it.
        $classPath = preg_replace('/^Metal\\\\/', '', $ns[1]);
        $fqn = $ns[1] . '\\' . $cls[1];
        $fqnFor[$classPath] = $fqn;
        $fqnFor[$classPath . '\\' . $cls[1]] = $fqn;
    }
}

$failures = 0;
ksort($expected);
foreach ($expected as $classPath => $count) {
    $fqn = $fqnFor[$classPath] ?? null;

    if (is_null($fqn)) {
        printf("%-48s NO .zep FOUND\n", $classPath);
        $failures++;
        continue;
    }

    if (!class_exists($fqn)) {
        printf("%-48s MISSING FROM EXTENSION (%s)\n", $classPath, $fqn);
        $failures++;
        continue;
    }

    $actual = count((new ReflectionClass($fqn))->getMethods());
    $ok = $actual === $count;
    printf(
        "%-48s annotated=%-5d reflected=%-5d %s\n",
        $classPath,
        $count,
        $actual,
        $ok ? 'OK' : 'MISMATCH'
    );
    if (!$ok) {
        $failures++;
    }
}

printf("classes=%d failures=%d\n", count($expected), $failures);

if ($failures > 0) {
    fwrite(STDERR, "REFLECTION_FAILED ({$failures})\n");
    exit(1);
}
echo "REFLECTION_OK\n";
