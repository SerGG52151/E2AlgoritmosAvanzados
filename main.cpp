#include<bits/stdc++.h>
#include <algorithm>
#include <climits>
#include "P1.h"
#include "P2.h"


using namespace std;

int n;
vector<vector<int>> distanceMatrix;
vector<vector<int>> flowMatrix;
vector<pair<int, int>> coords;

void readFile(const string& filePath){
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cerr << "Error: No se encontro el archivo" << filePath << endl;
        return;
    }

    // numero de vertices
    while (getline(file, line) && line.empty());
    n = stoi(line);

    // inicializar matrices
    distanceMatrix.assign(n, vector<int>(n));
    flowMatrix.assign(n, vector<int>(n));
    coords.resize(n);

    // matriz de distanciass
    for (int i = 0; i < n; ++i) {
        while (getline(file, line) && line.empty());
        stringstream ss(line);
        for (int j = 0; j < n; ++j) {
            ss >> distanceMatrix[i][j];
        }
    }

    // matriz de flujos
    for (int i = 0; i < n; ++i) {
        while (getline(file, line) && line.empty());
        stringstream ss(line);
        for (int j = 0; j < n; ++j) {
            ss >> flowMatrix[i][j];
        }
    }

    // coords
    for (int i = 0; i < n; ++i) {
        while (getline(file, line) && line.empty());
        line.erase(remove(line.begin(), line.end(), '('), line.end());
        line.erase(remove(line.begin(), line.end(), ')'), line.end());
        replace(line.begin(), line.end(), ',', ' ');
        stringstream ss(line);
        ss >> coords[i].first >> coords[i].second;
    }
}

void test(){
    cout << "N: " << n << endl;
    cout << "Matriz de Distancias:" << endl;
    for(const auto& row : distanceMatrix){
        for(int val : row){
            cout << val << " ";
        }
        cout << "\n\n";
    }

    cout << "Matriz de Flujo:" << endl;
    for(const auto& row : flowMatrix){
        for(int val : row){
            cout << val << " ";
        }
        cout << "\n\n";
    }

    cout << "Coordenadas:" << endl;
    for(const auto& p : coords){
        cout << "(" << p.first << "," << p.second << ")" << endl;
    }
    cout << "\n\n";
}

int main(){
    readFile("input.txt");
    test();
    primMST(distanceMatrix);
    solveTSP(distanceMatrix);
    
    return 0;
}