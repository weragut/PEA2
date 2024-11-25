#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;


class Matrix {
public:
    Matrix(); // constructor
    ~Matrix(); // deconstructor

    bool loadFromFile(const string& filename);   // load a matrix from  file
    void generateManual(int size, const string& type);  // generate a matrix manually

    void display() const;
    void freeMemory();

    int getSize() const;
    int getCost(int i, int j) const; // returns the cost of moving from node to node

private:
    int** matrix;
    int size;
};

#endif
