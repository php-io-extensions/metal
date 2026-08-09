PHP_ARG_ENABLE(metal, whether to enable metal, [ --enable-metal   Enable Metal])

if test "$PHP_METAL" = "yes"; then

	AC_CANONICAL_HOST
	case "$host_os" in
		darwin*)
			;;
		*)
			AC_MSG_ERROR([The metal extension requires macOS (Darwin).])
			;;
	esac

	dnl Zephir-generated C is noisy on modern clang; keep build green.
	CFLAGS="$CFLAGS -Wno-error=incompatible-pointer-types -Wno-error=int-conversion -Wno-error=implicit-function-declaration -Wno-error=implicit-int -fobjc-arc"
	OBJCFLAGS="$OBJCFLAGS -fobjc-arc -Wno-deprecated-declarations"

	AC_DEFINE(HAVE_METAL, 1, [Whether you have Metal])
	dnl ObjC .m sources are wired via Makefile.frag — phpize mishandles .m rules.
	metal_sources="metal.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c metal/mtl/app.zep.c metal/mtl/device.zep.c metal/mtl/menu.zep.c metal/mtl/window.zep.c"
	PHP_NEW_EXTENSION(metal, $metal_sources, $ext_shared,, )
	PHP_ADD_BUILD_DIR([$ext_builddir/kernel/])
	for dir in "metal/mtl" "src"; do
		PHP_ADD_BUILD_DIR([$ext_builddir/$dir])
	done
	PHP_ADD_MAKEFILE_FRAGMENT
	dnl Link Apple frameworks into the shared module (PHP_ADD_FRAMEWORK is for php binary).
	METAL_SHARED_LIBADD="$METAL_SHARED_LIBADD -framework Foundation -framework AppKit -framework Metal -framework QuartzCore"
	PHP_SUBST(METAL_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([metal], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([metal], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_ADD_INCLUDE([$ext_srcdir/src])
	PHP_ADD_INCLUDE([$ext_builddir/src])

	PHP_INSTALL_HEADERS([ext/metal], [php_METAL.h])

fi
