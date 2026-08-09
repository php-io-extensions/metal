#!/usr/bin/env python3
"""Fix Zephir 0.19 ZEPHIR_REGISTER_CLASS truncation for Metal\\MTL\\* classes."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EXT = ROOT / "ext"

# Map truncated register names → correct Zend class name + file hint
FIXES = {
    "Metal\\MT\\App": "Metal\\MTL\\App",
    "Metal\\MT\\Device": "Metal\\MTL\\Device",
    "Metal\\MT\\Menu": "Metal\\MTL\\Menu",
    "Metal\\MT\\Window": "Metal\\MTL\\Window",
    "Metal\\MT\\Texture": "Metal\\MTL\\Texture",
}


def fix_file(path: Path) -> int:
    text = path.read_text(encoding="utf-8")
    original = text
    for bad, good in FIXES.items():
        # ZEPHIR_REGISTER_CLASS(Metal\\MT, App, ...
        # Also init entries that embed the truncated name.
        text = text.replace(bad, good)
    # Common 0.19 truncation pattern: Metal_MT_App → Metal_MTL_App in symbols if present
    text = re.sub(r"\bMetal_MT_(App|Device|Menu|Window|Texture)\b", r"Metal_MTL_\1", text)
    if text != original:
        path.write_text(text, encoding="utf-8")
        return 1
    return 0


def main() -> None:
    if not EXT.exists():
        raise SystemExit("ext/ missing — run zephir generate first")
    changed = 0
    for path in EXT.rglob("*.c"):
        changed += fix_file(path)
    for path in EXT.rglob("*.h"):
        changed += fix_file(path)
    print(f"fixup-zephir-register: touched {changed} files")


if __name__ == "__main__":
    main()
