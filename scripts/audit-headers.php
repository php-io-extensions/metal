#!/usr/bin/env php
<?php
/**
 * audit-headers.php — SDK header ↔ binding faithfulness audit.
 *
 * For every class annotated in src/*.h (@zep or @reserved), parse the class's
 * own SDK header and count its declared members:
 *
 *   member count = methods (- and +) + 2 × readwrite properties
 *                + 1 × readonly properties
 *
 * counted across every @interface block *and* every @protocol block for the
 * class in that one header (base interface + same-file categories, or the
 * protocol definition itself — Metal's API objects are protocols). Both are
 * matched by name only: a protocol merely *adopted* by a type (e.g. the
 * `<NSObject>` in an adoption list) contributes nothing unless it is itself
 * the audited class.
 *
 * The audit fails unless bound(@zep) + reserved(@reserved) equals the header
 * member count. `@zep-construct` methods are synthesized inherited designated
 * initializers — they are printed as construct=N and are not part of that
 * sum. A non-exempt class must also have a construction path: an `init*`
 * binding, a class-method factory (no-handle `@zep` returning int), at
 * least one `@zep-construct`, or an `@audit factory` marker (below).
 * Access-only classes (shared/factory objects you never alloc) are listed
 * in ACCESS_ONLY.
 *
 * Protocol-typed values (e.g. Metal's `id<MTLCommandQueue>`) are produced by
 * an instance method on some other, already-constructed class rather than by
 * `alloc`/`init` — that producer method's own `@zep` binding always takes a
 * handle, so it can never satisfy the no-handle-factory rule for the
 * protocol type it returns. A src header may instead declare:
 *
 *   /*@audit factory MTL\Type Producer::method * /
 *
 * which grants Type a construction path iff a `@zep` annotation for the bare
 * class `Producer` with selector `method` exists somewhere in src/*.h and
 * returns either `int` (a plain handle) or — only for a selector whose name
 * ends in `Error`, i.e. the sanctioned NSError** pattern — `array`, whose
 * `{handle, error}` shape still yields the handle. Any other array-returning
 * binding is a plain list and must not pass (e.g. `functionNames`). A marker
 * naming a producer/selector pair with no such binding is a hard failure
 * (a typo'd, dangling or wrong-shaped marker must not silently pass).
 *
 * A class may be declared intentionally partial with a visible
 * marker in its src header:
 *
 *   /*@audit partial NS\NSNotificationCenter observe lives in Bridge * /
 *
 * A partial class must not exceed the header count but may fall short; it is
 * reported as PARTIAL so review can see exactly what is sanctioned.
 *
 * Bridge\* classes are PHP-side glue with no SDK counterpart and are skipped.
 *
 * Known limits (documented, reviewable): both branches of an #if/#else are
 * counted, and members a category adds to this class from a *different*
 * header are out of scope — each class is audited against its own header,
 * matching the one-agent-one-header fan-out. Companion classes that have
 * no `{Class}.h` (e.g. NSSecureTextFieldCell, or a Metal protocol living
 * in its producer's header) are resolved by scanning the framework Headers
 * directory for a real `@interface`/`@protocol Class` *block*; headers
 * that only forward-declare the name are skipped.
 * NS-prefixed types that live in Foundation rather than Metal
 * (e.g. NSNotificationCenter in Foundation/NSNotification.h)
 * resolve via FRAMEWORK_FALLBACK after the Metal search misses.
 *
 * Usage:
 *   php scripts/audit-headers.php [root] [--frameworks DIR]
 *   php scripts/audit-headers.php --count <header.h> <ClassName>
 */

declare(strict_types=1);

const DEFAULT_FRAMEWORKS = '/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks';

/** First namespace segment → SDK framework name. */
const FRAMEWORK_MAP = [
    'MTL' => 'Metal',
    'QuartzCore' => 'QuartzCore',
];

/** Extra frameworks searched when `{Class}.h` is absent from the mapped one. */
const FRAMEWORK_FALLBACK = [
    'MTL' => ['Foundation'],
];

/**
 * Classes you obtain from the system (sharedApplication, screens, events,
 * the default notification center) rather than alloc+init. They are exempt
 * from the construction-path check.
 */
const ACCESS_ONLY = [];

function fail(string $msg): never
{
    fwrite(STDERR, "audit-headers: {$msg}\n");
    exit(1);
}

