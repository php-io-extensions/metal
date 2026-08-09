#!/bin/bash

# macOS installer for the Metal Zephir extension (Darwin only).
# - Verifies Metal / AppKit frameworks
# - Builds via scripts/prepare-ext.sh + phpize/configure/make
# - Installs .so and enables for detected SAPIs
# - Finds zephir automatically or respects $ZEPHIR_BIN

set -Eeuo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXTENSION_NAME="metal"
BUILD_SO="${SCRIPT_DIR}/ext/modules/${EXTENSION_NAME}.so"
LOG_FILE="${SCRIPT_DIR}/build.log"

if [ "$(uname -s)" != "Darwin" ]; then
    echo "❌ metal is macOS (Darwin) only."
    exit 1
fi

if [ "${EUID:-$(id -u)}" -ne 0 ]; then
    SUDO="sudo"
else
    SUDO=""
fi

die() {
    echo ""
    echo "❌ $*"
    exit 1
}

require_cmd() {
    local cmd="$1"
    command -v "$cmd" >/dev/null 2>&1 || die "Required command not found: $cmd"
}

header() {
    echo "=========================================="
    echo "Metal Extension Installer (macOS)"
    echo "=========================================="
    echo ""
}

step() {
    echo "$*"
}

ok() {
    echo "   ✓ $*"
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
    if [ -f "${SCRIPT_DIR}/compile-errors.log" ]; then
        echo ""
        echo "---- Last 120 lines of compile-errors.log ----"
        tail -120 "${SCRIPT_DIR}/compile-errors.log" || true
    fi
}

ensure_metal_macos() {
    step "🖼️  Verifying Metal / AppKit frameworks..."

    local frameworks=(Metal AppKit QuartzCore Foundation GameController CoreGraphics)
    local fw
    for fw in "${frameworks[@]}"; do
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
}

header

step "🔎 Preflight checks..."
require_cmd php
require_cmd php-config
require_cmd phpize
require_cmd make
require_cmd python3

if [ -n "${ZEPHIR_BIN:-}" ]; then
    ZEPHIR="$ZEPHIR_BIN"
elif command -v zephir >/dev/null 2>&1; then
    ZEPHIR="$(command -v zephir)"
elif [ -x "$HOME/.composer/vendor/bin/zephir" ]; then
    ZEPHIR="$HOME/.composer/vendor/bin/zephir"
elif [ -x "$HOME/.config/composer/vendor/bin/zephir" ]; then
    ZEPHIR="$HOME/.config/composer/vendor/bin/zephir"
else
    die "Zephir not found. Install via composer (composer global require phalcon/zephir) or set ZEPHIR_BIN."
fi
ok "Found zephir: $ZEPHIR"
export ZEPHIR_BIN="$ZEPHIR"

ensure_metal_macos

PHP_VER_MM="$(php -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;')"
PHP_VER_NN="$(php -r 'echo PHP_MAJOR_VERSION.PHP_MINOR_VERSION;')"

PHP_BIN_REAL="$(php -r 'echo PHP_BINARY;' 2>/dev/null)"
PHP_BIN_DIR="$(dirname "$PHP_BIN_REAL")"
RESOLVED_PHP_CONFIG="${PHP_BIN_DIR}/php-config"

if [ -x "$RESOLVED_PHP_CONFIG" ]; then
    PHP_EXT_DIR="$("$RESOLVED_PHP_CONFIG" --extension-dir)"
elif command -v php-config >/dev/null 2>&1; then
    PHP_EXT_DIR="$(php-config --extension-dir)"
else
    die "Could not locate php-config."
fi
[ -n "$PHP_EXT_DIR" ] || die "Could not determine PHP extension dir."

