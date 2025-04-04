class Solution {
	/*
	* Shortest Path from Node 1 to Node n
	* Pattern :
	*	1.	Minimum step asked : Hence BFS
 	*	2.  Weighted graph (positive weights) : Dijksta BFS (using Min Heap)
	* 	2. 	Details
	*		3.1	Parent vector for shortest path tracking
 	*		3.2 No need for visited vector to prevent cycle, distance vector won't allow it. Won't revisit a node until we get a smaller distance for it.
	*/

    struct NodeData
    {
        int node;
        int distance;
    };
  public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        // undirected graph, weighted : 
        //  - Double sided adjacency list with {node,weight} values
        unordered_map<int, vector<NodeData>> adj;
        for (auto& edge : edges)
        {
            int src = edge[0], dest = edge[1], weight = edge[2];
            adj[src].push_back({dest, weight});
            adj[dest].push_back({src, weight});
        }
        
        // Shortest path (weighted graph) : BFS (Dijkstra i.e. minHeap)
        vector<int> distance(n + 1, INT_MAX); 				//1-based indexing
        priority_queue<int, vector<int>, greater<int>> q;   // min-heap
        distance[1] = 0;    								// source node
        q.push(1);          
        
        vector<int> parent(n + 1, -1);  // For shortest path tracking
        while (q.size())
        {
            int curNode = q.top();
            q.pop();
            for (auto& neighbour : adj[curNode])
            {
                if (distance[neighbour.node] > distance[curNode] + neighbour.distance)
                {
                    distance[neighbour.node] = distance[curNode] + neighbour.distance;
                    q.push(neighbour.node);
                    parent[neighbour.node] = curNode;
                }
            }
        }
        
        vector<int> result;
        if (distance[n] == INT_MAX) // unreachable
            return {-1};

		// we need to get vector = {size of shortest path, path from node 1 to n}
        int node = n;
        while (node != -1)
        {
            result.push_back(node);
            node = parent[node];
        }
        result.push_back(distance[n]);
        std::reverse(result.begin(), result.end());
        return result;
    }
};
