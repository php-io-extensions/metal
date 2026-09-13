#!/bin/bash
#
# macOS installer for the Metal Zephir extension (Darwin only).
#
#   prepare-ext → phpize → configure --enable-metal → make
#   → cp → xattr -cr + codesign --force --sign -
#   → 30-metal.ini → php -m / php --ri metal
#
# A copied Mach-O is SIGKILLed on Apple Silicon unless it is ad-hoc
# re-signed after cp. Respects $ZEPHIR_BIN.

set -Eeuo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXTENSION_NAME="metal"
# config.json is the single source of truth: zephir generates ext/php_metal.h
# from it. composer.json is the one copy nothing generates, so it is asserted
# against config.json rather than trusted.
EXPECTED_VERSION="$(sed -n 's/.*"version"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/p' "${SCRIPT_DIR}/config.json" | head -1)"
COMPOSER_VERSION="$(sed -n 's/.*"version"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/p' "${SCRIPT_DIR}/composer.json" | head -1)"
LOG_FILE="${SCRIPT_DIR}/build.log"
BUILD_ROOT="${SCRIPT_DIR}"
BUILD_TMP=""

cleanup_build_tmp() {
    if [ -n "${BUILD_TMP}" ] && [ -d "${BUILD_TMP}" ]; then
        rm -rf "${BUILD_TMP}"
    fi
}
trap cleanup_build_tmp EXIT

if [ "$(uname -s)" != "Darwin" ]; then
    echo "❌ metal is macOS (Darwin) only."
    exit 1
fi

if [ "${EUID:-$(id -u)}" -ne 0 ]; then
    SUDO="sudo"
else
    SUDO=""
fi

die()  { echo ""; echo "❌ $*"; exit 1; }
step() { echo "$*"; }
ok()   { echo "   ✓ $*"; }

if [ -z "${EXPECTED_VERSION}" ]; then
    die "Could not read \"version\" from config.json"
fi
if [ "${COMPOSER_VERSION}" != "${EXPECTED_VERSION}" ]; then
    die "Version mismatch: config.json is ${EXPECTED_VERSION}, composer.json is ${COMPOSER_VERSION}"
fi

require_cmd() {
    command -v "$1" >/dev/null 2>&1 || die "Required command not found: $1"
}

show_failure_logs() {
    if [ -f "$LOG_FILE" ]; then
        echo ""
        echo "---- Errors in ${LOG_FILE} ----"
        grep -i "error:" "$LOG_FILE" | grep -v "warning:" | grep -v "note:" || true
        echo ""
        echo "---- Last 80 lines of ${LOG_FILE} ----"
        tail -80 "$LOG_FILE" || true
    fi
}

echo "=========================================="
echo " Metal Extension Installer (macOS)"
echo "=========================================="
echo ""

step "🔎 Preflight checks..."
require_cmd php
require_cmd make
require_cmd codesign

if [ -n "${ZEPHIR_BIN:-}" ]; then
    ZEPHIR="$ZEPHIR_BIN"
elif command -v zephir >/dev/null 2>&1; then
    ZEPHIR="$(command -v zephir)"
elif [ -x "$HOME/.composer/vendor/bin/zephir" ]; then
    ZEPHIR="$HOME/.composer/vendor/bin/zephir"
elif [ -x "$HOME/.config/composer/vendor/bin/zephir" ]; then
    ZEPHIR="$HOME/.config/composer/vendor/bin/zephir"
else
    die "Zephir not found. Install via: composer global require phalcon/zephir  (or set ZEPHIR_BIN)"
fi
ok "Found zephir: $ZEPHIR"
export ZEPHIR_BIN="$ZEPHIR"

step "🖼️  Verifying Metal frameworks..."
for fw in Metal Foundation QuartzCore; do
    if [ -d "/System/Library/Frameworks/${fw}.framework" ]; then
        ok "${fw}.framework found"
        continue
    fi
    if [ -n "${SDKROOT:-}" ] && [ -d "${SDKROOT}/System/Library/Frameworks/${fw}.framework" ]; then
        ok "${fw}.framework found in SDKROOT"
        continue
    fi
    die "${fw}.framework was not found. Expected on macOS."
done

PHP_VER_MM="$(php -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;')"
PHP_BIN_REAL="$(php -r 'echo PHP_BINARY;' 2>/dev/null)"
PHP_BIN_DIR="$(dirname "$PHP_BIN_REAL")"
_PHP_VER_NODOT="${PHP_VER_MM//./}"

