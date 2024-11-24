#include "TSPBranchAndBound.h"
#include <chrono>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

TSPBranchAndBound::TSPBranchAndBound(Matrix* inputMatrix) {
    matrix = inputMatrix;
    matrix_size = matrix->getSize();
    final_res = INT_MAX;
    visited.resize(matrix_size, false);
    final_path.resize(matrix_size + 1, -1);
}

void TSPBranchAndBound::copyToFinal(const vector<int>& curr_path) {
    final_path = curr_path;
    final_path.push_back(curr_path[0]); // Zamykamy cykl
}

int TSPBranchAndBound::firstMin(int i) {
    int min_value = INT_MAX;
    for (int k = 0; k < matrix_size; k++) {
        if (matrix->getCost(i, k) != -1 && i != k) {
            min_value = min(min_value, matrix->getCost(i, k));
        }
    }
    return min_value;
}

int TSPBranchAndBound::secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < matrix_size; j++) {
        if (i == j || matrix->getCost(i, j) == -1) continue;
        int cost = matrix->getCost(i, j);
        if (cost <= first) {
            second = first;
            first = cost;
        } else if (cost < second) {
            second = cost;
        }
    }
    return second;
}

int TSPBranchAndBound::calculateBound(const vector<int>& curr_path) {
    int bound = 0;

    // Dla każdego wierzchołka
    for (int i = 0; i < matrix_size; i++) {
        if (!visited[i]) {
            bound += (firstMin(i) + secondMin(i)) / 2;
        }
    }

    return bound;
}

void TSPBranchAndBound::TSPRec(int curr_weight, int level, vector<int>& curr_path) {
    if (level == matrix_size) {
        if (matrix->getCost(curr_path[level - 1], curr_path[0]) != -1) {
            int curr_res = curr_weight + matrix->getCost(curr_path[level - 1], curr_path[0]);
            if (curr_res < final_res) {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }

    for (int i = 0; i < matrix_size; i++) {
        if (!visited[i] && matrix->getCost(curr_path[level - 1], i) != -1) {
            int temp_weight = curr_weight + matrix->getCost(curr_path[level - 1], i);
            int temp_bound = temp_weight + calculateBound(curr_path);

            if (temp_bound < final_res) {
                curr_path[level] = i;
                visited[i] = true;

                TSPRec(temp_weight, level + 1, curr_path);
            }

            // Backtracking
            curr_path[level] = -1;
            visited[i] = false;
        }
    }
}

void TSPBranchAndBound::solveTSP() {
    auto start = chrono::high_resolution_clock::now();

    vector<int> curr_path(matrix_size, -1);

    visited[0] = true;
    curr_path[0] = 0;

    TSPRec(0, 1, curr_path);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> duration = end - start;
    executionTime = duration.count();
}

int TSPBranchAndBound::getFinalCost() const {
    return final_res;
}

double TSPBranchAndBound::getExecutionTime() const {
    return executionTime;
}

void TSPBranchAndBound::printResult() {
    cout << "Final Path Content: ";
    for (int node : final_path) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Minimum Cost: " << final_res << endl;
}
