class Solution {
    /* 
    *	Cycle detection in Undirected graph : BFS
    *	1. A node should not be already visited (unless it is the immediate parent of current node)
    *	2. Try from each source node, to tackle case of disjoint graph
    *	3. Return early, as soon as cycle found
	*	4. To track parent, push {node, parent} pair in queue
    */
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
        
        queue<pair<int, int>> q;
        vector<bool> visited(V, 0);
        // Start from each source node - tackle disjoint graphs case
        for (int src = 0; src < V; ++src)
        {
            if (!visited[src])
            {
                q.push({src, -1});
                visited[src] = true;
                // Traverse
                while (q.size())
                {
                    auto curNode = q.front();
                    q.pop();
                    for (auto& neighbour : adj[curNode.first])
                    {
                        if (!visited[neighbour])
                        {
                            q.push({neighbour, curNode.first});
                            visited[neighbour] = true;
                        }
                        else
                        {
                            // If neighbour has already been visited,
                            // unless it is my parent, a cycle exists
                            int parent = curNode.second;
                            if (neighbour != parent)
                                return true;
                        }
                    }
                }
            }
        }
        return false;
    }
};
