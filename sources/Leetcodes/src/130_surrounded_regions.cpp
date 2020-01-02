#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


/// 该怎么样去寻找 O 是否被 X 包围呢？

/// https://leetcode.com/problems/surrounded-regions/discuss/464479/C%2B%2B-DFS
/// 反向思维，找到边界的 O，标出，向 board 的内部扩张
/// 

class Solution {
public:

    void solve(vector<vector<char>>& board) 
    {
        if(board.size() == 0)
            return;
        int w = board.size();
        if(board[0].size() == 0)
            return;
        int h = board[0].size();

        for(int i = 0; i < w; i++)
        {
            dfs(i, 0, board);
            dfs(i, h-1, board);
        }
        
        for(int j = 0; j < h; j++)
        {
            dfs(0, j, board);
            dfs(w-1, j, board);
        }

        for(int i = 0; i < w; i++)
        {
            for(int j = 0; j < h; j++)
            {
                if(board[i][j] == 'O')
                    board[i][j] = 'X';
                else if(board[i][j] == 'A')
                    board[i][j] = 'O';
            }
        }
    }

    void dfs(int i, int j, vector<vector<char>>& board)
    {
        if(i <0 || i >= board.size() || j < 0 || j >= board[0].size())
            return;
        if(board[i][j] == 'O')
        {
            board[i][j] = 'A';
            dfs(i+1,j, board);
            dfs(i-1, j, board);
            dfs(i, j+1, board);
            dfs(i, j-1, board);

        }
    }
};

int main()
{

//    [["X","O","X","O","X","O"],
//     ["O","X","O","X","O","X"],
//     ["X","O","X","O","X","O"],
//     ["O","X","O","X","O","X"]]
    return 0;
}