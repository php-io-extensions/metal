# Objective-C bridge — phpize does not emit correct rules for .m sources.
MTL_OBJC_CFLAGS = -fobjc-arc -x objective-c -Wno-deprecated-declarations

$(builddir)/src/metal-app.lo: $(srcdir)/src/metal-app.m
	$(LIBTOOL) --tag=CC --mode=compile $(CC) -I. -I$(srcdir) $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS) $(MTL_OBJC_CFLAGS) -DZEND_COMPILE_DL_EXT=1 -c $(srcdir)/src/metal-app.m -o $@

$(builddir)/src/metal-window.lo: $(srcdir)/src/metal-window.m
	$(LIBTOOL) --tag=CC --mode=compile $(CC) -I. -I$(srcdir) $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS) $(MTL_OBJC_CFLAGS) -DZEND_COMPILE_DL_EXT=1 -c $(srcdir)/src/metal-window.m -o $@

$(builddir)/src/metal-menu.lo: $(srcdir)/src/metal-menu.m
	$(LIBTOOL) --tag=CC --mode=compile $(CC) -I. -I$(srcdir) $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS) $(MTL_OBJC_CFLAGS) -DZEND_COMPILE_DL_EXT=1 -c $(srcdir)/src/metal-menu.m -o $@

$(builddir)/src/metal-device.lo: $(srcdir)/src/metal-device.m
	$(LIBTOOL) --tag=CC --mode=compile $(CC) -I. -I$(srcdir) $(COMMON_FLAGS) $(CFLAGS_CLEAN) $(EXTRA_CFLAGS) $(MTL_OBJC_CFLAGS) -DZEND_COMPILE_DL_EXT=1 -c $(srcdir)/src/metal-device.m -o $@

shared_objects_metal += src/metal-app.lo src/metal-window.lo src/metal-menu.lo src/metal-device.lo