/** Replace comment and string-literal contents with spaces, keeping newlines. */
function blankCommentsAndStrings(string $src): string
{
    $len = strlen($src);
    $out = $src;
    $i = 0;
    while ($i < $len) {
        $c = $src[$i];
        $n = $i + 1 < $len ? $src[$i + 1] : '';
        if ($c === '/' && $n === '/') {
            while ($i < $len && $src[$i] !== "\n") {
                $out[$i] = ' ';
                $i++;
            }
            continue;
        }
        if ($c === '/' && $n === '*') {
            $out[$i] = $out[$i + 1] = ' ';
            $i += 2;
            while ($i < $len && !($src[$i] === '*' && $i + 1 < $len && $src[$i + 1] === '/')) {
                if ($src[$i] !== "\n") {
                    $out[$i] = ' ';
                }
                $i++;
            }
            if ($i < $len) {
                $out[$i] = ' ';
                if ($i + 1 < $len) {
                    $out[$i + 1] = ' ';
                }
                $i += 2;
            }
            continue;
        }
        if ($c === '"' || $c === "'") {
            $quote = $c;
            $out[$i] = ' ';
            $i++;
            while ($i < $len && $src[$i] !== $quote) {
                if ($src[$i] === '\\' && $i + 1 < $len) {
                    $out[$i] = $out[$i + 1] = ' ';
                    $i += 2;
                    continue;
                }
                if ($src[$i] !== "\n") {
                    $out[$i] = ' ';
                }
                $i++;
            }
            if ($i < $len) {
                $out[$i] = ' ';
                $i++;
            }
            continue;
        }
        $i++;
    }

    return $out;
}

/** Blank preprocessor lines (with backslash continuations), keeping newlines. */
function blankPreprocessor(string $src): string
{
    $lines = explode("\n", $src);
    $inDirective = false;
    foreach ($lines as $k => $line) {
        $isDirective = $inDirective || preg_match('/^\s*#/', $line) === 1;
        if ($isDirective) {
            $inDirective = str_ends_with(rtrim($line, "\r"), '\\');
            $lines[$k] = '';
        }
    }

    return implode("\n", $lines);
}

/**
 * Extract the body of every block introduced by $keyword (`@interface` or
 * `@protocol`) for $class in the header (base declaration and same-file
 * categories), excluding the ivar block.
 *
 * A bare forward declaration (`@protocol Name;`, or a comma list like
 * `@protocol A, B;`) matches the same `$keyword Name` text but opens no
 * block at all — it has no `@end` of its own. Treating it as an opener
 * would close the "block" at the next literal `@end` found anywhere later
 * in the file, which may belong to a completely different, real
 * declaration: a mismatched name discards that swallowed span but leaves
 * the scan offset past the real block (so the real declaration is never
 * matched on its own), and a matching name would merge unrelated leading
 * text into the real body. Real Metal headers do exactly this immediately
 * before the protocol they forward-declare (e.g. MTLCommandQueue.h has
 * `@protocol MTLDevice;` / `@protocol MTLCommandBuffer;` /
 * `@protocol MTLResidencySet;` right before the real
 * `@protocol MTLCommandQueue <NSObject> ... @end`), so forward declarations
 * must be recognized and skipped without ever being treated as openers.
 *
 * @return list<string>
 */
function classBlocks(string $blanked, string $class, string $keyword): array
{
    $blocks = [];
    $offset = 0;
    $len = strlen($blanked);
    $pattern = '/' . preg_quote($keyword, '/') . '\s+([A-Za-z_][A-Za-z0-9_]*)/';
    // A forward declaration's name may be followed by `, Other, Names` before
    // its terminating `;` (e.g. `@protocol A, B, C;`).
    $fwdPattern = '/^(?:\s*,\s*[A-Za-z_][A-Za-z0-9_]*)*\s*;/';
    while (preg_match($pattern, $blanked, $m, PREG_OFFSET_CAPTURE, $offset)) {
        $name = $m[1][0];
        $afterName = $m[0][1] + strlen($m[0][0]);

        if (preg_match($fwdPattern, substr($blanked, $afterName), $fm) === 1) {
            // Forward declaration, not a block opener: resume right after
            // its `;` without ever searching for an `@end`.
            $offset = $afterName + strlen($fm[0]);
            continue;
        }

        $start = $afterName;
        $end = strpos($blanked, '@end', $start);
        if ($end === false) {
            $end = $len;
        }
        $offset = $end + 4;
        if ($name !== $class) {
            continue;
        }
        $body = substr($blanked, $start, $end - $start);

        // Drop the intro (superclass, category parens, protocol list, generics)
        // up to the end of its line; members always start on a later line.
        $introEnd = strpos($body, "\n");
        $body = $introEnd === false ? '' : substr($body, $introEnd);

        // Skip an ivar block if the first non-space char is '{'.
        $trimmed = ltrim($body);
        if ($trimmed !== '' && $trimmed[0] === '{') {
            $bracePos = strpos($body, '{');
            $depth = 0;
            $bodyLen = strlen($body);
            for ($i = $bracePos; $i < $bodyLen; $i++) {
                if ($body[$i] === '{') {
                    $depth++;
                } elseif ($body[$i] === '}') {
                    $depth--;
                    if ($depth === 0) {
                        $body = substr($body, $i + 1);
                        break;
                    }
                }
            }
        }

        $blocks[] = $body;
    }

    return $blocks;
}

