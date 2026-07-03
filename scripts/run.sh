#!/usr/bin/env sh
set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
cd "$ROOT_DIR"

CONFIG_FILE="config/weights.conf"
DATA_FILE="records.dat"

usage() {
  echo "Usage:"
  echo "  $0 [--category CATEGORY] \"content\""
}

if [ $# -eq 0 ]; then
  usage
  exit 1
fi

if [ "$1" = "--category" ]; then
  if [ $# -lt 3 ]; then
    usage
    exit 1
  fi
  CATEGORY=$2
  shift 2
  CONTENT=$1
  exec ./bin/weight "$CONFIG_FILE" "$DATA_FILE" "$CATEGORY" "$CONTENT"
fi

CONTENT=$1
exec ./bin/weight "$CONFIG_FILE" "$DATA_FILE" "$CONTENT"
