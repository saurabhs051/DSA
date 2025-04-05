class Solution {
	/*
	* We're at {0,0} cell, find minimum path to reach last cell {m-1, n-1} cell. Can only go through cells marked as 0.
	* Pattern :
	*	1.	Minimum step asked : Hence BFS
	*	2.	Level Order BFS, since all nodes at a given level will have same distance from source.
	* 	3. 	Details
	*		3.1	Mark visited to avoid cycle (We never unmark in BFS)
 	*		3.2 Step count increases AFTER moving (i.e. after processing all neighbour nodes)
	*/

    bool isValid(int m, int n, int x, int y)
    {
        return (x >= 0 && x < m && y >= 0 && y < n);
    }

    // Get all possible directions
    // static : initialize once, const& : return const reference, avoid copy
    static const vector<pair<int, int>>& getDirections()
    {
        static const vector<pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
            {0, 1}, {1, -1}, {1, 0}, {1, 1}
        };
        return directions;
    }

public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size();
        if (!m)
            return -1;
        int n = grid[0].size();
        if (grid[0][0] == 1 || grid[m-1][n-1] == 1) // Not possible to reach
            return -1;
        vector<vector<bool>> visited(m, vector<bool>(n, 0));
        queue<pair<int, int>> q;
        q.push({0, 0});
        int distance = 1; // Origin cell also included in answer
        while (q.size())
        {
            int size = q.size();
            while (size--)	// Level order BFS
            {
                auto curNode = q.front();
                q.pop();
                if (curNode.first == m-1 && curNode.second == n-1) // Answer condition : Process for answer during popping from queue
                    return distance;
                for (auto& dir : getDirections())
                {
                    int nx = curNode.first + dir.first;
                    int ny = curNode.second + dir.second;
                    if (isValid(m, n, nx, ny) && grid[nx][ny] == 0 && !visited[nx][ny]) // Stopping/Invalid conditions
                    {
                        q.push({nx, ny});
                        visited[nx][ny] = true;
                    }
                }
            }
            ++distance;
        }
        return -1; //Can't reach
    }
};
