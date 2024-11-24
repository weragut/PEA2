#include "BestFirstSearchBranchAndBound.h"
#include <iostream>
#include <chrono>
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
        bool visited = false;
        for (int j = 0; j < level; ++j) {
            if (path[j] == i) {
                visited = true;
                break;
            }
        }
        if (!visited) {
            int min_cost = INT_MAX;
            for (int j = 0; j < matrix_size; ++j) {
                if (matrix->getCost(i, j) != -1 && i != j) {
                    if (matrix->getCost(i, j) < min_cost) {
                        min_cost = matrix->getCost(i, j);
                    }
                }
            }
            bound += min_cost;
        }
    }

    return bound;
}

void BestFirstSearchBranchAndBound::pushNode(const Node& node) {
    manualQueue.push_back(node);
    for (size_t i = manualQueue.size() - 1; i > 0; --i) {
        if (manualQueue[i].bound < manualQueue[i - 1].bound) {
            std::swap(manualQueue[i], manualQueue[i - 1]);
        } else {
            break;
        }
    }
}

BestFirstSearchBranchAndBound::Node BestFirstSearchBranchAndBound::popNode() {
    Node top = manualQueue.front();
    manualQueue.erase(manualQueue.begin());
    return top;
}

void BestFirstSearchBranchAndBound::solveTSP() {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> initial_path(matrix_size, -1);
    initial_path[0] = 0;

    int initial_bound = calculateLowerBound(initial_path, 1);
    pushNode(Node(1, 0, initial_bound, initial_path));

    while (!manualQueue.empty()) {
        Node current = popNode();

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
            bool visited = false;
            for (int j = 0; j < current.level; ++j) {
                if (current.path[j] == i) {
                    visited = true;
                    break;
                }
            }
            if (!visited) {
                std::vector<int> new_path = current.path;
                new_path[current.level] = i;

                int new_cost = current.cost + matrix->getCost(current.path[current.level - 1], i);
                int new_bound = calculateLowerBound(new_path, current.level + 1);

                if (new_bound < final_res) {
                    pushNode(Node(current.level + 1, new_cost, new_bound, new_path));
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start;
    executionTime = duration.count();
}

double BestFirstSearchBranchAndBound::getExecutionTime() const {
    return executionTime;
}

void BestFirstSearchBranchAndBound::printResult() {
    std::cout << "Final Path: ";
    for (int node : final_path) {
        std::cout << node << " ";
    }
    std::cout << "\nMinimum Cost: " << final_res << std::endl;
}

int BestFirstSearchBranchAndBound::getFinalCost() const {
    return final_res;
}
