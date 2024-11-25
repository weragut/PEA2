#ifndef BEST_FIRST_SEARCH_BRANCH_AND_BOUND_H
#define BEST_FIRST_SEARCH_BRANCH_AND_BOUND_H

#include <vector>
#include <limits>
#include "Matrix.h"
using namespace std;

class BestFirstSearchBranchAndBound {
private:

    // definition of a node structure
    struct Node {
        int level; // depth (the number of visited nodes)
        int cost; // cost for the current path
        int bound; // lower bound for this node
        vector<int> path; // list of visited nodes in the current path

        // Node constructor
        Node(int lvl, int cst, int bnd, const vector<int>& pth): level(lvl), cost(cst), bound(bnd), path(pth) {}
    };

    Matrix* matrix; // matrix pointer
    int matrix_size;
    int final_res;  // cost of the min cost path
    vector<int> final_path; // min cost path
    double executionTime; // time

    // lower bound calculation
    int calculateLowerBound(const vector<int>& path, int level);

    // priority queue
    vector<Node> manualQueue;

    // functions for managing priority queue
    void pushNode(const Node& node);
    Node popNode();

public:
    BestFirstSearchBranchAndBound(Matrix* inputMatrix); // constructor

    void solveTSP(); // tsp solving function
    double getExecutionTime() const; // returns the time

    int getFinalCost() const; // returns min cost
    void printResult(); // prints result
};

#endif // BEST_FIRST_SEARCH_BRANCH_AND_BOUND_H
