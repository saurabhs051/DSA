#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class TarjanSCC {
    int V; // Number of vertices
    vector<vector<int>> adj;
    vector<int> disc, low;
    vector<bool> inStack;
    stack<int> st;
    int time;

    void dfs(int u, vector<vector<int>>& result) {
        disc[u] = low[u] = time++;
        st.push(u);
        inStack[u] = true;

        for (int v : adj[u]) {
            // Unvisited
            if (disc[v] == -1) {
                dfs(v, result);
                low[u] = min(low[u], low[v]);
            }
            // Visited
            else if (inStack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        // If u is the head of an SCC (id[node] == low[node]
        if (disc[u] == low[u]) {
            vector<int> scc;
            while (st.size())
            {
                int v = st.top(); st.pop();
                inStack[v] = false;
                scc.push_back(v);
                if (v == u)
                  break;
            }
            result.push_back(scc);
        }
    }

public:
    TarjanSCC(int V) : V(V) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void findSCCs() {
        disc.assign(V, -1);
        low.assign(V, -1);
        inStack.assign(V, false);
        time = 0;

        vector<vector<int>> result;

        for (int i = 0; i < V; ++i) {
            if (disc[i] == -1) {
                dfs(i, result);
            }
        }

        // Output the SCCs
        cout << "Strongly Connected Components (Tarjan):\n";
        for (const auto& scc : result) {
            for (int node : scc)
                cout << node << " ";
            cout << "\n";
        }
    }
};

int main() {
    TarjanSCC g(7);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 1);
    g.addEdge(4, 5);
    g.addEdge(5, 6);

    g.findSCCs();
    return 0;
}
