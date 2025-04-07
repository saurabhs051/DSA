class Solution {
	/*
	* Shortest Path from Node 1 to Node n
	* Pattern :
	*	1.  Minimum step asked : Hence BFS
 	*	2.  Weighted graph (positive weights) : Dijksta BFS (using Min Heap)
	* 	3.  Details
	*		3.1  Parent vector for shortest path tracking
 	*		3.2  No need for visited vector to prevent cycle, distance vector won't allow it. Won't revisit a node until we get a smaller distance for it.
	*/
    struct NodeData
    {
        int node;
        int distance;
    };
    
    // Comparator for min heap
    struct Comparator{
        bool operator()(const NodeData& a, const NodeData& b)
        {
            return a.distance > b.distance; // Min heap - we write reverse condition
        }
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
        vector<int> distance(n + 1, INT_MAX); //1-based indexing
        priority_queue<NodeData, vector<NodeData>, Comparator> q;   // min-heap
        distance[1] = 0;    // source node
        q.push({1, 0});     // Have to push both, because min heap will use distance for sorting
        
        vector<int> parent(n + 1, -1);  // For shortest path tracking
        while (q.size())
        {
            auto curNode = q.top();
            q.pop();
            for (auto& neighbour : adj[curNode.node])
            {
                if (distance[neighbour.node] > distance[curNode.node] + neighbour.distance)
                {
                    distance[neighbour.node] = distance[curNode.node] + neighbour.distance;
                    q.push({neighbour.node, distance[neighbour.node]});
                    parent[neighbour.node] = curNode.node;
                }
            }
        }
        
        vector<int> result;
        if (distance[n] == INT_MAX) // unreachable
            return {-1};
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
