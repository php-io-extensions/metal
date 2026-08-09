#import <AppKit/AppKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import <GameController/GameController.h>
#import <string.h>
#import "metal-input.h"
#import "metal-window.h"

static BOOL mtl_input_ready = NO;
static double mtl_scroll_dx = 0.0;
static double mtl_scroll_dy = 0.0;

void mtl_input_init(void)
{
    if (mtl_input_ready) {
        return;
    }

    @autoreleasepool {
        [GCController startWirelessControllerDiscoveryWithCompletionHandler:nil];
        mtl_input_ready = YES;
        mtl_scroll_dx = 0.0;
        mtl_scroll_dy = 0.0;
    }
}

void mtl_input_begin_frame(void)
{
    mtl_scroll_dx = 0.0;
    mtl_scroll_dy = 0.0;
}

void mtl_input_handle_event(void *nsevent)
{
    if (!nsevent) {
        return;
    }

    @autoreleasepool {
        NSEvent *event = (__bridge NSEvent *)nsevent;
        if (event.type == NSEventTypeScrollWheel) {
            /* Prefer precise deltas when available (trackpads). */
            if (event.hasPreciseScrollingDeltas) {
                mtl_scroll_dx += (double)event.scrollingDeltaX;
                mtl_scroll_dy += (double)event.scrollingDeltaY;
            } else {
                mtl_scroll_dx += (double)event.deltaX;
                mtl_scroll_dy += (double)event.deltaY;
            }
        }
    }
}

int mtl_input_key_down(int keycode)
{
    if (keycode < 0 || keycode > 0xFFFF) {
        return 0;
    }
    return CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState, (CGKeyCode)keycode) ? 1 : 0;
}

int mtl_input_mouse_button_down(int button)
{
    if (button < 0 || button > 31) {
        return 0;
    }
    @autoreleasepool {
        NSUInteger mask = [NSEvent pressedMouseButtons];
        return (mask & (1UL << (NSUInteger)button)) ? 1 : 0;
    }
}

int mtl_input_mouse_position(uintptr_t window, double *x, double *y)
{
    if (!x || !y) {
        return 0;
    }

    @autoreleasepool {
        NSPoint screen = [NSEvent mouseLocation];
        if (window == 0) {
            *x = (double)screen.x;
            *y = (double)screen.y;
            return 1;
        }
        return mtl_window_screen_to_content(window, (double)screen.x, (double)screen.y, x, y);
    }
}

void mtl_input_mouse_scroll_delta(double *dx, double *dy)
{
    if (dx) {
        *dx = mtl_scroll_dx;
    }
    if (dy) {
        *dy = mtl_scroll_dy;
    }
}

static GCController *mtl_gamepad_at(int index)
{
    if (index < 0) {
        return nil;
    }
    NSArray<GCController *> *pads = [GCController controllers];
    if ((NSUInteger)index >= pads.count) {
        return nil;
    }
    return pads[(NSUInteger)index];
}

int mtl_input_gamepad_count(void)
{
    @autoreleasepool {
        return (int)[GCController controllers].count;
    }
}

int mtl_input_gamepad_name(int index, char *buf, int buf_len)
{
    if (!buf || buf_len <= 0) {
        return 0;
    }
    buf[0] = '\0';

    @autoreleasepool {
        GCController *pad = mtl_gamepad_at(index);
        if (!pad) {
            return 0;
        }
        NSString *name = pad.vendorName ?: pad.productCategory ?: @"Gamepad";
        const char *utf8 = [name UTF8String];
        if (!utf8) {
            return 0;
        }
        strncpy(buf, utf8, (size_t)buf_len - 1);
        buf[buf_len - 1] = '\0';
        return 1;
    }
}

static int mtl_gamepad_button_pressed(GCController *pad, int button)
{
    GCExtendedGamepad *ext = pad.extendedGamepad;
    if (!ext) {
        /* Fallback: microGamepad (Siri Remote-style) — map a subset. */
        GCMicroGamepad *micro = pad.microGamepad;
        if (!micro) {
            return 0;
        }
        switch (button) {
            case 0: return micro.buttonA.pressed ? 1 : 0;
            case 1: return micro.buttonX.pressed ? 1 : 0;
            case 11: return micro.dpad.up.pressed ? 1 : 0;
            case 12: return micro.dpad.right.pressed ? 1 : 0;
            case 13: return micro.dpad.down.pressed ? 1 : 0;
            case 14: return micro.dpad.left.pressed ? 1 : 0;
            default: return 0;
        }
    }

    switch (button) {
        case 0: return ext.buttonA.pressed ? 1 : 0;
        case 1: return ext.buttonB.pressed ? 1 : 0;
        case 2: return ext.buttonX.pressed ? 1 : 0;
        case 3: return ext.buttonY.pressed ? 1 : 0;
        case 4: return ext.leftShoulder.pressed ? 1 : 0;
        case 5: return ext.rightShoulder.pressed ? 1 : 0;
        case 6: return (ext.buttonOptions && ext.buttonOptions.pressed) ? 1 : 0;
        case 7: return (ext.buttonMenu && ext.buttonMenu.pressed) ? 1 : 0;
        case 8: return (ext.buttonHome && ext.buttonHome.pressed) ? 1 : 0;
        case 9: return (ext.leftThumbstickButton && ext.leftThumbstickButton.pressed) ? 1 : 0;
        case 10: return (ext.rightThumbstickButton && ext.rightThumbstickButton.pressed) ? 1 : 0;
        case 11: return ext.dpad.up.pressed ? 1 : 0;
        case 12: return ext.dpad.right.pressed ? 1 : 0;
        case 13: return ext.dpad.down.pressed ? 1 : 0;
        case 14: return ext.dpad.left.pressed ? 1 : 0;
        default: return 0;
    }
}

int mtl_input_gamepad_button_down(int index, int button)
{
    @autoreleasepool {
        GCController *pad = mtl_gamepad_at(index);
        if (!pad) {
            return 0;
        }
        return mtl_gamepad_button_pressed(pad, button);
    }
}

static float mtl_gamepad_axis_value(GCController *pad, int axis)
{
    GCExtendedGamepad *ext = pad.extendedGamepad;
    if (!ext) {
        GCMicroGamepad *micro = pad.microGamepad;
        if (!micro) {
            return 0.0f;
        }
        switch (axis) {
            case 0: return (float)micro.dpad.xAxis.value;
            case 1: return (float)micro.dpad.yAxis.value;
            default: return 0.0f;
        }
    }

    switch (axis) {
        case 0: return (float)ext.leftThumbstick.xAxis.value;
        case 1: return (float)ext.leftThumbstick.yAxis.value;
        case 2: return (float)ext.rightThumbstick.xAxis.value;
        case 3: return (float)ext.rightThumbstick.yAxis.value;
        case 4: return (float)ext.leftTrigger.value;
        case 5: return (float)ext.rightTrigger.value;
        default: return 0.0f;
    }
}

float mtl_input_gamepad_axis(int index, int axis)
{
    @autoreleasepool {
        GCController *pad = mtl_gamepad_at(index);
        if (!pad) {
            return 0.0f;
        }
        return mtl_gamepad_axis_value(pad, axis);
    }
}
