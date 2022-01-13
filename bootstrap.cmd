rd /s /q vs_build
mkdir vs_build
cd vs_build
conan install .. -s build_type=Debug
conan install .. -s build_type=Release
cmake ../ -G "Visual Studio 17 2022" -T host=x64 -A x64 -DCMAKE_SYSTEM_VERSION=10.0 -DCMAKE_INSTALL_PREFIX=install
cd ..
