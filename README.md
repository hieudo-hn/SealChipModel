# SealNet Seal Chipping

This is the code base to create a trained model to recognize seal face (seal.dat). It will be used in SealNet 2.0 to automate seal face-chipping.

## Usage:

cmake is required to make any changes to or compile the c++ code, and can be found here: https://cmake.org/download/

dlib is also required for this model. See the link for download in Useful Resources

You can add the data in the DataSet folder:
- Add more photos in the folder
- training.xml is used for training
- testing.xml is used for testing
- format of the xml file:

```
<image file='FILE_NAME'>
    <box top='y' left='x' width='w' height='h'/> 
    <!-- 
    where (x,y) denotes the top-left coordinate of where a seal face is located in the photo
    and (w,h) denotes the width and height respectively of the area containing the seal face
    -->
    <box ... />
</image>
```

Compile the code to run:

mkdir build

cd build

cmake ..

cmake --build . --config Release

Running:


## Useful resources:

### Link to SealNet 1.0:
https://github.com/aylab/SealFaceRecognition

### CNNs (Neural network architecture):

Introduction to the concepts: https://towardsdatascience.com/simple-introduction-to-convolutional-neural-networks-cdf8d3077bac

### Dlib (Face chipping):

Documentation: http://dlib.net/

Basis of detection code: https://github.com/davisking/dlib/blob/master/examples/dnn_mmod_dog_hipsterizer.cpp
