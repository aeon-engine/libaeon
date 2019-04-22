#!/bin/bash

./bootstrap.sh

cd build
make -j2
LD_LIBRARY_PATH=$(pwd)/bin:$LD_LIBRARY_PATH ctest
