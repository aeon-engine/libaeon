rd /s /q build
mkdir build
conan install . -if build -s build_type=Debug
conan install . -if build -s build_type=Release
cmake  . -B build -G "Visual Studio 17 2022" -T host=x64 -A x64 -DCMAKE_SYSTEM_VERSION=10.0 -DCMAKE_INSTALL_PREFIX=%CD%/build/install
