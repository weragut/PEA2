#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
using namespace std;

class Config {
public:
    string matrix_source;
    string alghoritm_type;
    int repetitions;
    bool progress_indicator;
    // when matrix_source = "file"
    string input_file;
    // when matrix_source = "file"
    int matrix_size;
    string matrix_type;

    // function to load configuration file
    bool loadConfig(const string& filename);
};

#endif
