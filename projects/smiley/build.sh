#!/bin/sh
set -e
HERE="$(cd "$(dirname "$0")" && pwd)"
exec "$HERE/../../scripts/build_plugin.sh" "$HERE" Smiley
