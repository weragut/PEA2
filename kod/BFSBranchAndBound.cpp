#include "BFSBranchAndBound.h"

BFSBranchAndBound::BFSBranchAndBound(Matrix* inputMatrix) {
    matrix = inputMatrix;
    matrix_size = matrix->getSize();
    final_res = INT_MAX;
    final_path.resize(matrix_size + 1, -1);
}

int BFSBranchAndBound::calculateBound(const Node& node) {
    int bound = node.cost;

    for (int i = 0; i < matrix_size; i++) {
        if (!node.visited[i]) {
            int minCost = INT_MAX;
            for (int j = 0; j < matrix_size; j++) {
                if (matrix->getCost(i, j) != -1 && i != j && !node.visited[j]) {
                    // Sprawdzamy: istnieje krawędź z i do j, i != j, oraz j nie jest odwiedzony
                    minCost = min(minCost, matrix->getCost(i, j)); // Znajdujemy minimalny koszt
                }
            }
            bound += minCost;
        }
    }
    return bound;
}

void BFSBranchAndBound::copyToFinal(const vector<int>& path) {
    final_path = path;
    final_path.push_back(path[0]); // Zamykamy cykl, wracając do startu
}

void BFSBranchAndBound::solveTSP() {
    queue<Node> q;

    // Tworzymy korzeń drzewa
    Node root;
    root.level = 1;
    root.cost = 0;
    root.bound = 0;
    root.path.push_back(0); // Startujemy od wierzchołka 0
    root.visited.resize(matrix_size, false);
    root.visited[0] = true;

    root.bound = calculateBound(root);
    q.push(root);

    while (!q.empty()) {
        Node curr = q.front();
        q.pop();

        if (curr.bound >= final_res) continue;

        for (int i = 0; i < matrix_size; i++) {
            if (!curr.visited[i] && matrix->getCost(curr.path.back(), i) != -1) {
                Node child = curr;
                child.level = curr.level + 1;
                child.cost += matrix->getCost(curr.path.back(), i);
                child.path.push_back(i);
                child.visited[i] = true;

                if (child.level == matrix_size) {
                    // Jeśli mamy pełną ścieżkę, dodajemy koszt powrotu
                    if (matrix->getCost(i, 0) != -1) {
                        int totalCost = child.cost + matrix->getCost(i, 0);
                        if (totalCost < final_res) {
                            final_res = totalCost;
                            copyToFinal(child.path);
                        }
                    }
                } else {
                    child.bound = calculateBound(child);
                    if (child.bound < final_res) {
                        q.push(child);
                    }
                }
            }
        }
    }
}

void BFSBranchAndBound::printResult() {
    cout << "Final Path Content: ";
    for (int node : final_path) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Minimum Cost: " << final_res << endl;
    cout << "Path Taken: ";
    for (size_t i = 0; i < final_path.size(); i++) {
        if (final_path[i] == -1) {
            cerr << "Warning: Path contains invalid node (-1)!" << endl;
        }
        cout << final_path[i] << " ";
    }
    cout << endl;
}
