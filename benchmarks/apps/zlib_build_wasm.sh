#!/bin/bash

#cross compile zlib with wasi toolchain

COMPILER_BIN=/opt/wasi-sdk/bin
WASM_SYSROOT=/opt/wasi-sdk/share/wasi-sysroot
sudo mkdir -p /usr/local/zlib_wasm


CC=${COMPILER_BIN}/clang \
AR=${COMPILER_BIN}/llvm-ar \
RANLIB=${COMPILER_BIN}/llvm-ranlib \
NM=${COMPILER_BIN}/llvm-nm \
CFLAGS="--target=wasm32-wasi -fno-trapping-math --sysroot=${WASM_SYSROOT} -fno-exceptions" ./configure --prefix=/usr/local/zlib_wasm 

make


