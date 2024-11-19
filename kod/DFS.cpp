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

    // base case: if the current path includes all vertices
    if (level == size) {
        // add the cost of returning to the starting vertex
        int totalCost = currentCost + matrix.getCost(path[level - 1], path[0]);
        cout << "Considered route: ";
        for (int i = 0; i < size; ++i) {
            cout << path[i] << " ";
        }

        cout << path[0] << " - Cost: " << totalCost << endl;

        // update the best path and its cost if the totalCost is better
        if (totalCost < minCost) {
            minCost = totalCost; // update the minimum cost
            if (bestPath == nullptr) bestPath = new int[size + 1]; // allocate memory for the best path
            for (int i = 0; i < size; ++i) {
                bestPath[i] = path[i]; // copy the current path to the best path
            }
            bestPath[size] = path[0]; // add the return to the starting vertex
        }
        return; // backtrack
    }

    // explore all possible next vertices
    for (int i = 1; i < size; ++i) {
        if (!visited[i]) { // check if the vertex has not been visited
            // calculate the cost of visiting the next vertex
            int newCost = currentCost + matrix.getCost(path[level - 1], i);

            // only continue if the newCost is less than the current minimum cost
            if (newCost < minCost) {
                path[level] = i; // add the vertex to the current path
                visited[i] = true; // mark the vertex as visited

                // recursively call branchAndBound to explore further
                branchAndBound(path, visited, level + 1, newCost);

                // backtrack: unmark the vertex as visited
                visited[i] = false;
            }else {
                // bound
                cout << "Ograniczenie aktywne: newCost = " << newCost
                 << ", minCost = " << minCost
                 << ", trasa odrzucona." << endl;
            }
        }
    }
}
