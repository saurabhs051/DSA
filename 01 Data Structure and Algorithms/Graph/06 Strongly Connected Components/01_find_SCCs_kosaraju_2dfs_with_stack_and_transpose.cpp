class Solution {
/*
 * 1. Kosaraju Algorithm : Find strongly connected components
 * 2. Algorithm :
 *    2.1  -> 1st DFS to collect elements in stack (last to first)
 *    2.2  -> Transpose the graph (Reverse all edges).
 *    2.3  -> Then 2nd DFS to visit elements in Transpose(Reversed) graph in order as present in stack. Elements visited in single iteration are all part of same SCC.
 * 3. Time Complexity : 
 *    3.1  -> O(V+E) :  1st DFS
 *    3.2  -> O(E)   :  Reverse all edges (Transpose Graph)
 *    3.3  -> O(V+E) :  2nd DFS
 *    3.4  -> Total : O(V+E)
 */
    // Collect elements in stack in order of finish time
    void dfs1(vector<vector<int>>& adj, int node, vector<bool>& visited, stack<int>& st) {
        if (visited[node])
            return;
        // Visit
        visited[node] = true;
        for (auto& next : adj[node]) {
            if (!visited[next])
                dfs1(adj, next, visited, st);
        }
        st.push(node); // Collect node in stack - after visiting all children
    }

    // Visit all reachable elements - part of same SCC
    void dfs2(vector<vector<int>>& transpose, int node, vector<bool>& visited) {
        if (visited[node])
            return;
        // Visit
        visited[node] = true;
        for (auto& next : transpose[node]) {
            if (!visited[next])
                dfs2(transpose, next, visited);
        }
    }

public:
    int kosaraju(vector<vector<int>>& adj) {
        int V = adj.size();
        vector<bool> visited(V, false);
        stack<int> st;

        // Step 1: First DFS to fill elements in stack by finish times(i.e. last to first)
        for (int i = 0; i < V; ++i) {
            if (!visited[i])
                dfs1(adj, i, visited, st);
        }

        // Step 2: Transpose the graph (Reverse the edges)
        vector<vector<int>> transpose(V);
        for (int i = 0; i < V; ++i) {
            for (int nei : adj[i])
                transpose[nei].push_back(i);
        }

        // Step 3: Second DFS based on finishing time (elements in stack)
        fill(visited.begin(), visited.end(), false); //Reset visited array to reuse
        int components = 0;
        while (!st.empty()) {
            int node = st.top(); st.pop();
            if (!visited[node]) {
                ++components;
                dfs2(transpose, node, visited);
            }
        }

        return components;
    }
};
