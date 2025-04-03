class Solution {
    int getCycle(vector<vector<int>>& adj, int src, vector<bool> &visited, vector<bool> &recStack)
    {
        if (recStack[src]) // Answer check first
            return true;
            
        if (visited[src])
            return false;
            
        // Visit
        visited[src] = true;
        recStack[src] = true;
        for (auto& neighbour : adj[src])
        {
            if (getCycle(adj, neighbour, visited, recStack))
                return true;
        }
        recStack[src] = false;
        return false;
    }

  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(vector<vector<int>> &adj) {
        int A = adj.size();
        vector<bool> visited(A, false);
        vector<bool> recStack(A, false);
        for (int i = 0; i < A; ++i)
        {
            if (getCycle(adj, i, visited, recStack))
                return true;
        }
        return false;
    }
};
