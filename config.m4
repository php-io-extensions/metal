PHP_ARG_ENABLE([metal],
  [whether to enable metal support],
  [AS_HELP_STRING([--enable-metal], [Enable Metal bindings])],
  [no])

if test "$PHP_METAL" != "no"; then
  case $host_os in
    darwin*) ;;
    *) AC_MSG_ERROR([metal binds Metal, which only macOS provides]) ;;
  esac

  if test "$ext_shared" != "yes"; then
    AC_MSG_ERROR([metal builds as a shared extension only])
  fi

  METAL_SOURCES="src/metal.m src/runtime.m src/MTLDevice.m src/MTLTypes.m src/MTLResource.m src/MTLPipeline.m src/MTLCommand.m src/CAMetalLayer.m"

  dnl No C sources: every translation unit is Objective-C, compiled by the rules below.
  PHP_NEW_EXTENSION([metal], [], [$ext_shared],, [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1])
  PHP_ADD_BUILD_DIR([$ext_builddir/src])

  dnl PHP_ADD_SOURCES only knows .c/.s/.S/.cpp, so the .m rules are written the way it
  dnl writes a .c rule, with the ObjC flags added. -fno-objc-arc: retain/release are explicit.
  for metal_src in $METAL_SOURCES; do
    metal_obj=$(echo "$metal_src" | $SED -e 's/\.m$//')
    shared_objects_metal="$shared_objects_metal $metal_obj.lo"
    cat >>Makefile.objects<<EOF
-include $metal_obj.dep
$metal_obj.lo: $abs_srcdir/$metal_src
	$shared_c_pre -I. -I$abs_srcdir $shared_c_meta -DZEND_COMPILE_DL_EXT=1 -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -x objective-c -fno-objc-arc -fobjc-exceptions -Wno-unused-parameter -c $abs_srcdir/$metal_src -o $metal_obj.lo $shared_c_post -MMD -MF $metal_obj.dep -MT $metal_obj.lo
EOF
  done

  METAL_SHARED_LIBADD="-framework Foundation -framework Metal -framework QuartzCore -lobjc"
  PHP_SUBST([METAL_SHARED_LIBADD])
fi
