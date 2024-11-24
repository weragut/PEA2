#ifndef DFSBRANCHANDBOUND_H
#define DFSBRANCHANDBOUND_H

#include "Matrix.h"
#include <vector>
#include <climits>
#include <iostream>

class DFSBranchAndBound {
private:
    struct Node {
        int level;                      // Poziom w drzewie
        int bound;                      // Ograniczenie dla tej ścieżki
        int cost;                       // Koszt dotychczasowy
        std::vector<int> path;          // Obecna ścieżka
        std::vector<bool> visited;      // Węzły odwiedzone
    };

    Matrix* matrix;                     // Wskaźnik na macierz kosztów
    int matrix_size;                    // Liczba wierzchołków
    int final_res;                      // Minimalny koszt
    std::vector<int> final_path;        // Najlepsza ścieżka
    double executionTime;               // Czas wykonania algorytmu

    void dfs(Node node);                // Funkcja DFS
    int calculateBound(const Node& node); // Obliczanie ograniczenia
    int firstMin(int i);                // Pierwsze minimum dla wierzchołka i
    int secondMin(int i);               // Drugie minimum dla wierzchołka i
    void copyToFinal(const std::vector<int>& path); // Kopiowanie ścieżki

public:
    DFSBranchAndBound(Matrix* inputMatrix);
    void solveTSP();
    double getExecutionTime() const;
    int getFinalCost() const;
    void printResult();
};

#endif // DFSBRANCHANDBOUND_H
