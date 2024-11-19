#ifndef DFS_H
#define DFS_H

#include "Matrix.h"

class DFS {
public:
    // Konstruktor: przyjmuje referencję do obiektu klasy Matrix
    DFS(const Matrix& matrix);

    // Destruktor: zwalnia dynamicznie alokowaną pamięć dla bestPath
    ~DFS();

    // Metoda wykonująca algorytm BFS, aby znaleźć najkrótszą trasę
    void findShortestPath();
    void findShortestPathSymmetric();  // Algorytm dla macierzy symetrycznych

    // Metoda wyświetlająca wynik końcowy
    void displayResult() const;

    // Metoda rekurencyjna do wykonywania algorytmu branch and bound na częściach trasy
    void branchAndBound(int* path, bool* visited, int level, int currentCost);
    void branchAndBoundSymmetric(int* path, bool* visited, int level, int currentCost); // Branch and Bound dla macierzy symetrycznych

private:
    const Matrix& matrix;      // Referencja do macierzy kosztów
    int minCost;         // Minimalny koszt znalezionej trasy
    int* bestPath;       // Najkrótsza trasa, reprezentowana jako dynamiczna tablica

};

#endif // BFS_H
