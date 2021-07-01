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

template <long num_filters, typename SUBNET>
using con5d = con<num_filters, 5, 5, 2, 2, SUBNET>;
template <long num_filters, typename SUBNET>
using con5 = con<num_filters, 5, 5, 1, 1, SUBNET>;

template <typename SUBNET>
using downsampler = relu<bn_con<con5d<32, relu<bn_con<con5d<32, relu<bn_con<con5d<16, SUBNET> > > > > > > > >;
template <typename SUBNET>
using rcon5 = relu<bn_con<con5<45, SUBNET> > >;

using net_type = loss_mmod<con<1, 9, 9, 1, 1, rcon5<rcon5<rcon5<downsampler<input_rgb_image_pyramid<pyramid_down<6> > > > > > > >;

// ----------------------------------------------------------------------------------------

const double LOWERBOUND = -0.5;
const double UPPERBOUND = 0.5;
const double INCREMENT = 0.4;
const string MODEL_LOG = "Cross_validation_log.txt";
const string FOLD_LOG = "log.txt";

// ----------------------------------------------------------------------------------------

template <
    typename SUBNET,
    typename image_array_type>
const matrix<double, 1, 4> count_correct_hits(
    loss_mmod<SUBNET> &detector,
    const image_array_type &images,
    const std::vector<std::vector<mmod_rect> > &truth_dets,
    std::vector<std::pair<double, bool> > &all_dets,
    const test_box_overlap &overlap_tester = test_box_overlap(),
    const double adjust_threshold = 0,
    const test_box_overlap &overlaps_ignore_tester = test_box_overlap())
{
    // make sure requires clause is not broken
    DLIB_CASSERT(is_learning_problem(images, truth_dets) == true,
                 "\t matrix test_object_detection_function()"
                     << "\n\t invalid inputs were given to this function"
                     << "\n\t is_learning_problem(images,truth_dets): " << is_learning_problem(images, truth_dets)
                     << "\n\t images.size(): " << images.size());

    double correct_hits = 0;
    double total_true_targets = 0;

    unsigned long missing_detections = 0;

    resizable_tensor temp;

    // iterate through each image
    for (unsigned long i = 0; i < images.size(); ++i)
    {
        // chip each image into hits
        std::vector<mmod_rect> hits;
        detector.to_tensor(&images[i], &images[i] + 1, temp);
        detector.subnet().forward(temp);
        detector.loss_details().to_label(temp, detector.subnet(), &hits, adjust_threshold);

        std::vector<full_object_detection> truth_boxes;
        std::vector<rectangle> ignore;
        std::vector<std::pair<double, rectangle> > boxes;

        // copy hits and truth_dets into the above three objects
        for (auto &&b : truth_dets[i])
        {
            if (b.ignore)
                ignore.push_back(b);
            truth_boxes.push_back(full_object_detection(b.rect));
            ++total_true_targets;
        }
        for (auto &&b : hits)
        {
            boxes.push_back(std::make_pair(b.detection_confidence, b.rect));
        }

        // count number of correct_hits, missing_detections, and add all detections with their score + boolean (true/false positive) into all_dets
        correct_hits += dlib::impl::number_of_truth_hits(truth_boxes, ignore, boxes, overlap_tester, all_dets, missing_detections, overlaps_ignore_tester);
    }

    std::sort(all_dets.rbegin(), all_dets.rend());

    double total_hits = all_dets.size();

    matrix<double, 1, 4> res;
    res = correct_hits, total_hits, total_true_targets, missing_detections;
    return res;
}

// ----------------------------------------------------------------------------------------

matrix<double, 1, 2> calculate_precision_recall(
    double correct_hits,
    double total_hits,
    double total_true_targets)
{
    //calculating precision and recall
    double precision, recall, average_prec;

    if (total_hits == 0)
        precision = 1;
    else
        precision = correct_hits / total_hits; // True Positive / (True Positive + False Positive)

    if (total_true_targets == 0)
        recall = 1;
    else
        recall = correct_hits / total_true_targets; // True Positive / (True Positive + False Negative)

    matrix<double, 1, 2> res;
    res = precision, recall;
    return res;
}

