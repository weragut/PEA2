#include "BestFirstSearchBranchAndBound.h"
#include <iostream>
#include <algorithm>
#include <climits>

BestFirstSearchBranchAndBound::BestFirstSearchBranchAndBound(Matrix* inputMatrix)
    : matrix(inputMatrix), matrix_size(inputMatrix->getSize()), final_res(INT_MAX) {
    final_path.resize(matrix_size + 1, -1);
}

int BestFirstSearchBranchAndBound::calculateLowerBound(const std::vector<int>& path, int level) {
    int bound = 0;

    // Dodaj koszt bieżącej ścieżki
    for (int i = 1; i < level; ++i) {
        bound += matrix->getCost(path[i - 1], path[i]);
    }

    // Dodaj dolną granicę kosztów dla nieodwiedzonych wierzchołków
    for (int i = 0; i < matrix_size; ++i) {
        if (find(path.begin(), path.begin() + level, i) == path.begin() + level) {
            int min_cost = INT_MAX;
            for (int j = 0; j < matrix_size; ++j) {
                if (matrix->getCost(i, j) != -1 && i != j) {
                    min_cost = std::min(min_cost, matrix->getCost(i, j));
                }
            }
            bound += min_cost;
        }
    }

    return bound;
}

void BestFirstSearchBranchAndBound::solveTSP() {
    // Priority queue to explore the node with the smallest bound first
    priority_queue<Node> pq;

    vector<int> initial_path(matrix_size, -1);
    initial_path[0] = 0;

    int initial_bound = calculateLowerBound(initial_path, 1);
    pq.push(Node(1, 0, initial_bound, initial_path));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.bound >= final_res) {
            continue;
        }

        if (current.level == matrix_size) {
            int cost = current.cost + matrix->getCost(current.path[matrix_size - 1], 0);
            if (cost < final_res) {
                final_res = cost;
                final_path = current.path;
                final_path.push_back(0);
            }
            continue;
        }

        for (int i = 0; i < matrix_size; ++i) {
            if (find(current.path.begin(), current.path.begin() + current.level, i) == current.path.begin() + current.level) {
                vector<int> new_path = current.path;
                new_path[current.level] = i;

                int new_cost = current.cost + matrix->getCost(current.path[current.level - 1], i);
                int new_bound = calculateLowerBound(new_path, current.level + 1);

                if (new_bound < final_res) {
                    pq.push(Node(current.level + 1, new_cost, new_bound, new_path));
                }
            }
        }
    }
}

void BestFirstSearchBranchAndBound::printResult() {
    cout << "Final Path: ";
    for (int node : final_path) {
        cout << node << " ";
    }
    cout << "\nMinimum Cost: " << final_res << std::endl;
}
