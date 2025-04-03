class Solution {
	/* 
 	*	Traversal of Directed/Undirected graph : BFS
 	*	1. Traverse from each source node
	*		1.1	Handles traversing all disconnected components in DISJOINT graphs (directed / undirected)
 	*		1.2	Handles visiting all sources in FORKED DIRECTED graphs 
    *	2. Don't visit already visited node.
	*		1.1 Prevents endless loop in case of cycle (directed/undirected graph)
 	*		1.2	Prevents back traversal of edges in undirected graph
  	*		1.3 Prevents revisiting already visited node/path in case of Forked directed graph (multiple src pointing to same destination)
    */
  public:
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfs(vector<vector<int>> &adj) {
        int V = adj.size();
        if (!V)
            return {};
        vector<int> result;
        queue<int> q;
        vector<bool> visited(V, false);
        // For disjoint graph (directed / undirected)
        // For Forked directed graph
        for (int src = 0; src < V; ++src)
        {
            if(visited[src])
                continue;
            // Add source node to queue
            q.push(src);
            visited[src] = true; // Add to visited during insertion to queue
            while (q.size())
            {
                int curNode = q.front();
                q.pop();
                result.push_back(curNode); // Add to result during pop
                for (auto& neighbour : adj[curNode])
                {
                    if (!visited[neighbour])  // Prevent cycle
                    {
                        q.push(neighbour);
                        visited[neighbour] = true;
                    }
                }
            }
        }
        return result;
    }
};
