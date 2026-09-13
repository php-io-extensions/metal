#!/bin/bash
# Laravel Herd helper — same as install-macos.sh, prefers Herd's PHP on PATH.
# This file only rearranges PATH; the build/install lives in install-macos.sh.
set -Eeuo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if command -v herd >/dev/null 2>&1; then
    HERD_PHP="$(herd which-php 2>/dev/null || true)"
    if [ -n "$HERD_PHP" ] && [ -x "$HERD_PHP" ]; then
        export PATH="$(dirname "$HERD_PHP"):$PATH"
    fi
fi

exec bash "${SCRIPT_DIR}/install-macos.sh"
