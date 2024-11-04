#include "Config.h"
#include <iostream>
#include <fstream>

using namespace std;


bool Config::loadConfig(const string& filename) {
    ifstream file(filename); // otworzenie pliku konfiguracyjnego do odczytu

    if (!file.is_open()) { // sprawdzenie czy plik zostal otwarty
        cerr << "Nie mozna otworzyc pliku konfiguracyjnego: " << filename << endl;
        return false;
    }

    string key;
    while (file >> key) { // odczytywanie kluczy
        if (key == "matrix_source") { // sprawdzenie klucza i przypisanie wartosci, która jest po spacji
            file >> matrix_source;
        } else if (key == "progress_indicator") {
            file >> progress_indicator;
        } else if (key == "repetitions") {
            file >> repetitions;
        } else if (key == "input_file") {
            file >> input_file;
        } else if (key == "matrix_size") {
            file >> matrix_size;
        } else if (key == "matrix_type") {
            file >> matrix_type;
        }else if (key == "alghoritm_type") {
            file >> alghoritm_type;
        } else if (key == "start_node") {
            file >> start_node;
        }else if (key == "display_cost") {
            file >> display_cost;
        }
    }

    file.close(); // zamkniecie pliku
    return true;
}
