#import <AppKit/AppKit.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#import "metal-window.h"
#import "metal-app.h"

@interface MTLPhpView : NSView
@property (nonatomic, strong) CAMetalLayer *metalLayer;
@property (nonatomic, assign) BOOL closedFlag;
@end

@implementation MTLPhpView

+ (Class)layerClass
{
    return [CAMetalLayer class];
}

- (instancetype)initWithFrame:(NSRect)frameRect
{
    self = [super initWithFrame:frameRect];
    if (self) {
        CAMetalLayer *metalLayer = [CAMetalLayer layer];
        /* Match offscreen MTLTexture RGBA8Unorm so present_texture can blit. */
        metalLayer.pixelFormat = MTLPixelFormatRGBA8Unorm;
        metalLayer.contentsScale = NSScreen.mainScreen.backingScaleFactor ?: 1.0;
        metalLayer.framebufferOnly = NO;
        self.layer = metalLayer;
        self.wantsLayer = YES;
        self.metalLayer = metalLayer;
        self.closedFlag = NO;
    }
    return self;
}

/*
 * Accept and swallow key events so AppKit does not NSBeep on arrows / space
 * when PHP polls key state via mtl_input_key_down (game-style input).
 */
- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (BOOL)becomeFirstResponder
{
    return YES;
}

- (void)keyDown:(NSEvent *)event
{
    (void)event;
}

- (void)keyUp:(NSEvent *)event
{
    (void)event;
}

- (void)layout
{
    [super layout];
    CGFloat scale = self.window.backingScaleFactor ?: 1.0;
    self.metalLayer.contentsScale = scale;
    self.metalLayer.drawableSize = CGSizeMake(self.bounds.size.width * scale,
                                              self.bounds.size.height * scale);
}

@end

@interface MTLPhpWindowDelegate : NSObject <NSWindowDelegate>
@property (nonatomic, assign) void *boxPtr;
@end

typedef struct {
    void *window;   /* NSWindow * (retained) */
    void *view;     /* MTLPhpView * (retained) */
    void *delegate; /* MTLPhpWindowDelegate * (retained) */
    void *device;   /* id<MTLDevice> (retained) */
    void *queue;    /* id<MTLCommandQueue> (retained) */
} mtl_window_box;

@implementation MTLPhpWindowDelegate
- (BOOL)windowShouldClose:(NSWindow *)sender
{
    (void)sender;
    mtl_window_box *box = (mtl_window_box *)self.boxPtr;
    if (box && box->view) {
        MTLPhpView *view = (__bridge MTLPhpView *)box->view;
        view.closedFlag = YES;
    }
    mtl_app_terminate();
    return YES;
}
@end

static inline mtl_window_box *mtl_window_box_from(uintptr_t handle)
{
    return handle ? (mtl_window_box *)handle : NULL;
}

static inline void *mtl_retain_obj(id object)
{
    return object ? (__bridge_retained void *)object : NULL;
}

static inline void mtl_release_obj(void **slot)
{
    if (slot && *slot) {
        CFRelease(*slot);
        *slot = NULL;
    }
}

uintptr_t mtl_window_create(const char *title, int width, int height)
{
    if (!mtl_app_init()) {
        return 0;
    }
    if (width <= 0) {
        width = 800;
    }
    if (height <= 0) {
        height = 600;
    }

    @autoreleasepool {
        NSRect rect = NSMakeRect(0, 0, (CGFloat)width, (CGFloat)height);
        NSUInteger style = NSWindowStyleMaskTitled
            | NSWindowStyleMaskClosable
            | NSWindowStyleMaskMiniaturizable
            | NSWindowStyleMaskResizable;

        NSWindow *window = [[NSWindow alloc] initWithContentRect:rect
                                                       styleMask:style
                                                         backing:NSBackingStoreBuffered
                                                           defer:NO];
        NSString *nsTitle = title ? [NSString stringWithUTF8String:title] : @"Metal";
        [window setTitle:nsTitle];
        [window center];
        [window setReleasedWhenClosed:NO];

        MTLPhpView *view = [[MTLPhpView alloc] initWithFrame:rect];
        [window setContentView:view];

        mtl_window_box *box = calloc(1, sizeof(mtl_window_box));
        if (!box) {
            return 0;
        }

        MTLPhpWindowDelegate *delegate = [MTLPhpWindowDelegate new];
        delegate.boxPtr = box;
        [window setDelegate:delegate];

        box->window = mtl_retain_obj(window);
        box->view = mtl_retain_obj(view);
        box->delegate = mtl_retain_obj(delegate);
        box->device = NULL;
        box->queue = NULL;

        [window makeKeyAndOrderFront:nil];
        [window makeFirstResponder:view];
        [NSApp activateIgnoringOtherApps:YES];

        return (uintptr_t)box;
    }
}

