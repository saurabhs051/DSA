/*
 * 1. Tarjan Algorithm - Variant 3 (Articulation Point) ( Original one for finding strongly connected components uses stack as well)
 * 2. Algorithm :
 *    2.1  -> Part 1 : Assign ID to each node on first visit
 *    2.2  -> Part 2 : Visit neighbours (case 1 : Not visited, visit it and use its low[neighbour] to minimize self low link low[node], case 2 if already visited & not my parent, it's a back edge (cycle), update low link to the target of back edge)
 *    2.3  -> Part 3 : If I'm  a root node with 2 or more unconnected children(i.e. starting from 1 children in dfs doesn't visit the other one) , that means it is connecting the 2 disconnected subtrees, so, it is an Articulation point (Single point of Failure)
 *    2.4  -> Part 4 : If I'm not the root, I'm some middle node - If the neighbour didn't bring a *lower* low key, that means its cycle is somewhere in front of me or I'm the root of the cycle, hence, I'm the joining node, I'm becomes Articulation point (Single point of Failure)
 *    2.5  -> Part 5 (Not applicable) : Unlike in actual Tarjan SCC algorithm, we do not pop from Stack in step 4 to get actual SCC components)
 * 3. Time Complexity : 
 *    3.1  -> Total : O(V+E) (1 DFS)
 */
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj;

    void DFS(int u, vector<bool>& visited, vector<int>& disc,
             vector<int>& low, vector<int>& parent, set<int>& ap, int& time) {
        visited[u] = true;
        disc[u] = low[u] = ++time;
        int children = 0;

        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                DFS(v, visited, disc, low, parent, ap, time);

                low[u] = min(low[u], low[v]);

                // u is an articulation point in following cases:
                // 1. u is root of DFS tree and has two or more children.
                if (parent[u] == -1 && children > 1)
                    ap.insert(u);

                // 2. If u is not root and low value of one of its child
                // is more than discovery value of u.
                if (parent[u] != -1 && low[v] >= disc[u])
                    ap.insert(u);
            }
            else if (v != parent[u]) {
                // Update low value of u for back edge
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    void findArticulationPoints() {
        vector<bool> visited(V, false);
        vector<int> disc(V, -1), low(V, -1), parent(V, -1);
        set<int> ap; // store articulation points
        int time = 0;

        for (int i = 0; i < V; ++i)
            if (!visited[i])
                DFS(i, visited, disc, low, parent, ap, time);

        cout << "Articulation points:\n";
        for (int point : ap)
            cout << point << " ";
        cout << endl;
    }
};

int main() {
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    g.findArticulationPoints();

    return 0;
}
