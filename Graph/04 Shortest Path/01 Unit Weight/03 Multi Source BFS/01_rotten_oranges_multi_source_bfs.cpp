class Solution {
/*
 * Rotten oranges :
 * Given a matrix mat[][] of dimension n * m where each cell in the matrix can have values 0, 1 or 2 which has the following meaning:
 * 0 : Empty cell
 * 1 : Cell have fresh oranges
 * 2 : Cell have rotten oranges
 * Can rot (up, down, left and right) in a unit time.
 * Return the minimum time to rot all the fresh oranges. If not possible returns -1.
 *
 * Spreading Behaviour / Minimum time asked : BFS | Count the time : Level Order | Execution (Rotting) starts from multiple points simultaneously : Multi Source BFS
 */
    bool isValid(int m, int n, int x, int y)
    {
        return (x >= 0 && x < m && y >= 0 && y < n);
    }
  public:
    int orangesRotting(vector<vector<int>>& mat) {
        int m = mat.size();
        if (!m)
            return 0;
        int n = mat[0].size();
        
        queue<pair<int, int>> q;
        int freshOranges = 0;   // Count fresh oranges, since there is a change that we fail to rot all oranges(when surrounded by empty cell)
        for (int i = 0; i < m ; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (mat[i][j] == 2) // rotten
                    q.push({i, j});
                else if (mat[i][j] == 1) // fresh
                    ++freshOranges;
            }
        }
        
        int minTime = 0;
        vector<pair<int, int>> dirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        while (q.size())
        {
            int k = q.size();   // Level order, since we need to count time
            while (k--)
            {
                auto curNode = q.front();
                q.pop();
                for (auto& dir : dirs)
                {
                    int x = curNode.first + dir.first;
                    int y = curNode.second + dir.second;
                    if (isValid(m, n, x, y) && mat[x][y] == 1 /*fresh*/)
                    {
                        mat[x][y] = 2;  // mark rotten
                        --freshOranges;
                        q.push({x, y});
                    }
                }
            }
            ++minTime;
        }
        if (freshOranges == 0)  // Either we rot all orange, or maybe there was nothing to rot
            return minTime == 0 ? minTime : minTime - 1; // Mind this
        return -1;  // Couldn't rot all oranges
    }
};
