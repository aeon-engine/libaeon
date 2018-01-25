wget https://dl.bintray.com/aeon-engine/aeon_engine_dependencies/cmake/${CMAKE_VERSION_STRING}/cmake_${BUILD_ENVIRONMENT_NAME}.tar.gz
wget https://dl.bintray.com/aeon-engine/aeon_engine_dependencies/clang/${CLANG_VERSION_STRING}/clang_${BUILD_ENVIRONMENT_NAME}.tar.xz
tar xf cmake_${BUILD_ENVIRONMENT_NAME}.tar.gz
export PATH=$(pwd)/$(find . -maxdepth 1 -type d -name 'cmake-*')/bin:$PATH
tar xf clang_${BUILD_ENVIRONMENT_NAME}.tar.xz
export CLANG_BASE_PATH=$(pwd)/$(find . -maxdepth 1 -type d -name 'clang+llvm*')
export PATH=${CLANG_BASE_PATH}/bin:$PATH
mkdir build
cd build
cmake .. -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX -DAEON_ENABLE_CURL=1 -DAEON_ENABLE_SOCKETS=1 -DAEON_ENABLE_MIDI=1 -DAEON_ENABLE_HDF5=1 -DCMAKE_CXX_FLAGS="-stdlib=libc++ -I${CLANG_BASE_PATH}/include/c++/v1/"
make