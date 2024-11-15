#include "BFS.h"
#include <iostream>
#include <climits>
using namespace std;

// konstruktor
BFS::BFS(const Matrix& m) : matrix(m), minCost(INT_MAX), bestPath(nullptr) {}

// dekonstruktor
BFS::~BFS() {
    delete[] bestPath;
}

void BFS::findShortestPath() {
    int size = matrix.getSize();
    if (size == 0) return;

    // tablica przechowujaca obecnie przetwarzana trase
    int* path = new int[size + 1];
    // tablica przechowujaca informacje czy wierzcholek byl odwiedzony
    bool* visited = new bool[size]();

    path[0] = 0; // wierzcholek startowy
    visited[0] = true; // wierzcholek startowy oznaczony jako odwiedzony

    // wywolanie metody branchAndBound
    branchAndBound(path, visited, 1, 0);

    delete[] path;
    delete[] visited;
}

void BFS::displayResult() const {
    if (bestPath != nullptr) {
        cout << "Najkrotsza trasa: ";
        for (int i = 0; i <= matrix.getSize(); ++i) {
            cout << bestPath[i] << " ";
        }
        cout << "\nKoszt: " << minCost << endl;
    } else {
        cout << "Nie znaleziono rozwiazania." << endl;
    }
}

void BFS::branchAndBound(int* path, bool* visited, int level, int currentCost) {
    int size = matrix.getSize();

    if (level == size) {
        int totalCost = currentCost + matrix.getCost(path[level - 1], path[0]);
        cout << "Rozważana trasa: ";
        for (int i = 0; i < size; ++i) {
            cout << path[i] << " ";
        }
        cout << path[0] << " - Koszt: " << totalCost << endl;

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


// Algorytm dla macierzy symetrycznych
void BFS::findShortestPathSymmetric() {
    int size = matrix.getSize();
    if (size == 0) return;

    int* path = new int[size + 1];
    bool* visited = new bool[size]();

    path[0] = 0;
    visited[0] = true;

    branchAndBoundSymmetric(path, visited, 1, 0);

    delete[] path;
    delete[] visited;
}

// Branch and Bound dla macierzy symetrycznych
void BFS::branchAndBoundSymmetric(int* path, bool* visited, int level, int currentCost) {
    int size = matrix.getSize();

    // Jeśli osiągnęliśmy pełną trasę (powrót do miasta początkowego)
    if (level == size) {
        int totalCost = currentCost + matrix.getCost(path[level - 1], path[0]);
        cout << "Rozważana trasa (symetryczna): ";
        for (int i = 0; i < size; ++i) {
            cout << path[i] << " ";
        }
        cout << path[0] << " - Koszt: " << totalCost << endl;

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

    // Eksploruj kolejne wierzchołki
    for (int i = 1; i < size; ++i) {
        if (!visited[i] && i > path[level - 1]) { // Jeśli wierzchołek nie został jeszcze odwiedzony
            int newCost = currentCost + matrix.getCost(path[level - 1], i);

            if (newCost < minCost) { // Jeśli nowy koszt jest obiecujący
                path[level] = i;
                visited[i] = true;

                branchAndBoundSymmetric(path, visited, level + 1, newCost);

                visited[i] = false; // Cofanie (backtracking)
            }
        }
    }
}