void mtl_window_destroy(uintptr_t window)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box) {
        return;
    }

    @autoreleasepool {
        if (box->window) {
            NSWindow *win = (__bridge NSWindow *)box->window;
            [win setDelegate:nil];
            [win close];
        }
        mtl_release_obj(&box->queue);
        mtl_release_obj(&box->device);
        mtl_release_obj(&box->delegate);
        mtl_release_obj(&box->view);
        mtl_release_obj(&box->window);
    }
    free(box);
}

void mtl_window_set_title(uintptr_t window, const char *title)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->window) {
        return;
    }
    @autoreleasepool {
        NSWindow *win = (__bridge NSWindow *)box->window;
        NSString *nsTitle = title ? [NSString stringWithUTF8String:title] : @"";
        [win setTitle:nsTitle];
    }
}

void mtl_window_show(uintptr_t window)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->window) {
        return;
    }
    NSWindow *win = (__bridge NSWindow *)box->window;
    [win makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
}

void mtl_window_hide(uintptr_t window)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->window) {
        return;
    }
    NSWindow *win = (__bridge NSWindow *)box->window;
    [win orderOut:nil];
}

int mtl_window_should_close(uintptr_t window)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->view) {
        return 1;
    }
    MTLPhpView *view = (__bridge MTLPhpView *)box->view;
    if (view.closedFlag) {
        return 1;
    }
    if (mtl_app_should_quit()) {
        return 1;
    }
    return 0;
}

int mtl_window_get_width(uintptr_t window)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->view) {
        return 0;
    }
    MTLPhpView *view = (__bridge MTLPhpView *)box->view;
    return (int)lround(view.bounds.size.width);
}

int mtl_window_get_height(uintptr_t window)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->view) {
        return 0;
    }
    MTLPhpView *view = (__bridge MTLPhpView *)box->view;
    return (int)lround(view.bounds.size.height);
}

int mtl_window_attach_device(uintptr_t window, uintptr_t device)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->view || !device) {
        return 0;
    }

    @autoreleasepool {
        id<MTLDevice> dev = (__bridge id<MTLDevice>)(void *)device;
        MTLPhpView *view = (__bridge MTLPhpView *)box->view;
        if (!dev || !view) {
            return 0;
        }

        mtl_release_obj(&box->queue);
        mtl_release_obj(&box->device);

        box->device = mtl_retain_obj(dev);
        view.metalLayer.device = dev;

        id<MTLCommandQueue> queue = [dev newCommandQueue];
        if (!queue) {
            return 0;
        }
        box->queue = mtl_retain_obj(queue);
        return 1;
    }
}

uintptr_t mtl_window_get_layer(uintptr_t window)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->view) {
        return 0;
    }
    MTLPhpView *view = (__bridge MTLPhpView *)box->view;
    if (!view.metalLayer) {
        return 0;
    }
    return (uintptr_t)(__bridge void *)view.metalLayer;
}

