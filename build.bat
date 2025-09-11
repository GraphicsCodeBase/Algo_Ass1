@echo off
set BUILD_DIR=build

:: Make sure we’re in the project root (where CMakeLists.txt is)
if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

cd %BUILD_DIR%

:: Run CMake configure and build
cmake .. -G "Ninja" || cmake .. -G "MinGW Makefiles" || cmake ..
cmake --build .

cd ..
