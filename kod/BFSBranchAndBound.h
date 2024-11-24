#ifndef BFSBRANCHANDBOUND_H
#define BFSBRANCHANDBOUND_H

#include "Matrix.h"
#include <queue>
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

class BFSBranchAndBound {
private:
    Matrix* matrix;                     // Macierz kosztów
    int matrix_size;                    // Liczba wierzchołków
    int final_res;                      // Minimalny koszt
    vector<int> final_path;             // Najlepsza ścieżka

    struct Node {
        int level;                      // Poziom w drzewie (ilość odwiedzonych wierzchołków)
        int bound;                      // Ograniczenie dla tej ścieżki
        int cost;                       // Koszt dotychczasowy
        vector<int> path;               // Bieżąca ścieżka
        vector<bool> visited;           // Odwiedzone wierzchołki
    };

    // Funkcje pomocnicze
    int calculateBound(const Node& node);
    double executionTime; // Pole do przechowywania czasu wykonania

    void copyToFinal(const vector<int>& path);

public:
    BFSBranchAndBound(Matrix* inputMatrix);
    void solveTSP();
    double getExecutionTime() const; // Funkcja zwracająca czas wykonania
    void printResult();

    int getFinalCost() const;
};

#endif // BFSBRANCHANDBOUND_H
