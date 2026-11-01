#!/bin/sh
set -e
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
exec "$ROOT/scripts/build_plugin.sh" "$ROOT/sdk/FZ_SDK_923/Samples/Tools/Triangle" Triangle
