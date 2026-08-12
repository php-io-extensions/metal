#ifndef PHP_METAL_TEXTURE_H
#define PHP_METAL_TEXTURE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create an offscreen RGBA8Unorm 2D texture (render target + shader read).
 * Storage is Shared (unified memory) or Managed — CPU read/write capable.
 * Returns opaque retained handle, or 0 on failure.
 */
uintptr_t mtl_texture_create_rgba8(uintptr_t device, int width, int height);

void mtl_texture_release(uintptr_t texture);

int mtl_texture_get_width(uintptr_t texture);

int mtl_texture_get_height(uintptr_t texture);

/**
 * GPU clear via render pass. RGBA components are 0..1.
 * Requires a command queue from the same device. Returns 1 on success.
 */
int mtl_texture_clear(uintptr_t texture, uintptr_t queue, float r, float g, float b, float a);

/**
 * CPU write one RGBA8 pixel (0..255). Returns 1 on success.
 */
int mtl_texture_write_pixel(
	uintptr_t texture,
	int x,
	int y,
	unsigned char r,
	unsigned char g,
	unsigned char b,
	unsigned char a
);

/**
 * CPU fill an axis-aligned rect with one solid RGBA8 color (0..255).
 * One replaceRegion for the whole rect (not per-pixel). Returns 1 on success.
 */
int mtl_texture_fill_rect(
	uintptr_t texture,
	int x,
	int y,
	int width,
	int height,
	unsigned char r,
	unsigned char g,
	unsigned char b,
	unsigned char a
);

/**
 * CPU read one RGBA8 pixel (0..255). Returns 1 on success.
 */
int mtl_texture_read_pixel(
	uintptr_t texture,
	uintptr_t queue,
	int x,
	int y,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *a
);

/**
 * Read the full texture into out (RGBA8888, row-major, tightly packed).
 * out_len must be >= width*height*4. Synchronizes GPU work first.
 * Returns byte count written, or 0 on failure.
 */
int mtl_texture_read_rgba8(uintptr_t texture, uintptr_t queue, unsigned char *out, int out_len);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_TEXTURE_H */
