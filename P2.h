#include <bits/stdc++.h>
#include <algorithm> 
#include <vector>
#include <iostream>
#include <climits> 

using namespace std;


void solveTSP(vector<vector<int>> &distMatrix) {
    int n = distMatrix.size();
    if (n <= 1) {
        cout << "Ruta del repartidor: (A)\nCosto total: 0\n";
        return;
    }

    // Crear vector de ciudades a visitar (todas excepto la 0)
    vector<int> otherCities;
    for (int i = 1; i < n; i++) {
        otherCities.push_back(i);
    }

    // Inicializar variables para guardar la mejor ruta 

    // Usamos long long por si las sumas son muy grandes
    long long minPathCost = LLONG_MAX;
    // Guardamos la primera permutacion como la "mejor" inicial
    vector<int> bestPath = otherCities; 

    // Iterar sobre todas las permutaciones posibles 
    do {
        long long currentPathCost = 0;

        // Costo desde el inicio (A) a la primera ciudad de la permutacion
        currentPathCost += distMatrix[0][otherCities[0]];

        // Costo entre las ciudades intermedias
        for (int i = 0; i < n - 2; i++) {
            currentPathCost += distMatrix[otherCities[i]][otherCities[i + 1]];
        }

        // Costo desde la ultima ciudad de la permutacion de regreso al inicio
        currentPathCost += distMatrix[otherCities.back()][0];

        // Actualizar si encontramos una ruta mejor
        if (currentPathCost < minPathCost) {
            minPathCost = currentPathCost;
            bestPath = otherCities;
        }

    } while (next_permutation(otherCities.begin(), otherCities.end()));

    // Imprimir la solucion
    cout << "\n2. Ruta del repartidor (TSP):" << endl;
    cout << "   Ruta: A";
    for (int cityIndex : bestPath) {
        cout << " -> " << char(cityIndex + 65); 
    }
    cout << " -> A" << endl;
    cout << "   Costo total: " << minPathCost << endl;
}