#ifndef PHP_METAL_APP_H
#define PHP_METAL_APP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Initialize NSApplication (shared). Idempotent. Returns 1 on success. */
int mtl_app_init(void);

/** Process pending AppKit events once. Returns 1 if the app should keep running. */
int mtl_app_poll(void);

/** Blocking NSApp run loop (rarely used from PHP; prefer poll). */
void mtl_app_run(void);

/** Request application termination. */
void mtl_app_terminate(void);

/** Returns 1 when termination was requested (window close / Quit menu / terminate). */
int mtl_app_should_quit(void);

/** Reset the quit flag (after a previous run). */
void mtl_app_reset_quit(void);

#ifdef __cplusplus
}
#endif

#endif /* PHP_METAL_APP_H */
