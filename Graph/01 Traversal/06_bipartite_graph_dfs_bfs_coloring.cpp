
/* 
 * Bipartite Graph : Adjacent nodes have different colors (belong to different set)
 * 1. Traversal : Can do with BFS / DFS
 * 2. Graph can be disjoint : Start from each unvisited source node
 * 3. Details :
 *      3.1 BFS : Color during adding to queue(i.e. while visiting)
 * 4. Time complexity = O(V + E) - traversal
 */
class Solution {
    bool bfs_coloring(vector<vector<int>>& graph, int src, vector<int>& visited)
    {
        queue<int> q;
        q.push(src);
        visited[src] = 0; // Start with '0' colour
        while (q.size())
        {
            int curNode = q.front(); q.pop();
            for (auto& neighbour : graph[curNode])
            {
                if (visited[neighbour] == -1)   // unvisited
                {
                    visited[neighbour] = !visited[curNode]; // apply opposite colour
                    q.push(neighbour);
                }
                else   // already visited / colored node
                {
                    if (visited[neighbour] == visited[curNode]) // Adjacent nodes have same color
                        return false;
                }
            }
        }
        return true;
    }

    bool dfs_coloring(vector<vector<int>>& graph, int src, vector<int>& visited, int color)
    {
        if (visited[src] == -1) // unvisited
        {
            visited[src] = color;                  // Color it with given color
            for (auto& neighbour : graph[src])     // Color neighbours
            {
                if (!dfs_coloring(graph, neighbour, visited, !color))  // Early return if not possoble
                    return false;
            }
        }
        else    // Already visited / coloured
        {
            if (visited[src] != color)  // Color different from expected, not bipartite
                return false;
        }
        return true;
    }

public:
    bool isBipartite(vector<vector<int>>& graph) {
        int V = graph.size();
        vector<int> visited(V, -1); // Used for visited tracking as well as colouring of nodes

        // Disconnected Graph : Start from each yet unvisited source node
        for (int src = 0; src < V; ++src)
        {
            if (visited[src] == -1)
            {
                //if (!bfs_coloring(graph, src, visited))
                if (!dfs_coloring(graph, src, visited, 0))
                    return false;
            }
        }
        return true;
    }
};
