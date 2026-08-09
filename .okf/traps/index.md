# Traps

* [Darwin-only builds](darwin-only.md) - Linux/Windows will not build or load
* [No SDL3/GLFW coupling](no-sdl-glfw-coupling.md) - Standalone product boundary
* [poll vs run](poll-vs-run.md) - Prefer App::poll() from PHP event loops
* [ObjC Makefile.frag required](objc-makefile-frag.md) - phpize mishandles .m sources
* [Framework link via METAL_SHARED_LIBADD](framework-shared-libadd.md) - PHP_ADD_FRAMEWORK is not enough
* [Explicit CAMetalLayer assignment](cametal-layer-assign.md) - Do not rely on layerClass alone
* [Prefer make -j1](parallel-make.md) - Conservative ObjC fragment builds
