class Solution {
/*
* Rat is at {0,0}, find all possible paths to {m-1, n-1} cell. Can't go through cell marked 0.
* Pattern :
*	1.	Positive / Answer / goal base condition
*	2.	Stopping / Negative conditions (these can be added in a if consition over visit call)
* 	3. 	Visit node, visit neighbours
*		3.1	Mark visited to avoid cycle, mark unvisited/free after visiting to allow revisiting through another path
*/
private:
    // Check if a position is valid within the grid
    bool isValid(int m, int n, int x, int y) const {
        return (x >= 0 && x < m && y >= 0 && y < n);
    }

    // Returns possible movement directions (Up, Down, Left, Right)
    // static : initialized only once
    // const& : avoid making copies, return const reference
    static const vector<tuple<int, int, char>>& getDirs() {
        static const vector<tuple<int, int, char>> directions = {
            std::make_tuple(-1, 0, 'U'),
            std::make_tuple(1, 0, 'D'),
            std::make_tuple(0, -1, 'L'),
            std::make_tuple(0, 1, 'R')
        };
        return directions;
    }

    // Backtracking function to find paths
    void getPaths(const vector<vector<int>>& mat, int row, int col, 
                  string& path, vector<vector<bool>>& visited, 
                  vector<string>& result) {
        int m = mat.size();
        int n = mat[0].size();
        
        // 1. Answer case
        // If we reached the destination
        if (row == m - 1 && col == n - 1) {
            result.push_back(path);
            return;
        }
        
        // 2. Stopping base cases
        // If out of bounds, cell is blocked, or already visited, stop
        if (!isValid(m, n, row, col) || mat[row][col] == 0 || visited[row][col]) 
            return;
        
        // 3. Visit
        // Prevent cycle : Mark the cell as visited
        visited[row][col] = true;

        // Explore all four possible directions
        for (const auto& dir : getDirs()) {
            int nx = row + get<0>(dir);
            int ny = col + get<1>(dir);
            int direction = get<2>(dir);
            path.push_back(direction);
            getPaths(mat, nx, ny, path, visited, result);
            path.pop_back(); // Backtrack
        }

        // Free the node : allow revisiting via another path
        visited[row][col] = false;
    }

public:
    // Function to find all possible paths from (0,0) to (m-1,n-1)
    vector<string> findPath(const vector<vector<int>>& mat) {
        int m = mat.size();
        if (mat.empty())
            return {};
        int n = mat[0].size();

        if (mat[0][0] == 0) // Can't move from here
            return {}; 

        vector<string> result;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        string path;

        getPaths(mat, 0, 0, path, visited, result);
        return result;
    }
};
