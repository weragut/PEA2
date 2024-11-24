#include "Matrix.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cstdlib>  // do funkcji rand()
using namespace std;

// konstruktor inicjalizuje macierz jako pusta i rozmiar = 0
Matrix::Matrix() : matrix(nullptr), size(0) {}
// dekonstruktor wywoluje funkcje zwalniajaca pamiec
Matrix::~Matrix() {
    freeMemory();
}
// funkcja wczytujaca macierz z pliku
bool Matrix::loadFromFile(const string& filename) {
    ifstream inputFile(filename);// otwieranie pliku

    if (!inputFile.is_open()) {
        cout << "Proba otwarcia pliku: " << filename << endl;
        cerr << "Nie można otworzyc pliku: " << filename << endl;
        return false;
    }

    // usuniecie pamieci przed wczytaniem macierzy
    freeMemory();

    inputFile >> size; // wprowadzenie rozmiaru z pliku z danymi

    // wczytanie wartości z pliku do macierzy
    matrix = new int*[size]; // alokacja dynamicznej tablicy wskazników
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size]; // alokacja pamieci dla wierszy macierzy
        for (int j = 0; j < size; ++j) {
            inputFile >> matrix[i][j]; // wczytanie wrtosci
        }
    }

    inputFile.close(); // zamkniecie pliku
    return true;
}

// funkcja generujaca losowa macierz
void Matrix::generateManual(int matrixsize, const string& type) {
    // usuniecie pamieci przed wczytaniem macierzy
    freeMemory();
    size = matrixsize; // przypisanie rozmiaru
    matrix = new int*[size]; // alokacja dynamicznej tablicy wskazników

    if(type == "asynchronous") {
        for (int i = 0; i < size; ++i) {
            matrix[i] = new int[size]; // alokacja pamieci dla kazdego wiersza
            for (int j = 0; j < size; ++j) {
                if (i == j) {
                    matrix[i][j] = -1;  // przekatna = -1
                } else {
                    matrix[i][j] = rand() % 100 + 1;  // wartosci od 1 do 100
                }
            }
        }
    }else if (type == "synchronous"){
        for (int i = 0; i < size; ++i) {
            matrix[i] = new int[size]; // alokacja pamieci dla kazdego wiersza
            for (int j = 0; j < size; ++j) {
                if (i == j) {
                    matrix[i][j] = -1;  // przekatna = -1
                } else if(i<j){
                    matrix[i][j] = rand() % 100 + 1;
                }else if(i>j) { // dla elementow ponizej przekatnej
                    matrix[i][j] = matrix[j][i]; // to zapisujemy wartosc symetryczna do przekatnej
                }
            }
        }

    }

}

// wyswietlenie macierzy
void Matrix::display() const {
    if (matrix == nullptr) return;

    cout << "Matrix (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
// wyczyszczenie pamieci
void Matrix::freeMemory() {
    if (matrix != nullptr) {
        for (int i = 0; i < size; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}
// funkcja zwraca rozmiar macierzy
int Matrix::getSize() const {
    return size;
}
// funkcja zwraca koszt miedzy wierzcholkami
int Matrix::getCost(int i, int j) const {
    if (i < size && j < size) {
        return matrix[i][j];
    } else {
        return -1;
    }
}