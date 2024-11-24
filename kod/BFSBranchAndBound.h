#ifndef BFSBRANCHANDBOUND_H
#define BFSBRANCHANDBOUND_H

#include "Matrix.h"
#include "QueueClass.h"
#include <vector>
#include <climits>
#include <iostream>

class BFSBranchAndBound {
private:
    Matrix* matrix;                     // Macierz kosztów
    int matrix_size;                    // Liczba wierzchołków
    int final_res;                      // Minimalny koszt
    std::vector<int> final_path;        // Najlepsza ścieżka

    struct Node {
        int level;                      // Poziom w drzewie (liczba odwiedzonych wierzchołków)
        int bound;                      // Ograniczenie dla tej ścieżki
        int cost;                       // Koszt dotychczasowy
        std::vector<int> path;          // Aktualna ścieżka
        std::vector<bool> visited;      // Wierzchołki odwiedzone
    };

    double executionTime;               // Czas wykonania algorytmu

    int calculateBound(const Node& node); // Funkcja obliczająca ograniczenie dla węzła
    void copyToFinal(const std::vector<int>& path); // Kopiowanie do finalnej ścieżki

public:
    BFSBranchAndBound(Matrix* inputMatrix);
    void solveTSP();                    // Rozwiązanie problemu TSP
    double getExecutionTime() const;    // Zwraca czas wykonania
    int getFinalCost() const;           // Zwraca minimalny koszt
    void printResult();                 // Wyświetla wynik
};

#endif // BFSBRANCHANDBOUND_H
