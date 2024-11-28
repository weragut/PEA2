#include "DFSBranchAndBound.h"
#include <chrono>

// constructor
DFSBranchAndBound::DFSBranchAndBound(Matrix* inputMatrix) {
    matrix = inputMatrix; // data matrix
    matrix_size = matrix->getSize(); // size of matrix
    final_res = INT_MAX; // sets the initial result to the max value of int
    final_path.resize(matrix_size + 1, -1);  // allocate space for the final path
}

// copies the current path into the final path
void DFSBranchAndBound::copyToFinal(const vector<int>& path) {
    final_path = path;
    final_path.push_back(path[0]);  // closing the cycle with the starting node
}

//  finds and returns the smallest cost from city i to any other city
int DFSBranchAndBound::firstMin(int i) {
    int min = INT_MAX;
    for (int j = 0; j < matrix_size; j++) {
        if (matrix->getCost(i, j) != -1 && i != j) {
            if (matrix->getCost(i, j) < min) {
                min = matrix->getCost(i, j);
            }
        }
    }
    return min;
}

// finds and returns the second smallest cost from city i to any other city
int DFSBranchAndBound::secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < matrix_size; j++) {
        if (matrix->getCost(i, j) != -1 && i != j) {
            if (matrix->getCost(i, j) <= first) {
                second = first;
                first = matrix->getCost(i, j);
            } else if (matrix->getCost(i, j) < second) {
                second = matrix->getCost(i, j);
            }
        }
    }
    return second;
}

// calculating the lower bound
int DFSBranchAndBound::calculateBound(const Node& node) {
    int bound = 0;

    // last visited city in the current path
    int lastVisited = node.path.back();
    // adding the first and second min to the bound
    bound += firstMin(lastVisited) + secondMin(lastVisited);

    // for unvisited nodes add only the first minimum cost
    for (int i = 0; i < matrix_size; i++) {
        if (!node.visited[i]) {
            bound += firstMin(i);
        }
    }

    if (bound % 2 == 0) {
        return bound / 2;  // for even bounds
    } else {
        return (bound + 1) / 2;  // for odd bounds add 1
    }
}

void DFSBranchAndBound::dfs(Node node) {
    // if all vertices are visited
    if (node.level == matrix_size) {
        if (matrix->getCost(node.path.back(), node.path[0]) != -1) {
            //calculate the cost to return to the starting city
            int currentCost = node.cost + matrix->getCost(node.path.back(), node.path[0]);
            // update the best cost and path
            if (currentCost < final_res) {
                copyToFinal(node.path); // best path
                final_res = currentCost; // best cost
            }
        }
        return;
    }

    // expand branches
    for (int i = 0; i < matrix_size; i++) {
        // if the node is unvisited
        if (!node.visited[i] && matrix->getCost(node.path.back(), i) != -1) {
            Node child = node; // create a copy of the current node
            child.level = node.level + 1; // add level
            child.cost += matrix->getCost(node.path.back(), i); // add the cost to this node to total cost
            child.path.push_back(i); // add node to the path
            child.visited[i] = true; // mark node as visited

            // calculate the lower bound
            child.bound = calculateBound(child);

            // if the bound is lower than the current best result
            if (child.bound < final_res) {
                dfs(child); // explore this branch
            }
        }
    }
}

void DFSBranchAndBound::solveTSP() {
    // start the timer
    auto start = chrono::high_resolution_clock::now();

    // initialize the root node
    Node root;
    root.level = 1;
    root.cost = 0;
    root.bound = 0;
    root.path.push_back(0); // starting with node 0
    root.visited.resize(matrix_size, false); // visited vector false for all nodes
    root.visited[0] = true; // mark node as visited

    // calculate the initial bound
    root.bound = calculateBound(root);

    // start the dfs
    dfs(root);

    // stop the timer
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start; // calculate the time
    executionTime = duration.count();
}

// return the execution time
double DFSBranchAndBound::getExecutionTime() const {
    return executionTime;
}

// return the final cost
int DFSBranchAndBound::getFinalCost() const {
    return final_res;
}

// print the path and min cost
void DFSBranchAndBound::printResult() {
    cout << "Final Path: ";
    for (int node : final_path) {
        cout << node << " ";
    }
    cout << "\nMinimum Cost: " << final_res << "\n";
}
