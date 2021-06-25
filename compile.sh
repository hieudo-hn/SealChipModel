#!/bin/sh

# function to build the C++ scripts
build(){
    mkdir -p build
    cd build
    cmake ..
    cmake --build . --config Debug
}

ROOT_DIR = $(pwd)
BUILD_DIR = $ROOT_DIR/build

# build scripts and move to current working directory
build
mv ./trainModel ../
mv ./cv ../ 

