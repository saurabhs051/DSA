class Solution {
    /* 
    *	Cycle detection in Undirected graph : DFS
    *	1. A node should not be already visited (unless it is the immediate parent of current node)
    *	2. Try from each source node, to tackle case of disjoint graph
    *	3. Return early, as soon as cycle found
    */
    bool isCycle(unordered_map<int, vector<int>>& adj, int src, int parent, vector<bool>& visited)
    {
        if (!visited[src])
        {
            visited[src] = true;
            for (auto& neighbour :adj[src])
            {
                if (!visited[neighbour])
                {
                    if (isCycle(adj, neighbour, src, visited))
                        return true;
                }
                else
                {
					// Visited neighbour which is not parent, i.e. cycle exists
                    if (neighbour != parent)
                        return true;
                }
            }
        }
        return false;
    }
  public:
    bool isCycle(int V, vector<vector<int>>& edges) {
        if (!edges.size())
            return false;
        // Create adjacency list
        unordered_map<int, vector<int>> adj;
        for (auto& edge : edges)
        {
            // undirected graph, push both ways
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        // Find cycle
        vector<bool> visited(V, 0);
        for (int src = 0; src < V; ++src)
        {
            if (isCycle(adj, src, -1, visited))
                return true;
        }
        return false;
    }
};
