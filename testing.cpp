/*
This script is to used for testing your trained model. Usually used right after having trained the model in train.cpp
*/

#include <iostream>
#include <fstream>
#include <dlib/dnn.h>
#include <dlib/data_io.h>

using namespace std;
using namespace dlib;

// ----------------------------------------------------------------------------------------

template <long num_filters, typename SUBNET> using con5d = con<num_filters, 5, 5, 2, 2, SUBNET>;
template <long num_filters, typename SUBNET> using con5 = con<num_filters, 5, 5, 1, 1, SUBNET>;

template <typename SUBNET> using downsampler = relu<bn_con<con5d<32, relu<bn_con<con5d<32, relu<bn_con<con5d<16, SUBNET>>>>>>>>>;
template <typename SUBNET> using rcon5 = relu<bn_con<con5<45, SUBNET>>>;

using net_type = loss_mmod<con<1, 9, 9, 1, 1, rcon5<rcon5<rcon5<downsampler<input_rgb_image_pyramid<pyramid_down<6>>>>>>>>;

// ----------------------------------------------------------------------------------------

int LOWERBOUND = -1;
int UPPERBOUND = 1;
int INCREMENT = 1;

int main(int argc, char** argv) try
{
    if (argc != 3)
    {
        cout << "Give the name of the trained model to calculate precision-recall" << endl;
        cout << "and give the name of the folder that has the testing dataset" << endl;
        cout << "For example, execute this program by running:" << endl;
        cout << "       ./testModel ./seal.dat ./Fold1" << endl;
        cout << endl;
        return 0;
    }

    // load the models
    net_type net;
    deserialize(argv[1]) >> net;

    // load the testing images
    const std::string faces_directory = argv[2];
    std::vector<matrix<rgb_pixel>> images_test;
    std::vector<std::vector<mmod_rect>> face_boxes_test;
    load_image_dataset(images_test, face_boxes_test, faces_directory+"/testing.xml");

    //log output to files
    const std::string output = faces_directory + "_log.txt";
    ofstream Output(output);

    for (int adjust_threshold = LOWERBOUND; adjust_threshold <= UPPERBOUND; adjust_threshold += INCREMENT){
        const matrix<double, 1, 3> res = test_object_detection_function(net, images_test, face_boxes_test, test_box_overlap(), 10); 
        Output << "Testing " << argv[1] << " with threshold at " << adjust_threshold << " give precision, recall, and average precision: " << res << endl;
    }

    Output.close();

}
catch(std::exception& e)
{
    cout << e.what() << endl;
}