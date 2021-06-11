# SealChipModel
This repository is to train a facial detection model (e.g: seal.dat) used by SealNet Chipping GUI found at: https://github.com/hieudo-hn/dlibSealGUI.git

## Requirements:

Cmake is required to make any changes to or compile the c++ code, and can be found here: https://cmake.org/download/

You also need dlib to run the program. Go to http://dlib.net/ and click download dlib.

Clone this repo: `git clone https://github.com/hieudo-hn/SealChipModel.git`

## Preparing the data to train your model with imglab:
You can use imglab to mark the bounding boxes that indicate the seal faces to be trained. 
Imglab is a simple graphical tool for annotating images with object bounding
boxes and optionally their part locations.  Generally, you use it when you want
to train an object detector (e.g. a face detector) since it allows you to
easily create the needed training dataset.

To compile imglab, first you need to locate dlib on your computer. Then, run the following on your terminal window:
```
cd <PATHTODLIB>     
cd tools/imglab
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

Next, to use it, lets assume you have a folder of images called images. First, move the folder into dlib/tools/imglab/build.
These images should contain examples of the objects you want to learn to detect.  You will use the imglab tool to label 
these objects.  Do this by typing the following command:
```
    ./imglab -c training.xml ./images
```
This will create a file called mydataset.xml which simply lists the images in
./images.  To add bounding boxes to the objects you run:
```
    ./imglab training.xml
```
and a window will appear showing all the images.  You can use the up and down
arrow keys to cycle though the images and the mouse to label objects.  In
particular, holding the shift key, left clicking, and dragging the mouse will
allow you to draw boxes around the objects you wish to detect.  

Once you finish labeling objects go to the file menu, click save, and then
close the program. This will save the object boxes back to mydataset.xml.  You
can verify this by opening the tool again with:
```
    ./imglab training.xml
```
and observing that the boxes are present.


imglab can do a few additional things.  To see these run:
```
    imglab -h 
```
and also read the instructions in the About->Help menu.

* Note: to increase the accuracy of your model, some faces in the photos might be cut/blurry/of bad quality. If you are unsure 
whether your model should detect such faces or not, indicate "ignore" option on such bounding boxes by clicking on the box and 
press "i". Example:
![Imglab Example](https://ibb.co/sj3pTpQ)
* Note: you should have training.xml for training and testing.xml for testing

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


