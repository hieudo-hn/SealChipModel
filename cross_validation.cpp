#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <dlib/cmd_line_parser.h>
#include "dlib/data_io.h"
#include "dlib/string.h"

using namespace std;
using namespace dlib;

const std::string TRAINING_NAME = "Training Set";
const std::string TRAINING_COMMENT = "Data to train for Seal Chipping.";
const std::string TESTING_NAME = "Testing Set";
const std::string TESTING_COMMENT = "Data to test on training data.";

void split_helper(
    dlib::image_dataset_metadata::dataset &data,
    std::vector<dlib::image_dataset_metadata::dataset> &fold_training_testing_list,
    int num_split)
{
    const double testing_fraction = 1 / (double)num_split;
    const unsigned long num_test_images = static_cast<unsigned long>(std::round(testing_fraction * data.images.size()));

    for (int i = 0; i < fold_training_testing_list.size() / 2; i++){
        for (unsigned long j = 0; j < data.images.size(); ++j)
        {
            dlib::image_dataset_metadata::image current_image = data.images[j];
            current_image.filename = "../" + current_image.filename; //edit pathing because the training and testing folder is not in the same working directory as the photos
            if (num_test_images * i <= j && j < num_test_images * (i + 1)){
                fold_training_testing_list[2*i+1].images.push_back(current_image);
            } else {
                fold_training_testing_list[2*i].images.push_back(current_image);
            }
        }
    }
}

std::vector<dlib::image_dataset_metadata::dataset> generate_fold(int num_split)
{
    cout << "Generating " << num_split << " fold..." << endl;
    std::vector<dlib::image_dataset_metadata::dataset> fold_training_testing_list;
    for (int i = 1; i <= num_split; i++)
    {
        struct stat buffer;
        string folderName = "Fold" + std::to_string(i);
        // Check if directory already exists and if it doesn't create a new one
        // fold_training_testing_list has [fold_1_train, fold_1_test, fold_2_train, fold_2_test, etc...]
        if ((stat (folderName.c_str(), &buffer) == 0) || mkdir(folderName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0)
        {
            dlib::image_dataset_metadata::dataset data_train, data_test;
            data_train.name = TRAINING_NAME;
            data_train.comment = TRAINING_COMMENT;
            data_test.name = TESTING_NAME;
            data_test.comment = TESTING_COMMENT;
            fold_training_testing_list.push_back(data_train);
            fold_training_testing_list.push_back(data_test);
        }
        else
        {
            cout << "Error creating Fold " << i << endl;
        }
    }
    
    return fold_training_testing_list;
}

int save_fold(std::vector<dlib::image_dataset_metadata::dataset> &fold_training_testing_list){

    for (int i = 1; i <= fold_training_testing_list.size() / 2; i++){
        string folderName = "Fold" + std::to_string(i);
        save_image_dataset_metadata(fold_training_testing_list[2*i-2], folderName + "/training.xml");
        save_image_dataset_metadata(fold_training_testing_list[2*i-1], folderName + "/testing.xml");
    }

    cout << "Done splitting" << endl;

    return EXIT_SUCCESS;
}

int split_train_test_with_xml(const string file, int num_split)
{
    dlib::image_dataset_metadata::dataset data;
    load_image_dataset_metadata(data, file);
    std::random_shuffle(data.images.begin(), data.images.end());

    std::vector<dlib::image_dataset_metadata::dataset> fold_training_testing_list = generate_fold(num_split);

    split_helper(data, fold_training_testing_list, num_split);

    save_fold(fold_training_testing_list);

    return EXIT_SUCCESS;
}

int split_train_test_with_txt(const string file, int num_split)
{
    string line;
    ifstream configfile(file);
    std::vector<std::string> fileList;
    if (configfile.is_open())
    {
        while (getline(configfile, line))
        {
            fileList.push_back(line);
        }
        configfile.close();
    }

    else
        std::cout << "Unable to open file " << file << std::endl;

    dlib::image_dataset_metadata::dataset data;
    std::vector<dlib::image_dataset_metadata::dataset> fold_training_testing_list = generate_fold(num_split);

    for (string xmlFile : fileList)
    {
        load_image_dataset_metadata(data, xmlFile);
        std::random_shuffle(data.images.begin(), data.images.end());
        split_helper(data, fold_training_testing_list, num_split);
    }

    save_fold(fold_training_testing_list);

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------------------------- //

int main(int argc, char **argv)
{
    try
    {
        command_line_parser parser;

        parser.add_option("h", "Displays this information.");

        parser.add_option("cross-validation", "Split the data set to prepare for n-fold cross-validation", 1);

        parser.add_option("fold", "Number of folds for cross validation", 1);

        // Parse the command line
        parser.parse(argc, argv);

        // Check that each of these options is only present atmost once
        const char *singles[] = {"h", "cross-validation", "fold"};
        parser.check_one_time_options(singles);

        if (parser.option("h"))
        {
            cout << "Usage: cv [options] [args]\n";
            parser.print_options(cout);
            cout << endl
                 << endl;
            return EXIT_SUCCESS;
        }

        if (parser.option("cross-validation"))
        {
            //default value of split is 5-fold cross validation
            int num_split = get_option(parser, "fold", 5);
            num_split = (num_split < 2) ? 5 : num_split;
            const string file_read = parser.option("cross-validation").argument();

            // if you pass an xml file
            if (file_read.length() > 4 && file_read.compare(file_read.length() - 4, 4, ".xml") == 0)
            {
                split_train_test_with_xml(file_read, num_split);
            }
            // if you pass a txt file containing the list of all xml folders
            else if (file_read.length() > 4 && file_read.compare(file_read.length() - 4, 4, ".txt") == 0)
            {
                split_train_test_with_txt(file_read, num_split);
            }
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
}