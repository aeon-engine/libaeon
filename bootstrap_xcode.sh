#!/bin/bash

rm -rf build
mkdir build
cd build
conan install ..
cmake ../ -G "Xcode"
open .
cd ..
