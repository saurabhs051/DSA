class Solution {
	/*
	* Given starting cell {x,y} as source, Change colour of all cells in the grid whose color is same as source cell to given color.
	* Pattern :
	*	1.	Spreading behaviour : Hence BFS
	*	2.	Nothing asked, just need to do some operation/traversal : hence, standard BFS
	* 	3. 	Details
	*		3.1	Using change in original matrix to track visited cells.
	*/
    bool isValid (int m, int n, int x, int y)
    {
        return (x >= 0 && x < m && y >= 0 && y < n);
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int m = image.size();
        if (!m)
            return image;
        int n = image[0].size();
        queue<pair<int, int>> q;
        // No need of visited, will track via changed color of image grid
        int sourceColor = image[sr][sc];
        if (sourceColor == color)
            return image; // Nothing to do // source color same as required color
        
        q.push({sr, sc});
        image[sr][sc] = color; // mark visited : we are using color change for visited tracking
        static const vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };
        while (q.size())
        {
            auto curCell = q.front();
            q.pop();
            // Move sideways
            for (auto& dir : directions)
            {
                int nx = curCell.first + dir.first;
                int ny = curCell.second + dir.second;
                if (isValid(m, n, nx, ny) && image[nx][ny] == sourceColor)
                {
                    q.push({nx, ny});
                    image[nx][ny] = color; // mark visited
                }
            }
        }
        return image;
    }
};
