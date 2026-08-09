#ifndef PHP_METAL_WINDOW_H
#define PHP_METAL_WINDOW_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create an NSWindow hosting a CAMetalLayer-backed view.
 * Returns opaque handle (0 on failure). Caller owns the handle — call mtl_window_destroy.
 */
uintptr_t mtl_window_create(const char *title, int width, int height);

void mtl_window_destroy(uintptr_t window);

void mtl_window_set_title(uintptr_t window, const char *title);

void mtl_window_show(uintptr_t window);

void mtl_window_hide(uintptr_t window);

/** 1 if the user closed the window (or it was destroyed). */
int mtl_window_should_close(uintptr_t window);

int mtl_window_get_width(uintptr_t window);

int mtl_window_get_height(uintptr_t window);

/**
 * Attach an MTLDevice (opaque handle from mtl_device_create_system_default)
 * to the window's CAMetalLayer.
 */
int mtl_window_attach_device(uintptr_t window, uintptr_t device);

/** Opaque CAMetalLayer pointer for advanced use (0 if unavailable). */
uintptr_t mtl_window_get_layer(uintptr_t window);

/**
 * Acquire next drawable, clear to RGBA (0..1), present.
 * Requires attach_device first. Returns 1 on success.
 */
int mtl_window_clear(uintptr_t window, float r, float g, float b, float a);

/**
 * Opaque MTLDevice currently attached to the window (0 if none).
 * Borrowed — do not release; owned by the window until destroy / re-attach.
 */
uintptr_t mtl_window_get_device(uintptr_t window);

/**
 * Blit an RGBA8Unorm offscreen texture to the window's CAMetalLayer drawable and present.
 * Requires attach_device first. Sets drawableSize to the texture dimensions.
 * Returns 1 on success.
 */
int mtl_window_present_texture(uintptr_t window, uintptr_t texture);

/**
 * Convert AppKit screen coordinates (origin bottom-left) to content-view local coords.
 * Returns 1 on success. Used by mtl_input_mouse_position.
 */
int mtl_window_screen_to_content(uintptr_t window, double screen_x, double screen_y, double *out_x, double *out_y);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_WINDOW_H */
