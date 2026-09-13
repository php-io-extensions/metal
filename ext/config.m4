PHP_ARG_ENABLE(metal, whether to enable metal, [ --enable-metal   Enable Metal])

if test "$PHP_METAL" = "yes"; then

	

	METAL_SHARED_LIBADD="$METAL_SHARED_LIBADD -framework Foundation -framework Metal -framework QuartzCore"

	AC_DEFINE(HAVE_METAL, 1, [Whether you have Metal])
	metal_sources="metal.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c metal/bridge/bridge.zep.c
	metal/mtl/mtlblitcommandencoder/mtlblitcommandencoder.zep.c
	metal/mtl/mtlbuffer/mtlbuffer.zep.c
	metal/mtl/mtlcommandbuffer/mtlcommandbuffer.zep.c
	metal/mtl/mtlcommandencoder/mtlcommandencoder.zep.c
	metal/mtl/mtlcommandqueue/mtlcommandqueue.zep.c
	metal/mtl/mtlcomputecommandencoder/mtlcomputecommandencoder.zep.c
	metal/mtl/mtlcomputepipelinestate/mtlcomputepipelinestate.zep.c
	metal/mtl/mtldepthstencildescriptor/mtldepthstencildescriptor.zep.c
	metal/mtl/mtldepthstencilstate/mtldepthstencilstate.zep.c
	metal/mtl/mtldevice/mtldevice.zep.c
	metal/mtl/mtlfunction/mtlfunction.zep.c
	metal/mtl/mtllibrary/mtllibrary.zep.c
	metal/mtl/mtlrendercommandencoder/mtlrendercommandencoder.zep.c
	metal/mtl/mtlrenderpassattachmentdescriptor/mtlrenderpassattachmentdescriptor.zep.c
	metal/mtl/mtlrenderpasscolorattachmentdescriptor/mtlrenderpasscolorattachmentdescriptor.zep.c
	metal/mtl/mtlrenderpasscolorattachmentdescriptorarray/mtlrenderpasscolorattachmentdescriptorarray.zep.c
	metal/mtl/mtlrenderpassdescriptor/mtlrenderpassdescriptor.zep.c
	metal/mtl/mtlrenderpipelinecolorattachmentdescriptor/mtlrenderpipelinecolorattachmentdescriptor.zep.c
	metal/mtl/mtlrenderpipelinecolorattachmentdescriptorarray/mtlrenderpipelinecolorattachmentdescriptorarray.zep.c
	metal/mtl/mtlrenderpipelinedescriptor/mtlrenderpipelinedescriptor.zep.c
	metal/mtl/mtlrenderpipelinestate/mtlrenderpipelinestate.zep.c
	metal/mtl/mtlsamplerdescriptor/mtlsamplerdescriptor.zep.c
	metal/mtl/mtlsamplerstate/mtlsamplerstate.zep.c
	metal/mtl/mtltexture/mtltexture.zep.c
	metal/mtl/mtltexturedescriptor/mtltexturedescriptor.zep.c
	metal/mtl/mtlvertexattributedescriptor/mtlvertexattributedescriptor.zep.c
	metal/mtl/mtlvertexattributedescriptorarray/mtlvertexattributedescriptorarray.zep.c
	metal/mtl/mtlvertexbufferlayoutdescriptor/mtlvertexbufferlayoutdescriptor.zep.c
	metal/mtl/mtlvertexbufferlayoutdescriptorarray/mtlvertexbufferlayoutdescriptorarray.zep.c
	metal/mtl/mtlvertexdescriptor/mtlvertexdescriptor.zep.c
	metal/quartzcore/cametaldrawable/cametaldrawable.zep.c
	metal/quartzcore/cametallayer/cametallayer.zep.c"
	PHP_NEW_EXTENSION(metal, $metal_sources, $ext_shared,, -fobjc-arc -Wno-deprecated-declarations)
	shared_objects_metal="$shared_objects_metal src/ca-metallayer.lo src/mtl-blitcommandencoder.lo src/mtl-bridge.lo src/mtl-buffer.lo src/mtl-commandbuffer.lo src/mtl-commandencoder.lo src/mtl-commandqueue.lo src/mtl-computecommandencoder.lo src/mtl-computepipeline.lo src/mtl-depthstencil.lo src/mtl-device.lo src/mtl-library.lo src/mtl-rendercommandencoder.lo src/mtl-renderpass.lo src/mtl-renderpipeline.lo src/mtl-sampler.lo src/mtl-texture.lo src/mtl-vertexdescriptor.lo"
	PHP_ADD_BUILD_DIR([$ext_builddir/kernel/])
	for dir in "metal/bridge metal/mtl/mtlblitcommandencoder metal/mtl/mtlbuffer metal/mtl/mtlcommandbuffer metal/mtl/mtlcommandencoder metal/mtl/mtlcommandqueue metal/mtl/mtlcomputecommandencoder metal/mtl/mtlcomputepipelinestate metal/mtl/mtldepthstencildescriptor metal/mtl/mtldepthstencilstate metal/mtl/mtldevice metal/mtl/mtlfunction metal/mtl/mtllibrary metal/mtl/mtlrendercommandencoder metal/mtl/mtlrenderpassattachmentdescriptor metal/mtl/mtlrenderpasscolorattachmentdescriptor metal/mtl/mtlrenderpasscolorattachmentdescriptorarray metal/mtl/mtlrenderpassdescriptor metal/mtl/mtlrenderpipelinecolorattachmentdescriptor metal/mtl/mtlrenderpipelinecolorattachmentdescriptorarray metal/mtl/mtlrenderpipelinedescriptor metal/mtl/mtlrenderpipelinestate metal/mtl/mtlsamplerdescriptor metal/mtl/mtlsamplerstate metal/mtl/mtltexture metal/mtl/mtltexturedescriptor metal/mtl/mtlvertexattributedescriptor metal/mtl/mtlvertexattributedescriptorarray metal/mtl/mtlvertexbufferlayoutdescriptor metal/mtl/mtlvertexbufferlayoutdescriptorarray metal/mtl/mtlvertexdescriptor metal/quartzcore/cametaldrawable metal/quartzcore/cametallayer"; do
		PHP_ADD_BUILD_DIR([$ext_builddir/$dir])
	done
	PHP_ADD_BUILD_DIR([$ext_builddir/src])
	PHP_ADD_MAKEFILE_FRAGMENT
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

	PHP_INSTALL_HEADERS([ext/metal], [php_METAL.h])

fi
