#!/usr/bin/env bash
# Generate Zephir C sources and rewrite ext/config.m4 for Darwin Metal/AppKit.
set -Eeuo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
cd "$ROOT_DIR"

if [ -n "${ZEPHIR_BIN:-}" ]; then
    ZEPHIR="$ZEPHIR_BIN"
elif command -v zephir >/dev/null 2>&1; then
    ZEPHIR="$(command -v zephir)"
elif [ -x "$HOME/.composer/vendor/bin/zephir" ]; then
    ZEPHIR="$HOME/.composer/vendor/bin/zephir"
elif [ -x "$HOME/.config/composer/vendor/bin/zephir" ]; then
    ZEPHIR="$HOME/.config/composer/vendor/bin/zephir"
else
    echo "Zephir not found. Set ZEPHIR_BIN." >&2
    exit 1
fi

echo "Using zephir: $ZEPHIR"
"$ZEPHIR" generate

# Sync Objective-C bridge into ext/ (PIE builds from ext/ only).
mkdir -p ext/src
cp -f src/*.h src/*.m ext/src/
cp -f "${SCRIPT_DIR}/Makefile.frag" ext/Makefile.frag

python3 "${SCRIPT_DIR}/patch-config-m4.py"
python3 "${SCRIPT_DIR}/fixup-zephir-register.py"

# Strip phpize junk so Packagist/PIE never ships host-absolute paths.
cd ext
rm -rf Makefile Makefile.fragments Makefile.objects Makefile.global modules .libs autom4te.cache \
    build configure configure.ac configure~ config.h config.h.in config.h.in~ config.log config.status \
    config.nice libtool run-tests.php install-sh missing mkinstalldirs \
    config.guess config.sub ltmain.sh aclocal.m4 acinclude.m4 \
    metal.so metal.la metal.lo metal.o metal.dep 2>/dev/null || true
rm -rf metal.so.dSYM .libs 2>/dev/null || true
find . -name '*.lo' -delete 2>/dev/null || true
find . -name '*.o' -delete 2>/dev/null || true
find . -name '*.dep' -delete 2>/dev/null || true
find . -name '*.la' -delete 2>/dev/null || true
find . -name '*.so' -delete 2>/dev/null || true
find . -name '.libs' -type d -exec rm -rf {} + 2>/dev/null || true
find . -name '*.dSYM' -type d -exec rm -rf {} + 2>/dev/null || true
cd "$ROOT_DIR"

echo "prepare-ext: done"
