#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    int numIslands(vector<vector<char>>& grid) {
        if(grid.size() == 0)
            return 0;

        int islandCounter = 0;

        int rows = grid.size();
        int cols = grid[0].size();
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(grid[i][j] == '1') {
                    islandCounter ++;
                    dfs(grid, rows, cols, i, j);
                }
            }
        }
        return islandCounter;
    }

    // 把一个岛全部化为 0
    void dfs(vector<vector<char>>& grid, int rows, int cols, int row, int col) {
        if(row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] == '0') {
            return;
        }
        
        grid[row][col] = '0';
        dfs(grid, rows, cols, row, col + 1);
        dfs(grid, rows, cols, row, col - 1);
        dfs(grid, rows, cols, row + 1, col);
        dfs(grid, rows, cols, row - 1, col);
    }
};

int main()
{
    Solution solu;
    auto test = [&](vector<vector<char>> grid) {
        int result = solu.numIslands(grid);
        cout << result << endl;
    };

    test({{'1','1','0','0','0'},{'1','1','0','0','0'},{'0','0','1','0','0'},{'0','0','0','1','1'}});

    return 0;
}