<?php

declare(strict_types=1);

/*
 * The support list: every method and property accessor that the SDK's Metal headers declare on a
 * class, a category or a protocol, the Metal classes of QuartzCore (CAMetalLayer, CAMetalDrawable,
 * CAEDRMetadata, CAMetalDisplayLink), and Metal's C functions, marked bound when a stub declares the
 * PHP method or function its naming rule gives (selector parts joined).
 *
 *   php84 scripts/support.php           writes SUPPORT.md and the README badge
 *   php84 scripts/support.php --check   exits 1 when either differs (the date is not compared)
 *
 * The headers are read through clang's AST dump of the macOS SDK (15.4 is this extension's floor).
 * Metal's objects are protocols (id<MTLDevice>), so protocol methods are members, unlike AppKit's.
 * A member is not deprecated or unavailable on macOS. A method a stub declares on a protocol that
 * adopts the declaring one (MTLRenderCommandEncoder's label, from MTLCommandEncoder) counts for it.
 */

const SUPPORT_LABEL = 'Metal API';
const SUPPORT_MEASURED = [
    '/Metal.framework/Headers/',
    '/QuartzCore.framework/Headers/CAMetalLayer.h',
    '/QuartzCore.framework/Headers/CAEDRMetadata.h',
    '/QuartzCore.framework/Headers/CAMetalDisplayLink.h',
];

/** A header this list measures. */
function support_measured(string $file): bool
{
    foreach (SUPPORT_MEASURED as $part) {
        if (str_contains($file, $part)) {
            return true;
        }
    }

    return false;
}

/**
 * @return array<string, list<string>> class or protocol ('functions' for C functions) => sorted keys,
 *                                     -[Owner sel] / +[Owner sel] / function name
 */
function support_counted(string $ast): array
{
    $counted = [];
    foreach (support_owners($ast) as $owner) {
        if ($owner['class'] === null || $owner['deprecated']) {
            continue;
        }
        $hidden = [];
        foreach ($owner['properties'] as $property) {
            if ($property['deprecated']) {
                $hidden[$property['getter']] = true;
                $hidden[$property['setter']] = true;
            }
        }
        foreach ($owner['methods'] as $method) {
            if (! $method['measured'] || $method['deprecated'] || isset($hidden[$method['selector']])) {
                continue;
            }
            $counted[$owner['class']][] = "{$method['sign']}[{$owner['class']} {$method['selector']}]";
        }
    }
    foreach (support_c_functions($ast) as $function) {
        $counted['functions'][] = $function;
    }
    foreach ($counted as &$keys) {
        $keys = array_values(array_unique($keys));
        sort($keys, SORT_STRING);
    }
    unset($keys);
    ksort($counted, SORT_STRING);

    return $counted;
}

/**
 * A property whose getter is renamed (`getter=isDepthWriteEnabled`) binds under the property's name:
 * class or protocol => lowercased property name => the getter's key.
 * @return array<string, array<string, string>>
 */
function support_property_names(string $ast): array
{
    $names = [];
    foreach (support_owners($ast) as $owner) {
        if ($owner['class'] === null || $owner['class'] === '?') {
            continue;
        }
        foreach ($owner['properties'] as $property) {
            if ($property['name'] !== $property['getter']) {
                $names[$owner['class']][strtolower($property['name'])] = "-[{$owner['class']} {$property['getter']}]";
            }
        }
    }

    return $names;
}

/** @return array<string, list<string>> class or protocol => its superclass and adopted protocols */
function support_parents(string $ast): array
{
    $parents = [];
    foreach (support_owners($ast) as $owner) {
        if ($owner['class'] !== null && $owner['class'] !== '?' && $owner['parents'] !== []) {
            $parents[$owner['class']] = array_values(array_unique(array_merge($parents[$owner['class']] ?? [], $owner['parents'])));
        }
    }
    ksort($parents, SORT_STRING);

    return $parents;
}

/**
 * The top-level interfaces, categories and protocols of a text AST dump, each with its methods and
 * properties. A location without a path is in the file last printed with one, as clang prints them.
 * @return list<array{class: ?string, parents: list<string>, deprecated: bool, methods: list<array{sign: string, selector: string, measured: bool, deprecated: bool}>, properties: list<array{getter: string, setter: string, deprecated: bool}>}>
 */
