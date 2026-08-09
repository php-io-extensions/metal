#ifndef PHP_METAL_DEVICE_H
#define PHP_METAL_DEVICE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** MTLCreateSystemDefaultDevice — opaque retained handle, or 0. */
uintptr_t mtl_device_create_system_default(void);

void mtl_device_release(uintptr_t device);

/** New command queue for device — opaque retained handle, or 0. */
uintptr_t mtl_device_new_command_queue(uintptr_t device);

void mtl_command_queue_release(uintptr_t queue);

/** UTF-8 device name into out (NUL-terminated). Returns 1 on success. */
int mtl_device_get_name(uintptr_t device, char *out, int out_len);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_DEVICE_H */
