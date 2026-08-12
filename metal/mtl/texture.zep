namespace Metal\MTL;

%{
#include "metal-texture.h"
#include <stdint.h>
#include <stdlib.h>
}%

/**
 * Offscreen MTLTexture (RGBA8Unorm) — headless render targets for engines/UIs.
 * Handles are opaque ints owned by the caller until release().
 */
class Texture
{
	/**
	 * @return int Opaque texture handle, or 0 on failure
	 */
	public static function create(int device, int width, int height) -> int
	{
		int handle;
		%{
			handle = (zend_long) mtl_texture_create_rgba8((uintptr_t) device, (int) width, (int) height);
		}%
		return handle;
	}

	public static function release(int texture) -> void
	{
		%{
			mtl_texture_release((uintptr_t) texture);
		}%
	}

	public static function getWidth(int texture) -> int
	{
		int w;
		%{
			w = mtl_texture_get_width((uintptr_t) texture);
		}%
		return w;
	}

	public static function getHeight(int texture) -> int
	{
		int h;
		%{
			h = mtl_texture_get_height((uintptr_t) texture);
		}%
		return h;
	}

	/**
	 * GPU clear. RGBA components are integers 0..255.
	 */
	public static function clear(int texture, int queue, int r, int g, int b, int a = 255) -> bool
	{
		int ok;
		%{
			ok = mtl_texture_clear(
				(uintptr_t) texture,
				(uintptr_t) queue,
				((float) r) / 255.0f,
				((float) g) / 255.0f,
				((float) b) / 255.0f,
				((float) a) / 255.0f
			);
		}%
		return ok ? true : false;
	}

	/**
	 * CPU write one RGBA8 pixel (0..255).
	 */
	public static function writePixel(int texture, int x, int y, int r, int g, int b, int a = 255) -> bool
	{
		int ok;
		%{
			ok = mtl_texture_write_pixel(
				(uintptr_t) texture,
				(int) x,
				(int) y,
				(unsigned char) (r < 0 ? 0 : (r > 255 ? 255 : r)),
				(unsigned char) (g < 0 ? 0 : (g > 255 ? 255 : g)),
				(unsigned char) (b < 0 ? 0 : (b > 255 ? 255 : b)),
				(unsigned char) (a < 0 ? 0 : (a > 255 ? 255 : a))
			);
		}%
		return ok ? true : false;
	}

	/**
	 * CPU fill an axis-aligned rect with one solid RGBA8 color (0..255).
	 * One replaceRegion for the whole rect — use this instead of writePixel loops.
	 */
	public static function fillRect(int texture, int x, int y, int width, int height, int r, int g, int b, int a = 255) -> bool
	{
		int ok;
		%{
			ok = mtl_texture_fill_rect(
				(uintptr_t) texture,
				(int) x,
				(int) y,
				(int) width,
				(int) height,
				(unsigned char) (r < 0 ? 0 : (r > 255 ? 255 : r)),
				(unsigned char) (g < 0 ? 0 : (g > 255 ? 255 : g)),
				(unsigned char) (b < 0 ? 0 : (b > 255 ? 255 : b)),
				(unsigned char) (a < 0 ? 0 : (a > 255 ? 255 : a))
			);
		}%
		return ok ? true : false;
	}

	/**
	 * CPU read one RGBA8 pixel as [r, g, b, a] ints 0..255, or empty array on failure.
	 */
	public static function readPixel(int texture, int queue, int x, int y) -> array
	{
		array out = [];
		%{
			unsigned char r = 0, g = 0, b = 0, a = 0;
			if (mtl_texture_read_pixel((uintptr_t) texture, (uintptr_t) queue, (int) x, (int) y, &r, &g, &b, &a)) {
				array_init(&out);
				add_next_index_long(&out, (zend_long) r);
				add_next_index_long(&out, (zend_long) g);
				add_next_index_long(&out, (zend_long) b);
				add_next_index_long(&out, (zend_long) a);
			} else {
				array_init(&out);
			}
		}%
		return out;
	}

	/**
	 * Full RGBA8888 tightly packed bytes (row-major), or "" on failure.
	 */
	public static function readPixels(int texture, int queue) -> string
	{
		string bytes;
		%{
			int w = mtl_texture_get_width((uintptr_t) texture);
			int h = mtl_texture_get_height((uintptr_t) texture);
			if (w <= 0 || h <= 0) {
				ZVAL_EMPTY_STRING(&bytes);
			} else {
				size_t need = (size_t) w * (size_t) h * 4u;
				unsigned char *buf = (unsigned char *) emalloc(need);
				int n = mtl_texture_read_rgba8((uintptr_t) texture, (uintptr_t) queue, buf, (int) need);
				if (n <= 0) {
					efree(buf);
					ZVAL_EMPTY_STRING(&bytes);
				} else {
					ZVAL_STRINGL(&bytes, (char *) buf, n);
					efree(buf);
				}
			}
		}%
		return bytes;
	}
}