function support_owners(string $ast): array
{
    $owners = [];
    $owner = null;
    $item = null; // the method or property the deeper lines belong to: ['methods'|'properties', index]
    $file = '';
    foreach (explode("\n", $ast) as $line) {
        if (preg_match('#<(/[^:<>]+):\d+:\d+#', $line, $m) === 1) {
            $file = $m[1];
        }
        if (preg_match('/^[|`]-(\w+)/', $line, $m) === 1) {
            if ($owner !== null) {
                $owners[] = $owner;
            }
            $owner = null;
            $item = null;
            $name = preg_match('/ (\w+)$/', $line, $n) === 1 ? $n[1] : null;
            $owner = match ($m[1]) {
                'ObjCInterfaceDecl', 'ObjCProtocolDecl' => ['class' => $name, 'parents' => [], 'deprecated' => false, 'methods' => [], 'properties' => []],
                'ObjCCategoryDecl' => ['class' => '?', 'parents' => [], 'deprecated' => false, 'methods' => [], 'properties' => []],
                default => null,
            };
            continue;
        }
        if ($owner === null) {
            continue;
        }
        if (preg_match('/^[| ] [|`]-(.*)$/', $line, $m) === 1) {
            $item = null;
            $body = $m[1];
            if (preg_match("/^super ObjCInterface 0x[0-9a-f]+ '(\\w+)'/", $body, $s) === 1) {
                $owner['parents'][] = $s[1];
            } elseif (preg_match("/^ObjCInterface 0x[0-9a-f]+ '(\\w+)'/", $body, $s) === 1 && $owner['class'] === '?') {
                $owner['class'] = $s[1];
            } elseif (preg_match("/^ObjCProtocol 0x[0-9a-f]+ '(\\w+)'/", $body, $s) === 1) {
                $owner['parents'][] = $s[1];
            } elseif (preg_match("/^ObjCMethodDecl .*? ([-+]) ([\\w:]+) '/", $body, $s) === 1) {
                $owner['methods'][] = ['sign' => $s[1], 'selector' => $s[2], 'measured' => support_measured($file), 'deprecated' => false];
                $item = ['methods', count($owner['methods']) - 1];
            } elseif (preg_match("/^ObjCPropertyDecl .*? col:\\d+ (\\w+) '/", $body, $s) === 1) {
                $owner['properties'][] = ['name' => $s[1], 'getter' => $s[1], 'setter' => 'set' . ucfirst($s[1]) . ':', 'deprecated' => false];
                $item = ['properties', count($owner['properties']) - 1];
            } elseif (support_unavailable($body)) {
                $owner['deprecated'] = true;
            }
            continue;
        }
        if ($item !== null && preg_match('/^[| ] [| ] [|`]-(.*)$/', $line, $m) === 1) {
            $body = $m[1];
            if (support_unavailable($body)) {
                $owner[$item[0]][$item[1]]['deprecated'] = true;
            } elseif ($item[0] === 'properties' && preg_match("/^(getter|setter) ObjCMethod 0x[0-9a-f]+ '([\\w:]+)'/", $body, $s) === 1) {
                $owner['properties'][$item[1]][$s[1]] = $s[2];
            }
        }
    }
    if ($owner !== null) {
        $owners[] = $owner;
    }

    return $owners;
}

/** @return list<string> the MTL C functions the measured headers declare, live on macOS */
function support_c_functions(string $ast): array
{
    $functions = [];
    $file = '';
    $current = null;
    foreach (explode("\n", $ast) as $line) {
        if (preg_match('#<(/[^:<>]+):\d+:\d+#', $line, $m) === 1) {
            $file = $m[1];
        }
        if (preg_match('/^[|`]-/', $line) === 1) {
            $current = null;
            if (preg_match("/^[|`]-FunctionDecl .*? (MTL\\w+) '/", $line, $m) === 1 && support_measured($file)) {
                $current = $m[1];
                $functions[$current] = true;
            }
            continue;
        }
        if ($current !== null && preg_match('/^[| ] [|`]-(.*)$/', $line, $m) === 1 && support_unavailable($m[1])) {
            unset($functions[$current]);
        }
    }

    return array_keys($functions);
}

