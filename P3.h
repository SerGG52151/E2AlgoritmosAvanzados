#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Función auxiliar para realizar BFS y encontrar un camino aumentante
bool bfs(const vector<vector<int>>& capacidad, vector<vector<int>>& flujo, vector<int>& padre, int inicio, int fin) {
    int nodo_cantidad = capacidad.size();

    // Inicializar todos los nodos como no visitados
    // Marcar raiz como nodo especial (-2)
    fill(padre.begin(), padre.end(), -1);
    padre[inicio] = -2; 

    // Cada nodo tiene una pareja con el # del nodo y su capacidad
    // El inicial tiene capacidad infinita al empezar
    queue<pair<int, int>> q;
    q.push({inicio, INT_MAX});


    while (!q.empty()) {
        //Procesar nodo actual
        int u = q.front().first;
        int capacidad_actual = q.front().second;
        q.pop();
        
        //Exploramos vecinos que no hayan sido visitados mientras haya capacidad
        for (int v = 0; v < nodo_cantidad; v++) {
            if (padre[v] == -1 && capacidad[u][v] - flujo[u][v] > 0) {
                padre[v] = u;

                //actualizamos la capacidad
                int nueva_capacidad = min(capacidad_actual, capacidad[u][v] - flujo[u][v]);

                //solo salimos de la busqueda de este camino al momento de encontrar el nodo fin
                if (v == fin)
                    return true;

                //si no es el final, actualizamos q con el nodo vecino y su capacidad
                q.push({v, nueva_capacidad});
            }
        }
    }
    return false;
}

// Implementación de Edmonds-Karp
int edmondsKarp(vector<vector<int>> capacidad) {
    cout << "Ingrese el nodo fuente (0 a " << n - 1 << "): ";
    cin >> inicio;
    cout << "Ingrese el nodo destino (0 a " << n - 1 << "): ";
    cin >> fin;

    if (inicio < 0 || inicio >= n || fin < 0 || fin >= n) {
        cerr << "Error: Nodos inválidos. Deben estar entre 0 y " << n - 1 << endl;
        return 1;
    }
    
    if (inicio == fin) {
        cerr << "Error: El nodo fuente y destino deben ser diferentes." << endl;
        return 1;
    }


    int n = capacidad.size();
    vector<vector<int>> flujo(n, vector<int>(n, 0));
    vector<int> padre(n);
    int flujo_maximo = 0;

    while (bfs(capacidad, flujo, padre, inicio, fin)) {
        int incremento = INT_MAX;

        // Recorre el camino desde el nodo fin hasta el inicio usando el vector padre
        for (int v = fin; v != inicio; v = padre[v]) {
            int u = padre[v];
            incremento = min(incremento, capacidad[u][v] - flujo[u][v]);
        }

        // Actualiza el flujo residual
        for (int v = fin; v != inicio; v = padre[v]) {
            int u = padre[v];
            flujo[u][v] += incremento;
            flujo[v][u] -= incremento;
        }

        flujo_maximo += incremento;
    }

    cout << "\nFlujo máximo de información del nodo " << inicio
         << " (Colonia " << char('A' + inicio) << ") al nodo " << fin
         << " (Colonia " << char('A' + fin) << "): " << flujo_maximo << endl;
   
}

