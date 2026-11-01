#!/bin/sh
# Build a formZ SDK plugin into build/<Name>/<Name>.fzp (universal) plus its .fzr/.bmp resources.
# usage: ./scripts/build_plugin.sh <plugin source dir containing src/c src/h src/fzr> <Name>
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
[ "$#" -eq 2 ] || { echo "usage: $0 <plugin dir> <Name>"; exit 1; }
SRC="$1"; NAME="$2"
case "$NAME" in
	''|*[!A-Za-z0-9_-]*) echo "plugin name must contain only letters, digits, underscores, or hyphens"; exit 1 ;;
esac
[ -d "$SRC/src/c" ] && [ -n "$NAME" ] || { echo "usage: $0 <plugin dir> <Name>"; exit 1; }
[ -f "$ROOT/sdk/FZ_SDK_923/src/h/fz_api.h" ] || { echo "SDK missing: place FZ_SDK_923 in $ROOT/sdk/"; exit 1; }
OUT="$ROOT/build/$NAME"
rm -rf "$OUT"; mkdir -p "$OUT/$NAME.fzp/Contents/MacOS"

clang -arch arm64 -arch x86_64 -mmacosx-version-min=10.14 -bundle -std=gnu99 -fno-inline -w \
	-I"$ROOT/sdk/FZ_SDK_923/src/h" -I"$SRC/src/h" "$SRC"/src/c/*.c \
	-o "$OUT/$NAME.fzp/Contents/MacOS/$NAME"

printf 'fzplVTVS' > "$OUT/$NAME.fzp/Contents/PkgInfo"
cat > "$OUT/$NAME.fzp/Contents/Info.plist" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleExecutable</key><string>$NAME</string>
	<key>CFBundleIdentifier</key><string>dev.formz-dev.$NAME.fzp</string>
	<key>CFBundleInfoDictionaryVersion</key><string>6.0</string>
	<key>CFBundlePackageType</key><string>fzpl</string>
	<key>CFBundleSignature</key><string>VTVS</string>
	<key>CFBundleVersion</key><string>1.0</string>
	<key>CSResourcesFileMapped</key><string>yes</string>
</dict>
</plist>
EOF
cp "$SRC"/src/fzr/* "$OUT/" 2>/dev/null || true
codesign --force -s - "$OUT/$NAME.fzp"
echo "built $OUT"
