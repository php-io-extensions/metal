<?php

declare(strict_types=1);

require_once __DIR__ . '/../scripts/support.php';

const SUPPORT_TEST_HEADERS = '/SDK/System/Library/Frameworks/Metal.framework/Headers/';

/** A text AST dump of two protocols, a function and a Foundation interface, as clang prints them. */
function supportTestAst(): string
{
    $h = SUPPORT_TEST_HEADERS;

    return implode("\n", [
        'TranslationUnitDecl 0x1 <<invalid sloc>> <invalid sloc>',
        "|-ObjCProtocolDecl 0x2 <{$h}MTLCommandEncoder.h:10:1, line:20:2> line:10:11 MTLCommandEncoder",
        "| |-ObjCPropertyDecl 0x3 <line:12:1, col:30> col:30 label 'NSString *' readwrite copy atomic",
        "| |-ObjCMethodDecl 0x4 <line:14:1, col:20> col:1 - endEncoding 'void'",
        "| |-ObjCMethodDecl 0x5 <line:12:30> col:30 implicit - label 'NSString *'",
        "| `-ObjCMethodDecl 0x6 <line:12:30> col:30 implicit - setLabel: 'void'",
        "|-ObjCProtocolDecl 0x7 <{$h}MTLRenderCommandEncoder.h:30:1, line:40:2> line:30:11 MTLRenderCommandEncoder",
        "| |-ObjCProtocol 0x2 'MTLCommandEncoder'",
        "| |-ObjCPropertyDecl 0x8 <line:31:1, col:40> col:40 depthWriteEnabled 'BOOL' readwrite atomic",
        "| | `-getter ObjCMethod 0x9 'isDepthWriteEnabled'",
        "| |-ObjCMethodDecl 0xa <line:33:1, col:60> col:1 - setViewport: 'void'",
        "| |-ObjCMethodDecl 0xb <line:34:1, col:60> col:1 - oldCall: 'void'",
        "| | `-AvailabilityAttr 0xc <col:1> macos 10.11 10.14 0 \"\" \"\" 0",
        "| `-ObjCMethodDecl 0x9 <line:31:40> col:40 implicit - isDepthWriteEnabled 'BOOL'",
        "|-FunctionDecl 0xd <{$h}MTLDevice.h:50:1, col:40> col:30 MTLCreateSystemDefaultDevice 'id<MTLDevice> (void)' extern",
        "|-ObjCInterfaceDecl 0xe </SDK/System/Library/Frameworks/Foundation.framework/Headers/NSObject.h:5:1, line:9:2> line:5:12 NSObject",
        '| `-ObjCMethodDecl 0xf <line:6:1, col:10> col:1 + new \'instancetype\'',
    ]);
}

it('counts protocol members and C functions of the measured headers, without deprecated ones or Foundation', function (): void {
    expect(support_counted(supportTestAst()))->toBe([
        'MTLCommandEncoder' => ['-[MTLCommandEncoder endEncoding]', '-[MTLCommandEncoder label]', '-[MTLCommandEncoder setLabel:]'],
        'MTLRenderCommandEncoder' => ['-[MTLRenderCommandEncoder isDepthWriteEnabled]', '-[MTLRenderCommandEncoder setViewport:]'],
        'functions' => ['MTLCreateSystemDefaultDevice'],
    ]);
});

it('reads adopted protocols as parents', function (): void {
    expect(support_parents(supportTestAst()))->toBe(['MTLRenderCommandEncoder' => ['MTLCommandEncoder']]);
});

it('names a member as its binding: selector parts joined; a C function keeps its name', function (): void {
    expect(support_php_name('MTLDevice', '-[MTLDevice newBufferWithLength:options:]'))->toBe(['MTLDevice', 'newBufferWithLengthOptions'])
        ->and(support_php_name('functions', 'MTLCreateSystemDefaultDevice'))->toBe(['', 'MTLCreateSystemDefaultDevice']);
});

it('binds a method up the adopted-protocol graph, a renamed getter by its property, and a function by name', function (): void {
    $ast = supportTestAst();
    $bound = [
        'MTLRenderCommandEncoder' => ['setLabel' => true, 'depthWriteEnabled' => true, 'setViewport' => true, 'pointer' => true],
        '' => ['MTLCreateSystemDefaultDevice' => true],
    ];
    $md = support_render(support_counted($ast), $bound, 'Metal, macOS SDK 15.4', '2026-10-28', support_parents($ast), support_property_names($ast));

    expect($md)->toContain('- [x] `-[MTLCommandEncoder setLabel:]`')
        ->toContain('- [ ] `-[MTLCommandEncoder label]`')
        ->toContain('- [x] `-[MTLRenderCommandEncoder isDepthWriteEnabled]`')
        ->toContain('- [x] `-[MTLRenderCommandEncoder setViewport:]`')
        ->toContain('- [x] `MTLCreateSystemDefaultDevice`')
        ->toContain('Metal, macOS SDK 15.4 — 4 / 6 members bound (66.7%) — 2026-10-28')
        ->toContain('- `MTLRenderCommandEncoder::pointer`');
});

it('computes the badge from the counts', function (): void {
    expect(support_badge('Metal API', 189, 1738))
        ->toBe('[![Metal API](https://img.shields.io/badge/Metal_API-10.9%25_%28189%2F1738%29-blue?style=flat-square)](SUPPORT.md)');
});
