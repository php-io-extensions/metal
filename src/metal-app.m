#import <AppKit/AppKit.h>
#import "metal-app.h"
#import "metal-input.h"

static BOOL mtl_app_ready = NO;
static BOOL mtl_app_quit = NO;

@interface MTLAppDelegate : NSObject <NSApplicationDelegate>
@end

@implementation MTLAppDelegate
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    (void)sender;
    return NO;
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
    (void)sender;
    mtl_app_quit = YES;
    return NSTerminateCancel;
}
@end

static MTLAppDelegate *mtl_app_delegate = nil;

int mtl_app_init(void)
{
    if (mtl_app_ready) {
        return 1;
    }

    @autoreleasepool {
        [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

        mtl_app_delegate = [MTLAppDelegate new];
        [NSApp setDelegate:mtl_app_delegate];

        [NSApp finishLaunching];
        mtl_app_ready = YES;
        mtl_app_quit = NO;
        mtl_input_init();
    }

    return 1;
}

int mtl_app_poll(void)
{
    if (!mtl_app_ready) {
        return 0;
    }

    @autoreleasepool {
        mtl_input_begin_frame();
        NSEvent *event;
        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                           untilDate:[NSDate distantPast]
                                              inMode:NSDefaultRunLoopMode
                                             dequeue:YES])) {
            mtl_input_handle_event((__bridge void *)event);
            [NSApp sendEvent:event];
        }
        [NSApp updateWindows];
    }

    return mtl_app_quit ? 0 : 1;
}

void mtl_app_run(void)
{
    if (!mtl_app_ready) {
        mtl_app_init();
    }
    [NSApp run];
}

void mtl_app_terminate(void)
{
    mtl_app_quit = YES;
    if (mtl_app_ready) {
        [NSApp stop:nil];
        // Nudge the run loop so stop is noticed if someone called run().
        NSEvent *event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                            location:NSMakePoint(0, 0)
                                       modifierFlags:0
                                           timestamp:0
                                        windowNumber:0
                                             context:nil
                                             subtype:0
                                               data1:0
                                               data2:0];
        [NSApp postEvent:event atStart:YES];
    }
}

int mtl_app_should_quit(void)
{
    return mtl_app_quit ? 1 : 0;
}

void mtl_app_reset_quit(void)
{
    mtl_app_quit = NO;
}
