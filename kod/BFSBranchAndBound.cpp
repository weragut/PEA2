#include "BFSBranchAndBound.h"
#include <chrono>
#include <algorithm>

BFSBranchAndBound::BFSBranchAndBound(Matrix* inputMatrix) {
    matrix = inputMatrix;
    matrix_size = matrix->getSize();
    final_res = INT_MAX;
    final_path.resize(matrix_size + 1, -1);
}

int BFSBranchAndBound::calculateBound(const Node& node) {
    int bound = node.cost;

    // Dodajemy pierwsze minimum dla każdego nieodwiedzonego wierzchołka
    for (int i = 0; i < matrix_size; i++) {
        if (!node.visited[i]) {
            int minCost = INT_MAX;
            for (int j = 0; j < matrix_size; j++) {
                if (!node.visited[j] && i != j && matrix->getCost(i, j) != -1) {
                    minCost = std::min(minCost, matrix->getCost(i, j));
                }
            }
            bound += minCost;
        }
    }

    return bound;
}

void BFSBranchAndBound::copyToFinal(const std::vector<int>& path) {
    final_path = path;
    final_path.push_back(path[0]); // Zamykamy cykl
}

void BFSBranchAndBound::solveTSP() {
    auto start = std::chrono::high_resolution_clock::now(); // Start pomiaru czasu

    QueueClass<Node> queue;

    // Inicjalizacja węzła startowego
    Node root;
    root.level = 1;
    root.cost = 0;
    root.bound = 0;
    root.path.push_back(0); // Startujemy od wierzchołka 0
    root.visited.resize(matrix_size, false);
    root.visited[0] = true;

    root.bound = calculateBound(root);
    queue.push(root);

    // Przetwarzanie węzłów w kolejce
    while (!queue.empty()) {
        Node current = queue.front();
        queue.pop();

        // Jeśli ograniczenie dla węzła przekracza obecny najlepszy wynik, pomijamy go
        if (current.bound >= final_res) continue;

        // Rozwijanie węzła
        for (int i = 0; i < matrix_size; i++) {
            if (!current.visited[i] && matrix->getCost(current.path.back(), i) != -1) {
                Node child = current;
                child.level = current.level + 1;
                child.cost += matrix->getCost(current.path.back(), i);
                child.path.push_back(i);
                child.visited[i] = true;

                // Jeśli wszystkie wierzchołki zostały odwiedzone, obliczamy koszt końcowy
                if (child.level == matrix_size) {
                    int returnCost = matrix->getCost(i, child.path[0]); // Powrót do startu
                    if (returnCost != -1) {
                        int totalCost = child.cost + returnCost;
                        if (totalCost < final_res) {
                            final_res = totalCost;
                            copyToFinal(child.path);
                        }
                    }
                } else {
                    child.bound = calculateBound(child);
                    if (child.bound < final_res) {
                        queue.push(child);
                    }
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start;
    executionTime = duration.count();
}

double BFSBranchAndBound::getExecutionTime() const {
    return executionTime;
}

int BFSBranchAndBound::getFinalCost() const {
    return final_res;
}

void BFSBranchAndBound::printResult() {
    std::cout << "Final Path: ";
    for (int node : final_path) {
        std::cout << node << " ";
    }
    std::cout << "\nMinimum Cost: " << final_res << "\n";
}
