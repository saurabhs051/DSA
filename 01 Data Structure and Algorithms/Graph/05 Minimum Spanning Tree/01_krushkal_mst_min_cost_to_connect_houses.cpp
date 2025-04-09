
class Solution {
/* 
 * 1. Min cost to connect all the houses (MST) : n-1 edges
 * 2. Krushkal - Edge based greedy algorithm : just choose N-1 min weight edges (unless they are not forming a cycle)
 * 3. Time Complexity : 
 *      3.1 Sort E edges : ElogE (This is dense graph (all to all). Hence, O(n² log n²) = O(n² log n) --this is right!
 * 4. Space complexity : Edge list: O(n²)   ,   Disjoint set: O(n)
 */
    int findParent(vector<int>& parent, int node)
    {
        if (parent[node] == node)
            return node;
        return parent[node] = findParent(parent, parent[node]);
    }
    void unite(vector<int>& parent, vector<int>& rank, int src, int dest)
    {
        int parent1 = findParent(parent, src);
        int parent2 = findParent(parent, dest);
        if (parent1 != parent2)
        {
            if (rank[parent1] < rank[parent2])
                parent[parent1] = parent2;
            else if (rank[parent2] < rank[parent1])
                parent[parent2] = parent1;
            else
            {
                parent[parent2] = parent1;
                ++rank[parent1];
            }
        }
    }
    bool createsCycle(const vector<int> road, vector<int>& parent, vector<int>& rank)
    {
        int src = road[0], dest = road[1];
        int parent1 = findParent(parent, src);
        int parent2 = findParent(parent, dest);
        if (parent1 == parent2) //already same parent
            return true;
        unite(parent, rank, src, dest);
        return false;
    }
  public:
    int minCost(vector<vector<int>>& houses) {
        // adjacency matrix
        int n = houses.size();
        if (!n)
            return 0;
        vector<vector<int>> roads;
        for (int i = 0; i < n - 1; ++i) 
        {
            for (int j = 1; j < n; ++j) //if i,j processed, don't process j,i
            {
                int distance = abs(houses[i][0] - houses[j][0]) + abs(houses[i][1] - houses[j][1]);
                roads.push_back({i, j, distance});
            }
        }

      // Sort edges by weight
        std::sort(roads.begin(), roads.end(), [](const vector<int>& road1, const vector<int>& road2){
            return road1[2] < road2[2];
        });
        
        int minCost = 0;
        vector<int> parent(n);
        vector<int> rank(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
        // Try to take n-1 min cost edges, as long as it doesn't form cycle
        --n;     // n-1 edges
        for (auto& road : roads)
        {
            int src = road[0], dest = road[1], distance = road[2];
            if (!createsCycle(road, parent, rank))
            {
                minCost += distance;
                --n;
            }
            if (!n)
                break;
        }
        return minCost;
        
    }
};