int mtl_window_clear(uintptr_t window, float r, float g, float b, float a)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->view || !box->queue) {
        return 0;
    }

    @autoreleasepool {
        MTLPhpView *view = (__bridge MTLPhpView *)box->view;
        id<MTLCommandQueue> queue = (__bridge id<MTLCommandQueue>)box->queue;
        CAMetalLayer *layer = view.metalLayer;
        if (!layer || !queue) {
            return 0;
        }

        id<CAMetalDrawable> drawable = [layer nextDrawable];
        if (!drawable) {
            return 0;
        }

        MTLRenderPassDescriptor *pass = [MTLRenderPassDescriptor renderPassDescriptor];
        pass.colorAttachments[0].texture = drawable.texture;
        pass.colorAttachments[0].loadAction = MTLLoadActionClear;
        pass.colorAttachments[0].storeAction = MTLStoreActionStore;
        pass.colorAttachments[0].clearColor = MTLClearColorMake(r, g, b, a);

        id<MTLCommandBuffer> cmd = [queue commandBuffer];
        id<MTLRenderCommandEncoder> enc = [cmd renderCommandEncoderWithDescriptor:pass];
        [enc endEncoding];
        [cmd presentDrawable:drawable];
        [cmd commit];
        return 1;
    }
}

uintptr_t mtl_window_get_device(uintptr_t window)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->device) {
        return 0;
    }
    return (uintptr_t)box->device;
}

int mtl_window_present_texture(uintptr_t window, uintptr_t texture)
{
    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->view || !box->queue || !texture) {
        return 0;
    }

    @autoreleasepool {
        MTLPhpView *view = (__bridge MTLPhpView *)box->view;
        id<MTLCommandQueue> queue = (__bridge id<MTLCommandQueue>)box->queue;
        id<MTLTexture> src = (__bridge id<MTLTexture>)(void *)texture;
        CAMetalLayer *layer = view.metalLayer;
        if (!view || !queue || !src || !layer) {
            return 0;
        }

        layer.pixelFormat = MTLPixelFormatRGBA8Unorm;
        layer.drawableSize = CGSizeMake((CGFloat)src.width, (CGFloat)src.height);

        id<CAMetalDrawable> drawable = [layer nextDrawable];
        if (!drawable || !drawable.texture) {
            return 0;
        }

        NSUInteger w = MIN(src.width, drawable.texture.width);
        NSUInteger h = MIN(src.height, drawable.texture.height);
        if (w == 0 || h == 0) {
            return 0;
        }

        id<MTLCommandBuffer> cmd = [queue commandBuffer];
        if (!cmd) {
            return 0;
        }

        id<MTLBlitCommandEncoder> blit = [cmd blitCommandEncoder];
        if (!blit) {
            return 0;
        }

        [blit copyFromTexture:src
                  sourceSlice:0
                  sourceLevel:0
                 sourceOrigin:MTLOriginMake(0, 0, 0)
                   sourceSize:MTLSizeMake(w, h, 1)
                    toTexture:drawable.texture
             destinationSlice:0
             destinationLevel:0
            destinationOrigin:MTLOriginMake(0, 0, 0)];
        [blit endEncoding];
        [cmd presentDrawable:drawable];
        [cmd commit];
        return 1;
    }
}

int mtl_window_screen_to_content(uintptr_t window, double screen_x, double screen_y, double *out_x, double *out_y)
{
    if (!out_x || !out_y) {
        return 0;
    }

    mtl_window_box *box = mtl_window_box_from(window);
    if (!box || !box->window || !box->view) {
        return 0;
    }

    @autoreleasepool {
        NSWindow *win = (__bridge NSWindow *)box->window;
        NSView *view = (__bridge NSView *)box->view;
        NSPoint screenPt = NSMakePoint((CGFloat)screen_x, (CGFloat)screen_y);
        NSRect screenRect = NSMakeRect(screenPt.x, screenPt.y, 0, 0);
        NSRect windowRect = [win convertRectFromScreen:screenRect];
        NSPoint local = [view convertPoint:windowRect.origin fromView:nil];
        *out_x = (double)local.x;
        *out_y = (double)local.y;
        return 1;
    }
}
