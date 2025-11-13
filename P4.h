#ifndef P4_H
#define P4_H

#include <vector>
#include <utility>
#include <iostream>
#include <climits>

using namespace std;

int nearestCentralIndex(const vector<pair<int,int>>& coords, int x, int y) {
    if (coords.empty()) {
        return -1;
    }

    long long bestDist2 = LLONG_MAX;
    int bestIndex = 0;

    for (int i = 0; i < (int)coords.size(); ++i) {
        long long dx = x - coords[i].first;
        long long dy = y - coords[i].second;
        long long dist2 = dx * dx + dy * dy;

        if (dist2 < bestDist2) {
            bestDist2 = dist2;
            bestIndex = i;
        }
    }

    return bestIndex;
}

void nearestCentralInteractive(const vector<pair<int,int>>& coords) {
    if (coords.empty()) {
        cerr << "No hay centrales registradas.\n";
        return;
    }

    int x, y;
    cout << "\n4. Central mas cercana para una nueva contratacion\n";
    cout << "   Ingrese las coordenadas de la nueva casa (x y): ";
    
    if (!(cin >> x >> y)) {
        cerr << "Entrada invalida.\n";
        return;
    }

    int idx = nearestCentralIndex(coords, x, y);
    
    if (idx == -1) {
        cerr << "No se pudo determinar la central mas cercana.\n";
        return;
    }

    cout << "   Casa nueva en: (" << x << ", " << y << ")\n";
    cout << "   Central mas cercana: #" << (idx + 1)
         << " en (" << coords[idx].first
         << ", " << coords[idx].second << ")\n";
}

#endif // P4_H
