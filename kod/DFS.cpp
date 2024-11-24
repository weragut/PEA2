#include "DFS.h"
#include <iostream>
#include <climits>
using namespace std;

// constructor initializes the matrix reference, sets the minimum cost to INT_MAX, and the best path to nullptr
DFS::DFS(const Matrix& m) : matrix(m), minCost(INT_MAX), bestPath(nullptr) {}

// destructor
DFS::~DFS() {
    delete[] bestPath;
}

// finds the shortest path using DFS-style branch and bound
void DFS::findShortestPath() {
    int size = matrix.getSize();
    if (size == 0) return; // if the matrix is empty, return immediately

    // dynamically allocate an array to store the current path
    int* path = new int[size + 1];
    // dynamically allocate an array to track visited vertices and initialize to false
    bool* visited = new bool[size]();

    path[0] = 0; // set the starting vertex as 0
    visited[0] = true; // mark the starting vertex as visited

    // call the recursive branchAndBound function to find the shortest path
    branchAndBound(path, visited, 1, 0);

    // free the dynamically allocated memory for path and visited arrays
    delete[] path;
    delete[] visited;
}

// displays the shortest path and its cost
void DFS::displayResult() const {
    if (bestPath != nullptr) { // if a valid path was found
        cout << "Shortest path: "; // print the shortest path
        for (int i = 0; i <= matrix.getSize(); ++i) {
            cout << bestPath[i] << " ";
        }
        cout << "\nCost: " << minCost << endl; // print the cost of the shortest path
    } else {
        cout << "No solution was find." << endl; // no solution was found
    }
}

// recursive function to explore paths using branch and bound
void DFS::branchAndBound(int* path, bool* visited, int level, int currentCost) {
    int size = matrix.getSize();

    // Log rozwijanej trasy
    cout << "Rozwijana trasa: ";
    for (int i = 0; i < level; ++i) {
        cout << path[i] << " ";
    }
    cout << "- Koszt dotychczasowy: " << currentCost << endl;

    // Jeśli osiągnięto pełną trasę (powrót do początkowego węzła)
    if (level == size) {
        int totalCost = currentCost + matrix.getCost(path[level - 1], path[0]);
        cout << "Rozważana pełna trasa: ";
        for (int i = 0; i < size; ++i) {
            cout << path[i] << " ";
        }
        cout << path[0] << " - Koszt całkowity: " << totalCost << endl;

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

    // Rozważanie kolejnych wierzchołków
    for (int i = 1; i < size; ++i) {
        if (!visited[i]) {
            int newCost = currentCost + matrix.getCost(path[level - 1], i);

            // Jeśli koszt nowej ścieżki jest mniejszy niż obecny minimalny koszt
            if (newCost < minCost) {
                path[level] = i;
                visited[i] = true;

                branchAndBound(path, visited, level + 1, newCost);

                visited[i] = false; // Cofanie
            } else {
                // Wyświetlenie kosztu tylko do momentu przekroczenia ograniczenia
                cout << "Odrzucono trase z powodu wysokiego kosztu: ";
                for (int j = 0; j <= level - 1; ++j) {
                    cout << path[j] << " ";
                }
                cout << i << " - Koszt: " << currentCost + matrix.getCost(path[level - 1], i) << endl;

                // Przerwanie rozwijania tej gałęzi
            }
        }
    }
}