// ----------------------------------------------------------------------------------------

std::vector<std::vector<double> > main_test_function(
    const std::string model,
    const std::string faces_directory)
{
    // load the models
    net_type net;
    deserialize(model) >> net;

    // load the testing images
    std::vector<matrix<rgb_pixel> > images_test;
    std::vector<std::vector<mmod_rect> > face_boxes_test;
    load_image_dataset(images_test, face_boxes_test, faces_directory + "/testing.xml"); // Default testing data must be stored in testing.xml

    //log output to files
    //log.txt in each folder stores precision, recall, and average precision of each fold
    const std::string output = faces_directory + "/" + FOLD_LOG;
    ofstream Output(output);

    std::vector<std::vector<double> > summary;
    for (double adjust_threshold = LOWERBOUND; adjust_threshold <= UPPERBOUND; adjust_threshold += INCREMENT)
    {
        std::vector<std::pair<double, bool> > all_dets;

        const matrix<double, 1, 4> res = count_correct_hits(net, images_test, face_boxes_test, all_dets, test_box_overlap(), adjust_threshold);

        // calculate precision and recall
        const double correct_hits = res(0), total_hits = res(1), total_true_targets = res(2), missing_detections = res(3);
        matrix<double, 1, 2> precision_recall = calculate_precision_recall(correct_hits, total_hits, total_true_targets);

        Output << adjust_threshold << " " << precision_recall(0) << " " << precision_recall(1) << " " << average_precision(all_dets, missing_detections) << endl;

        summary.push_back({correct_hits, total_hits, total_true_targets});
    }

    Output.close();
    return summary;
}

// ----------------------------------------------------------------------------------------

int main(int argc, char **argv)
try
{

    // if the command prompt is ./testModel ./seal.dat ./Fold1 (only evaluate a train-test split and output its precision-recall into log.txt)

    if (argc == 3)
    {
        main_test_function(argv[1], argv[2]);
    }

    // if the command prompt is ./testModel num_fold (do a n-fold cross-validation, output a log.txt file for each fold and a shared log file for all n-fold cross-validation)

    else if (argc == 2)
    {
        int num_fold = stoi(argv[1]);

        // summary will contain the total number of hits and other metrics across all folds to calculate the average precision and recall of our model
        std::vector<std::vector<double> > summary;
        for (double adjust_threshold = LOWERBOUND; adjust_threshold <= UPPERBOUND; adjust_threshold += INCREMENT)
            summary.push_back({0, 0, 0});

        for (int i = 1; i <= num_fold; i++)
        {
            string faces_directory = "Fold" + to_string(i);
            std::vector<std::vector<double> > metrics = main_test_function(faces_directory + "/seal.dat", faces_directory);

            for (int j = 0; j < metrics.size(); j++)
            {
                summary[j][0] += metrics[j][0];
                summary[j][1] += metrics[j][1];
                summary[j][2] += metrics[j][2];
            }
        }

        // output log for the whole model
        ofstream Output(MODEL_LOG);

        // calculate the average precision and recall of the model
        for (int i = 0; i < summary.size(); i++)
        {
            double adjust_threshold = LOWERBOUND + i * INCREMENT;
            matrix<double, 1, 2> precision_recall = calculate_precision_recall(summary[i][0], summary[i][1], summary[i][2]);
            Output << adjust_threshold << " " << precision_recall;
        }

        Output.close();
    }

    else
    {
        cout << "Execute this program by running:" << endl;
        cout << "  ./testModel ./seal.dat ./Fold1" << endl;
        cout << "Or by running" << endl;
        cout << "  ./testModel num_fold" << endl;
        cout << endl;
        return 0;
    }
}
catch (std::exception &e)
{
    cout << e.what() << endl;
}