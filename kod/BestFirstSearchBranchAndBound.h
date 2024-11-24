#ifndef BEST_FIRST_SEARCH_BRANCH_AND_BOUND_H
#define BEST_FIRST_SEARCH_BRANCH_AND_BOUND_H

#include <vector>
#include <queue>
#include <limits>
#include "Matrix.h"
using namespace std;
class BestFirstSearchBranchAndBound {
private:
    struct Node {
        int level;                 // Poziom węzła w drzewie B&B
        int cost;                  // Koszt bieżącej ścieżki
        int bound;                 // Ograniczenie dla tego węzła
        vector<int> path;     // Ścieżka do tego węzła

        Node(int lvl, int cst, int bnd, const std::vector<int>& pth)
            : level(lvl), cost(cst), bound(bnd), path(pth) {}

        // Operator porównania, aby kopiec priorytetowy sortował węzły według bound (najniższy najpierw)
        bool operator<(const Node& other) const {
            return bound > other.bound;
        }
    };

    Matrix* matrix;                // Wskaźnik na macierz wag
    int matrix_size;               // Rozmiar macierzy (liczba wierzchołków)
    int final_res;                 // Minimalny koszt
    vector<int> final_path;   // Optymalna ścieżka

    int calculateLowerBound(const std::vector<int>& path, int level);

public:
    BestFirstSearchBranchAndBound(Matrix* inputMatrix);

    void solveTSP();
    void printResult();
};

#endif // BEST_FIRST_SEARCH_BRANCH_AND_BOUND_H
