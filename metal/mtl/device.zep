namespace Metal\MTL;

%{
#include "metal-device.h"
#include <stdint.h>
}%

/**
 * MTLDevice / MTLCommandQueue handles (opaque ints).
 */
class Device
{
    /**
     * @return int Opaque MTLDevice handle, or 0
     */
    public static function createSystemDefault() -> int
    {
        int handle;
        %{
            handle = (zend_long) mtl_device_create_system_default();
        }%
        return handle;
    }

    public static function release(int device) -> void
    {
        %{
            mtl_device_release((uintptr_t) device);
        }%
    }

    /**
     * @return int Opaque MTLCommandQueue handle, or 0
     */
    public static function newCommandQueue(int device) -> int
    {
        int handle;
        %{
            handle = (zend_long) mtl_device_new_command_queue((uintptr_t) device);
        }%
        return handle;
    }

    public static function releaseCommandQueue(int queue) -> void
    {
        %{
            mtl_command_queue_release((uintptr_t) queue);
        }%
    }

    public static function getName(int device) -> string
    {
        string name;
        %{
            char buf[512];
            buf[0] = '\0';
            if (mtl_device_get_name((uintptr_t) device, buf, (int) sizeof(buf))) {
                ZVAL_STRING(&name, buf);
            } else {
                ZVAL_STRING(&name, "");
            }
        }%
        return name;
    }
}
