#import <Metal/Metal.h>
#import <Foundation/Foundation.h>
#import "metal-texture.h"
#include <stdlib.h>

static inline id mtl_tex_bridge_id(uintptr_t handle)
{
	return handle ? (__bridge id)(void *)handle : nil;
}

static inline uintptr_t mtl_tex_retain_handle(id object)
{
	if (!object) {
		return 0;
	}
	return (uintptr_t)(__bridge_retained void *)object;
}

static void mtl_texture_synchronize(id<MTLTexture> texture, id<MTLCommandQueue> queue)
{
	if (!texture || !queue) {
		return;
	}
	if (texture.storageMode == MTLStorageModePrivate) {
		return;
	}
	if (texture.storageMode == MTLStorageModeShared) {
		return;
	}

	id<MTLCommandBuffer> cmd = [queue commandBuffer];
	id<MTLBlitCommandEncoder> blit = [cmd blitCommandEncoder];
	[blit synchronizeResource:texture];
	[blit endEncoding];
	[cmd commit];
	[cmd waitUntilCompleted];
}

uintptr_t mtl_texture_create_rgba8(uintptr_t device, int width, int height)
{
	if (!device || width <= 0 || height <= 0) {
		return 0;
	}

	@autoreleasepool {
		id<MTLDevice> dev = mtl_tex_bridge_id(device);
		if (!dev) {
			return 0;
		}

		MTLTextureDescriptor *desc = [MTLTextureDescriptor
			texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm
			width:(NSUInteger)width
			height:(NSUInteger)height
			mipmapped:NO];
		desc.usage = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead | MTLTextureUsageShaderWrite;
		if (dev.hasUnifiedMemory) {
			desc.storageMode = MTLStorageModeShared;
		} else {
			desc.storageMode = MTLStorageModeManaged;
		}

		id<MTLTexture> texture = [dev newTextureWithDescriptor:desc];
		return mtl_tex_retain_handle(texture);
	}
}

void mtl_texture_release(uintptr_t texture)
{
	if (!texture) {
		return;
	}
	CFRelease((void *)texture);
}

int mtl_texture_get_width(uintptr_t texture)
{
	id<MTLTexture> tex = mtl_tex_bridge_id(texture);
	return tex ? (int)tex.width : 0;
}

int mtl_texture_get_height(uintptr_t texture)
{
	id<MTLTexture> tex = mtl_tex_bridge_id(texture);
	return tex ? (int)tex.height : 0;
}

int mtl_texture_clear(uintptr_t texture, uintptr_t queue, float r, float g, float b, float a)
{
	if (!texture || !queue) {
		return 0;
	}

	@autoreleasepool {
		id<MTLTexture> tex = mtl_tex_bridge_id(texture);
		id<MTLCommandQueue> q = mtl_tex_bridge_id(queue);
		if (!tex || !q) {
			return 0;
		}

		MTLRenderPassDescriptor *pass = [MTLRenderPassDescriptor renderPassDescriptor];
		pass.colorAttachments[0].texture = tex;
		pass.colorAttachments[0].loadAction = MTLLoadActionClear;
		pass.colorAttachments[0].storeAction = MTLStoreActionStore;
		pass.colorAttachments[0].clearColor = MTLClearColorMake(r, g, b, a);

		id<MTLCommandBuffer> cmd = [q commandBuffer];
		id<MTLRenderCommandEncoder> enc = [cmd renderCommandEncoderWithDescriptor:pass];
		[enc endEncoding];
		[cmd commit];
		[cmd waitUntilCompleted];
		return 1;
	}
}

