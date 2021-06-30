# SealChipModel
This repository is to train a facial detection model (e.g: seal.dat) used by SealNet Chipping GUI found at: https://github.com/hieudo-hn/dlibSealGUI.git

## Requirements:

Cmake is required to make any changes to or compile the c++ code, and can be found here: https://cmake.org/download/

You also need dlib to run the program. Go to http://dlib.net/ and click download dlib.

Clone this repo: `git clone https://github.com/hieudo-hn/SealChipModel.git`

## Training the model:
You need to be in the main directory of this repository to start training. Please move the photo folders from dlib/tools/imglab/build
as well as training.xml and testing.xml into the main directory.

Replace the path to dlib in CMakeLists.txt:
```
if (NOT DEFINED DLIB_PATH)
   set(DLIB_PATH YOUR_PATH_TO_DLIB)
endif()
```

In the main directory, run the following to compile the code for gpu usage:

```
mkdir build && cd build

cmake .. -DDLIB_USE_CUDA=1 -DUSE_AVX_INSTRUCTIONS=1

cmake --build . --config Release
```

After you compile dnn_mmod_seal.cpp, the compiled file will be in ./build/, you can move it into the root directory with your mouse or using the command 
```
mv compileModel ../
```

## Usage:
Train the model by calling this command 
```
./compileModel ./
```

## Useful resources:

### Link to SealNet 1.0:
https://github.com/aylab/SealFaceRecognition

### Dlib:
Documentation: http://dlib.net/

Source code for dnn_mmod_seal.cpp: http://dlib.net/dnn_mmod_ex.cpp.html


