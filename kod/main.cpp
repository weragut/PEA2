// Weronika Gut 273003
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <numeric>

#include "Config.h"
#include "Matrix.h"
#include "BFS.h"
#include "BFSBranchAndBound.h"
#include "DFS.h"
#include "TSPBranchAndBound.h"
#include "ProbyAlgorytmow.h"
#include "BestFirstSearchBranchAndBound.h"
#include "DFSBranchAndBound.h"

//#include <windows.h> // do pomiaru zajetej pamieci
//#include <psapi.h> // do pomiaru zajetej pamieci


using namespace std;

// obiekt config do przechowywania ustawien z pliku konfiguracyjnego
Config config;
// deklaracja macierzy
Matrix matrix;
/*
void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter; // struktura do przechowywania danych o zuzyciu pamieci
    GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter)); // ta funkcja pobiera informacje o zuzyciu pamieci dla danego procesu
    // argumenty: process handle, wskaznik na strukture przechowujaca dane o pamieci, rozmiar struktury
    cout << "Aktualnie zajeta pamiec: " << memCounter.WorkingSetSize / 1024 << " KB" << endl;
}*/

// wykonywanie algorytmu i zapis czasow do plikow
void algorithmExecution() {
/*
    // Pliki wyjściowe dla każdego algorytmu
    ofstream bfsFile("wyniki/bfs.csv", ios::app);
    ofstream dfsFile("wyniki/dfs.csv", ios::app);
    ofstream bestFile("wyniki/best.csv", ios::app);
*/
    vector<double> bfsTimes, dfsTimes, bestTimes; // Do przechowywania czasów


    for (int i = 0; i < config.repetitions; i++) {

        // Generowanie lub wczytywanie macierzy
        if (config.matrix_source == "manual") {
            matrix.generateManual(config.matrix_size, config.matrix_type);
        } else if (config.matrix_source == "file") {
            if (!matrix.loadFromFile(config.input_file)) {
                cerr << "Błąd wczytywania macierzy." << endl;
                return;
            }
        }

        matrix.display();

        if (config.alghoritm_type == "bfs"|| config.alghoritm_type == "all") {
            BFSBranchAndBound bfsSolver(&matrix);
            bfsSolver.solveTSP();
            double bfsTime = bfsSolver.getExecutionTime();
            bfsTimes.push_back(bfsTime);
            //bfsFile << matrix.getSize() << "," << bfsTime << "," << bfsSolver.getFinalCost() << "\n";
            cout << "BFS: final cost = " << bfsSolver.getFinalCost() << endl;
            bfsSolver.printResult();
            //BFS bfs(matrix);
            /*BFSBranchAndBound bfsSolver(&matrix);
            bfsSolver.solveTSP();
            cout << "BFS Branch and Bound Result:" << endl;
            bfsSolver.printResult();
            cout << "Czas wykonania (w mikrosekundach): " << bfsSolver.getExecutionTime() << " us" << std::endl;

*/
                // Wykonujemy algorytm BFS dla problemu komiwojażera
                //bfs.findShortestPath();


                // Wyświetlamy wynik
                //bfs.displayResult();
                //bfs.findShortestPathSymmetric();
                //bfs.displayResult();
                //cout<< "Metoda BFS" << endl;

        }

        if(config.alghoritm_type == "dfs"|| config.alghoritm_type == "all") {
            DFSBranchAndBound dfsSolver(&matrix);
            dfsSolver.solveTSP();
            double dfsTime = dfsSolver.getExecutionTime();
            dfsTimes.push_back(dfsTime);
            //dfsFile << matrix.getSize() << "," << dfsTime << "," << dfsSolver.getFinalCost() << "\n";
            cout << "DFS: final cost = " << dfsSolver.getFinalCost() << endl;
            dfsSolver.printResult();
            //DFS dfs(matrix);
           // dfs.findShortestPath();
            //dfs.displayResult();
            //cout<< "Metoda DFS" << endl;
            // Rozwiązanie TSP algorytmem Branch and Bound
            /*TSPBranchAndBound tsp(&matrix);
            tsp.solveTSP();
            tsp.printResult();
*/
            /*ProbyAlgorytmow tspSolver(&matrix);
            tspSolver.solveTSP();
            tspSolver.printResult();*/
        }

        if(config.alghoritm_type == "best" || config.alghoritm_type == "all") {
            BestFirstSearchBranchAndBound bestSolver(&matrix);
            bestSolver.solveTSP();
            double bestTime = bestSolver.getExecutionTime();
            bestTimes.push_back(bestTime);
            //bestFile << matrix.getSize() << "," << bestTime << "," << bestSolver.getFinalCost() << "\n";
            cout << "best: final cost = " << bestSolver.getFinalCost() << endl;

            /*BestFirstSearchBranchAndBound best(&matrix);
            best.solveTSP();
            best.printResult();
            */
        }


    }
    // otworzenie plikow w trybie dopisywania
    ofstream bfsFile("wyjscie/bfs.csv", ios::app);
    ofstream dfsFile("wyjscie/dfs.csv", ios::app);
    ofstream bestFile("wyjscie/best.csv", ios::app);

    // zapisanie wynikow
        if (config.alghoritm_type == "bfs"|| config.alghoritm_type == "all") {
        bfsFile << matrix.getSize() << endl; // zapisujemy rozmiar
        for (double time : bfsTimes) {
            bfsFile << time << " ";  // zapisujemy czasy oddzielone spacja
        }
        bfsFile << endl;
    }

    if(config.alghoritm_type == "dfs"|| config.alghoritm_type == "all") {
        dfsFile << matrix.getSize() << endl;
        for (double time : dfsTimes) {
            dfsFile << time << " ";
        }
        dfsFile << endl;
    }

    if(config.alghoritm_type == "best" || config.alghoritm_type == "all") {
        bestFile << matrix.getSize() << endl;
        for (double time : bestTimes) {
            bestFile << time << " ";
        }
        bestFile << endl;
    }

    // Zamykanie plików
    bfsFile.close();
    dfsFile.close();
    bestFile.close();

    //  informations
    cout << "Repetitions: " << config.repetitions << "\n";
    cout << "Matrix size: " << config.matrix_size << "\n"; // zle
    cout << "Alghoritm type: " << config.alghoritm_type << "\n";

    // Obliczanie średnich czasów dla każdego algorytmu
    if (!bfsTimes.empty()) {
        double avgBfsTime = accumulate(bfsTimes.begin(), bfsTimes.end(), 0.0) / bfsTimes.size();
        cout << "Average time BFS: " << avgBfsTime << " us" << endl;
    }
    if (!dfsTimes.empty()) {
        double avgDfsTime = accumulate(dfsTimes.begin(), dfsTimes.end(), 0.0) / dfsTimes.size();
        cout << "Average time DFS: " << avgDfsTime << " us" << endl;
    }
    if (!bestTimes.empty()) {
        double avgBestTime = accumulate(bestTimes.begin(), bestTimes.end(), 0.0) / bestTimes.size();
        cout << "Average time Best First Search: " << avgBestTime << " us" << endl;
    }


}


int main() {
    srand(time(0)); // ziarno do funkcji rand

    // wczytaj plik konfiguracyjny
    if (!config.loadConfig("wejscie/plik_konfiguracyjny.txt")) {
        return 1;
    }



    // alghoritm executions
    algorithmExecution();

    return 0;
}
