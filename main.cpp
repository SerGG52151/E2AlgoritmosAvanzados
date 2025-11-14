#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

#include "P1.h"
#include "P2.h"
#include "P3.h"
#include "P4.h"
#include "P5.h"

using namespace std;

int n;
vector<vector<int>> distanceMatrix;
vector<vector<int>> flowMatrix;
vector<pair<int, int>> coords;

void readFile(const string& filePath){
    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cerr << "Error: No se encontro el archivo " << filePath << endl;
        return;
    }

    while (getline(file, line) && line.empty());
    n = stoi(line);

    distanceMatrix.assign(n, vector<int>(n));
    flowMatrix.assign(n, vector<int>(n));
    coords.resize(n);

    for (int i = 0; i < n; ++i) {
        while (getline(file, line) && line.empty());
        stringstream ss(line);
        for (int j = 0; j < n; ++j) {
            ss >> distanceMatrix[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        while (getline(file, line) && line.empty());
        stringstream ss(line);
        for (int j = 0; j < n; ++j) {
            ss >> flowMatrix[i][j];
        }
    }
    
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
    //test();
    
    cout << "--- SINGLE-OBJECTIVE OPTIMIZATIONS ---\n";
    primMST(distanceMatrix);
    
    solveTSP_HeldKarp(distanceMatrix);                     
    
    edmondsKarp(flowMatrix);

    nearestCentralInteractive(coords);

    // --- PARETO-OPTIMAL FRONT GENERATION ---
    cout << "\n--- GENERATING PARETO-OPTIMAL FRONT DATA ---\n";
    ofstream plotFile("pareto_data.csv");
    if (plotFile.is_open()) {
        plotFile << "Alpha,Total_Distance,Total_Flow_Capacity\n";
        // Iterate through different alpha values to find multiple Pareto-optimal points
        for (int i = 0; i <= 100; ++i) {
            double alpha = i / 100.0;
            findParetoOptimalSolution(alpha, distanceMatrix, flowMatrix, n, plotFile);
        }
        plotFile.close();
        cout << "Data for Pareto front saved to 'pareto_data.csv'\n";
    } else {
        cerr << "Unable to open file for writing Pareto data.\n";
    }

    return 0;
}
