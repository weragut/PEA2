#include "Matrix.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// constructor initializes matrix as empty and size = 0
Matrix::Matrix() : matrix(nullptr), size(0) {}
// deconstructor
Matrix::~Matrix() {
    freeMemory();
}
// load matrix form file
bool Matrix::loadFromFile(const string& filename) {
    ifstream inputFile(filename);// open file

    if (!inputFile.is_open()) {
        cout << "Attempting to open file: " << filename << endl;
        cerr << "Cannot open file: " << filename << endl;
        return false;
    }

    freeMemory();

    inputFile >> size;  // insert size from data file

    // loading values from file into matrix
    matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            inputFile >> matrix[i][j]; // load value
        }
    }

    inputFile.close();
    return true;
}

// function generating random matrix
void Matrix::generateManual(int matrixsize, const string& type) {

    freeMemory();
    size = matrixsize;
    matrix = new int*[size]; // dynamic pointer array allocation

    if(type == "asynchronous") {
        for (int i = 0; i < size; ++i) {
            matrix[i] = new int[size];
            for (int j = 0; j < size; ++j) {
                if (i == j) {
                    matrix[i][j] = -1;  // diagonal = -1
                } else {
                    matrix[i][j] = rand() % 100 + 1;  // values from 1 to 100
                }
            }
        }
    }else if (type == "synchronous"){
        for (int i = 0; i < size; ++i) {
            matrix[i] = new int[size];
            for (int j = 0; j < size; ++j) {
                if (i == j) {
                    matrix[i][j] = -1;
                } else if(i<j){
                    matrix[i][j] = rand() % 100 + 1;
                }else if(i>j) { // for elements below the diagonal
                    matrix[i][j] = matrix[j][i]; //write a value symmetrical to the diagonal
                }
            }
        }

    }

}

// display matrix
void Matrix::display() const {
    if (matrix == nullptr) return;

    cout << "Matrix (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
// free memory
void Matrix::freeMemory() {
    if (matrix != nullptr) {
        for (int i = 0; i < size; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

// function returns the size of the matrix
int Matrix::getSize() const {
    return size;
}

// function returns cost between vertices
int Matrix::getCost(int i, int j) const {
    if (i < size && j < size) {
        return matrix[i][j];
    } else {
        return -1;
    }
}