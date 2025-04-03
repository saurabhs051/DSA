class Solution {
	/*
	* Knight is at {x,y} position, find minimum steps to reach a target {x1, y1} position.
	* Pattern :
	*	1.	Minimum step asked : Hence BFS
	*	2.	Level Order BFS, since all nodes at a given level will have same step count.
	* 	3. 	Details
	*		3.1	Mark visited to avoid cycle (We never unmark in BFS)
 	*		3.2 Step count increases AFTER moving (i.e. after processing all neighbour nodes)
	*/

    // 1-based indexing
    bool isValid(int n, int x, int y)
    {
        return (x > 0 && x <= n && y > 0 && y <= n);
    }

    // Get all possible knight movement directions
    // static : initialize once, const& : return const reference, avoid copy
    static const vector<pair<int, int>>& getDirections()
    {
        static const vector<pair<int, int>> directions = {
            {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
            {-1, -2}, {1, -2}, {-1, 2}, {1, 2}
        };
        return directions;
    }

  public:
    // Minimum path asked : BFS
    int minStepToReachTarget(vector<int>& knightPos, vector<int>& targetPos, int n) {
        // 1-based indexing
        vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, 0));
        queue<vector<int>> q;
        q.push(knightPos);
        visited[knightPos[0]][knightPos[1]] = 1; // mark while adding to queue
        int stepsTaken = 0;
        while (q.size())
        {
            int size = q.size();
            while (size--)  // Level order BFS, cover whole level in 1 go
            {
                auto curPos = q.front();
                q.pop();
                if (curPos[0] == targetPos[0] && curPos[1] == targetPos[1])
                    return stepsTaken;
                    
                // Move
                for (auto& dir : getDirections())
                {
                    int nx = curPos[0] + dir.first;
                    int ny = curPos[1] + dir.second;
                    if (isValid(n, nx, ny) && !visited[nx][ny])
                    {
                        q.push({nx, ny});
                        visited[nx][ny] = 1; // mark while adding to queue
                    }
                }
            }
            ++stepsTaken;
        }
        return stepsTaken;
    }
};
