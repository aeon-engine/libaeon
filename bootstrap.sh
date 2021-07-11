#!/bin/bash

rm -rf build
mkdir build
pushd build
conan install ..
cmake ../ -DCMAKE_INSTALL_PREFIX=$(pwd)/install
popd
