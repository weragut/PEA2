#include "BFS.h"
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm> // dodanie naglowka dla std::find

using namespace std;

// konstruktor klasy BFS, przyjmuje referencje do obiektu Matrix
BFS::BFS(const Matrix& matrix) : matrix(matrix) {}

// implementacja metody run, wykonuje algorytm BFS
void BFS::run(int startNode) {
    int size = matrix.getSize();
    if (size == 0) {
        cerr << "Macierz jest pusta. Algorytm BFS nie moze byc wykonany." << endl;
        return; // zwracamy, jesli macierz jest pusta
    }

    // struktura przechowujaca aktualny stan w algorytmie BFS
    struct State {
        int currentNode; // obecny wierzcholek
        vector<int> path; // sciezka odwiedzonych wierzcholkow
        int cost; // calkowity koszt sciezki

        // konstruktor struktury State
        State(int node, vector<int> p, int c) : currentNode(node), path(p), cost(c) {}
    };

    // kolejka do przechowywania stanow do przetworzenia
    queue<State> queue;
    queue.push(State(startNode, {startNode}, 0)); // inicjalizacja z wierzcholkiem startowym
    int bestCost = INT_MAX; // poczatkowo najlepszy koszt jest maksymalny
    vector<int> bestPath; // przechowywanie najlepszej sciezki

    // glowna petla algorytmu BFS
    while (!queue.empty()) {
        State current = queue.front(); // pobieramy pierwszy stan z kolejki
        queue.pop(); // usuwamy ten stan z kolejki

        // sprawdzamy, czy odwiedzono juz wszystkie miasta i powrot do startu jest mozliwy
        if (current.path.size() == size) {
            int returnCost = matrix.getCost(current.currentNode, startNode);
            if (returnCost > 0) { // sprawdzamy, czy koszt powrotu jest dodatni (czy istnieje krawedz)
                int totalCost = current.cost + returnCost;
                if (totalCost < bestCost) { // aktualizujemy najlepszy koszt, jesli znalezlismy lepszy
                    bestCost = totalCost;
                    bestPath = current.path;
                    bestPath.push_back(startNode); // dodajemy powrot do startu
                }
            }
            continue; // przechodzimy do kolejnego stanu w kolejce
        }

        // przegladanie sasiadow bieżącego wierzcholka
        for (int i = 0; i < size; ++i) {
            // sprawdzamy, czy istnieje krawedz i czy wierzcholek nie byl odwiedzony
            if (matrix.getCost(current.currentNode, i) > 0 && find(current.path.begin(), current.path.end(), i) == current.path.end()) {
                vector<int> newPath = current.path; // kopiujemy biezaca sciezke
                newPath.push_back(i); // dodajemy nowy wierzcholek do sciezki
                int newCost = current.cost + matrix.getCost(current.currentNode, i); // obliczamy nowy koszt

                // sprawdzamy, czy nowy koszt jest lepszy niz najlepszy dotychczasowy
                if (newCost < bestCost) {
                    queue.push(State(i, newPath, newCost)); // dodajemy nowy stan do kolejki
                }
            }
        }
    }

    // wyswietlanie najlepszego znalezionego rozwiazania
    if (!bestPath.empty()) {
        cout << "Najlepsza znaleziona sciezka: ";
        for (int node : bestPath) {
            cout << node << " ";
        }
        cout << "\nKoszt: " << bestCost << endl;
    } else {
        cout << "Nie znaleziono sciezki." << endl;
    }
}
