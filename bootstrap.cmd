rd /s /q build
cmake  . -B build -G "Visual Studio 17 2022" -T host=x64 -A x64 -DCMAKE_SYSTEM_VERSION=10.0 -DCMAKE_INSTALL_PREFIX=%CD%/build/install
