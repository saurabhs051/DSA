class Solution {
	/* Find cycle in UNDIRECTED graph using DISJOINT SET Algorithm (Union - Find)
	 *  1. Operations : 
	 *  	1.1 FIND : Find Parent of a node (i.e. representative of th set the node belongs to)
	 *  	1.2 UNION : Unite the two Disjoint sets
	 *  2. Cycle : Exists if the two ends of an unvisited edge already belongs to the same set
	 *  3. Optimizations : 
	 *  	3.1 During Find : Find time - O(V) to O(1) : PATH COMPRESSION (Cache the root parent of a node, so that next time we don't need to up-traverse again)
	 *		3.2 During Union : Reduce height of tree to decrease Find time from O(V) to O(logV) : Union by Rank (Lesser rank becomes child of Larger rank node)
	 */

    vector<int> parent, rank;

    // Find representative/parent of the node's set
    int findParent(int node)
    {
        if(parent[node] == node)
            return node;
        // Path compression (Cache before returning, later will become find O(1), not O(V))
        return parent[node] = findParent(parent[node]); 
    }
    
    // Union : Add both nodes in same set
    void do_union(int nodeA, int nodeB)
    {
        int parentA = findParent(nodeA);
        int parentB = findParent(nodeB);
        if (parentA == parentB) //already part of same set
            return; 
         // Union by rank (smaller rank becomes child of larger rank)
         // This reduces the tree height (increased the breadth instead, helps in faster findParent())
        else if (rank[parentA] < rank[parentB])
            parent[parentA] = parentB;
        else if (rank[parentB] < rank[parentA])
            parent[parentB] = parentA;
        else
        {
            parent[parentB] = parentA;
            ++rank[parentA];
        }
    }
    
  public:
    bool isCycle(int V, vector<vector<int>>& edges) {
		// Initially, rank of every node = 0;
        rank.resize(V, 0);
        parent.resize(V);
        // Initially, all nodes are their own parents (i.e. belong to different sets)
        for (int i = 0; i < V; ++i)
            parent[i] = i;
        // Process each edge
        for (auto& edge : edges)
        {
            int parentA = findParent(edge[0]);
            int parentB = findParent(edge[1]);
            // Both nodes already belong so same set even before processing / union
            // i.e., the node has already been processed, i.e. cycle exists
            if (parentA == parentB)
                return true;
            else
                // Process / unite nodes
                do_union(edge[0], edge[1]);
        }
        return false;
    }
};
