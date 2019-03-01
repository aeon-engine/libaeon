rd /s /q vs_build
mkdir vs_build
cd vs_build
cmake ../ -G "Visual Studio 16 2019" -T host=x64 -A x64 -DCMAKE_INSTALL_PREFIX=install
cd ..