/** An attribute line that takes a declaration away on macOS: deprecated, obsoleted or unavailable. */
function support_unavailable(string $body): bool
{
    if (str_starts_with($body, 'DeprecatedAttr') || str_starts_with($body, 'UnavailableAttr')) {
        return true;
    }
    if (preg_match('/^AvailabilityAttr .*? macos (\S+) (\S+) (\S+)( Unavailable)?/', $body, $m) !== 1) {
        return false;
    }

    return $m[2] !== '0' || $m[3] !== '0' || isset($m[4]) && $m[4] !== '';
}

/**
 * A member as its binding: -[MTLDevice newBufferWithLength:options:] => ['MTLDevice', 'newBufferWithLengthOptions'];
 * a C function keeps its name.
 * @return array{string, string}
 */
function support_php_name(string $class, string $key): array
{
    if (preg_match('/^[-+]\[\w+ ([\w:]+)\]$/', $key, $m) !== 1) {
        return ['', $key];
    }
    $parts = array_values(array_filter(explode(':', $m[1]), 'strlen'));

    return [$class, $parts[0] . implode('', array_map('ucfirst', array_slice($parts, 1)))];
}

/**
 * The PHP classes and functions the stubs declare.
 * @return array<string, array<string, true>> PHP class ('' for functions) => method names
 */
function support_bound(string $stubDir): array
{
    $bound = [];
    foreach (glob(rtrim($stubDir, '/') . '/*.stub.php') ?: [] as $file) {
        foreach (support_declared(file_get_contents($file)) as $class => $methods) {
            foreach ($methods as $method) {
                $bound[$class][$method] = true;
            }
        }
    }

    return $bound;
}

/**
 * The classes (with their namespace) and public methods, and the free functions, of one stub.
 * @return array<string, list<string>>
 */
function support_declared(string $source): array
{
    $tokens = token_get_all($source);
    $out = [];
    $namespace = '';
    $braced = false;
    $depth = 0;
    $class = null;
    $classDepth = -1;
    $next = static function (int $i) use ($tokens): int {
        for ($i++; $i < count($tokens); $i++) {
            if (! is_array($tokens[$i]) || ! in_array($tokens[$i][0], [T_WHITESPACE, T_COMMENT, T_DOC_COMMENT], true)) {
                return $i;
            }
        }

        return $i;
    };
    for ($i = 0, $n = count($tokens); $i < $n; $i++) {
        $token = $tokens[$i];
        if ($token === '{' || (is_array($token) && in_array($token[0], [T_CURLY_OPEN, T_DOLLAR_OPEN_CURLY_BRACES], true))) {
            $depth++;
            continue;
        }
        if ($token === '}') {
            if ($depth === 0 && $braced) {
                $braced = false;
                $namespace = '';
                continue;
            }
            $depth--;
            if ($class !== null && $depth === $classDepth) {
                $class = null;
            }
            continue;
        }
        if (! is_array($token)) {
            continue;
        }
        if ($token[0] === T_NAMESPACE) {
            $j = $next($i);
            $namespace = $tokens[$j] === '{' ? '' : $tokens[$j][1];
            $k = $tokens[$j] === '{' ? $j : $next($j);
            if ($tokens[$k] === '{') {
                $braced = true;
                $i = $k;
            }
            continue;
        }
        if (in_array($token[0], [T_CLASS, T_INTERFACE, T_TRAIT, T_ENUM], true)) {
            $j = $next($i);
            if (is_array($tokens[$j]) && $tokens[$j][0] === T_STRING) {
                $class = ltrim("{$namespace}\\{$tokens[$j][1]}", '\\');
                $classDepth = $depth;
                $out[$class] ??= [];
                for ($i = $j; $tokens[$i] !== '{'; $i++) {
                }
                $depth++;
            }
            continue;
        }
        if ($token[0] === T_FUNCTION) {
            $j = $next($i);
            // A method name may be a keyword (`new`); a closure has `(` here.
            if (! is_array($tokens[$j]) || preg_match('/^\w+$/', $tokens[$j][1]) !== 1) {
                continue;
            }
            if ($class === null) {
                $out[''][] = ltrim("{$namespace}\\{$tokens[$j][1]}", '\\');
            } elseif ($depth === $classDepth + 1 && ! support_hidden($tokens, $i)) {
                $out[$class][] = $tokens[$j][1];
            }
        }
    }

    return array_map(static fn (array $methods): array => array_values(array_unique($methods)), $out);
}

