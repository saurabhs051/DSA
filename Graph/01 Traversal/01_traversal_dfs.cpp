class Solution {
	/* 
    *	Traversal of Directed/Undirected graph : DFS
    *	1. Traverse from each source node (Handling of disjoint graph (directed/undirected) and Forked directed graph)
	*		1.1	Handles traversing all disconnected components in disjoint graphs
 	*		1.2	Handles visiting all sources in Forked directed graphs
    *	2. Just don't visit already visited node. (Handling of Cycle and Undirected 2-way edges)
	*		2.1 	Prevents endless loop in case of cycle (directed/undirected graph)
 	*		2.2 	Prevents back traversal of edges in undirected graph
  	*		2.3 	Prevents revisiting already visited node/path in case of Forked directed graph (multiple src pointing to same destination)
    */
    void dfs(vector<vector<int>>& adj, int src, vector<bool>& visited, vector<int>& result)
    {
		// Stopping base case
        if (visited[src])
            return;
        
        // Visit
        visited[src] = true;
        result.push_back(src);
        for (auto& neighbour : adj[src])
            dfs(adj, neighbour, visited, result);
    }
  public:
    // Traverse UNDIRECTED / DIRECTED graph
    vector<int> dfs(vector<vector<int>>& adj) {
        int V = adj.size();
		if (!V)
			return {};
		vector<int> result;
        vector<bool> visited(V, false);
		// Traverse from each source node
        for (int src = 0; src < V; ++src)
            dfs(adj, src, visited, result);
        return result;
    }
};
