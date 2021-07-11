#!/bin/bash

rm -rf build
mkdir build
pushd build
conan install .. -s build_type=Debug
cmake ../ -DCMAKE_INSTALL_PREFIX=$(pwd)/install -DCMAKE_BUILD_TYPE=Debug
popd
