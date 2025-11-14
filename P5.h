#ifndef P5_H
#define P5_H

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>

using namespace std;

// This function finds a network that balances total distance cost and max flow potential.
// It uses a weighted sum approach where 'alpha' controls the trade-off.
// alpha = 1.0 prioritizes minimizing distance.
// alpha = 0.0 prioritizes maximizing flow capacity.
void findParetoOptimalSolution(double alpha, const vector<vector<int>>& distanceMatrix, const vector<vector<int>>& flowMatrix, int n, ofstream& plotFile) {
    if (alpha < 0.0 || alpha > 1.0) {
        cerr << "Alpha must be between 0.0 and 1.0" << endl;
        return;
    }

    // 1. Normalize matrices to make values comparable (0 to 1 range)
    double max_dist = 0;
    double max_flow = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (distanceMatrix[i][j] > max_dist) max_dist = distanceMatrix[i][j];
            if (flowMatrix[i][j] > max_flow) max_flow = flowMatrix[i][j];
        }
    }

    vector<vector<double>> combined_cost(n, vector<double>(n, 1e9));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (distanceMatrix[i][j] > 0) { // Edge exists
                double norm_dist = (max_dist > 0) ? (double)distanceMatrix[i][j] / max_dist : 0;
                double norm_flow = (max_flow > 0) ? (double)flowMatrix[i][j] / max_flow : 0;
                
                // Cost function: lower is better.
                // We want to minimize distance (cost) and maximize flow (benefit).
                // So we use (1 - norm_flow) as the flow-related cost.
                combined_cost[i][j] = alpha * norm_dist + (1.0 - alpha) * (1.0 - norm_flow);
            }
        }
    }

    // 2. Run Prim's MST algorithm on the combined cost matrix to find the optimal network
    vector<int> parent(n);
    vector<double> key(n, 1e9);
    vector<bool> mstSet(n, false);

    key[0] = 0.0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; ++count) {
        double min_val = 1e9;
        int u = -1;
        for (int v_idx = 0; v_idx < n; ++v_idx) {
            if (!mstSet[v_idx] && key[v_idx] < min_val) {
                min_val = key[v_idx];
                u = v_idx;
            }
        }
        if (u == -1) {
            cerr << "Error: Could not find a spanning tree. The graph may be disconnected." << endl;
            return;
        }
        mstSet[u] = true;

        for (int v = 0; v < n; ++v) {
            if (combined_cost[u][v] < key[v] && !mstSet[v]) {
                parent[v] = u;
                key[v] = combined_cost[u][v];
            }
        }
    }

    // 3. Calculate and print the objective values for the resulting network
    double total_dist = 0;
    double total_flow_capacity = 0;
    
    cout << "\n--- Multi-Objective Solution (alpha = " << alpha << ") ---\n";
    cout << "   Network Edges:\n";
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            cout << "     (" << char(parent[i] + 65) << ", " << char(i + 65) << ")\n";
            total_dist += distanceMatrix[parent[i]][i];
            total_flow_capacity += flowMatrix[parent[i]][i];
        }
    }
    cout << "   Objective 1 - Total Distance: " << total_dist << endl;
    cout << "   Objective 2 - Total Flow Capacity: " << total_flow_capacity << endl;
    cout << "-------------------------------------------\n";

    // Write to plot file
    if (plotFile.is_open()) {
        plotFile << alpha << "," << total_dist << "," << total_flow_capacity << endl;
    }
}

#endif // P5_H
