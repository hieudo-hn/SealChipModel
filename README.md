# SealChipModel

This repository is to train a seal facial detection model (output into seal.dat) used by SealNet Chipping GUI found at: https://github.com/hieudo-hn/dlibSealGUI.git

## Requirements:

Cmake is required to make any changes to or compile the c++ code, and can be found here: https://cmake.org/download/

You also need dlib to run the program. Go to http://dlib.net/ and click download dlib. For more info on how to install these dependencies, visit 
the SealNet Chipping GUI.

Clone this repo: `git clone https://github.com/hieudo-hn/SealChipModel.git`

## Preparing the data:

- You need to manually draw the truth bounding boxes around the object you are trying to detect. For instance, in this case, we are dealing with seals.
Please refer to https://github.com/hieudo-hn/dlibSealGUI.git which modifies Davis King's imglab to assist you with preparing the data.

## Training and validation:

1. Split train-test data:
- If you are not doing n-fold cross-validation, you can either manually split your data into training.xml and testing.xml or split them into n folds and delete 
the other n-1 folds.

2. N-fold cross-validation:
- You can either do stratified n-fold cross-validation or normal n-fold cross-validation
- For stratified n-fold cross-validation, organize your photos into separate folders (each strata) which has a corresponding xml file that contains 
truth bounding boxes (must be prepared using the GUI). You need to have a text file (for instance, xmlList.txt) that lists all of the stratas' xml file.
Each of the xml file should be on its own line. See xmlList.txt as a guide.
- For normal n-fold cross-validation, you just need one xmlFile that contains all of the truth bounding box

## Note of training WITH/WITHOUT GPUs:

- The code is currently written to run on AWS machine on a g4dn.12xlarge instance that has 4 GPUs, 48 vCPUs, 192 GiB of memory, 1x900 NVMe SSD, 50 Gbps network performance. 
If you are running on a machine with 4 GPUS, the code should work fine. However, if you have fewer/more GPUs, you have to update training.cpp on line 51:
```
const int NUM_GPUS = how_many_gpus_you_have;
```

## Running the script for cross-fold validation:

- First, you need to compile all of the scripts. Make sure that you have all of the prerequisites installed before compiling. You can run `./compile.sh` to compile.

- For stratified n-fold cross-validation, run:
```
./split --file YOUR_TEXT_FILE --fold NUM_FOLD
```

For instance:
```
./split --file xmlList.txt --fold 10 #where xmlList.txt contains the list of all different xmlFile stratas
```

- For normal n-fold cross-validation, run:
```
./split --file YOUR_XML_FILE --fold NUM_FOLD
```

For instance:
```
./split --file allData.xml --fold 10
```

Both will create 10 folders whose names are Fold1, Fold2, Fold3, etc that contains the training.xml and testing.xml for you to run.

- You can run `./runCrossValidation.sh` to start doing n-fold cross-validation.

## Running the script for simple training/testing:

- First, you need to compile all of the scripts. Make sure that you have all of the prerequisites installed before compiling. You can run `./compile.sh` to compile.

- For training:
```
./trainModel FOLDER #this folder should contain your training.xml
```

For example:
```
./trainModel ./ #if training.xml is in your main directory
```

- For testing:
```
./testModel TRAINED_MODEL.dat FOLDER #this folder should contain your testing.xml
```

For example:
```
./testModel ./mmod_network.dat ./Fold1 #if your trained model is in mmod_network.dat and your testing.xml is in the main directory
```

## Optional for creating Precision Recall Curve

- You can use plot.py to create a Precision Recall Curve of your model. In order to do this, you need to install matplotlib.

- It is recommended that you set up a virtual environment prior to doing this, you can visit https://www.geeksforgeeks.org/python-virtual-environment/ to know more.

- Run `pip install matplotlib` to install matplotlib within the environment

- Then to draw graph, run `python plot.py NUM_FOLD`. For instance, `python plot.py 10` for 10-fold cross validation. The graph will be stored in 'precision_recall.png'.

## Summary of scripts:
1. training.cpp: C++ code for training the model. The code was modified based on Davis King's example for hipsterizing dog: http://blog.dlib.net/2016/10/hipsterize-your-dog-with-deep-learning.html.
Original source code can be found here: https://github.com/davisking/dlib/blob/master/examples/dnn_mmod_dog_hipsterizer.cpp.

2. testing.cpp: C++ code testing the model. The code was modified based on Davis King's dlib source code here: http://dlib.net/dlib/dnn/validation.h.html.

3. split.cpp: C++ code to split data for cross validation.

4. compile.sh: Scripts to compile all of the C++ code.

5. runCrossValidation.sh: Scripts to perform n-fold cross validation.

6. plot.py: plot Precision Recall Curve (it is hard-coded and you might need to edit it)

## Useful resources:

### Link to SealNet 1.0:
https://github.com/aylab/SealFaceRecognition

### Dlib:
Documentation: http://dlib.net/

Source code for dnn_mmod_seal.cpp: http://dlib.net/dnn_mmod_ex.cpp.html


