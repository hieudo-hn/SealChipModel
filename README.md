# SealChipModel
This repository is to train a seal facial detection model (output into seal.dat) used by SealNet Chipping GUI found at: https://github.com/hieudo-hn/dlibSealGUI.git

## Requirements:

Cmake is required to make any changes to or compile the c++ code, and can be found here: https://cmake.org/download/

You also need dlib to run the program. Go to http://dlib.net/ and click download dlib. For more info on how to install these dependencies, visit 
the SealNet Chipping GUI.

Clone this repo: `git clone https://github.com/hieudo-hn/SealChipModel.git`

## Training the model:
Training.cpp is the main script that you will use to train the model. In preparation to train the model, you can use the Chipping GUI to prepare the data.

* Split train-test data:
- 

* N-fold cross-validation:
- You can either do stratified n-fold cross-validation or normal n-fold cross-validation
- For stratified n-fold cross-validation, organize your photos into separate folders (each strata) which has a corresponding xml file that contains 
truth bounding boxes (must be prepared using the GUI). You need to have a text file (for instance, xmlList.txt) that lists all of the stratas' xml file.
Each of the xml file should be on its own line. See xmlList.txt as a guide.

## Testing the model:
Testing.cpp is the main script for testing your model.

* Test a model:


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


