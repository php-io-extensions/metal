#!/bin/bash
# Laravel Herd helper — same as install-macos.sh, prefers Herd's PHP on PATH.
set -Eeuo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if command -v herd >/dev/null 2>&1; then
    # Ensure herd's linked PHP is first on PATH when available.
    HERD_PHP="$(herd which-php 2>/dev/null || true)"
    if [ -n "$HERD_PHP" ] && [ -x "$HERD_PHP" ]; then
        export PATH="$(dirname "$HERD_PHP"):$PATH"
    fi
fi

exec bash "${SCRIPT_DIR}/install-macos.sh"
