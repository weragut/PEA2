#include "DFSBranchAndBound.h"
#include <chrono>

DFSBranchAndBound::DFSBranchAndBound(Matrix* inputMatrix) {
    matrix = inputMatrix;
    matrix_size = matrix->getSize();
    final_res = INT_MAX;
    final_path.resize(matrix_size + 1, -1);
}

void DFSBranchAndBound::copyToFinal(const std::vector<int>& path) {
    final_path = path;
    final_path.push_back(path[0]); // Zamykamy cykl
}

int DFSBranchAndBound::firstMin(int i) {
    int min = INT_MAX;
    for (int k = 0; k < matrix_size; k++) {
        if (matrix->getCost(i, k) != -1 && i != k) {
            if (matrix->getCost(i, k) < min) {
                min = matrix->getCost(i, k);
            }
        }
    }
    return min;
}

int DFSBranchAndBound::secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int k = 0; k < matrix_size; k++) {
        if (matrix->getCost(i, k) != -1 && i != k) {
            if (matrix->getCost(i, k) <= first) {
                second = first;
                first = matrix->getCost(i, k);
            } else if (matrix->getCost(i, k) < second) {
                second = matrix->getCost(i, k);
            }
        }
    }
    return second;
}

int DFSBranchAndBound::calculateBound(const Node& node) {
    int bound = 0;

    // Dodajemy pierwsze i drugie minimum dla ostatniego odwiedzonego wierzchołka
    int lastVisited = node.path.back();
    bound += firstMin(lastVisited) + secondMin(lastVisited);

    // Dla pozostałych nieodwiedzonych wierzchołków, dodajemy tylko pierwsze minimum
    for (int i = 0; i < matrix_size; i++) {
        if (!node.visited[i]) {
            bound += firstMin(i);
        }
    }

    // Dzielenie przez 2, aby uniknąć podwójnego liczenia
    return (bound + 1) / 2;
}

void DFSBranchAndBound::dfs(Node node) {
    // Jeśli odwiedziliśmy wszystkie wierzchołki
    if (node.level == matrix_size) {
        if (matrix->getCost(node.path.back(), node.path[0]) != -1) {
            int currentCost = node.cost + matrix->getCost(node.path.back(), node.path[0]);
            if (currentCost < final_res) {
                copyToFinal(node.path);
                final_res = currentCost;
            }
        }
        return;
    }

    // Rozwijamy gałęzie
    for (int i = 0; i < matrix_size; i++) {
        if (!node.visited[i] && matrix->getCost(node.path.back(), i) != -1) {
            Node child = node;
            child.level = node.level + 1;
            child.cost += matrix->getCost(node.path.back(), i);
            child.path.push_back(i);
            child.visited[i] = true;

            child.bound = calculateBound(child);

            if (child.bound < final_res) {
                dfs(child);
            }
        }
    }
}

void DFSBranchAndBound::solveTSP() {
    auto start = std::chrono::high_resolution_clock::now();

    Node root;
    root.level = 1;
    root.cost = 0;
    root.bound = 0;
    root.path.push_back(0); // Startujemy od wierzchołka 0
    root.visited.resize(matrix_size, false);
    root.visited[0] = true;

    root.bound = calculateBound(root);

    dfs(root);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start;
    executionTime = duration.count();
}

double DFSBranchAndBound::getExecutionTime() const {
    return executionTime;
}

int DFSBranchAndBound::getFinalCost() const {
    return final_res;
}

void DFSBranchAndBound::printResult() {
    std::cout << "Final Path: ";
    for (int node : final_path) {
        std::cout << node << " ";
    }
    std::cout << "\nMinimum Cost: " << final_res << "\n";
}
