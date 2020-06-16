#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word)
    {
        int m = board.size(), n = 0;
        if(m > 0)
            n = board[0].size();

        vector<vector<bool>> path(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(board[i][j] == word[0])
                {
                    if(helper(board, path, word, i, j, 0))
                        return true;
                }
            }
        }
        return false;
    }

    bool helper(vector<vector<char>>& board, vector<vector<bool>>& path, string &word, int i,int j, int idx)
    {
//        if(idx >= word.size())
//            return true;
        if(word[idx] != board[i][j])
            return false;
        else if(word[idx] == board[i][j] && idx == word.size()-1)
            return true;

        bool result = false;
        path[i][j] = true;
        if(i > 0 && !path[i-1][j])
            result |= helper(board, path, word, i-1, j, idx+1);
        if (result) return true;
        if(j > 0 && !path[i][j-1])
            result |= helper(board, path, word, i, j-1, idx+1);
        if (result) return true;
        if(i < board.size()-1 && !path[i+1][j])
            result |= helper(board, path, word, i+1, j, idx+1);
        if (result) return true;
        if(board.size()>0 && j < board[0].size()-1 && !path[i][j+1])
            result |= helper(board, path, word, i, j+1, idx+1);
        if (result) return true;
        path[i][j] = false;

        return false;
    }
};

int main()
{
    Solution solution;
    auto test = [&](vector<vector<char>> board, string word)
    {
        bool result = solution.exist(board, word);
        cout << word << "\t" << result << endl;
    };

    test({  {'A','B','C','E'},
         {'S','F','C','S'},
         {'A','D','E','E'}}, "ABCCED");
    test({  {'A','B','C','E'},
         {'S','F','C','S'},
         {'A','D','E','E'}}, "SEE");
    test({  {'A','B','C','E'},
         {'S','F','C','S'},
         {'A','D','E','E'}}, "ABCB");
    test({{'a'}}, "a");
    test({{}},"a");
    return 0;
}
