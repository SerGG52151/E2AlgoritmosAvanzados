#include <vector>
#include <algorithm> 
#include <climits>   
#include <iostream>

using namespace std;


void solveTSP_HeldKarp(vector<vector<int>> &distMatrix) {
    int n = distMatrix.size();
    if (n <= 1) {
        cout << "Ruta del repartidor: (A)\nCosto total: 0\n";
        return;
    }

    // Inicializar estructuras de DP
    
    // Costo minimo del camino desde 0, visitando nodos en 'mask', terminando en 'j'
    vector<vector<long long>> dp(1 << n, vector<long long>(n, LLONG_MAX));

    // Almacena el nodo 'k' (anterior) que dio el costo mínimo
    // para llegar a 'j' con el set 'mask'. Sirve para reconstruir la ruta.
    vector<vector<int>> parent(1 << n, vector<int>(n, -1));

    // El camino que solo visita {0} y termina en 0, tiene costo 0.
    dp[1][0] = 0;

    // Iteramos por todas las mascaras, pero nos aseguramos de que el nodo 0 este.
    for (int mask = 1; mask < (1 << n); mask += 2) { 
        // Iteramos por el nodo final 'j'
        for (int j = 1; j < n; j++) {
            // Si 'j' está en la mascara actual
            if (mask & (1 << j)) {
                // Buscamos el nodo anterior 'k'
                int prev_mask = mask ^ (1 << j); // Mascara sin el nodo 'j'

                for (int k = 0; k < n; k++) {
                    // Si 'k' está en la mascara anterior Y hay un camino válido hacia 'k'
                    if ((prev_mask & (1 << k)) && dp[prev_mask][k] != LLONG_MAX) {
                        
                        long long new_cost = dp[prev_mask][k] + distMatrix[k][j];

                        // Si encontramos un camino mas corto para [mask][j]
                        if (new_cost < dp[mask][j]) {
                            dp[mask][j] = new_cost;
                            parent[mask][j] = k;
                        }
                    }
                }
            }
        }
    }

    // La mascara con todos los nodos visitados
    int all_visited_mask = (1 << n) - 1; 
    long long minCost = LLONG_MAX;
    int last_node = -1;

    // Vemos cual es el mejor 'j' para terminar el ciclo y volver a 0
    for (int j = 1; j < n; j++) {
        if (dp[all_visited_mask][j] == LLONG_MAX) continue;

        long long final_path_cost = dp[all_visited_mask][j] + distMatrix[j][0];
        if (final_path_cost < minCost) {
            minCost = final_path_cost;
            last_node = j;
        }
    }

    cout << "\n2. Ruta del repartidor (TSP - Held-Karp):" << endl;

    if (last_node == -1) {
        cout << "   No se encontro una ruta valida." << endl;
        return;
    }

    vector<int> path;
    int curr_mask = all_visited_mask;
    int curr_node = last_node;

    // Backtracking usando la tabla 'parent'
    while (curr_node != 0) {
        path.push_back(curr_node);
        int prev_node = parent[curr_mask][curr_node];
        curr_mask ^= (1 << curr_node);
        curr_node = prev_node;
    }
    path.push_back(0);
    reverse(path.begin(), path.end());

    cout << "   Ruta: A";
    for (size_t i = 1; i < path.size(); i++) {
        cout << " -> " << char(path[i] + 65);
    }
    cout << " -> A" << endl;
    cout << "   Costo total: " << minCost << "\n\n";
}