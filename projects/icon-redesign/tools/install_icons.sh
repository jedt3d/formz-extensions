#!/bin/sh
# Copy formZ.app to "<name>.app" beside it and drop built icons into the copy.
# usage: install_icons.sh <built-icons-dir> [copy-name] [formZ-folder]
# The installed formZ.app is only read.
set -eu

ICONS_SRC=${1:?usage: install_icons.sh <built-icons-dir> [copy-name] [formZ-folder]}
NAME=${2:-"formZ style-test"}
APP_DIR=${3:-"/Applications/formZ 10/formZ 10.0 pro"}
SRC="$APP_DIR/formZ.app"
DST="$APP_DIR/$NAME.app"

[ -d "$SRC/Contents/Resources/Icons" ] || { echo "missing $SRC" >&2; exit 1; }
[ ! -e "$DST" ] || { echo "$DST already exists; remove it first" >&2; exit 1; }

ditto "$SRC" "$DST"
n=0
for f in "$ICONS_SRC"/Cic_*.bmp; do
	cp "$f" "$DST/Contents/Resources/Icons/"
	n=$((n + 1))
done
echo "built $DST with $n replaced icons"
