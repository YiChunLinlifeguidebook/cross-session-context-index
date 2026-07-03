#!/usr/bin/env sh
set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
cd "$ROOT_DIR"

if [ ! -x ./bin/index ]; then
  echo "bin/index not found. Run ./scripts/build.sh first."
  exit 1
fi

./bin/index records.dat "$@"
