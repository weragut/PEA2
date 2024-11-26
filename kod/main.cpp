// Weronika Gut 273003
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <numeric>

#include "Config.h"
#include "Matrix.h"

#include "BFSBranchAndBound.h"

#include "BestFirstSearchBranchAndBound.h"
#include "DFSBranchAndBound.h"




using namespace std;

// configuration object to store settings
Config config;
// matrix declaration
Matrix matrix;


// algorithm execution
void algorithmExecution() {

    vector<double> bfsTimes, dfsTimes, bestTimes; // vectors for storing times


    for (int i = 0; i < config.repetitions; i++) {

        // process indicator
        if (config.progress_indicator) {
            int progress = (i + 1) * 100 / config.repetitions;  // calculate completion percentage
            cout << "Progress: " << progress << "% (" << i + 1 << "/" << config.repetitions << ")\n";
            cout.flush();  // refresh
        }

        // generating a matrix or loading from file
        if (config.matrix_source == "manual") {
            matrix.generateManual(config.matrix_size, config.matrix_type);
        } else if (config.matrix_source == "file") {
            if (!matrix.loadFromFile(config.input_file)) {
                cerr << "Error loading matrix from file." << endl;
                return;
            }
        }

        //matrix.display();

        // execute BFS Branch and Bound
        if (config.alghoritm_type == "bfs"|| config.alghoritm_type == "all") {
            BFSBranchAndBound bfsSolver(&matrix);
            bfsSolver.solveTSP();
            double bfsTime = bfsSolver.getExecutionTime();
            bfsTimes.push_back(bfsTime);
            cout << "BFS: final cost = " << bfsSolver.getFinalCost() << endl;
            //bfsSolver.printResult();
        }

        // execute DFS Branch and Bound
        if(config.alghoritm_type == "dfs"|| config.alghoritm_type == "all") {
            DFSBranchAndBound dfsSolver(&matrix);
            dfsSolver.solveTSP();
            double dfsTime = dfsSolver.getExecutionTime();
            dfsTimes.push_back(dfsTime);
            cout << "DFS: final cost = " << dfsSolver.getFinalCost() << endl;
        }

        // execute Best-First Search Branch and Bound
        if(config.alghoritm_type == "best" || config.alghoritm_type == "all") {
            BestFirstSearchBranchAndBound bestSolver(&matrix);
            bestSolver.solveTSP();
            double bestTime = bestSolver.getExecutionTime();
            bestTimes.push_back(bestTime);
            cout << "best first search: final cost = " << bestSolver.getFinalCost() << endl;
        }


    }


    // save results to output files
    ofstream bfsFile("wyjscie/bfs.csv", ios::app);
    ofstream dfsFile("wyjscie/dfs.csv", ios::app);
    ofstream bestFile("wyjscie/best.csv", ios::app);

    // save BFS times to file if executed
        if (config.alghoritm_type == "bfs"|| config.alghoritm_type == "all") {
        bfsFile << matrix.getSize() << endl;
        for (double time : bfsTimes) {
            bfsFile << time << " ";
        }
        bfsFile << endl;
    }

    // save DFS times to file if executed
    if(config.alghoritm_type == "dfs"|| config.alghoritm_type == "all") {
        dfsFile << matrix.getSize() << endl;
        for (double time : dfsTimes) {
            dfsFile << time << " ";
        }
        dfsFile << endl;
    }

    // save Best-First Search times to file if executed
    if(config.alghoritm_type == "best" || config.alghoritm_type == "all") {
        bestFile << matrix.getSize() << endl;
        for (double time : bestTimes) {
            bestFile << time << " ";
        }
        bestFile << endl;
    }

    // file close
    bfsFile.close();
    dfsFile.close();
    bestFile.close();

    //  informations
    cout << "Repetitions: " << config.repetitions << "\n";
    cout << "Matrix size: " << matrix.getSize() << "\n"; // zle
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
    srand(time(0)); // seed for random number generation

    // load configuration file
    if (!config.loadConfig("wejscie/plik_konfiguracyjny.txt")) {
        return 1;
    }

    // alghoritm executions
    algorithmExecution();

    // print memory usage
    //printMemoryUsage();
    return 0;
}
