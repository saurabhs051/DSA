class Solution {
    /* 
    *	Cycle detection in Directed graph : DFS
    *	1. Node should not be in current path (i.e. in current Recursion Stack)
    *	2. Try from each source node, to tackle case of disjoint graph
    *	3. No need to visit already visited node (hence, maintain a visited vector, separate from recusion stack)
    */
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
        recStack[src] = false;  // Clear from recursion stack
        return false;
    }

  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(vector<vector<int>> &adj) {
        int A = adj.size();
        vector<bool> visited(A, false);
        vector<bool> recStack(A, false);
	// Check from each source node
        for (int i = 0; i < A; ++i)
        {
            if (getCycle(adj, i, visited, recStack))
                return true;	// Early return
        }
        return false;
    }
};