/** A private or protected method: the modifiers before `function`. */
function support_hidden(array $tokens, int $i): bool
{
    for ($k = $i - 1; $k >= 0; $k--) {
        $t = $tokens[$k];
        if (is_array($t) && in_array($t[0], [T_WHITESPACE, T_COMMENT, T_DOC_COMMENT, T_STATIC, T_ABSTRACT, T_FINAL, T_PUBLIC], true)) {
            continue;
        }

        return is_array($t) && in_array($t[0], [T_PRIVATE, T_PROTECTED], true);
    }

    return false;
}

/**
 * @param array<string, list<string>> $counted
 * @param array<string, array<string, true>> $bound
 * @param array<string, list<string>> $parents class or protocol => superclass and adopted protocols
 * @param array<string, array<string, string>> $propertyNames from support_property_names()
 */
function support_render(array $counted, array $bound, string $library, string $date, array $parents = [], array $propertyNames = []): string
{
    // owner => lowercased PHP method => key: PHP method names are case-insensitive.
    $byMethod = [];
    foreach ($counted as $owner => $keys) {
        foreach ($keys as $key) {
            [$class, $method] = support_php_name($owner, $key);
            $byMethod[$class][strtolower($method)] = $key;
        }
    }
    foreach ($propertyNames as $owner => $names) {
        foreach ($names as $name => $key) {
            if (in_array($key, $counted[$owner] ?? [], true)) {
                $byMethod[$owner][$name] ??= $key;
            }
        }
    }
    $boundKeys = [];
    $outside = [];
    foreach ($bound as $class => $methods) {
        foreach (array_keys($methods) as $method) {
            $found = support_find($byMethod, $parents, $class, strtolower($method));
            if ($found === null) {
                $outside[] = '- `' . ($class === '' ? $method : "{$class}::{$method}") . '`';
            } else {
                $boundKeys[$found] = true;
            }
        }
    }
    sort($outside, SORT_STRING);

    $sections = [];
    $hits = 0;
    $total = 0;
    foreach ($counted as $owner => $keys) {
        $lines = [];
        $ownerHits = 0;
        foreach ($keys as $key) {
            $isBound = isset($boundKeys[$key]);
            $ownerHits += $isBound ? 1 : 0;
            $lines[] = '- [' . ($isBound ? 'x' : ' ') . "] `{$key}`";
        }
        $hits += $ownerHits;
        $total += count($keys);
        $sections[] = "## {$owner} ({$ownerHits} / " . count($keys) . ")\n\n" . implode("\n", $lines) . "\n";
    }

    return '# ' . SUPPORT_LABEL . " support\n\n"
        . support_summary($library, $hits, $total, $date) . "\n\n"
        . "Generated by `php84 scripts/support.php` from the SDK's Metal headers, QuartzCore's Metal classes and `stubs/`. One line per member: `[x]` bound, `[ ]` not bound.\n\n"
        . implode("\n", $sections)
        . "\n## Bound outside the measured library\n\n"
        . "Bindings of other frameworks (Core Graphics, the rest of QuartzCore), of deprecated members, and the extension's own value classes and glue; none of them is counted.\n\n"
        . (count($outside) === 0 ? "None.\n" : implode("\n", $outside) . "\n");
}

/**
 * The member a stub method binds: on its own class or protocol, else up the superclass and
 * adopted-protocol graph, nearest first. A function ('' class) matches a C function by name.
 * @param array<string, array<string, string>> $byMethod
 * @param array<string, list<string>> $parents
 */
function support_find(array $byMethod, array $parents, string $class, string $method): ?string
{
    if ($class === '') {
        return $byMethod[''][$method] ?? null;
    }
    $queue = [$class];
    $seen = [];
    while ($queue !== [] && count($seen) < 256) {
        $owner = array_shift($queue);
        if (isset($seen[$owner])) {
            continue;
        }
        $seen[$owner] = true;
        if (isset($byMethod[$owner][$method])) {
            return $byMethod[$owner][$method];
        }
        array_push($queue, ...($parents[$owner] ?? []));
    }

    return null;
}

