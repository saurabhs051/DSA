/* Single source shortest path - Shortest path from one node to all other nodes
 * Negative weights allowed. Hence, Bellman Ford
 * Algorithm : Iterate V-1 times. Each time optimize distance for all the edges
 * Time complexity : O(V*E) : V-1 times we processed all edges
 */
class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        vector<int> dist(V, 1e8);
        dist[src] = 0;

        // Relax all edges V-1 times
        for (int i = 0; i < V - 1; ++i) {
            for (auto& edge : edges) {
                int u = edge[0], v = edge[1], wt = edge[2];
                // only update with help from reachable nodes
                if (dist[u] != 1e8 && dist[v] > dist[u] + wt) { 
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // Check for negative weight cycle
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], wt = edge[2];
            if (dist[u] != 1e8 && dist[v] > dist[u] + wt) {
                return {-1};
            }
        }
        return dist;
    }
};
