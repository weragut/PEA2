#ifndef BFS_H
#define BFS_H

#include "Matrix.h"
#include <iostream>
#include <queue>
#include <vector>

class BFS {
public:
    // konstruktor przyjmujacy referencje do obiektu klasy Matrix
    explicit BFS(const Matrix& matrix);

    // metoda uruchamiajaca algorytm BFS od podanego wierzcholka startowego
    void run(int startNode = 0);

private:
    const Matrix& matrix; // referencja do macierzy, ktora reprezentuje graf
};

#endif // BFS_H