function support_summary(string $library, int $hits, int $total, string $date): string
{
    return sprintf('%s — %d / %d members bound (%.1f%%) — %s', $library, $hits, $total, $total === 0 ? 0 : 100 * $hits / $total, $date);
}

function support_badge(string $label, int $bound, int $total): string
{
    $percent = sprintf('%.1f', $total === 0 ? 0 : 100 * $bound / $total);
    $message = str_replace('%20', '_', rawurlencode("{$percent}% ({$bound}/{$total})"));

    return "[![{$label}](https://img.shields.io/badge/" . str_replace(' ', '_', $label) . "-{$message}-blue?style=flat-square)](SUPPORT.md)";
}

/** Two support lists alike but for the date of their summary line. */
function support_same(string $a, string $b): bool
{
    $undated = static fn (string $s): string => preg_replace('/ — \d{4}-\d{2}-\d{2}$/m', '', $s);

    return $undated($a) === $undated($b);
}

/** The README with the badge line set: replaced where it is, else after the CI badge. */
function support_readme(string $readme, string $badge): string
{
    $lines = explode("\n", $readme);
    foreach ($lines as $i => $line) {
        if (str_starts_with($line, '[![' . SUPPORT_LABEL . ']')) {
            $lines[$i] = $badge;

            return implode("\n", $lines);
        }
    }
    foreach ($lines as $i => $line) {
        if (str_starts_with($line, '[![CI]')) {
            array_splice($lines, $i + 1, 0, [$badge]);

            return implode("\n", $lines);
        }
    }
    throw new RuntimeException('The README has no CI badge line to put the API badge after.');
}

/** @return array{int, int} bound and total, read back from a support list's summary line */
function support_totals(string $md): array
{
    preg_match('/ (\d+) \/ (\d+) members bound/', $md, $m);

    return [(int) $m[1], (int) $m[2]];
}

function support_main(array $argv): int
{
    $root = dirname(__DIR__);
    $sdk = trim((string) shell_exec('xcrun --show-sdk-path'));
    $version = trim((string) shell_exec('xcrun --show-sdk-version'));
    $source = tempnam(sys_get_temp_dir(), 'support') . '.m';
    file_put_contents($source, "#import <Metal/Metal.h>\n#import <QuartzCore/CAMetalLayer.h>\n#import <QuartzCore/CAEDRMetadata.h>\n#import <QuartzCore/CAMetalDisplayLink.h>\n");
    try {
        exec('/usr/bin/clang -x objective-c -fsyntax-only -isysroot ' . escapeshellarg($sdk) . ' -Xclang -ast-dump ' . escapeshellarg($source) . ' 2>/dev/null', $lines, $status);
    } finally {
        @unlink($source);
        @unlink(substr($source, 0, -2));
    }
    if ($status !== 0) {
        fwrite(STDERR, "clang could not read the Metal headers.\n");

        return 2;
    }
    $ast = implode("\n", $lines);
    $md = support_render(support_counted($ast), support_bound("{$root}/stubs"), "Metal, macOS SDK {$version}", date('Y-m-d'), support_parents($ast), support_property_names($ast));
    [$hits, $total] = support_totals($md);
    $readme = support_readme(file_get_contents("{$root}/README.md"), support_badge(SUPPORT_LABEL, $hits, $total));

    if (in_array('--check', $argv, true)) {
        $current = is_file("{$root}/SUPPORT.md") ? file_get_contents("{$root}/SUPPORT.md") : '';
        $same = support_same($current, $md) && $readme === file_get_contents("{$root}/README.md");
        fwrite(STDOUT, $same ? "SUPPORT.md and the badge are current.\n" : "SUPPORT.md or the badge differs: run php84 scripts/support.php.\n");

        return $same ? 0 : 1;
    }
    file_put_contents("{$root}/SUPPORT.md", $md);
    file_put_contents("{$root}/README.md", $readme);
    fwrite(STDOUT, "{$hits} / {$total}\n");

    return 0;
}

if (PHP_SAPI === 'cli' && isset($argv[0]) && realpath($argv[0]) === __FILE__) {
    exit(support_main($argv));
}