CLI_SCAN_DIR="$(php --ini 2>/dev/null | awk -F': ' '/Scan for additional \.ini files in:/{print $2}' || true)"
if [ -n "$CLI_SCAN_DIR" ] && [ -d "$CLI_SCAN_DIR" ] && ls "$CLI_SCAN_DIR"/*.so >/dev/null 2>&1; then
    PHP_EXT_DIR="$CLI_SCAN_DIR"
fi

ok "PHP version: ${PHP_VER_MM}"
ok "PHP binary: ${PHP_BIN_REAL}"
ok "Extension dir: ${PHP_EXT_DIR}"

export CFLAGS="-Wno-error -Wno-error=incompatible-pointer-types -Wno-pointer-compare"
export CPPFLAGS="${CPPFLAGS:-} -Wno-error -Wno-error=incompatible-pointer-types"
echo ""

step "🧹 Preparing extension sources..."
cd "${SCRIPT_DIR}"
: >"$LOG_FILE"
if ! bash "${SCRIPT_DIR}/scripts/prepare-ext.sh" >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "prepare-ext failed. See ${LOG_FILE}."
fi
ok "Sources prepared"
echo ""

step "🔨 Building extension..."
cd "${SCRIPT_DIR}/ext"
if ! phpize >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "phpize failed. See ${LOG_FILE}."
fi
if ! ./configure --enable-metal >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "configure failed. See ${LOG_FILE}."
fi
if ! make -j1 >>"$LOG_FILE" 2>&1; then
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
$SUDO mkdir -p "$PHP_EXT_DIR"
$SUDO cp -f "$BUILD_SO" "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
$SUDO chmod 755 "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
ok "Copied to: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
echo ""

step "⚙️  Enabling extension..."
declare -a CONF_DIR_CANDIDATES=()

if [ -n "$CLI_SCAN_DIR" ] && [ "$CLI_SCAN_DIR" != "(none)" ] && [ -d "$CLI_SCAN_DIR" ]; then
    CONF_DIR_CANDIDATES+=("$CLI_SCAN_DIR")
fi

for d in "/etc/php/${PHP_VER_MM}/cli/conf.d" "/etc/php/${PHP_VER_MM}/fpm/conf.d" "/etc/php/${PHP_VER_MM}/apache2/conf.d"; do
    [ -d "$d" ] && CONF_DIR_CANDIDATES+=("$d")
done

ALPINE_CONF="/etc/php${PHP_VER_NN}/conf.d"
[ -d "$ALPINE_CONF" ] && CONF_DIR_CANDIDATES+=("$ALPINE_CONF")

CONF_DIRS=()
while IFS= read -r _line; do
    CONF_DIRS+=("$_line")
done < <(printf "%s\n" "${CONF_DIR_CANDIDATES[@]}" | awk '!seen[$0]++')

# Normalize dirs so INI paths never get a double slash (Herd scan dirs often end with /).
PHP_EXT_DIR="${PHP_EXT_DIR%/}"

INI_NAME="30-${EXTENSION_NAME}.ini"
INI_CONTENT="extension=${PHP_EXT_DIR}/${EXTENSION_NAME}.so"

for confd in "${CONF_DIRS[@]:-}"; do
    confd="${confd%/}"
    INI_PATH="${confd}/${INI_NAME}"
    echo "$INI_CONTENT" | $SUDO tee "$INI_PATH" >/dev/null
    ok "Written: $INI_PATH"
done
echo ""

step "🔍 Verifying installation (CLI)..."
VERIFY_OUT="$("$PHP_BIN_REAL" -m 2>&1 || true)"
if printf '%s\n' "$VERIFY_OUT" | grep -q "^${EXTENSION_NAME}$"; then
    ok "Extension loaded successfully in CLI"
else
    echo ""
    echo "   PHP binary used: $PHP_BIN_REAL"
    echo "   Extension dir:   $PHP_EXT_DIR"
    echo "   INI written to:  ${CLI_SCAN_DIR:-unknown}/${INI_NAME}"
    echo "   php -m output:"
    printf '%s\n' "$VERIFY_OUT" | tail -40
    die "Extension not detected in CLI. Check ${INI_NAME} placement and php --ini."
fi
echo ""

step "=========================================="
step "Extension Information (CLI)"
step "=========================================="
"$PHP_BIN_REAL" --ri metal || true
echo ""

# Re-prepare committed ext/ tree (strip build junk) for a clean working tree.
step "🧼 Refreshing deploy-ready ext/ tree..."
cd "${SCRIPT_DIR}"
bash "${SCRIPT_DIR}/scripts/prepare-ext.sh" >>"$LOG_FILE" 2>&1 || true
ok "ext/ cleaned for PIE"

echo "✅ Installation complete!"
echo ""
echo "Demo:"
echo "  php examples/proof_window.php"
echo ""
echo "File locations:"
echo "  • Binary: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
if [ "${#CONF_DIRS[@]}" -gt 0 ]; then
    for d in "${CONF_DIRS[@]}"; do
        echo "  • Config: ${d}/${INI_NAME}"
    done
fi
echo ""
