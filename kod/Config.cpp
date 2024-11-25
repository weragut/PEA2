#include "Config.h"
#include <iostream>
#include <fstream>

using namespace std;


bool Config::loadConfig(const string& filename) {
    ifstream file(filename); // open configuration file for reading

    if (!file.is_open()) { // check if the file has been opened
        cerr << "Cannot open configuration file: " << filename << endl;
        return false;
    }

    string key;
    while (file >> key) { // reading keys
        if (key == "matrix_source") { // check the key and assign the value that comes after the space
            file >> matrix_source;
        } else if (key == "progress_indicator") {
            file >> progress_indicator;
        } else if (key == "repetitions") {
            file >> repetitions;
        } else if (key == "input_file") {
            file >> input_file;
        } else if (key == "matrix_size") {
            file >> matrix_size;
        } else if (key == "matrix_type") {
            file >> matrix_type;
        }else if (key == "alghoritm_type") {
            file >> alghoritm_type;
        }
    }

    file.close();
    return true;
}
