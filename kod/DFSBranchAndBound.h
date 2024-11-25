#ifndef DFSBRANCHANDBOUND_H
#define DFSBRANCHANDBOUND_H

#include "Matrix.h"
#include <vector>
#include <climits>
#include <iostream>
using namespace std;

class DFSBranchAndBound {
private:

    // definition of a node structure
    struct Node {
        int level; // depth (the number of visited nodes)
        int bound; // lower bound for this node
        int cost; // cost for the current path
        vector<int> path; // list of visited nodes in the current path
        vector<bool> visited; // visited nodes
    };

    Matrix* matrix;
    int matrix_size;
    int final_res; // cost of the min cost path
    vector<int> final_path; // min cost path
    double executionTime; // time

    void dfs(Node node); // DFS function to explore paths
    int calculateBound(const Node& node); // lower bound calculation
    int firstMin(int i); // calculate the smallest cost from a node
    int secondMin(int i); // calculate the second smallest cost from a node
    void copyToFinal(const vector<int>& path); // copies the current path into the final path
public:
    DFSBranchAndBound(Matrix* inputMatrix); // constructor
    void solveTSP();  // tsp solving function
    double getExecutionTime() const; // returns the time
    int getFinalCost() const;  // returns min cost
    void printResult(); // prints result
};

#endif // DFSBRANCHANDBOUND_H
