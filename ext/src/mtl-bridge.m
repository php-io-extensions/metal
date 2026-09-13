#include "mtl-bridge.h"
#include "mtl-value.h"

/* ====================================================================== */
/* Handle registry                                                       */
/* ====================================================================== */

static NSMutableDictionary<NSNumber *, id> *mtl_registry = nil;

static NSMutableDictionary *mtl_registry_table(void)
{
    if (mtl_registry == nil) mtl_registry = [NSMutableDictionary new];
    return mtl_registry;
}

zend_long mtl_handle_for(id object)
{
    if (object == nil) return 0;
    zend_long h = (zend_long) (uintptr_t) object;
    NSNumber *key = @(h);
    if ([mtl_registry_table() objectForKey:key] == nil) {
        [mtl_registry_table() setObject:object forKey:key];
    }
    return h;
}

id mtl_handle_object(zend_long h)
{
    if (h == 0) return nil;
    return [mtl_registry_table() objectForKey:@(h)];
}

void mtl_handle_release(zend_long h)
{
    if (h == 0) return;
    [mtl_registry_table() removeObjectForKey:@(h)];
}

zend_long mtl_bridge_retain(zval *handle)
{
    zend_long h = mtl_arg_long(handle);
    return mtl_handle_object(h) != nil ? 1 : 0;
}

void mtl_bridge_release(zval *handle)
{
    @autoreleasepool { mtl_handle_release(mtl_arg_long(handle)); }
}

zend_long mtl_bridge_is_valid(zval *handle)
{
    return mtl_handle_object(mtl_arg_long(handle)) != nil ? 1 : 0;
}

void mtl_bridge_class_name(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id o = mtl_arg_object(handle);
        mtl_ret_string(return_value, o != nil ? NSStringFromClass([o class]) : nil);
    }
}

/* ====================================================================== */
/* Cross-extension pointer seam (spec §5.4)                               */
/* ====================================================================== */

zend_long mtl_bridge_pointer_of(zval *handle)
{
    zend_long r = 0;
    @autoreleasepool {
        id o = mtl_handle_object(mtl_arg_long(handle));
        r = (zend_long) (uintptr_t) (__bridge void *) o;
    }
    return r;
}

zend_long mtl_bridge_adopt(zval *className, zval *pointerBits)
{
    zend_long r = 0;
    @autoreleasepool {
        void *p = (void *) (uintptr_t) mtl_arg_long(pointerBits);
        if (p == NULL) return 0;
        id o = (__bridge id) p;
        NSString *want = mtl_arg_string(className);
        Class cls = want != nil ? NSClassFromString(want) : Nil;
        /* Known class: enforce kind-of. Unknown name (e.g. a protocol
           name like MTLDevice): adopt unchecked — the caller asked. */
        if (cls != Nil && ![o isKindOfClass:cls]) return 0;
        r = mtl_handle_for(o); /* retains */
    }
    return r;
}

/* ====================================================================== */
/* NSError reader (spec §5.3 pattern)                                    */
/* ====================================================================== */

void mtl_bridge_error_description(zval *return_value, zval *handle)
{
    @autoreleasepool {
        id o = mtl_handle_object(mtl_arg_long(handle));
        if (o == nil || ![o isKindOfClass:[NSError class]]) {
            ZVAL_NULL(return_value);
            return;
        }
        mtl_ret_string(return_value, [(NSError *) o localizedDescription]);
    }
}
