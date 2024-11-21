#include "TSPBranchAndBound.h"
#include <iostream>
#include <climits>

using namespace std;

TSPBranchAndBound::TSPBranchAndBound(Matrix* inputMatrix) {
    matrix = inputMatrix;
    N = matrix->getSize();
    final_res = INT_MAX;
    visited.resize(N, false);
    final_path.resize(N+1, -1);
}

void TSPBranchAndBound::copyToFinal(const vector<int>& curr_path) {
    final_path = curr_path; // Kopiujemy bieżącą ścieżkę
    if (final_path[0] != -1) {
        final_path.push_back(final_path[0]); // Dodajemy punkt startowy tylko raz
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

int TSPBranchAndBound::firstMin(int i) {
    int min_cost = INT_MAX;
    for (int k = 0; k < N; k++) {
        if (matrix->getCost(i, k) != -1 && i != k) {
            min_cost = min(min_cost, matrix->getCost(i, k));
        }
    }
    return min_cost;
}

int TSPBranchAndBound::secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int k = 0; k < N; k++) {
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

    if (level == N) {
        if (matrix->getCost(curr_path[level - 1], curr_path[0]) != -1) {
            int curr_res = curr_weight + matrix->getCost(curr_path[level - 1], curr_path[0]);
            if (curr_res < final_res) {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (matrix->getCost(curr_path[level - 1], i) != -1 && !visited[i]) {
            int temp = curr_bound;
            curr_weight += matrix->getCost(curr_path[level - 1], i);

            if (level == 1)
                curr_bound -= (firstMin(curr_path[level - 1]) + firstMin(i)) / 2;
            else
                curr_bound -= (secondMin(curr_path[level - 1]) + firstMin(i)) / 2;

            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                TSPRec(curr_bound, curr_weight, level + 1, curr_path);
            }

            curr_weight -= matrix->getCost(curr_path[level - 1], i);
            curr_bound = temp;
            fill(visited.begin(), visited.end(), false);
            for (int j = 0; j <= level - 1; j++) {
                visited[curr_path[j]] = true;
            }
        }
    }
}

void TSPBranchAndBound::solveTSP() {
    vector<int> curr_path(N, -1);
    int curr_bound = 0;

    for (int i = 0; i < N; i++) {
        curr_bound += firstMin(i) + secondMin(i);
    }
    curr_bound = (curr_bound % 2 == 0) ? curr_bound / 2 : curr_bound / 2 + 1;

    visited[0] = true;
    curr_path[0] = 0;

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

