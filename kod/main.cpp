// Weronika Gut 273003
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Config.h"
#include "Matrix.h"
#include "BFS.h"
#include "DFS.h"
#include "TSPBranchAndBound.h"

using namespace std;

// obiekt config do przechowywania ustawien z pliku konfiguracyjnego
Config config;
// deklaracja macierzy
Matrix matrix;


// wykonywanie algorytmu i zapis czasow do plikow
void algorithmExecution() {
    for (int i = 0; i < config.repetitions; i++) {

        double executionTime = 0.0;
        int minCost = -1;
        int startNode = config.start_node; // wierzcholek z pliku

        if (config.alghoritm_type == "bfs") {
            BFS bfs(matrix);

            if (startNode >= 0 && startNode < matrix.getSize()) {
                // Wykonujemy algorytm BFS dla problemu komiwojażera
                bfs.findShortestPath();


                // Wyświetlamy wynik
                bfs.displayResult();
                //bfs.findShortestPathSymmetric();
                //bfs.displayResult();
                cout<< "Metoda BFS" << endl;

            } else {
                cerr << "Nieprawidlowy wierzcholek startowy." << endl;
            }
        }else if(config.alghoritm_type == "dfs") {
            //DFS dfs(matrix);
           // dfs.findShortestPath();
            //dfs.displayResult();
            cout<< "Metoda DFS" << endl;
            // Rozwiązanie TSP algorytmem Branch and Bound
            TSPBranchAndBound tsp(&matrix);
            tsp.solveTSP();
            tsp.printResult();
        }


    }
}


int main() {
    srand(time(0)); // ziarno do funkcji rand

    // wczytaj plik konfiguracyjny
    if (!config.loadConfig("wejscie/plik_konfiguracyjny.txt")) {
        return 1;
    }

    // tworzenie macierzy z pliku lub generowanie jej manualnie
    if (config.matrix_source == "file") {
        if (!matrix.loadFromFile(config.input_file)) {
            return 1;
        }
    } else if (config.matrix_source == "manual") {
        matrix.generateManual(config.matrix_size, config.matrix_type);
    }

    // wyswietlenie rozmiaru macierzy
    cout << "Rozmiar macierzy: " << matrix.getSize() << "x" << matrix.getSize() << endl;
    matrix.display();
    // wywolanie wykonania algorytmu
    algorithmExecution();

    return 0;
}
