class Solution {
/*
 * 1. Tarjan Algorithm - Variant 2 ( Original one for finding strongly connected components uses stack as well)
 * 2. Algorithm :
 *    2.1  -> Part 1 : Assign ID to each node on first visit
 *    2.2  -> Part 2 : Visit neighbours (case 1 : Not visited, visit it and use its low[neighbour] to minimize self low link low[node], case 2 if already visited, it's a back edge (cycle), update low link to the target of back edge)
 *    2.3  -> Part 3 : If the neighbour didn't bring a lower or equal low link, that means its cycle is somewhere in front of me, not encompasing me (hence, our edge becomes Bridge Edge (Single point of Failure)
 *    2.4  -> Part 4 (Not applicable) : Unlike in actual Tarjan SCC algorithm, we do not pop from Stack in step 4 to get actual SCC components)
 * 3. Time Complexity : 
 *    3.1  -> Total : O(V+E) (1 DFS)
 */
    void dfs(unordered_map<int, vector<int>>& adj, int node, int parent,
             vector<int>& id, vector<int>& low, int& time,
             vector<vector<int>>& bridges) {
        // Mark the current node with the discovery time and low-link value
        id[node] = low[node] = time++;

        // Explore all adjacent nodes
        for (int nei : adj[node]) {
            if (id[nei] == -1) {  // Unvisited
                // If neighbor not visited, recurse
                dfs(adj, nei, node, id, low, time, bridges);
                low[node] = min(low[node], low[nei]);  // update my low-link based on neighbour. it might've found a lower low-link (back edge)

                // Check if this is a bridge
                if (low[nei] > id[node]) {    // Beware : id[node], not low[node]
                    bridges.push_back({node, nei});
                }
            } else if (nei != parent) {  // Already visited, i.e. a Back Edge found
                // Update low-link value for back edge
                low[node] = min(low[node], id[nei]); // id[nei], not low[neil], we track where exactly the back-edge landed
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Build the adjacency list
        unordered_map<int, vector<int>> adj;
        for (const auto& edge : connections) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]); // Undirected graph
        }

        // Initialize ids and low-link values
        vector<int> id(n, -1), low(n, -1);
        vector<vector<int>> bridges;
        int time = 0;

        // Run DFS from each unvisited node
        for (int i = 0; i < n; ++i) {
            if (id[i] == -1) {
                dfs(adj, i, -1, id, low, time, bridges);
            }
        }

        return bridges;
    }
};
