#!/bin/bash

rm -rf build
mkdir build
pushd build
cmake ../ -DAEON_ENABLE_CURL=1 -DAEON_ENABLE_SOCKETS=1 -DAEON_ENABLE_MIDI=1 -DAEON_ENABLE_HDF5=1
popd

