#!/usr/bin/env php
<?php
/**
 * check-parity.php — mechanical 1:1 binding guard.
 *
 * Proves, and exits non-zero on any drift:
 *
 *   1. Every @zep / @zep-construct annotation has a following C prototype,
 *      and every binding mtl_* prototype (everything in src/*.h except
 *      mtl-value.h) has one of those annotations.
 *   2. Every .zep bare call has an optimizer and vice versa.
 *   3. Emitted arity agrees across .zep signature, optimizer check, and C
 *      prototype (return_value does not count).
 *   4. Every src/*.m is listed in config.json extra-sources, and every
 *      extra-sources entry names a file that exists.
 *   5. Composite guard: a binding .m body may send at most its declared
 *      selector. Sanctioned exceptions: alloc + init... inside init*
 *      bindings (construction glue), and a bounds-check read from
 *      GUARD_SELECTORS (e.g. [t width]/[t height] used only to validate a
 *      region before the declared send — guards-in-glue ruling, not
 *      composition). mtl-bridge.m is glue and is exempt.
 *
 * Prints per-class bound/reserved counts, then PARITY_OK with the three-way
 * zep/optimizer/prototype totals. Header-member audit against the SDK is a
 * separate script (not this one).
 *
 * Optional argv[1]: package root (defaults to the package root). Used by
 * the self-test fixtures.
 */

declare(strict_types=1);

const MARSHALLING_HEADER = 'mtl-value.h';
const GLUE_SOURCE = 'mtl-bridge.m';
const PARAM_TYPES = ['int', 'double', 'bool', 'string', 'var', 'array'];
const RETURN_TYPES = ['int', 'double', 'bool', 'string', 'var', 'array', 'void'];

/**
 * Zero-argument accessor selectors sanctioned as validation-guard reads —
 * a second (or third) send used only to bounds-check inputs before the
 * declared send (e.g. [t width]/[t height] guarding a getBytes: region) is
 * glue, not composition, and does not count toward the composite guard.
 * Guards-in-glue ruling; keep this list narrow and reviewed.
 *
 * `length` joined the list in Wave A: MTLBuffer's contents pointer cannot
 * cross into PHP, so contentsBytes/setContentsBytes memcpy through a
 * window that [b length] is read to validate first.
 */
const GUARD_SELECTORS = ['width', 'height', 'length'];

$errors = [];

function error(string $msg): void
{
    global $errors;
    $errors[] = $msg;
}

function skipWs(string $s, int &$i): void
{
    $len = strlen($s);
    while ($i < $len && ctype_space($s[$i])) {
        $i++;
    }
}

function isIdentStart(string $ch): bool
{
    return $ch !== '' && (ctype_alpha($ch) || $ch === '_');
}

function readIdent(string $s, int &$i): string
{
    $len = strlen($s);
    $start = $i;
    if ($i < $len && isIdentStart($s[$i])) {
        $i++;
        while ($i < $len && (ctype_alnum($s[$i]) || $s[$i] === '_')) {
            $i++;
        }
    }

    return substr($s, $start, $i - $start);
}

function matchingClose(string $s, int $open, string $openCh = '[', string $closeCh = ']'): int
{
    $len = strlen($s);
    $depth = 0;
    for ($i = $open; $i < $len; $i++) {
        if ($s[$i] === $openCh) {
            $depth++;
        } elseif ($s[$i] === $closeCh) {
            $depth--;
            if ($depth === 0) {
                return $i;
            }
        }
    }

    return $len - 1;
}

/**
 * Replace comments and string/char-literal contents with spaces (newlines
 * kept) so later scans can ignore them without a second state machine.
 */