# php-config / phpize next to the PHP binary first (Herd, asdf, versioned names).
# Autoconf cannot handle whitespace in --with-php-config even when quoted.
RESOLVED_PHP_CONFIG=""
for _candidate in \
    "${PHP_BIN_DIR}/php-config${_PHP_VER_NODOT}" \
    "${PHP_BIN_DIR}/php-config" \
    "$(command -v "php-config${_PHP_VER_NODOT}" 2>/dev/null || true)" \
    "$(command -v php-config 2>/dev/null || true)"
do
    if [ -x "$_candidate" ]; then
        RESOLVED_PHP_CONFIG="$_candidate"
        break
    fi
done
[ -n "$RESOLVED_PHP_CONFIG" ] || die "Could not locate php-config. Install php-dev or set PHP_CONFIG."

RESOLVED_PHPIZE=""
for _candidate in \
    "${PHP_BIN_DIR}/phpize${_PHP_VER_NODOT}" \
    "${PHP_BIN_DIR}/phpize" \
    "$(command -v "phpize${_PHP_VER_NODOT}" 2>/dev/null || true)" \
    "$(command -v phpize 2>/dev/null || true)"
do
    if [ -x "$_candidate" ]; then
        RESOLVED_PHPIZE="$_candidate"
        break
    fi
done
[ -n "$RESOLVED_PHPIZE" ] || die "Could not locate phpize."

PHP_EXT_DIR="$("$RESOLVED_PHP_CONFIG" --extension-dir)"
[ -n "$PHP_EXT_DIR" ] || die "Could not determine PHP extension dir."

