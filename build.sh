#!/bin/bash
set -e

TARGET=target/hello.html
rm -rf target
mkdir target
emcc \
  src/hello.cpp \
  -s FETCH=1 \
  -s WASM=1 \
  -o $TARGET \
  --preload-file models \
  --emrun
cp -r models target/
emrun --browser=chrome $TARGET
