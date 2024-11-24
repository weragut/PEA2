#include "BFS.h"
#include <iostream>
#include <climits>
using namespace std;

// konstruktor
BFS::BFS(const Matrix& m)
    : matrix(m), minCost(INT_MAX), bestPath(nullptr), queueSize(0), front(0), rear(0) {
    int size = matrix.getSize();
    queueSize = 100000; // ustalony maksymalny rozmiar kolejki
    pathQueue = new int*[queueSize];
    costQueue = new int[queueSize];
    levelQueue = new int[queueSize];
    visitedQueue = new bool*[queueSize];

    for (int i = 0; i < queueSize; ++i) {
        pathQueue[i] = new int[size + 1];
        visitedQueue[i] = new bool[size];
    }
}

// destruktor
BFS::~BFS() {
    delete[] bestPath;
    for (int i = 0; i < queueSize; ++i) {
        delete[] pathQueue[i];
        delete[] visitedQueue[i];
    }
    delete[] pathQueue;
    delete[] costQueue;
    delete[] levelQueue;
    delete[] visitedQueue;
}

// metoda główna
void BFS::findShortestPath() {
    branchAndBound();
}

// metoda wyświetlająca wynik
void BFS::displayResult() const {
    if (bestPath != nullptr) {
        cout << "Najkrotsza trasa: ";
        for (int i = 0; i <= matrix.getSize(); ++i) {
            cout << bestPath[i] << " ";
        }
        cout << "\nKoszt: " << minCost << endl;
    } else {
        cout << "Nie znaleziono rozwiazania." << endl;
    }
}

// metoda realizująca algorytm BFS z ograniczeniami (Branch and Bound)
void BFS::branchAndBound() {
    int size = matrix.getSize();

    // inicjalizacja stanu początkowego
    pathQueue[rear][0] = 0;       // ścieżka zaczyna się od wierzchołka 0
    for (int i = 0; i < size; ++i) {
        visitedQueue[rear][i] = false;
    }
    visitedQueue[rear][0] = true; // oznaczenie wierzchołka 0 jako odwiedzonego
    costQueue[rear] = 0;          // początkowy koszt
    levelQueue[rear] = 1;         // początkowy poziom
    rear = (rear + 1) % queueSize;

    // główna pętla BFS
    while (front != rear) {
    // Pobierz bieżący stan z kolejki
    int* currentPath = pathQueue[front];
    bool* currentVisited = visitedQueue[front];
    int currentCost = costQueue[front];
    int currentLevel = levelQueue[front];
    front = (front + 1) % queueSize;

    // Odrzuć bieżący stan, jeśli częściowy koszt przekracza aktualny minCost
    if (currentCost >= minCost) {
        cout << "Odrzucono trase z powodu wysokiego kosztu: ";
        for (int i = 0; i < currentLevel; ++i) {
            cout << currentPath[i] << " ";
        }
        cout << "- Koszt: " << currentCost << endl;
        continue;
    }

    // Jeśli osiągnięto pełną ścieżkę
    if (currentLevel == size) {
        int totalCost = currentCost + matrix.getCost(currentPath[currentLevel - 1], 0);
        cout << "Rozwazana trasa: ";
        for (int i = 0; i < size; ++i) {
            cout << currentPath[i] << " ";
        }
        cout << "0 - Koszt: " << totalCost << endl;

        if (totalCost < minCost) {
            minCost = totalCost;
            if (bestPath == nullptr) bestPath = new int[size + 1];
            for (int i = 0; i < size; ++i) {
                bestPath[i] = currentPath[i];
            }
            bestPath[size] = 0;
        }
        continue;
    }

    // Generuj kolejne stany
    for (int i = 1; i < size; ++i) {
        if (!currentVisited[i]) {
            // Deklaracja newCost wewnątrz pętli
            int newCost = currentCost + matrix.getCost(currentPath[currentLevel - 1], i);

            // Odrzucenie ścieżki od razu po przekroczeniu minCost
            if (newCost >= minCost) {
                cout << "Odrzucono trase: ";
                for (int j = 0; j < currentLevel; ++j) {
                    cout << currentPath[j] << " ";
                }
                cout << i << " - Koszt: " << newCost << endl;
                continue; // Przejdź do następnej iteracji pętli
            }

            // Ograniczenie: jeśli kolejny wierzchołek przekracza limit, przerwij rozwijanie
            if (newCost >= minCost) {
                break; // Koniec rozwijania tej ścieżki
            }

            // Sprawdź przepełnienie kolejki
            if ((rear + 1) % queueSize == front) {
                cerr << "Przekroczono maksymalny rozmiar kolejki!" << endl;
                exit(1);
            }

            // Kopiuj bieżący stan do nowego elementu kolejki
            for (int j = 0; j < size; ++j) {
                visitedQueue[rear][j] = currentVisited[j];
            }
            for (int j = 0; j < currentLevel; ++j) {
                pathQueue[rear][j] = currentPath[j];
            }
            pathQueue[rear][currentLevel] = i; // Dodaj nowy wierzchołek do ścieżki
            visitedQueue[rear][i] = true;     // Oznacz wierzchołek jako odwiedzony

            costQueue[rear] = newCost;
            levelQueue[rear] = currentLevel + 1;

            rear = (rear + 1) % queueSize;
        }
    }
}

}
