@echo off

rem Create build directory
mkdir build
if errorlevel 1 (
    echo mkdir failed
    exit /b 1
) else (
    echo mkdir succeeded
)

rem Update path into build directory
cd build
if errorlevel 1 (
    echo cd failed
    exit /b 1
) else (
    echo cd succeeded
)

rem Install conan dependencies
conan install .. --build=missing
if errorlevel 1 (
    echo conan install dependencies failed
    exit /b 1
) else (
    echo conan install dependencies succeeded
)

rem Configure cmake
cmake .. -DCMAKE_TOOLCHAIN_FILE=..\conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 (
    echo cmake config failed
    exit /b 1
) else (
    echo cmake config succeeded
)

rem Build using cmake
cmake --build . --config Release
if errorlevel 1 (
    echo cmake build failed
    exit /b 1
) else (
    echo cmake build succeeded
)

rem You can add more commands here if needed
rem ...

rem Return to the original directory
cd ..

rem Exit with success status
exit /b 0
