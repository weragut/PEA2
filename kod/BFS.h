#ifndef BFS_H
#define BFS_H

#include "Matrix.h"

class BFS {
private:
    const Matrix& matrix;   // referencja do macierzy kosztów
    int minCost;            // minimalny koszt (najlepszy znaleziony)
    int* bestPath;          // najlepsza ścieżka
    int queueSize;          // rozmiar kolejki
    int front;              // indeks początku kolejki
    int rear;               // indeks końca kolejki
    int** pathQueue;        // kolejka przechowująca ścieżki
    int* costQueue;         // kolejka przechowująca koszty
    int* levelQueue;        // kolejka przechowująca poziomy
    bool** visitedQueue;    // kolejka przechowująca odwiedzone wierzchołki

public:
    BFS(const Matrix& m);   // konstruktor
    ~BFS();                 // destruktor

    void findShortestPath();  // metoda główna do znajdowania najkrótszej ścieżki
    void displayResult() const; // metoda do wyświetlania wyników

private:
    void branchAndBound();    // metoda realizująca BFS z ograniczeniami
};

#endif // BFS_H
