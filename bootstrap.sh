#!/bin/bash

rm -rf build
cmake . -B build -DCMAKE_INSTALL_PREFIX=$(pwd)/build/install
