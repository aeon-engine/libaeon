#!/bin/bash

rm -rf build
mkdir build
conan install . -if build -s build_type=Debug
cmake . -B build -DCMAKE_INSTALL_PREFIX=$(pwd)/build/install -DCMAKE_BUILD_TYPE=Debug