function blankCommentsAndStrings(string $src): string
{
    $len = strlen($src);
    $out = $src;
    $i = 0;
    while ($i < $len) {
        $c = $src[$i];
        $n = $i + 1 < $len ? $src[$i + 1] : '';
        if ($c === '/' && $n === '/') {
            $i += 2;
            while ($i < $len && $src[$i] !== "\n") {
                $out[$i] = ' ';
                $i++;
            }
            continue;
        }
        if ($c === '/' && $n === '*') {
            $out[$i] = ' ';
            $out[$i + 1] = ' ';
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
        if ($c === '@' && $n === '"') {
            $out[$i] = ' ';
            $out[$i + 1] = ' ';
            $i += 2;
            while ($i < $len && $src[$i] !== '"') {
                if ($src[$i] === '\\' && $i + 1 < $len) {
                    $out[$i] = ' ';
                    $out[$i + 1] = ' ';
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
        if ($c === '"' || $c === "'") {
            $quote = $c;
            $out[$i] = ' ';
            $i++;
            while ($i < $len && $src[$i] !== $quote) {
                if ($src[$i] === '\\' && $i + 1 < $len) {
                    $out[$i] = ' ';
                    $out[$i + 1] = ' ';
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

function listFiles(string $dir, string $suffix): array
{
    if (!is_dir($dir)) {
        return [];
    }
    $out = [];
    $it = new RecursiveIteratorIterator(
        new RecursiveDirectoryIterator($dir, FilesystemIterator::SKIP_DOTS)
    );
    foreach ($it as $file) {
        if ($file->isFile() && str_ends_with($file->getFilename(), $suffix)) {
            $out[] = $file->getPathname();
        }
    }
    sort($out);

    return $out;
}

function relativeTo(string $path, string $root): string
{
    $root = rtrim($root, '/') . '/';
    if (str_starts_with($path, $root)) {
        return substr($path, strlen($root));
    }

    return $path;
}

function studly(string $snake): string
{
    return str_replace(' ', '', ucwords(str_replace('_', ' ', $snake)));
}

function isInitMethod(string $method): bool
{
    return (bool) preg_match('/^init(With|$|[A-Z])/', $method);
}

/**
 * True when `$i` points at a `[` that starts an Objective-C message send,
 * not a C subscript, `@(…)`, or `@[…]`.
 */
function isMessageSend(string $s, int $i): bool
{
    if ($i > 0 && $s[$i - 1] === '@') {
        return false;
    }
    $j = $i + 1;
    skipWs($s, $j);
    $len = strlen($s);
    if ($j >= $len) {
        return false;
    }
    while ($j < $len && $s[$j] === '(') {
        $j = matchingClose($s, $j, '(', ')') + 1;
        skipWs($s, $j);
    }
    if ($j >= $len) {
        return false;
    }
    if ($s[$j] === '[') {
        return true;
    }
    if (!isIdentStart($s[$j])) {
        return false;
    }
    readIdent($s, $j);
    while ($j < $len && $s[$j] === '.') {
        $j++;
        readIdent($s, $j);
    }
    skipWs($s, $j);

    return $j < $len && isIdentStart($s[$j]);
}

function selectorHead(string $s, int $open): string
{
    $j = $open + 1;
    $len = strlen($s);
    skipWs($s, $j);
    while ($j < $len && $s[$j] === '(') {
        $j = matchingClose($s, $j, '(', ')') + 1;
        skipWs($s, $j);
    }
    if ($j < $len && $s[$j] === '[') {
        $j = matchingClose($s, $j) + 1;
        skipWs($s, $j);

        return readIdent($s, $j);
    }
    readIdent($s, $j);
    while ($j < $len && $s[$j] === '.') {
        $j++;
        readIdent($s, $j);
    }
    skipWs($s, $j);

    return readIdent($s, $j);
}

/**
 * @return list<string> selector heads in source order
 */
function collectMessageSends(string $body): array
{
    $blank = blankCommentsAndStrings($body);
    $len = strlen($blank);
    $sends = [];
    for ($i = 0; $i < $len; $i++) {
        if ($blank[$i] === '[' && isMessageSend($blank, $i)) {
            $sel = selectorHead($blank, $i);
            if ($sel !== '') {
                $sends[] = $sel;
            }
        }
    }

    return $sends;
}

/**
 * @return array<string, string> symbol → function body (including braces)
 */
function findFunctionBodies(string $src): array
{
    $blank = blankCommentsAndStrings($src);
    $len = strlen($blank);
    $out = [];
    $offset = 0;
    while (($pos = strpos($blank, 'mtl_', $offset)) !== false) {
        $before = $pos;
        while ($before > 0 && ctype_space($blank[$before - 1])) {
            $before--;
        }
        $typeEnd = $before;
        $typeStart = $typeEnd;
        while ($typeStart > 0 && (ctype_alnum($blank[$typeStart - 1]) || $blank[$typeStart - 1] === '_')) {
            $typeStart--;
        }
        $returnType = substr($blank, $typeStart, $typeEnd - $typeStart);
        if (!in_array($returnType, ['zend_long', 'double', 'void'], true)) {
            $offset = $pos + 3;
            continue;
        }

        $i = $pos;
        $symbol = readIdent($blank, $i);
        skipWs($blank, $i);
        if ($i >= $len || $blank[$i] !== '(') {
            $offset = $pos + 3;
            continue;
        }
        $i = matchingClose($blank, $i, '(', ')') + 1;
        skipWs($blank, $i);
        if ($i >= $len || $blank[$i] !== '{') {
            $offset = $pos + 3;
            continue;
        }
        $close = matchingClose($blank, $i, '{', '}');
        $out[$symbol] = substr($src, $i, $close - $i + 1);
        $offset = $close + 1;
    }

    return $out;
}

/**
 * Parse src/*.h @zep/@reserved annotations and C prototypes.
 *
 * @return array{
 *   methods: list<array{classPath: string, method: string, params: int, returnType: string, symbol: string, bareCall: string, header: string, line: int}>,
 *   reserved: array<string, int>,
 * }
 */
function parseHeaders(string $root): array
{
    $methods = [];
    $reserved = [];
    foreach (glob("{$root}/src/*.h") ?: [] as $path) {
        $base = basename($path);
        $lines = file($path, FILE_IGNORE_NEW_LINES);
        if ($lines === false) {
            error("cannot read {$path}");
            continue;
        }
        $total = count($lines);
        $skipMarshalling = $base === MARSHALLING_HEADER;

        for ($i = 0; $i < $total; $i++) {
            $line = $lines[$i];
            $lineNo = $i + 1;
            $rel = 'src/' . $base;

            if (preg_match('#/\*\s*@reserved\s+([A-Za-z0-9_\\\\]+)\s+(.*?)\s*\*/#', $line, $m)) {
                $reserved[$m[1]] = ($reserved[$m[1]] ?? 0) + 1;
                continue;
            }

            if (preg_match('#/\*\s*@zep(?:-construct)?\s+([A-Za-z0-9_\\\\]+)\s+(\w+)\s*\(([^)]*)\)\s*->\s*(\w+)\s*\*/#', $line, $m)) {
                [, $classPath, $method, $paramSrc, $returnType] = $m;
                if (!in_array($returnType, RETURN_TYPES, true)) {
                    error("{$rel}:{$lineNo} unknown return type '{$returnType}'");
                }
                $paramCount = 0;
                if (trim($paramSrc) !== '') {
                    foreach (explode(',', $paramSrc) as $p) {
                        $parts = preg_split('/\s+/', trim($p));
                        if (count($parts) !== 2 || !in_array($parts[0], PARAM_TYPES, true)) {
                            error("{$rel}:{$lineNo} bad parameter '" . trim($p) . "'");
                            continue;
                        }
                        $paramCount++;
                    }
                }

                $proto = null;
                for ($j = $i + 1; $j < $total; $j++) {
                    if (trim($lines[$j]) !== '') {
                        $proto = $lines[$j];
                        $i = $j;
                        break;
                    }
                }
                if (is_null($proto) || !preg_match('/^\s*(zend_long|double|void)\s+(mtl_[a-z0-9_]+)\s*\(([^)]*)\)\s*;/', $proto, $pm)) {
                    error("{$rel}:{$lineNo} @zep for '{$method}' is not followed by a parseable C prototype");
                    continue;
                }
                [, $cReturn, $symbol, $cParamSrc] = $pm;
                $cParams = trim($cParamSrc) === '' || trim($cParamSrc) === 'void'
                    ? []
                    : array_map('trim', explode(',', $cParamSrc));
                $hasReturnValueArg = $cParams !== [] && str_contains($cParams[0], 'return_value');
                $cArity = count($cParams) - ($hasReturnValueArg ? 1 : 0);
                $expectedCReturn = match ($returnType) {
                    'int', 'bool' => 'zend_long',
                    'double' => 'double',
                    default => 'void',
                };
                if ($cReturn !== $expectedCReturn) {
                    error("{$symbol}: @zep return '{$returnType}' expects C '{$expectedCReturn}', found '{$cReturn}'");
                }
                $needsSymbolWrite = in_array($returnType, ['string', 'array', 'var'], true);
                if ($needsSymbolWrite !== $hasReturnValueArg) {
                    error("{$symbol}: @zep return '{$returnType}' "
                        . ($needsSymbolWrite
                            ? 'requires a leading zval *return_value parameter'
                            : 'must not take a return_value parameter'));
                }
                if ($cArity !== $paramCount) {
                    error("{$symbol}: @zep declares {$paramCount} parameter(s), C prototype has {$cArity}");
                }

                $methods[] = [
                    'classPath' => $classPath,
                    'method' => $method,
                    'params' => $paramCount,
                    'returnType' => $returnType,
                    'symbol' => $symbol,
                    'bareCall' => preg_replace('/^mtl_/', '', $symbol),
                    'header' => $rel,
                    'line' => $lineNo,
                    'cArity' => $cArity,
                ];
                continue;
            }

            if (str_contains($line, '@zep')) {
                error("{$rel}:{$lineNo} malformed @zep annotation: {$line}");
                continue;
            }

            if ($skipMarshalling) {
                continue;
            }

            if (preg_match('/^\s*(zend_long|double|void)\s+(mtl_[a-z0-9_]+)\s*\(([^)]*)\)\s*;/', $line, $pm)) {
                $prev = null;
                for ($j = $i - 1; $j >= 0; $j--) {
                    if (trim($lines[$j]) !== '') {
                        $prev = $lines[$j];
                        break;
                    }
                }
                if (is_null($prev) || !preg_match('#/\*\s*@zep(?:-construct)?\s+#', $prev)) {
                    error("{$rel}:{$lineNo} prototype '{$pm[2]}' has no preceding @zep");
                }
            }
        }
    }

    return ['methods' => $methods, 'reserved' => $reserved];
}

/**
 * @return array<string, array{arity: int, file: string}> bareCall → info
 */
function parseZepCalls(string $root): array
{
    $calls = [];
    foreach (listFiles("{$root}/metal", '.zep') as $path) {
        $src = (string) file_get_contents($path);
        $rel = relativeTo($path, $root);
        if (!preg_match_all(
            '/public static function \w+\(([^)]*)\)\s*->\s*\w+\s*\{(.*?)\}/s',
            $src,
            $blocks,
            PREG_SET_ORDER
        )) {
            continue;
        }
        foreach ($blocks as $block) {
            $paramSrc = trim($block[1]);
            $arity = $paramSrc === '' ? 0 : count(array_map('trim', explode(',', $paramSrc)));
            $body = $block[2];
            if (!preg_match('/\b([a-z][a-z0-9_]*)\s*\(/', $body, $cm)) {
                error("{$rel}: static method has no bare call");
                continue;
            }
            $bare = $cm[1];
            if (isset($calls[$bare])) {
                error("duplicate zep bare call '{$bare}' ({$calls[$bare]['file']} and {$rel})");
            }
            $calls[$bare] = ['arity' => $arity, 'file' => $rel];
        }
    }

    return $calls;
}

/**
 * @return array<string, array{arity: int, file: string, symbol: string}> bareCall → info
 */
function parseOptimizers(string $root): array
{
    $opts = [];
    foreach (glob("{$root}/optimizers/*Optimizer.php") ?: [] as $path) {
        $src = (string) file_get_contents($path);
        $rel = relativeTo($path, $root);
        if (!preg_match('/\b(mtl_[a-z0-9_]+)\s*\(/', $src, $sm)) {
            error("{$rel}: optimizer does not call an mtl_* symbol");
            continue;
        }
        $symbol = $sm[1];
        $bare = preg_replace('/^mtl_/', '', $symbol);
        if (!preg_match('/count\(\$expression\[\'parameters\'\]\)\s*!==\s*(\d+)/', $src, $am)) {
            error("{$rel}: optimizer has no arity check against \$expression['parameters']");
            continue;
        }
        $arity = (int) $am[1];
        $expectedClass = studly($bare) . 'Optimizer';
        $base = basename($path, '.php');
        if ($base !== $expectedClass) {
            error("{$rel}: file class/name '{$base}' does not match symbol '{$symbol}' (expected {$expectedClass})");
        }
        if (isset($opts[$bare])) {
            error("duplicate optimizer for '{$bare}' ({$opts[$bare]['file']} and {$rel})");
        }
        $opts[$bare] = ['arity' => $arity, 'file' => $rel, 'symbol' => $symbol];
    }

    return $opts;
}

function checkExtraSources(string $root): int
{
    $configPath = "{$root}/config.json";
    if (!is_file($configPath)) {
        error('config.json is missing');

        return 0;
    }
    $config = json_decode((string) file_get_contents($configPath), true);
    if (!is_array($config)) {
        error('config.json is not valid JSON');

        return 0;
    }
    $listed = $config['extra-sources'] ?? null;
    if (!is_array($listed)) {
        error("config.json has no extra-sources array");
        $listed = [];
    }
    $listed = array_values(array_map('strval', $listed));

    $onDisk = [];
    foreach (glob("{$root}/src/*.m") ?: [] as $path) {
        $onDisk[] = relativeTo($path, $root);
    }
    sort($onDisk);

    foreach ($onDisk as $rel) {
        if (!in_array($rel, $listed, true)) {
            error("{$rel} exists but is not in config.json extra-sources");
        }
    }
    foreach ($listed as $rel) {
        if (!is_file("{$root}/{$rel}")) {
            error("config.json extra-sources lists '{$rel}' but the file does not exist");
        }
    }

    return count($onDisk);
}

function checkComposite(string $root, array $methods): void
{
    $bodies = [];
    $homes = [];
    foreach (glob("{$root}/src/*.m") ?: [] as $path) {
        $rel = relativeTo($path, $root);
        $src = (string) file_get_contents($path);
        foreach (findFunctionBodies($src) as $symbol => $body) {
            if (isset($bodies[$symbol])) {
                error("duplicate definition of {$symbol} in {$rel} (already in {$homes[$symbol]})");
            }
            $bodies[$symbol] = $body;
            $homes[$symbol] = $rel;
        }
    }

    foreach ($methods as $m) {
        $symbol = $m['symbol'];
        if (!isset($bodies[$symbol])) {
            error("{$symbol}: @zep has no function definition in src/*.m");
            continue;
        }
        $home = $homes[$symbol];
        if (basename($home) === GLUE_SOURCE) {
            continue;
        }
        $sends = collectMessageSends($bodies[$symbol]);
        $guarded = array_values(array_filter(
            $sends,
            static fn (string $s): bool => !in_array($s, GUARD_SELECTORS, true)
        ));
        $count = count($guarded);
        if ($count <= 1) {
            continue;
        }
        $listed = implode(', ', $guarded);
        if (isInitMethod($m['method']) && isAllocInitOnly($guarded)) {
            continue;
        }
        if (isInitMethod($m['method'])) {
            error("{$home}: {$symbol} sends [{$listed}] — init bindings may only alloc+init");
        } else {
            error("{$home}: {$symbol} sends [{$listed}] — only the declared selector is allowed (alloc+init excepted in init bindings)");
        }
    }
}

function isAllocInitOnly(array $sends): bool
{
    if (count($sends) !== 2) {
        return false;
    }
    $kinds = [];
    foreach ($sends as $sel) {
        if ($sel === 'alloc') {
            $kinds[] = 'alloc';
        } elseif (isInitMethod($sel)) {
            $kinds[] = 'init';
        } else {
            return false;
        }
    }
    sort($kinds);

    return $kinds === ['alloc', 'init'];
}

// ---- main ----

$root = isset($argv[1]) ? rtrim($argv[1], '/') : dirname(__DIR__);
if (!is_dir($root)) {
    fwrite(STDERR, "check-parity: root '{$root}' is not a directory\n");
    exit(1);
}

$parsed = parseHeaders($root);
$methods = $parsed['methods'];
$reserved = $parsed['reserved'];

if ($methods === []) {
    error('no @zep annotations found in any header');
}

$seenSymbols = [];
$seenMethods = [];
foreach ($methods as $m) {
    if (isset($seenSymbols[$m['symbol']])) {
        error("duplicate C symbol '{$m['symbol']}'");
    }
    $seenSymbols[$m['symbol']] = true;
    $methodKey = $m['classPath'] . '::' . $m['method'];
    if (isset($seenMethods[$methodKey])) {
        error("duplicate method '{$methodKey}'");
    }
    $seenMethods[$methodKey] = true;
}

$zepCalls = parseZepCalls($root);
$optimizers = parseOptimizers($root);
$objcCount = checkExtraSources($root);
checkComposite($root, $methods);

$protoBare = [];
foreach ($methods as $m) {
    $protoBare[$m['bareCall']] = $m;
}

$zepNames = array_keys($zepCalls);
$optNames = array_keys($optimizers);
$protoNames = array_keys($protoBare);
sort($zepNames);
sort($optNames);
sort($protoNames);

foreach (array_diff($zepNames, $optNames) as $bare) {
    error("zep call '{$bare}' has no optimizer");
}
foreach (array_diff($optNames, $zepNames) as $bare) {
    error("optimizer for '{$bare}' has no zep call");
}
foreach (array_diff($protoNames, $zepNames) as $bare) {
    error("C prototype 'mtl_{$bare}' has no zep call");
}
foreach (array_diff($zepNames, $protoNames) as $bare) {
    error("zep call '{$bare}' has no C prototype");
}
foreach (array_diff($protoNames, $optNames) as $bare) {
    error("C prototype 'mtl_{$bare}' has no optimizer");
}
foreach (array_diff($optNames, $protoNames) as $bare) {
    error("optimizer for '{$bare}' has no C prototype");
}

foreach ($protoBare as $bare => $m) {
    $cArity = $m['cArity'];
    if (isset($zepCalls[$bare]) && $zepCalls[$bare]['arity'] !== $cArity) {
        error("{$m['symbol']}: zep arity {$zepCalls[$bare]['arity']} != C arity {$cArity}");
    }
    if (isset($optimizers[$bare]) && $optimizers[$bare]['arity'] !== $cArity) {
        error("{$m['symbol']}: optimizer arity {$optimizers[$bare]['arity']} != C arity {$cArity}");
    }
}

$byClass = [];
foreach ($methods as $m) {
    $byClass[$m['classPath']]['bound'] = ($byClass[$m['classPath']]['bound'] ?? 0) + 1;
}
foreach ($reserved as $classPath => $count) {
    $byClass[$classPath]['reserved'] = $count;
}
ksort($byClass);
foreach ($byClass as $classPath => $info) {
    $bound = $info['bound'] ?? 0;
    $res = $info['reserved'] ?? 0;
    echo sprintf("%-40s bound=%-4d reserved=%-4d\n", $classPath, $bound, $res);
}

$zepCount = count($zepCalls);
$optCount = count($optimizers);
$protoCount = count($protoBare);
echo "zep_calls={$zepCount} optimizers={$optCount} prototypes={$protoCount} extra_sources={$objcCount}\n";

if ($errors !== []) {
    foreach ($errors as $e) {
        fwrite(STDERR, "parity: {$e}\n");
    }
    fwrite(STDERR, 'parity: ' . count($errors) . " drift(s)\n");
    exit(1);
}

if ($zepCount !== $optCount || $optCount !== $protoCount) {
    fwrite(STDERR, "parity: count mismatch zep={$zepCount} optimizers={$optCount} prototypes={$protoCount}\n");
    exit(1);
}

echo "PARITY_OK\n";

// One command enforces parity + audit (spec §11 intent): once parity itself
// is proven, run the SDK header audit too. Only against the real package
// tree, though — a custom argv[1] root (the self-test fixtures' temp trees,
// e.g. scripts/tests/parity-guard.php) has no real SDK counterpart to audit
// against, so those stay parity-only.
if ($root === dirname(__DIR__)) {
    $auditScript = __DIR__ . '/audit-headers.php';
    passthru('php ' . escapeshellarg($auditScript), $auditExit);
    if ($auditExit !== 0) {
        exit($auditExit);
    }
}
