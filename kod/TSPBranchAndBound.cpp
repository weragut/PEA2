#include "TSPBranchAndBound.h"
#include <iostream>
#include <climits>

using namespace std;

TSPBranchAndBound::TSPBranchAndBound(Matrix* inputMatrix) {
    matrix = inputMatrix;
    matrix_size = matrix->getSize(); // number of vertices
    final_res = INT_MAX; // final cost
    visited.resize(matrix_size, false); // visited vector
    final_path.resize(matrix_size+1, -1); // final path
}

void TSPBranchAndBound::copyToFinal(const vector<int>& curr_path) {
    final_path = curr_path; // copy actual path
    if (final_path[0] != -1) {
        final_path.push_back(final_path[0]); // additn the starting point at the end to close the cycle
    } else {
        cerr << "Error: Invalid starting node (-1) in path!" << endl;
    }

    // Debugging
    cout << "Final path after copying: ";
    for (int node : final_path) {
        cout << node << " ";
    }
    cout << endl;
}

// finding the lowest cost from the vertex
int TSPBranchAndBound::firstMin(int i) {
    int first_min = INT_MAX;
    for (int k = 0; k < matrix_size; k++) {
        if (matrix->getCost(i, k) != -1 && i != k) {
            first_min = min(first_min, matrix->getCost(i, k));
        }
    }
    return first_min;
}
// finding the second lowest cost from the vertex
int TSPBranchAndBound::secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int k = 0; k < matrix_size; k++) {
        if (matrix->getCost(i, k) != -1 && i != k) {
            if (matrix->getCost(i, k) <= first) {
                second = first;
                first = matrix->getCost(i, k);
            } else if (matrix->getCost(i, k) < second) {
                second = matrix->getCost(i, k);
            }
        }
    }
    return second;
}

void TSPBranchAndBound::TSPRec(int curr_bound, int curr_weight, int level, vector<int>& curr_path) {
    cout << "TSPRec - Level: " << level << ", Current Path: ";
    for (int node : curr_path) {
        cout << node << " ";
    }
    cout << ", Current Weight: " << curr_weight << ", Current Bound: " << curr_bound << endl;

    // checking if all vertices are in the path
    if (level == matrix_size) {
        if (matrix->getCost(curr_path[level - 1], curr_path[0]) != -1) {
            // adding the cost of return to the starting vertex
            int curr_res = curr_weight + matrix->getCost(curr_path[level - 1], curr_path[0]);
            // if the current path has lower cost than the previous cost
            if (curr_res < final_res) {
                // new final path
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }

    // expanding the branch
    for (int i = 0; i < matrix_size; i++) {
        // checking if there is a path and if it has already been visited
        if (matrix->getCost(curr_path[level - 1], i) != -1 && !visited[i]) {
            // copy current bound
            int the_bound = curr_bound;
            // adding weight
            curr_weight += matrix->getCost(curr_path[level - 1], i);

            // update bound
            if (level == 1)
                curr_bound -= (firstMin(curr_path[level - 1]) + firstMin(i)) / 2;
            else
                curr_bound -= (secondMin(curr_path[level - 1]) + firstMin(i)) / 2;

            // pruning branches
            // if the branch is potentially better
            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                // recursively explorinf further levels
                TSPRec(curr_bound, curr_weight, level + 1, curr_path);
            }

            // backtracking
            curr_weight -= matrix->getCost(curr_path[level - 1], i); // subtracting the cost of the last added edge
            curr_bound = the_bound; // returning to previous bound
            fill(visited.begin(), visited.end(), false); // reset the visited vertices
            for (int j = 0; j <= level - 1; j++) {
                visited[curr_path[j]] = true; // adding visited vertices to the path
            }
        }
    }
}

void TSPBranchAndBound::solveTSP() {
    // vector to store the current route
    vector<int> curr_path(matrix_size, -1);
    // lower bound
    int curr_bound = 0;

    //initial lower bound based on the first and second minimum costs for each vertex
    for (int i = 0; i < matrix_size; i++) {
        curr_bound += firstMin(i) + secondMin(i);
    }

    if(curr_bound % 2 == 0) {
        curr_bound = curr_bound/2;
    }else if (curr_bound % 2 == 1) {
        curr_bound = curr_bound/2 + 1;
    }

    visited[0] = true; // first vertex visited
    curr_path[0] = 0; // first vertex set as the start of the path

    TSPRec(curr_bound, 0, 1, curr_path);
}

void TSPBranchAndBound::printResult() {
    cout << "Final Path Content: ";
    for (int node : final_path) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Minimum Cost: " << final_res << endl;
    cout << "Path Taken: ";
    for (size_t i = 0; i < final_path.size(); i++) {
        if (final_path[i] == -1) {
            cerr << "Warning: Path contains invalid node (-1)!" << endl;
        }
        cout << final_path[i] << " ";
    }
    cout << endl;
}

