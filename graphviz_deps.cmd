rd /s /q vs_build
mkdir vs_build
cd vs_build
cmake ../ -G "Visual Studio 16 2019" -T host=x64 -A x64 -DCMAKE_SYSTEM_VERSION=10.0 -DCMAKE_INSTALL_PREFIX=install --graphviz=dependencies.dot
sfdp -Goverlap=prism -Gsize=50,50! -Gsplines=true -n -Tpng dependencies.dot 1>dependencies.png
cd ..