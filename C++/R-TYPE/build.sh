#!/usr/bin/bash

# Function to test exit status of a command.
# It exits if the command failed.
function testExitStatus()
{
    if [ $1 -ne 0 ]
    then
        echo "$2 failed"
        exit 1
    else
        echo "$2 successed"
    fi
}

# Create build directory
mkdir -p build
testExitStatus $? "mkdir"

# Update path into build directory
cd build
testExitStatus $? "cd"

# Install conan dependencies
conan install .. --build=missing
testExitStatus $? "conan install dependencies"

# Configure cmake
cmake .. -DCMAKE_TOOLCHAIN_FILE=../conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
testExitStatus $? "cmake config"

# Build using cmake
cmake --build . --config=Release
 testExitStatus $? "cmake build"
# find . -type f ! -name 'build.sh' ! -name 'delete.sh' ! -name 'conanfile.txt' ! -name 'main.cpp' ! -name 'CMake*' -exec rm -f {} \;