#ifndef PHP_METAL_INPUT_H
#define PHP_METAL_INPUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Human-input C ABI for AppKit + GameController (0.7.2+).
 *
 * Keyboard / mouse button state uses live system queries (CoreGraphics / NSEvent).
 * Scroll deltas accumulate during mtl_app_poll and clear at the start of each poll.
 * Gamepads use Apple's GameController framework (GCController).
 *
 * Mouse / stick Y: AppKit / GCController convention — up is positive.
 * Key codes: macOS virtual key codes (kVK_*), e.g. A=0x00, S=0x01.
 *
 * Mouse buttons: 0=left, 1=right, 2=middle (NSEvent pressedMouseButtons bits).
 * Gamepad buttons: 0=A, 1=B, 2=X, 3=Y, 4=L1, 5=R1, 6=BACK, 7=START, 8=GUIDE,
 *   9=L3, 10=R3, 11=DPAD_UP, 12=DPAD_RIGHT, 13=DPAD_DOWN, 14=DPAD_LEFT.
 * Gamepad axes: 0=LEFT_X, 1=LEFT_Y, 2=RIGHT_X, 3=RIGHT_Y, 4=LEFT_TRIGGER, 5=RIGHT_TRIGGER.
 *   Sticks -1..1; triggers 0..1.
 */

/** Ensure GameController discovery is running. Idempotent. Called from mtl_app_init. */
void mtl_input_init(void);

/** Clear per-poll scroll deltas. Called at the start of mtl_app_poll. */
void mtl_input_begin_frame(void);

/**
 * Observe one NSEvent for scroll accumulation.
 * Implemented in metal-input.m; called from mtl_app_poll before sendEvent.
 * Opaque void* is NSEvent* — C callers pass NULL (no-op).
 */
void mtl_input_handle_event(void *nsevent);

/** 1 if the macOS virtual key code is currently down. */
int mtl_input_key_down(int keycode);

/** 1 if mouse button is currently down (0=left, 1=right, 2=middle). */
int mtl_input_mouse_button_down(int button);

/**
 * Mouse position. window=0 → screen coords (AppKit, origin bottom-left).
 * window!=0 → content-view local coords for that mtl window handle.
 * Returns 1 on success.
 */
int mtl_input_mouse_position(uintptr_t window, double *x, double *y);

/**
 * Scroll deltas accumulated since the last mtl_input_begin_frame / mtl_app_poll.
 * Does not clear (cleared at next begin_frame).
 */
void mtl_input_mouse_scroll_delta(double *dx, double *dy);

/** Number of currently connected GCController pads. */
int mtl_input_gamepad_count(void);

/** UTF-8 product name into buf; returns 1 on success. */
int mtl_input_gamepad_name(int index, char *buf, int buf_len);

/** 1 if digital button is pressed on pad index. */
int mtl_input_gamepad_button_down(int index, int button);

/** Axis value for pad index (see header comment for axis ids). */
float mtl_input_gamepad_axis(int index, int axis);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_INPUT_H */
