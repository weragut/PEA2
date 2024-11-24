#ifndef BEST_FIRST_SEARCH_BRANCH_AND_BOUND_H
#define BEST_FIRST_SEARCH_BRANCH_AND_BOUND_H

#include <vector>
#include <limits>
#include "Matrix.h"

class BestFirstSearchBranchAndBound {
private:
    struct Node {
        int level;                 // Poziom węzła w drzewie B&B
        int cost;                  // Koszt bieżącej ścieżki
        int bound;                 // Ograniczenie dla tego węzła
        std::vector<int> path;     // Ścieżka do tego węzła

        Node(int lvl, int cst, int bnd, const std::vector<int>& pth)
            : level(lvl), cost(cst), bound(bnd), path(pth) {}
    };

    Matrix* matrix;                // Wskaźnik na macierz wag
    int matrix_size;               // Rozmiar macierzy (liczba wierzchołków)
    int final_res;                 // Minimalny koszt
    std::vector<int> final_path;   // Optymalna ścieżka
    double executionTime;          // Pole do przechowywania czasu wykonania

    int calculateLowerBound(const std::vector<int>& path, int level);

    // Manually implemented priority queue
    std::vector<Node> manualQueue;

    void pushNode(const Node& node);
    Node popNode();

public:
    BestFirstSearchBranchAndBound(Matrix* inputMatrix);

    void solveTSP();
    double getExecutionTime() const; // Funkcja zwracająca czas wykonania

    int getFinalCost() const;
    void printResult();
};

#endif // BEST_FIRST_SEARCH_BRANCH_AND_BOUND_H
