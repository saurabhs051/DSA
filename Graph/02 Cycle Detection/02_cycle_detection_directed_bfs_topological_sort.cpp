class Solution {
	/* 
    *	Cycle detection in Directed graph : BFS (Multi-point)
    *	1. Topological Sort (Kahn's algo) : Cycle if couldn't visit all nodes  
    *	2. Tracking visited nodes won't do as a visited node can be encountered again even without cycle
    *	3. Visited vector is only for tracking visited nodes. For preventing infinite loop in traversal, indegree == 0 check is enough.
    * 	4. Notes :
    *		4.1 If edges are gives rather than adjacency list, don't do `if(!edges.size()) return;` as there can we vertices without edges.
    */
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(vector<vector<int>> &adj) {
        // Create indegree vector
        int V = adj.size();
        vector<int> indegree(V, 0);
        for (int src = 0; src < V; ++src)
        {
            for (auto& dest : adj[src])
                ++indegree[dest];
        }
        
        // Add 0 indegree nodes to queue
        queue<int> q;
        vector<int> visited(V, false);
        for (int node = 0; node < V; ++node)
        {
            if (indegree[node] == 0)
            {
                q.push(node);
                visited[node] = true; // Mark visited during insertion in queue
            }
        }
        
        // Traverse BFS
        while (q.size())
        {
            int curNode = q.front();
            q.pop();
            for (auto& neighbour : adj[curNode])
            {
                --indegree[neighbour];
                // Visited check not required
                // Can visit only once, since indegree == 0 only once
                if (indegree[neighbour] == 0)
                {
                    q.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }
        
        // If there is an unvisited node, cycle exists
        for (auto& status : visited)
        {
            if (status == 0)
                return true;
        }
        
        return false;
    }
};
