#!/bin/bash
set -e

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
MYBASH_DIR="$ROOT_DIR/exercises/20_mybash"

cd "$MYBASH_DIR"

./bin/myfile ./bin/mybash
./bin/myfile ./obj/mybash/main.o

./bin/mysed s/unix/linux/ "unix is opensource. unix is free os."

./bin/mytrans ./src/mytrans/text.txt

./bin/mywc ./src/mytrans/text.txt