/** @return list<string> */
function interfaceBlocks(string $blanked, string $class): array
{
    return classBlocks($blanked, $class, '@interface');
}

/** @return list<string> */
function protocolBlocks(string $blanked, string $class): array
{
    return classBlocks($blanked, $class, '@protocol');
}

/**
 * @return array{methods: int, rw: int, ro: int, expected: int}
 */
function countMembers(string $headerPath, string $class): array
{
    $src = file_get_contents($headerPath);
    if ($src === false) {
        fail("cannot read {$headerPath}");
    }
    $blanked = blankPreprocessor(blankCommentsAndStrings($src));

    $methods = 0;
    $rw = 0;
    $ro = 0;

    $blocks = array_merge(interfaceBlocks($blanked, $class), protocolBlocks($blanked, $class));
    foreach ($blocks as $body) {
        $len = strlen($body);
        $i = 0;
        while ($i < $len) {
            // Seek start of line.
            $lineStart = $i;
            while ($lineStart < $len && ($body[$lineStart] === ' ' || $body[$lineStart] === "\t")) {
                $lineStart++;
            }
            if ($lineStart >= $len) {
                break;
            }
            $c = $body[$lineStart];

            if (($c === '-' || $c === '+')) {
                $methods++;
                $semi = strpos($body, ';', $lineStart);
                $i = $semi === false ? $len : $semi + 1;
            } elseif ($c === '@' && substr($body, $lineStart, 9) === '@property') {
                $semi = strpos($body, ';', $lineStart);
                $decl = substr($body, $lineStart, ($semi === false ? $len : $semi) - $lineStart);
                $attrs = '';
                if (preg_match('/@property\s*\(([^)]*)\)/', $decl, $am)) {
                    $attrs = $am[1];
                }
                if (preg_match('/\breadonly\b/', $attrs)) {
                    $ro++;
                } else {
                    $rw++;
                }
                $i = $semi === false ? $len : $semi + 1;
            } else {
                $nl = strpos($body, "\n", $lineStart);
                $i = $nl === false ? $len : $nl + 1;
            }
        }
    }

    return ['methods' => $methods, 'rw' => $rw, 'ro' => $ro, 'expected' => $methods + 2 * $rw + $ro];
}

function isInitMethodName(string $method): bool
{
    return (bool) preg_match('/^init(With|$|[A-Z])/', $method);
}

/**
 * Collect per-class bound/reserved/construct counts, construction-path
 * flags, and partial markers from src/*.h.
 *
 * @return array{
 *   classes: array<string, array{bound: int, reserved: int, construct: int, hasConstruction: bool}>,
 *   partial: array<string, string>
 * }
 */