CLI_SCAN_DIR="$(php --ini 2>/dev/null | awk -F': ' '/Scan for additional \.ini files in:/{print $2}' || true)"
if [ -n "$CLI_SCAN_DIR" ] && [ "$CLI_SCAN_DIR" != "(none)" ] && [ -d "$CLI_SCAN_DIR" ] && \
   ls "$CLI_SCAN_DIR"/*.so >/dev/null 2>&1; then
    PHP_EXT_DIR="$CLI_SCAN_DIR"
fi

ok "PHP version:   ${PHP_VER_MM}"
ok "PHP binary:    ${PHP_BIN_REAL}"
ok "php-config:    ${RESOLVED_PHP_CONFIG}"
ok "Extension dir: ${PHP_EXT_DIR}"

export CFLAGS="${CFLAGS:-} -Wno-error -Wno-error=incompatible-pointer-types -Wno-pointer-compare"
export CPPFLAGS="${CPPFLAGS:-} -Wno-error -Wno-error=incompatible-pointer-types"
echo ""

step "📦 prepare-ext (zephir generate, stage src/, patch config.m4)..."
cd "${SCRIPT_DIR}"
: >"$LOG_FILE"
if ! bash "${SCRIPT_DIR}/scripts/prepare-ext.sh" >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "prepare-ext failed. See ${LOG_FILE}."
fi
ok "Sources prepared"
echo ""

# Homebrew phpize rejects whitespace in the build cwd ("metal copy", etc.).
step "🔨 phpize / configure --enable-metal / make..."
case "${SCRIPT_DIR}" in
    *\ * | *$'\t'*)
        BUILD_TMP="$(mktemp -d "${TMPDIR:-/tmp}/metal-ext-build.XXXXXX")"
        case "${BUILD_TMP}" in
            *\ * | *$'\t'*)
                die "Temp build dir still contains whitespace: ${BUILD_TMP}. Set TMPDIR to a path without spaces."
                ;;
        esac
        step "   Staging build in ${BUILD_TMP} (phpize forbids whitespace in source path)..."
        if command -v rsync >/dev/null 2>&1; then
            rsync -a --delete "${SCRIPT_DIR}/ext/" "${BUILD_TMP}/ext/"
        else
            rm -rf "${BUILD_TMP}/ext"
            mkdir -p "${BUILD_TMP}/ext"
            cp -R "${SCRIPT_DIR}/ext/." "${BUILD_TMP}/ext/"
        fi
        BUILD_ROOT="${BUILD_TMP}"
        ok "Staged space-free build tree"
        ;;
esac

BUILD_SO="${BUILD_ROOT}/ext/modules/${EXTENSION_NAME}.so"
cd "${BUILD_ROOT}/ext"
if ! "$RESOLVED_PHPIZE" >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "phpize failed. See ${LOG_FILE}."
fi
if ! ./configure --enable-metal "--with-php-config=${RESOLVED_PHP_CONFIG}" >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "configure --enable-metal failed. See ${LOG_FILE}."
fi
if ! make -j"$(sysctl -n hw.logicalcpu 2>/dev/null || echo 2)" >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "make failed. See ${LOG_FILE}."
fi
if [ ! -f "$BUILD_SO" ]; then
    show_failure_logs
    die "Build output not found at ${BUILD_SO}."
fi
ok "Build complete"
echo ""

step "📦 Installing binary..."
PHP_EXT_DIR="${PHP_EXT_DIR%/}"
$SUDO mkdir -p "$PHP_EXT_DIR"
$SUDO cp -f "$BUILD_SO" "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
$SUDO chmod 755 "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
# Copied Mach-O pages invalidate the linker-signed adhoc seal → SIGKILL.
$SUDO xattr -cr "${PHP_EXT_DIR}/${EXTENSION_NAME}.so" 2>/dev/null || true
$SUDO codesign --force --sign - "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
sleep 2
ok "Copied, xattr-cleared, and adhoc-signed: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
echo ""

step "⚙️  Enabling extension (30-metal.ini)..."
declare -a CONF_DIR_CANDIDATES=()

if [ -n "${CLI_SCAN_DIR:-}" ] && [ "$CLI_SCAN_DIR" != "(none)" ] && [ -d "$CLI_SCAN_DIR" ]; then
    CONF_DIR_CANDIDATES+=("$CLI_SCAN_DIR")
fi
for d in "/etc/php/${PHP_VER_MM}/cli/conf.d" "/etc/php/${PHP_VER_MM}/fpm/conf.d"; do
    [ -d "$d" ] && CONF_DIR_CANDIDATES+=("$d")
done

CONF_DIRS=()
while IFS= read -r _line; do
    CONF_DIRS+=("$_line")
done < <(printf "%s\n" "${CONF_DIR_CANDIDATES[@]:-}" | awk '!seen[$0]++')

[ "${#CONF_DIRS[@]}" -eq 0 ] && echo "   ⚠️  No conf.d directories found."

INI_NAME="30-${EXTENSION_NAME}.ini"
INI_CONTENT="extension=${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
for confd in "${CONF_DIRS[@]:-}"; do
    confd="${confd%/}"
    INI_PATH="${confd}/${INI_NAME}"
    echo "$INI_CONTENT" | $SUDO tee "$INI_PATH" >/dev/null
    ok "Written: $INI_PATH"
done
echo ""

step "🔍 Verifying installation (php -m / php --ri metal)..."
VERIFY_OUT="$("$PHP_BIN_REAL" -m 2>&1 || true)"
if ! printf '%s\n' "$VERIFY_OUT" | grep -qx "${EXTENSION_NAME}"; then
    echo ""
    echo "   PHP binary used: $PHP_BIN_REAL"
    echo "   Extension dir:   $PHP_EXT_DIR"
    echo "   INI written to:  ${CLI_SCAN_DIR:-unknown}/${INI_NAME}"
    echo "   php -m output:"
    printf '%s\n' "$VERIFY_OUT" | tail -40
    die "Extension not detected in php -m. Check ${INI_NAME} placement and php --ini."
fi
ok "php -m lists ${EXTENSION_NAME}"

RI_OUT="$("$PHP_BIN_REAL" --ri metal 2>&1)" || die "php --ri metal failed"
if ! printf '%s\n' "$RI_OUT" | grep -qE "Version[[:space:]]*=>[[:space:]]*${EXPECTED_VERSION//./\\.}([[:space:]]|$)"; then
    echo "$RI_OUT"
    die "php --ri metal did not report version ${EXPECTED_VERSION} (from config.json); the installed .so is stale"
fi
ok "php --ri metal reports ${EXPECTED_VERSION}"
echo ""

step "=========================================="
step " Extension Information (CLI)"
step "=========================================="
printf '%s\n' "$RI_OUT"
echo ""

echo "✅ Installation complete!"
echo ""
echo "File locations:"
echo "  • Binary: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
for d in "${CONF_DIRS[@]:-}"; do
    echo "  • Config: ${d%/}/${INI_NAME}"
done
echo ""
