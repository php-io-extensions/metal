#ifndef PHP_METAL_MTL_VALUE_H
#define PHP_METAL_MTL_VALUE_H

/*
 * Marshalling between zvals and Metal values. Included by every bridge .m.
 *
 * Handles: every Objective-C object that crosses into PHP does so as an int —
 * its pointer — and the registry in mtl-bridge.m holds a strong reference for
 * as long as PHP holds the handle. 0 is nil. Resolving validates against the
 * registry, so a stale or fabricated int is nil rather than a crash.
 *
 * Structs cross as their components in (doubles) and as assoc arrays out.
 * NSString crosses as string; nil is null.
 */

#include "php.h"
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#ifdef __cplusplus
extern "C" {
#endif

/* mtl-bridge.m */
zend_long mtl_handle_for(id object);     /* register (retain) if new; 0 for nil */
id        mtl_handle_object(zend_long h); /* nil when unknown */
void      mtl_handle_release(zend_long h);

#ifdef __cplusplus
}
#endif

static inline zval *mtl_deref(zval *z)
{
    if (z != NULL) { ZVAL_DEREF(z); }
    return z;
}

static inline zend_long mtl_arg_long(zval *z)
{
    z = mtl_deref(z);
    if (z == NULL) return 0;
    switch (Z_TYPE_P(z)) {
        case IS_LONG:   return Z_LVAL_P(z);
        case IS_DOUBLE: return (zend_long) Z_DVAL_P(z);
        case IS_TRUE:   return 1;
        default:        return 0;
    }
}

static inline double mtl_arg_double(zval *z)
{
    z = mtl_deref(z);
    if (z == NULL) return 0.0;
    switch (Z_TYPE_P(z)) {
        case IS_DOUBLE: return Z_DVAL_P(z);
        case IS_LONG:   return (double) Z_LVAL_P(z);
        default:        return 0.0;
    }
}

static inline BOOL mtl_arg_bool(zval *z)
{
    z = mtl_deref(z);
    if (z == NULL) return NO;
    switch (Z_TYPE_P(z)) {
        case IS_TRUE: return YES;
        case IS_LONG: return Z_LVAL_P(z) != 0;
        default:      return NO;
    }
}

/* NSString or nil (null / non-string). */
static inline NSString *mtl_arg_string(zval *z)
{
    z = mtl_deref(z);
    if (z == NULL || Z_TYPE_P(z) != IS_STRING) return nil;
    return [[NSString alloc] initWithBytes:Z_STRVAL_P(z) length:Z_STRLEN_P(z) encoding:NSUTF8StringEncoding];
}

static inline id mtl_arg_object(zval *z)
{
    return mtl_handle_object(mtl_arg_long(z));
}

/* PHP list of handles -> NSArray of objects (unknown handles skipped). */
static inline NSArray *mtl_arg_object_array(zval *z)
{
    NSMutableArray *out = [NSMutableArray new];
    z = mtl_deref(z);
    if (z == NULL || Z_TYPE_P(z) != IS_ARRAY) return out;
    zval *e;
    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(z), e) {
        id o = mtl_arg_object(e);
        if (o != nil) [out addObject:o];
    }     ZEND_HASH_FOREACH_END();
    return out;
}

/* ---- returns: write into return_value ---- */

static inline void mtl_ret_string(zval *rv, NSString *s)
{
    if (s == nil) { ZVAL_NULL(rv); return; }
    const char *u = [s UTF8String];
    if (u == NULL) { ZVAL_EMPTY_STRING(rv); return; }
    ZVAL_STRINGL(rv, u, (size_t) strlen(u));
}

static inline void mtl_ret_object_array(zval *rv, NSArray *a)
{
    array_init(rv);
    for (id o in a) { add_next_index_long(rv, mtl_handle_for(o)); }
}

/* NSArray<NSString *> -> PHP list of strings (non-strings skipped). */
static inline void mtl_ret_string_array(zval *rv, NSArray *a)
{
    array_init(rv);
    for (id o in a) {
        if (![o isKindOfClass:[NSString class]]) continue;
        const char *u = [(NSString *) o UTF8String];
        if (u == NULL) continue;
        add_next_index_stringl(rv, u, (size_t) strlen(u));
    }
}

/* The sanctioned NSError** shape: {handle: int, error: int}, exactly one
   of them non-zero (both zero only when the call could not be made at
   all — a nil receiver or an unresolvable argument). */
static inline void mtl_ret_handle_error(zval *rv, zend_long handle, zend_long error)
{
    array_init(rv);
    add_assoc_long(rv, "handle", handle);
    add_assoc_long(rv, "error", error);
}

/* Resolve a handle to an instance of a class; nil when not that kind. */
#define MTL_ARG_AS(Type, z) ((Type *) mtl_arg_typed(z, [Type class]))

static inline id mtl_arg_typed(zval *z, Class cls)
{
    id o = mtl_arg_object(z);
    return (o != nil && [o isKindOfClass:cls]) ? o : nil;
}

/* Protocol-typed registry fetch: Metal API objects are id<MTLDevice> etc.
   Handles are untyped ints, so a caller can hand any live handle to any
   binding; resolving without a check let (say) an MTLTexture handle reach
   a binding that sends [b contents], which raises an unrecognized-selector
   NSException and aborts the process. The conformance test is the same
   kind-of guard MTL_ARG_AS applies to classes, and keeps nil semantics:
   a non-conforming (or unknown) handle reads as nil, and every binding
   already treats nil as "no-op / empty result". Protocol inheritance
   counts, so a render-encoder handle still satisfies MTLCommandEncoder. */
#define MTL_ARG_PROTO(Proto, zv) ((id<Proto>) mtl_arg_conforming(zv, @protocol(Proto)))

static inline id mtl_arg_conforming(zval *z, Protocol *proto)
{
    id o = mtl_arg_object(z);
    return (o != nil && [o conformsToProtocol:proto]) ? o : nil;
}

static inline void mtl_ret_cgsize(zval *rv, CGSize s)
{
    array_init(rv);
    add_assoc_double(rv, "width", (double) s.width);
    add_assoc_double(rv, "height", (double) s.height);
}

static inline void mtl_ret_clearcolor(zval *rv, MTLClearColor c)
{
    array_init(rv);
    add_assoc_double(rv, "red", c.red);
    add_assoc_double(rv, "green", c.green);
    add_assoc_double(rv, "blue", c.blue);
    add_assoc_double(rv, "alpha", c.alpha);
}

#endif /* PHP_METAL_MTL_VALUE_H */
