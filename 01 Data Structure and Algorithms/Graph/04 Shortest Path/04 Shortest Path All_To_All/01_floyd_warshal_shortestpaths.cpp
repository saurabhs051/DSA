/*
 * Floyd Warshall : Shortest path from all nodes to all other nodes. Output : 2D matrix
 * Handles Negative cycle as well, like Bellman Ford
 * Algorithm : Considering each node as intermediate node, try to reduce distance between all other pair of nodes.
 * Time Complexity : O(V^3)
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

vector<vector<int>> floydWarshallWithCycleDetection(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> dist = graph;

    // Main Floyd-Warshall algorithm - O(V^3)
    // Take each node as intermediate node, and minimize distance between all pair of nodes
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check for negative cycles
    bool hasNegativeCycle = false;
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) {
            hasNegativeCycle = true;
            break;
        }
    }
    if (!hasNegativeCycle)
      return dist;
    return {};
}

int main() {
    int V = 4;
    vector<vector<int>> graph = {
        {0,   1,  INF, INF},
        {INF, 0,  -1, INF},
        {INF, INF, 0,  -1},
        {-1, INF, INF, 0}
    };
    vector<vector<int>> dist = floydWarshallWithCycleDetection(graph);
    if (dist.empty()) {
        cout << "Graph contains a negative weight cycle.\n";
    } else {
        cout << "No negative weight cycle detected.\n";
        cout << "Shortest distances between all pairs of vertices:\n";
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][j] == INF)
                    cout << "Not Reachable" << "\t";
                else
                    cout << dist[i][j] << "\t";
            }
            cout << endl;
        }
    }
    return 0;
}

