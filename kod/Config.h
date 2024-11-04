#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
using namespace std;

class Config {
public:
    string matrix_source; // zrodlo danych wejsciowych file lub manual
    string alghoritm_type; // nazwa algorytmu: przeglad, najblizszych lub losowy
    int repetitions; // ilosc powtorzen do testow
    bool progress_indicator; // wskaznik postepu 1 - wyswietl, 0 - nie wyswietlaj
    int start_node; // wierzcholek startowy
    // gdy matrix_source = "file"
    string input_file; // plik z danymi wejsciowymi (nie zapomniec o katalogu)

    // gdy matrix_source = "file"
    int matrix_size; // rozmiar macierzy
    string matrix_type; // typ macierzy: synchronous lub asynchronous
    bool display_cost; // 1 - wyswietla koszt, 0 - nie wyswietla

    // funkcja do wczytania pliku konfiguracyjnego
    bool loadConfig(const string& filename);
};

#endif
