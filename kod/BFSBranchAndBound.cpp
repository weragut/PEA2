#include "BFSBranchAndBound.h"
#include <chrono>


// constructor
BFSBranchAndBound::BFSBranchAndBound(Matrix* inputMatrix) {
    matrix = inputMatrix; // data matrix
    matrix_size = matrix->getSize(); // size of matrix
    final_res = INT_MAX; // sets the initial result to the max value of int
    final_path.resize(matrix_size + 1, -1); // allocate space for the final path
}

// function to calculate the bound
int BFSBranchAndBound::calculateBound(const Node& node) {
    int bound = node.cost; // initialize the bound with the current cost

    // calculate the min cost
    for (int i = 0; i < matrix_size; i++) {
        // for all unvisited node
        if (!node.visited[i]) {
            // looking for the min cost edge connecting unvisited nodes
            int minCost = INT_MAX;
            for (int j = 0; j < matrix_size; j++) {
                if (!node.visited[j] && i != j && matrix->getCost(i, j) != -1) {
                    if(matrix->getCost(i,j) < minCost) {
                        minCost = matrix->getCost(i, j);
                    }
                }
            }
            // adding the min cost to the bound
            bound += minCost;
        }
    }

    return bound;
}

// copies the current path into the final path
void BFSBranchAndBound::copyToFinal(const vector<int>& path) {
    final_path = path;
    final_path.push_back(path[0]); // closing the cycle with the starting node
}

//  solving the TSP using BFS with Branch and Bound
void BFSBranchAndBound::solveTSP() {
    // start the timer
    auto start = chrono::high_resolution_clock::now();

    QueueClass<Node> queue; // create an instance of a queue

    // initialization of the starting node
    Node root;
    root.level = 1;
    root.cost = 0;
    root.bound = 0;
    root.path.push_back(0); // starting in node 0
    root.visited.resize(matrix_size, false);
    root.visited[0] = true; // marking the starting node as visited

    root.bound = calculateBound(root); // calculating the bound
    queue.push(root); // push the starting node


    while (!queue.empty()) {
        // currently exploring node
        Node current = queue.front(); // get the front node
        queue.pop(); // remove it from the queue


        // skip nodes with bounds greater than or equal to the current best result
        if (current.bound >= final_res) continue;

        // expanding the node
        for (int i = 0; i < matrix_size; i++) {
            // condition: not visited and have an existing edge
            if (!current.visited[i] && matrix->getCost(current.path.back(), i) != -1) {
                // generating child node
                Node child = current;
                child.level = current.level + 1;
                child.cost += matrix->getCost(current.path.back(), i); // adding the additional cost
                child.path.push_back(i); // adding to the queue
                child.visited[i] = true; // marking as visited

                // calculating the final cost if all vertices are visited
                if (child.level == matrix_size) {
                    int returnCost = matrix->getCost(i, child.path[0]); // cost to the starting node
                    if (returnCost != -1) {
                        int totalCost = child.cost + returnCost; // adding the returning cost
                        if (totalCost < final_res) {
                            final_res = totalCost; // store new best cost
                            copyToFinal(child.path); // and path
                        }
                    }
                    // if not all vertices are visited
                } else {
                    // calculate the bound for the child node
                    // bound estimates the minimum possible cost for the path
                    child.bound = calculateBound(child);
                    // if the bound is less than the best known cost
                    if (child.bound < final_res) {
                        queue.push(child); // adding the child node to the queue
                    }
                }
            }
        }
    }

    // stop the timer
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start; // calculate the time
    executionTime = duration.count();
}

// return the execution time
double BFSBranchAndBound::getExecutionTime() const {
    return executionTime;
}

// return the final cost
int BFSBranchAndBound::getFinalCost() const {
    return final_res;
}

// print the path and min cost
void BFSBranchAndBound::printResult() {
    cout << "Final Path: ";
    for (int node : final_path) {
        cout << node << " ";
    }
    cout << "\nMinimum Cost: " << final_res << "\n";
}