int mtl_texture_write_pixel(
	uintptr_t texture,
	int x,
	int y,
	unsigned char r,
	unsigned char g,
	unsigned char b,
	unsigned char a
) {
	if (!texture || x < 0 || y < 0) {
		return 0;
	}

	@autoreleasepool {
		id<MTLTexture> tex = mtl_tex_bridge_id(texture);
		if (!tex || (NSUInteger)x >= tex.width || (NSUInteger)y >= tex.height) {
			return 0;
		}
		if (tex.storageMode == MTLStorageModePrivate) {
			return 0;
		}

		unsigned char pixel[4] = { r, g, b, a };
		MTLRegion region = MTLRegionMake2D((NSUInteger)x, (NSUInteger)y, 1, 1);
		[tex replaceRegion:region mipmapLevel:0 withBytes:pixel bytesPerRow:4];
		return 1;
	}
}

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
) {
	if (!texture || width <= 0 || height <= 0) {
		return 0;
	}

	@autoreleasepool {
		id<MTLTexture> tex = mtl_tex_bridge_id(texture);
		if (!tex || tex.storageMode == MTLStorageModePrivate) {
			return 0;
		}

		int tex_w = (int)tex.width;
		int tex_h = (int)tex.height;
		int x0 = x < 0 ? 0 : x;
		int y0 = y < 0 ? 0 : y;
		int x1 = x + width;
		int y1 = y + height;
		if (x1 > tex_w) {
			x1 = tex_w;
		}
		if (y1 > tex_h) {
			y1 = tex_h;
		}
		int cw = x1 - x0;
		int ch = y1 - y0;
		if (cw <= 0 || ch <= 0) {
			return 0;
		}

		size_t bytes_per_row = (size_t)cw * 4u;
		size_t total = bytes_per_row * (size_t)ch;
		unsigned char *buf = (unsigned char *)malloc(total);
		if (!buf) {
			return 0;
		}

		for (size_t i = 0; i < total; i += 4u) {
			buf[i] = r;
			buf[i + 1] = g;
			buf[i + 2] = b;
			buf[i + 3] = a;
		}

		MTLRegion region = MTLRegionMake2D((NSUInteger)x0, (NSUInteger)y0, (NSUInteger)cw, (NSUInteger)ch);
		[tex replaceRegion:region mipmapLevel:0 withBytes:buf bytesPerRow:bytes_per_row];
		free(buf);
		return 1;
	}
}

int mtl_texture_read_pixel(
	uintptr_t texture,
	uintptr_t queue,
	int x,
	int y,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *a
) {
	if (!texture || !r || !g || !b || !a || x < 0 || y < 0) {
		return 0;
	}

	@autoreleasepool {
		id<MTLTexture> tex = mtl_tex_bridge_id(texture);
		id<MTLCommandQueue> q = mtl_tex_bridge_id(queue);
		if (!tex || !q || (NSUInteger)x >= tex.width || (NSUInteger)y >= tex.height) {
			return 0;
		}
		if (tex.storageMode == MTLStorageModePrivate) {
			return 0;
		}

		mtl_texture_synchronize(tex, q);

		unsigned char pixel[4] = { 0, 0, 0, 0 };
		MTLRegion region = MTLRegionMake2D((NSUInteger)x, (NSUInteger)y, 1, 1);
		[tex getBytes:pixel bytesPerRow:4 fromRegion:region mipmapLevel:0];
		*r = pixel[0];
		*g = pixel[1];
		*b = pixel[2];
		*a = pixel[3];
		return 1;
	}
}

int mtl_texture_read_rgba8(uintptr_t texture, uintptr_t queue, unsigned char *out, int out_len)
{
	if (!texture || !out || out_len <= 0) {
		return 0;
	}

	@autoreleasepool {
		id<MTLTexture> tex = mtl_tex_bridge_id(texture);
		id<MTLCommandQueue> q = mtl_tex_bridge_id(queue);
		if (!tex || !q) {
			return 0;
		}
		if (tex.storageMode == MTLStorageModePrivate) {
			return 0;
		}

		NSUInteger bytes = tex.width * tex.height * 4;
		if ((int)bytes > out_len) {
			return 0;
		}

		mtl_texture_synchronize(tex, q);

		MTLRegion region = MTLRegionMake2D(0, 0, tex.width, tex.height);
		[tex getBytes:out bytesPerRow:(tex.width * 4) fromRegion:region mipmapLevel:0];
		return (int)bytes;
	}
}
