#ifndef BFS_H
#define BFS_H

#include "Matrix.h"

class BFS {
public:
    // Konstruktor: przyjmuje referencję do obiektu klasy Matrix
    BFS(const Matrix& matrix);

    // Destruktor: zwalnia dynamicznie alokowaną pamięć dla bestPath
    ~BFS();

    // Metoda wykonująca algorytm BFS, aby znaleźć najkrótszą trasę
    void findShortestPath();

    // Metoda wyświetlająca wynik końcowy
    void displayResult() const;

    // Metoda rekurencyjna do wykonywania algorytmu branch and bound na częściach trasy
    void branchAndBound(int* path, bool* visited, int level, int currentCost);

private:
    const Matrix& matrix;      // Referencja do macierzy kosztów
    int minCost;         // Minimalny koszt znalezionej trasy
    int* bestPath;       // Najkrótsza trasa, reprezentowana jako dynamiczna tablica

};

#endif // BFS_H
