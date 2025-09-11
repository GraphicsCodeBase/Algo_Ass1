@echo off
set BUILD_DIR=build

if exist %BUILD_DIR% (
    echo Deleting %BUILD_DIR%...
    rmdir /s /q %BUILD_DIR%
) else (
    echo No build folder found.
)
