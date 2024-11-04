#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;


class Matrix {
public:
    Matrix(); // konstruktor
    ~Matrix(); // dekonstruktor

    bool loadFromFile(const string& filename);   // wczytywanie macierzy z pliku
    void generateManual(int size, const string& type);  // generowanie losowej macierzy, argumenty: rozmiar, typ (synchronous lub asynchronous)

    void display() const; // wyswietlenie macierzy (funkcja pomocnicza)
    void freeMemory(); // zwolnienie pamieci

    int getSize() const; // zwraca rozmiar macierzy
    int getCost(int i, int j) const; // zwraca koszt przejscia z miasta do miasta

private:
    int** matrix; // wskaznik do dwuwymiarowej tablicy (dynamicznie alokowana macierz)
    int size; // rozmiar macierzy
};

#endif
