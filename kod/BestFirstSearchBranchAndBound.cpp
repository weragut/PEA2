#include "BestFirstSearchBranchAndBound.h"
#include <iostream>
#include <chrono>
#include <climits>

// constructor
BestFirstSearchBranchAndBound::BestFirstSearchBranchAndBound(Matrix* inputMatrix)
    : matrix(inputMatrix), matrix_size(inputMatrix->getSize()), final_res(INT_MAX) {
    final_path.resize(matrix_size + 1, -1);
}

// calculating lower bound
int BestFirstSearchBranchAndBound::calculateLowerBound(const vector<int>& path, int level) {
    int bound = 0;

    // adding the cost of the current path
    for (int i = 1; i < level; ++i) {
        bound += matrix->getCost(path[i - 1], path[i]);
    }

    // adding an estimated minimum cost for unvisited nodes
    for (int i = 0; i < matrix_size; ++i) {
        bool visited = false;
        // checking if the nodes are visited
        for (int j = 0; j < level; ++j) {
            if (path[j] == i) {
                visited = true;
                break;
            }
        }
        // for unvisited nodes
        if (!visited) {
            int min_cost = INT_MAX; // the lowest cost from vertex j to another vertex
            for (int j = 0; j < matrix_size; ++j) {
                // if there is an existing edge
                if (matrix->getCost(i, j) != -1 && i != j) {
                    if (matrix->getCost(i, j) < min_cost) {
                        // new min cost
                        min_cost = matrix->getCost(i, j);
                    }
                }
            }
            bound += min_cost;
        }
    }

    return bound;
}

// adding a new node to the queue while keeping it sorted
// the node with the lowest bound is the first node in the priority queue
void BestFirstSearchBranchAndBound::pushNode(const Node& node) {
    manualQueue.push_back(node); // adding a new node to the queue

    // putting new node in right place in sorted queue
    for (size_t i = manualQueue.size() - 1; i > 0; --i) {
        if (manualQueue[i].bound < manualQueue[i - 1].bound) {
            swap(manualQueue[i], manualQueue[i - 1]);
        } else {
            break;
        }
    }
}

// removes and returns the node with the lowest bound from the queue
BestFirstSearchBranchAndBound::Node BestFirstSearchBranchAndBound::popNode() {
    Node top = manualQueue.front(); // saving the fornt node
    manualQueue.erase(manualQueue.begin()); // erase the first element
    return top; // returns the erased front node
}

void BestFirstSearchBranchAndBound::solveTSP() {
    // timer start
    auto start = chrono::high_resolution_clock::now();

    // initialize the initial path with -1 to represent unvisited nodes.
    vector<int> initial_path(matrix_size, -1);
    initial_path[0] = 0; // starting node

    // calculate the initial bound
    int initial_bound = calculateLowerBound(initial_path, 1);
    // push the initial node into the priority queue.
    pushNode(Node(1, 0, initial_bound, initial_path));

    // until the priority queue is empty
    // process nodes in the priority queue
    while (!manualQueue.empty()) {
        // the node with the lowest bouond
        Node current = popNode();


        // prune node if its bound is worse than the current best solution
        if (current.bound >= final_res) {
            continue; // skip
        }


        // if all nodes are visited, calculate the total cost
        if (current.level == matrix_size) {
            // adding the cost of returning
            int cost = current.cost + matrix->getCost(current.path[matrix_size - 1], 0);
            if (cost < final_res) {
                final_res = cost; // update the best cost
                final_path = current.path; // update the best path
                final_path.push_back(0); // close the cycle by returning to the starting node
            }
            continue; // skip and go to the next node it the priority queue
        }

        // expand the current node
        for (int i = 0; i < matrix_size; ++i) {
            // for each city not visited in the current path
            bool visited = false;
            // check if visited
            for (int j = 0; j < current.level; ++j) {
                if (current.path[j] == i) {
                    visited = true; // mark as visited
                    break; // stop checking
                }
            }

            // if not visited generate child node
            if (!visited) {
                // copy the current path and add the new node
                vector<int> new_path = current.path;
                new_path[current.level] = i;

                // calcuate new cost
                int new_cost = current.cost + matrix->getCost(current.path[current.level - 1], i);
                // calculate new bound
                int new_bound = calculateLowerBound(new_path, current.level + 1);

                // if the new bound is better than the current best solution
                if (new_bound < final_res) {
                    // push the node into the queue
                    pushNode(Node(current.level + 1, new_cost, new_bound, new_path));
                }
            }
        }
    }

    // timer stop
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> duration = end - start; // duration
    executionTime = duration.count();
}

// returns duration time
double BestFirstSearchBranchAndBound::getExecutionTime() const {
    return executionTime;
}

// printing final path and min cost
void BestFirstSearchBranchAndBound::printResult() {
    cout << "Final Path: ";
    for (int node : final_path) {
        cout << node << " ";
    }
    cout << "\nMinimum Cost: " << final_res << endl;
}

// returns final cost
int BestFirstSearchBranchAndBound::getFinalCost() const {
    return final_res;
}
