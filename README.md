# SealNet Seal Chipping

## Usage:

"python sealFindr.py /FOLDER_OF_PHOTOS"

Output will be written into folder /FOLDER_OF_PHOTOSChips

This will require a seal.exe executable. The included seal.exe is linux compatible. For a windows executable, follow the instructions below.


## Compiling changes:

cmake is required to make any changes to or compile the c++ code, and can be found here: https://cmake.org/download/

To edit and recreate the seal.exe executable, make changes to dnn_mmod_dog_hipsterizer.cpp, then run the following commands:
(If you just need a windows executable, simply follow the instructions without making changes)

mkdir build

cd build

cmake ..

cmake --build . --config Release

This will create an updated chipping executable, which you should rename seal.exe and place into the parent folder with sealFindr.py

Sample on linux:

cd Release

cp dnn_mmod_dog_hipsterizer.exe ../../seal.exe 
(This will create a copy of the new executable with the correct name in the parent folder)


## Important files:

sealFindr.py - Python code which takes input folder and calls chipping executable on each photo

dnn_mmod_dog_hipsterizer.cpp - Adapted Dlib code for seal face detection and chipping

CMakeLists.txt - File used by CMake to compile above code

seal.exe - Compiled executable called by sealFindr

seal.dat - Trained model for face detection used by seal.exe


# SealNet Classifier Additions

## format_data Usage:

"python format_data.py GALLERY/PROBE DIRECTORY"

Ex: python format_data.py GALLERY ../photos

Ex: python format_data.py PROBE ../chips

Output will be written into either ./probePhotos.txt or ./referencePhotos.txt respectively

## seenBefore Usage:

"python seenBefore.py"

This will require ./probePhotos.txt, ./referencePhotos.txt, and a trained SealNet model, which can be directed to in "model_name" in main().

Output will be written into ./testResult.txt

## Important files:

format_data.py - Python function to create probe and reference .txt files for seenBefore usage. Creating a probe list (the new chips to be classified) takes a single directory of chips. Creating a gallery (the classified reference groups) takes a folder of folders, each labelled with a number corresponding to a seal, with chips of that seal contained within. 

seenBefore.py - This script uses the a probePhotos.txt and referencePhotos.txt within the same folder to classify each of the probes as the closest reference, according to a trained SealNet model. The output is formated as: name_of_chip.jpeg 1,NUMBER OF CLASSIFIED SEAL

For example: BrandtLedges/Chip10.jpeg 1,64  Which means that Chip10.jpeg most closely matches the seal in labelled folder 64

## Useful resources:

### Link to SealNet 1.0:
https://github.com/aylab/SealFaceRecognition

### CNNs (Neural network architecture):

Introduction to the concepts: https://towardsdatascience.com/simple-introduction-to-convolutional-neural-networks-cdf8d3077bac

### Dlib (Face chipping):

Documentation: http://dlib.net/

Basis of detection code: https://github.com/davisking/dlib/blob/master/examples/dnn_mmod_dog_hipsterizer.cpp