function collectAnnotations(string $root): array
{
    $classes = [];
    $partial = [];
    $factoryMarkers = [];
    // bare class name => [selector => return type], for @audit factory lookups.
    $zepBySelector = [];

    foreach (glob("{$root}/src/*.h") ?: [] as $path) {
        foreach (file($path, FILE_IGNORE_NEW_LINES) ?: [] as $line) {
            if (preg_match('#/\*\s*@zep-construct\s+([A-Za-z0-9_\\\\]+)\s+(\w+)\s*\(([^)]*)\)\s*->\s*(\w+)\s*\*/#', $line, $m)) {
                $classPath = $m[1];
                $classes[$classPath]['construct'] = ($classes[$classPath]['construct'] ?? 0) + 1;
                $classes[$classPath]['hasConstruction'] = true;
            } elseif (preg_match('#/\*\s*@zep\s+([A-Za-z0-9_\\\\]+)\s+(\w+)\s*\(([^)]*)\)\s*->\s*(\w+)\s*\*/#', $line, $m)) {
                $classPath = $m[1];
                $method = $m[2];
                $paramSrc = $m[3];
                $returnType = $m[4];
                $classes[$classPath]['bound'] = ($classes[$classPath]['bound'] ?? 0) + 1;
                $hasHandle = preg_match('/\bhandle\b/', $paramSrc) === 1;
                if ($returnType === 'int' && (isInitMethodName($method) || !$hasHandle)) {
                    $classes[$classPath]['hasConstruction'] = true;
                }
                $segments = explode('\\', $classPath);
                $bareClass = (string) end($segments);
                $zepBySelector[$bareClass][$method] = $returnType;
            } elseif (preg_match('#/\*\s*@reserved\s+([A-Za-z0-9_\\\\]+)\s#', $line, $m)) {
                $classes[$m[1]]['reserved'] = ($classes[$m[1]]['reserved'] ?? 0) + 1;
            } elseif (preg_match('#/\*\s*@audit\s+partial\s+([A-Za-z0-9_\\\\]+)\s+(.*?)\s*\*/#', $line, $m)) {
                if (trim($m[2]) === '') {
                    fail("@audit partial for {$m[1]} needs a reason");
                }
                $partial[$m[1]] = $m[2];
            } elseif (preg_match('#/\*\s*@audit\s+factory\s+([A-Za-z0-9_\\\\]+)\s+([A-Za-z_][A-Za-z0-9_]*)::(\w+)\s*\*/#', $line, $m)) {
                $factoryMarkers[$m[1]] = ['producer' => $m[2], 'selector' => $m[3]];
            }
        }
    }

    // Resolved only after every src/*.h line has been scanned: a marker may
    // (and in practice does) appear in the file before the producer's own
    // @zep binding, so the producer index must be complete first.
    foreach ($factoryMarkers as $classPath => $marker) {
        $producer = $marker['producer'];
        $selector = $marker['selector'];
        $returnType = $zepBySelector[$producer][$selector] ?? null;
        // `int` is the plain handle-returning producer. `array` is accepted
        // only for the sanctioned NSError** pattern (binding-rules
        // amendment 3), whose bindings are named for their trailing
        // `error:` out-param: such a producer returns {handle, error} and so
        // still yields this class's handle. Any *other* array-returning
        // binding is a plain list (MTLLibrary::functionNames returns
        // strings, MTLDevice::copyAllDevices would return handles of the
        // wrong type) and must not silently satisfy a construction path.
        $isErrorPattern = $returnType === 'array' && str_ends_with($selector, 'Error');
        if ($returnType !== 'int' && !$isErrorPattern) {
            fail("factory marker for {$classPath} names unbound {$producer}::{$selector}");
        }
        $classes[$classPath]['hasConstruction'] = true;
    }

    return ['classes' => $classes, 'partial' => $partial];
}

function sdkHeaderFor(string $classPath, string $frameworksDir): ?string
{
    $segments = explode('\\', $classPath);
    if ($segments[0] === 'Bridge') {
        return null;
    }
    // An unmapped first segment falls back to itself as the framework name
    // (e.g. fixture namespaces); real MTL/QuartzCore stay explicitly mapped.
    $framework = FRAMEWORK_MAP[$segments[0]] ?? $segments[0];
    $class = end($segments);
    $search = [$framework];
    foreach (FRAMEWORK_FALLBACK[$segments[0]] ?? [] as $extra) {
        if (!in_array($extra, $search, true)) {
            $search[] = $extra;
        }
    }

    $missing = null;
    foreach ($search as $fw) {
        $dir = "{$frameworksDir}/{$fw}.framework/Headers";
        $direct = "{$dir}/{$class}.h";
        if (is_file($direct)) {
            return $direct;
        }
        if (is_null($missing)) {
            $missing = $direct;
        }
        if (!is_dir($dir)) {
            continue;
        }
        // Companion classes/protocols that live in another type's header
        // (e.g. NSSecureTextFieldCell in NSSecureTextField.h,
        // NSNotificationCenter in Foundation/NSNotification.h, or a Metal
        // protocol declared alongside the class that produces it).
        //
        // A *forward declaration* (`@protocol MTLFunction;`) matches the
        // same text as the real declaration but opens no block, and Metal's
        // headers forward-declare each other constantly: MTLFunction is
        // forward-declared in MTLComputeCommandEncoder.h, which sorts
        // before its real home MTLLibrary.h, and the same holds for
        // MTLRenderPipelineState, MTLSamplerState and
        // MTLRenderCommandEncoder. Picking such a header would audit the
        // class against zero members. So a candidate only wins when
        // classBlocks() — which already knows a forward declaration from an
        // opener — actually finds a block in it; a header that merely
        // mentions the name is remembered only as a last resort.
        $mentioned = null;
        foreach (glob("{$dir}/*.h") ?: [] as $candidate) {
            $src = file_get_contents($candidate);
            if ($src === false) {
                continue;
            }
            if (preg_match('/@(?:interface|protocol)\s+' . preg_quote((string) $class, '/') . '\b/', $src) !== 1) {
                continue;
            }
            $blanked = blankPreprocessor(blankCommentsAndStrings($src));
            if (interfaceBlocks($blanked, (string) $class) !== []
                || protocolBlocks($blanked, (string) $class) !== []) {
                return $candidate;
            }
            $mentioned ??= $candidate;
        }
        if (!is_null($mentioned)) {
            return $mentioned;
        }
    }

    return $missing;
}

