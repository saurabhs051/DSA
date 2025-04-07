class Solution {
	/* 
 	* 	Given a grid consisting of 'W's (Water) and 'L's (Land). Find the number of islands. Adjacent land comprises of all 8 directions.
    *	Traversal of Matrix i.e. Undirected graph : DFS / BFS
    *	1. Traverse from each source node
	*		1.1		Handles traversing all disconnected components (different islands)
    *	2. Just don't visit already visited node.
	*		2.1 	Prevents endless loop in case of cycle
 	*		2.2 	Prevents back traversal of edges.
    */
    bool isValid(int m, int n, int row, int col)
    {
        return (row >= 0 && row < m && col >= 0 && col < n);
    }
    
    static const vector<pair<int, int>>& getDirections()
    {
        static const vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {1, 1}, {1, -1}, {-1, 1}
        };
        return directions;
    }
    
    void visit_dfs(vector<vector<char>>& grid, int row, int col, vector<vector<bool>>& visited)
    {
        int m = grid.size();
        int n = grid[0].size();
        if (isValid(m, n, row, col) && grid[row][col] == 'L' && !visited[row][col])
        {
            visited[row][col] = true;
            for (auto& dir : getDirections())
            {
                int nx = row + dir.first;
                int ny = col + dir.second;
                visit_dfs(grid, nx, ny, visited);
            }
        }
    }
    
    void visit_bfs(vector<vector<char>>& grid, int row, int col, vector<vector<bool>>& visited)
    {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        q.push({row, col}); 		// Add source
        visited[row][col] = true; 	// visit while adding to queue
        while (q.size())
        {
            auto front = q.front();
            q.pop();
            for (auto& dir : getDirections())
            {
                int nx = front.first + dir.first;
                int ny = front.second + dir.second;
                if (isValid(m, n, nx, ny) && grid[nx][ny] == 'L' && !visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
    }
    
  public:
    int countIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        if (!m)
            return 0;
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int islands = 0;
        for (int row = 0; row < m; ++row)
        {
            for (int col = 0; col < n; ++col)
            {
                if (grid[row][col] == 'L' && !visited[row][col])
                {
                    ++islands;
                    visit_dfs(grid, row, col, visited); // DFS Traversal
                    // visit_bfs(grid, row, col, visited);  // BFS Traversal
                }
            }
        }
        return islands;
    }
};
