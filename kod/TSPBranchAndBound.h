#ifndef TSPBRANCHANDBOUND_H
#define TSPBRANCHANDBOUND_H

#include "Matrix.h"
#include <vector>
#include <climits>

class TSPBranchAndBound {
private:
    int final_res;                     // Minimalny koszt
    std::vector<int> final_path;       // Optymalna ścieżka
    std::vector<bool> visited;         // Węzły odwiedzone
    int matrix_size;                   // Liczba miast
    Matrix* matrix;                    // Wskaźnik do macierzy kosztów

    double executionTime;              // Czas wykonania algorytmu

    void copyToFinal(const std::vector<int>& curr_path);  // Kopiuje ścieżkę do final_path
    int calculateBound(const std::vector<int>& curr_path); // Ograniczenie dolne
    int firstMin(int i);               // Pierwsze minimum dla węzła i
    int secondMin(int i);              // Drugie minimum dla węzła i
    void TSPRec(int curr_weight, int level, std::vector<int>& curr_path); // Rekurencyjne B&B

public:
    TSPBranchAndBound(Matrix* inputMatrix);
    void solveTSP();
    int getFinalCost() const;
    double getExecutionTime() const;
    void printResult();
};

#endif // TSPBRANCHANDBOUND_H
