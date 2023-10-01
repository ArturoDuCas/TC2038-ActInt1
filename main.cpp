/*
    Actividad Integradora 1 - TC2038
    Integrantes:
        Arturo Duran Castillo - A00833516
        Andrés Marcelo De Luna Pámanes - A00832239
    Fecha: 1 de octubre 2023
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


void printVectorOfStrings(vector<string> vec) {
    for(int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

void readMCodes(vector<string> &vec) {
    ifstream file("./in/mcode.txt");

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string line;
    while (getline(file, line))
        vec.push_back(line);


    file.close();
}

void readTransmission(vector<string> &vec, string f) {
    ifstream file(f);

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo de transmision " << f << "\"" << endl;
        return;
    }

    string line;
    while (getline(file, line))
        vec.push_back(line);

    file.close();
}

int main() {
    vector<string> mcodes, transmissions;

    // read the files and store the data
    readMCodes(mcodes);
    readTransmission(transmissions, "./in/transmission1.txt");
    readTransmission(transmissions, "./in/transmission2.txt");
    readTransmission(transmissions, "./in/transmission3.txt");

    printVectorOfStrings(mcodes);
    cout << transmissions.size() << endl;

    return 0;
}