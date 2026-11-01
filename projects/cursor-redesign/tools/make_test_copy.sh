#!/bin/sh
# Build "formZ cursor-test.app" beside the installed formZ.app, using the
# vendor's existing art: each Cur_<id>.tif gets its HD/ art as a second
# (Retina) representation, and HotSpots.txt is rewritten in 32-pt space
# (FINDINGS.md D1, D4, D5, 6a). The installed app is only read.
set -eu

APP_DIR=${1:-"/Applications/formZ 10/formZ 10.0 pro"}
SRC="$APP_DIR/formZ.app"
DST="$APP_DIR/formZ cursor-test.app"
CUR="$DST/Contents/Resources/Cursors"
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT

[ -d "$SRC/Contents/Resources/Cursors" ] || { echo "missing $SRC" >&2; exit 1; }
[ ! -e "$DST" ] || { echo "$DST already exists; remove it first" >&2; exit 1; }

ditto "$SRC" "$DST"

px() { sips -g pixelWidth "$1" | awk 'NR==2{print $2}'; }

# Merge base + HD into one multi-representation TIFF per ID, only where the
# HD art is exactly 2x (614 and 616 already ship oversized base files).
for hd in "$CUR"/HD/Cur_*.tif; do
	name=$(basename "$hd")
	[ "$(px "$hd")" -eq $(($(px "$CUR/$name") * 2)) ] || { echo "skip $name (HD not 2x)"; continue; }
	tiffutil -cathidpicheck "$CUR/$name" "$hd" -out "$TMP/$name" >/dev/null 2>&1
	mv "$TMP/$name" "$CUR/$name"
done

# Hotspots: read every row (ignore the stale count), add the missing IDs,
# drop rows without files, then scale to the 32-pt canvas formZ forces.
tr '\r' '\n' < "$CUR/HotSpots.txt" | sed '1d;/^$/d' > "$TMP/rows"
printf '309,5,5\n310,5,5\n507,7,7\n508,7,7\n' >> "$TMP/rows"
: > "$TMP/out"
while IFS=, read -r id x y; do
	f="$CUR/Cur_$id.tif"
	[ -f "$f" ] || continue
	w=$(px "$f")
	# Base pixel width is the first representation; 32 px and larger already match 32 pt.
	case $w in
	16) x=$((x * 2)) y=$((y * 2)) ;;
	24) x=$((x * 4 / 3)) y=$((y * 4 / 3)) ;;
	esac
	printf '%s,%s,%s\r' "$id" "$x" "$y" >> "$TMP/out"
done < "$TMP/rows"
{ printf '%s\r' "$(tr '\r' '\n' < "$TMP/out" | grep -c .)"; cat "$TMP/out"; } > "$CUR/HotSpots.txt"

rm -rf "$CUR/HD" "$CUR/Cur_614@2x.tif" "$CUR/Cur_612.bmp"
echo "built $DST"