// ---- main ----

$args = array_slice($argv, 1);

// --count <header.h> <ClassName>: standalone breakdown for one header.
if (($args[0] ?? '') === '--count') {
    $header = $args[1] ?? null;
    $class = $args[2] ?? null;
    if (is_null($header) || is_null($class)) {
        fail('usage: audit-headers.php --count <header.h> <ClassName>');
    }
    if (!is_file($header)) {
        fail("header '{$header}' does not exist");
    }
    $c = countMembers($header, $class);
    echo "{$class} methods={$c['methods']} properties_rw={$c['rw']} properties_ro={$c['ro']} expected={$c['expected']}\n";
    exit(0);
}

$root = dirname(__DIR__);
$frameworksDir = DEFAULT_FRAMEWORKS;
for ($i = 0; $i < count($args); $i++) {
    if ($args[$i] === '--frameworks') {
        $frameworksDir = $args[++$i] ?? fail('--frameworks needs a directory');
    } else {
        $root = rtrim($args[$i], '/');
    }
}
if (!is_dir($root)) {
    fail("root '{$root}' is not a directory");
}
if (!is_dir($frameworksDir)) {
    fail("frameworks dir '{$frameworksDir}' is not a directory");
}

$annotations = collectAnnotations($root);
$failures = 0;
$audited = 0;
$skipped = 0;

ksort($annotations['classes']);
foreach ($annotations['classes'] as $classPath => $counts) {
    $headerPath = sdkHeaderFor($classPath, $frameworksDir);
    if (is_null($headerPath)) {
        $skipped++;
        echo sprintf("%-40s SKIP (glue, no SDK counterpart)\n", $classPath);
        continue;
    }
    if (!is_file($headerPath)) {
        echo sprintf("%-40s FAIL (SDK header missing: %s)\n", $classPath, $headerPath);
        $failures++;
        continue;
    }

    $bound = $counts['bound'] ?? 0;
    $reserved = $counts['reserved'] ?? 0;
    $construct = $counts['construct'] ?? 0;
    $total = $bound + $reserved;
    $segments = explode('\\', $classPath);
    $c = countMembers($headerPath, (string) end($segments));
    $expected = $c['expected'];
    $isPartial = isset($annotations['partial'][$classPath]);
    $accessOnly = in_array($classPath, ACCESS_ONLY, true);
    $hasConstruction = ($counts['hasConstruction'] ?? false) === true;
    $audited++;

    if ($total === $expected) {
        $status = 'OK';
    } elseif ($isPartial && $total < $expected) {
        $status = 'PARTIAL (' . $annotations['partial'][$classPath] . ')';
    } else {
        $status = 'FAIL';
        $failures++;
    }
    if ($status !== 'FAIL' && !$accessOnly && !$hasConstruction) {
        $status = 'FAIL (no construction path)';
        $failures++;
    }
    echo sprintf(
        "%-40s header=%-4d bound=%-4d reserved=%-4d construct=%-4d %s\n",
        $classPath,
        $expected,
        $bound,
        $reserved,
        $construct,
        $status
    );
}

echo "audited={$audited} skipped={$skipped} failures={$failures}\n";
if ($failures > 0) {
    fwrite(STDERR, "audit-headers: {$failures} class(es) out of parity with their SDK headers\n");
    exit(1);
}
echo "AUDIT_OK\n";
