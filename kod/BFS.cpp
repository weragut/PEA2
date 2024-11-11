#include "BFS.h"
#include <iostream>
#include <climits>

BFS::BFS(const Matrix& m) : matrix(m), minCost(INT_MAX), bestPath(nullptr) {}

BFS::~BFS() {
    delete[] bestPath;
}

void BFS::findShortestPath() {
    int size = matrix.getSize();
    if (size == 0) return;

    int* path = new int[size + 1];
    bool* visited = new bool[size]();

    path[0] = 0;
    visited[0] = true;

    branchAndBound(path, visited, 1, 0);

    delete[] path;
    delete[] visited;
}

void BFS::displayResult() const {
    if (bestPath != nullptr) {
        std::cout << "Najkrotsza trasa: ";
        for (int i = 0; i <= matrix.getSize(); ++i) {
            std::cout << bestPath[i] << " ";
        }
        std::cout << "\nKoszt: " << minCost << std::endl;
    } else {
        std::cout << "Nie znaleziono rozwiazania." << std::endl;
    }
}

void BFS::branchAndBound(int* path, bool* visited, int level, int currentCost) {
    int size = matrix.getSize();

    if (level == size) {
        int totalCost = currentCost + matrix.getCost(path[level - 1], path[0]);
        if (totalCost < minCost) {
            minCost = totalCost;
            if (bestPath == nullptr) bestPath = new int[size + 1];
            for (int i = 0; i < size; ++i) {
                bestPath[i] = path[i];
            }
            bestPath[size] = path[0];
        }
        return;
    }

    for (int i = 1; i < size; ++i) {
        if (!visited[i]) {
            int newCost = currentCost + matrix.getCost(path[level - 1], i);

            if (newCost < minCost) {
                path[level] = i;
                visited[i] = true;

                branchAndBound(path, visited, level + 1, newCost);

                visited[i] = false;
            }
        }
    }
}
