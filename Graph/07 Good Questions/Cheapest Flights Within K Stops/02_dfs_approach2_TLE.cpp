class Solution {
    /*
    * DFS Approach 2 (Better - reduce paths) : Gives right answer but TLE (Time Limit Exceeded) on large graphs because it explores almost 'all paths'
    */
    void getMinPrice(unordered_map<int, vector<pair<int, int>>> &adj, int src, int dest, int stopsAllowed, vector<int>& visited, int& minPrice, int curPrice)
    {
        if (src == dest)
        {
            minPrice = min(minPrice, curPrice);
            return;
        }
        
        if (curPrice > minPrice)
            return; //Path prunning - Reduce paths
        
        if (!visited[src] && stopsAllowed >= 0)
        {
            visited[src] = 1;
            for (auto& neighbour : adj[src])
                getMinPrice(adj, neighbour.first, dest, stopsAllowed - 1, visited, minPrice, curPrice + neighbour.second);
            
            visited[src] = 0;   // Mark unvisited, we want to go through it again, maybe other path will be smaller
        }
    }
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int stopsAllowed) {
        if (stopsAllowed < 0)      // Input validation
            return -1;
        if (src == dst) // Already at destination
            return 0;
        // Create adjacency list wth weights
        unordered_map<int, vector<pair<int, int>>> adj;
        for (const auto& flight : flights)
        {
            int source = flight[0], destination = flight[1], cost = flight[2];
            adj[source].push_back({destination, cost});
        }
        vector<int> visited(n, 0);
        int minPrice = INT_MAX;
        getMinPrice(adj, src, dst, stopsAllowed, visited, minPrice, 0);
        if (minPrice == INT_MAX)
            return -1;
        return minPrice;
    }
};
