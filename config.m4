PHP_ARG_ENABLE([metal],
  [whether to enable metal support],
  [AS_HELP_STRING([--enable-metal], [Enable Metal bindings])],
  [no])

if test "$PHP_METAL" != "no"; then
  case $host_os in
    darwin*) ;;
    *) AC_MSG_ERROR([metal binds Metal, which only macOS provides]) ;;
  esac

  METAL_SOURCES="src/metal.m src/runtime.m src/MTLDevice.m src/MTLTypes.m src/MTLResource.m src/MTLPipeline.m src/MTLCommand.m src/CAMetalLayer.m"

  dnl No C sources: every translation unit is Objective-C, compiled by the rules below.
  PHP_NEW_EXTENSION([metal], [], [$ext_shared],, [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1])
  PHP_ADD_BUILD_DIR([$ext_builddir/src])

  dnl PHP_ADD_SOURCES only knows .c/.s/.S/.cpp, so the .m rules are written the way
  dnl PHP_ADD_SOURCES_X writes a .c rule, with the ObjC flags added: shared objects for a
  dnl phpize build, PHP's own objects when compiled into PHP. -fno-objc-arc: retain/release
  dnl are explicit.
  case $ext_dir in
    "") metal_srcdir="$abs_srcdir/"; metal_bdir=""; metal_inc="-I. -I$abs_srcdir" ;;
    *) metal_srcdir="$abs_srcdir/$ext_dir/"; metal_bdir="$ext_dir/"; metal_inc="-I$metal_bdir -I$metal_srcdir" ;;
  esac
  if test "$ext_shared" = "yes"; then
    metal_cc="$shared_c_pre $metal_inc $shared_c_meta -DZEND_COMPILE_DL_EXT=1"
    metal_post=$shared_c_post
  else
    metal_cc="$php_c_pre $metal_inc $php_c_meta"
    metal_post=$php_c_post
  fi
  for metal_src in $METAL_SOURCES; do
    metal_obj=$metal_bdir$(echo "$metal_src" | $SED -e 's/\.m$//')
    if test "$ext_shared" = "yes"; then
      shared_objects_metal="$shared_objects_metal $metal_obj.lo"
    else
      PHP_GLOBAL_OBJS="$PHP_GLOBAL_OBJS $metal_obj.lo"
    fi
    cat >>Makefile.objects<<EOF
-include $metal_obj.dep
$metal_obj.lo: $metal_srcdir$metal_src
	$metal_cc -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -x objective-c -fno-objc-arc -fobjc-exceptions -Wno-unused-parameter -c $metal_srcdir$metal_src -o $metal_obj.lo $metal_post -MMD -MF $metal_obj.dep -MT $metal_obj.lo
EOF
  done

  dnl Shared, the frameworks go to the .so; compiled in, to PHP's own link line.
  METAL_FRAMEWORKS="Foundation Metal QuartzCore"
  if test "$ext_shared" = "yes"; then
    for metal_framework in $METAL_FRAMEWORKS; do
      METAL_SHARED_LIBADD="$METAL_SHARED_LIBADD -framework $metal_framework"
    done
    METAL_SHARED_LIBADD="$METAL_SHARED_LIBADD -lobjc"
    PHP_SUBST([METAL_SHARED_LIBADD])
  else
    for metal_framework in $METAL_FRAMEWORKS; do
      PHP_ADD_FRAMEWORK([$metal_framework])
    done
    PHP_ADD_LIBRARY([objc])
  fi
fi
