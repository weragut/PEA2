#ifndef BFSBRANCHANDBOUND_H
#define BFSBRANCHANDBOUND_H

#include "Matrix.h"
#include "QueueClass.h" // queue implementation
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

class BFSBranchAndBound {
private:
    Matrix* matrix;
    int matrix_size;
    int final_res; // cost of the min cost path
    vector<int> final_path; // min cost path

    // definition of a node structure
    struct Node {
        int level; // depth (the number of visited nodes)
        int bound; // lower bound for this node
        int cost; // cost for the current path
        vector<int> path; // list of visited nodes in the current path
        vector<bool> visited; // visited nodes
    };

    double executionTime; // time

    int calculateBound(const Node& node); // lower bound calculation
    void copyToFinal(const vector<int>& path); // copies the current path into the final path

public:
    BFSBranchAndBound(Matrix* inputMatrix); // constructor
    void solveTSP(); // tsp solving function
    double getExecutionTime() const; // returns the time
    int getFinalCost() const; // returns min cost
    void printResult(); // prints result
};

#endif // BFSBRANCHANDBOUND_H
