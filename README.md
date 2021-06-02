# SealChipModel

<<<<<<< HEAD
## Requirements:

cmake is required to make any changes to or compile the c++ code, and can be found here: https://cmake.org/download/

dlib is also required for this. Download link at the bottom.

## Preparing the data to train your model:
You can add the data in the DataSet folder by using imglab

imglab is a simple graphical tool for annotating images with object bounding
boxes and optionally their part locations.  Generally, you use it when you want
to train an object detector (e.g. a face detector) since it allows you to
easily create the needed training dataset.   

You can compile imglab with the following commands:
    cd imglab_source
    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release

Next, to use it, lets assume you have a folder of images called /tmp/images.
These images should contain examples of the objects you want to learn to
detect.  You will use the imglab tool to label these objects.  Do this by
typing the following command:
    ./imglab -c mydataset.xml /tmp/images
This will create a file called mydataset.xml which simply lists the images in
/tmp/images.  To add bounding boxes to the objects you run:
    ./imglab mydataset.xml
and a window will appear showing all the images.  You can use the up and down
arrow keys to cycle though the images and the mouse to label objects.  In
particular, holding the shift key, left clicking, and dragging the mouse will
allow you to draw boxes around the objects you wish to detect.  

Once you finish labeling objects go to the file menu, click save, and then
close the program. This will save the object boxes back to mydataset.xml.  You
can verify this by opening the tool again with:
    ./imglab mydataset.xml
and observing that the boxes are present.


imglab can do a few additional things.  To see these run:
    imglab -h 
and also read the instructions in the About->Help menu.

## Training the model:
You need to be in the main directory to start training. Please add the photo folders as well as training.xml and testing.xml into the main directory.

Replace the path to dlib in CMakeLists.txt:
if (NOT DEFINED DLIB_PATH)
   set(DLIB_PATH YOUR_PATH_TO_DLIB)
endif()

In the main directory, compile the code to run:
=======
This is the code base to create a trained model to recognize seal face (seal.dat). It will be used in SealNet 2.0 to automate seal face-chipping.

## Compiling:

cmake is required to make any changes to or compile the c++ code, and can be found here: https://cmake.org/download/

dlib is also required for this model. See the link for download in Useful Resources. After you download dlib, make sure the path to dlib is updated in CMakeLists.txt:

```
if (NOT DEFINED DLIB_PATH)
   set(DLIB_PATH "ADD_DLIB_PATH_HERE")
endif()
```

You can add more data for training or testing in the DataSet folder:
- Add more photos for training/testing in the folder
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
>>>>>>> 5dd89bd5002ef266b0bdcdcd5e900c541033bcf8

mkdir build

cd build

cmake ..

cmake --build . --config Release

After you compile dnn_mmod_seal.cpp, the compiled file will be in ./build/, you can move it into the source directory with your mouse or using the command `mv compileModel ../`

## Usage:
Train the model by calling this command `./compileModel DataSet`


## Useful resources:

### Link to SealNet 1.0:
https://github.com/aylab/SealFaceRecognition

### CNNs (Neural network architecture):

Introduction to the concepts: https://towardsdatascience.com/simple-introduction-to-convolutional-neural-networks-cdf8d3077bac

### Dlib (Face chipping):

Documentation: http://dlib.net/


