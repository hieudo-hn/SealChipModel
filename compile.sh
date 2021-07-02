#!/bin/sh

# function to build the C++ scripts
build(){
    mkdir -p build
    cd build
    cmake ..
    cmake --build . --config Debug
}

# build scripts and move to current working directory
build
mv ./trainModel ../
mv ./split ../ 
mv ./testModel ../

