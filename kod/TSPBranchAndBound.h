#ifndef TSPBRANCHANDBOUND_H
#define TSPBRANCHANDBOUND_H

#include "Matrix.h" // Klasa Matrix do obsługi macierzy
#include <vector>
#include <climits> // dla INT_MAX

class TSPBranchAndBound {
private:
    int final_res;                     // Minimalny koszt
    std::vector<int> final_path;       // Optymalna ścieżka
    std::vector<bool> visited;         // Węzły odwiedzone
    int matrix_size;                             // Liczba miast
    Matrix* matrix;                    // Wskaźnik do macierzy kosztów

    // Funkcje pomocnicze
    void copyToFinal(const std::vector<int>& curr_path); // Kopiuje ścieżkę do final_path
    int firstMin(int i);                                // Pierwsze minimum dla węzła i
    int secondMin(int i);                               // Drugie minimum dla węzła i
    int calculateBound();
    void TSPRec(int curr_bound, int curr_weight, int level, std::vector<int>& curr_path); // Rekurencyjne B&B

public:
    // Konstruktor
    TSPBranchAndBound(Matrix* inputMatrix);

    // Funkcja rozwiązująca problem TSP
    void solveTSP();

    // Funkcja wypisująca wynik
    void printResult();
};

#endif // TSPBRANCHANDBOUND_H
