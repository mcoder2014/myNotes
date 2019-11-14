#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<int>> board(n, vector<int>(n,0));
        vector<vector<string>> result;
        n_queen(board,result,0,0,n);
        return result;
    }

    ///
    /// \brief n_queen
    /// \param chessboard
    /// \param i
    /// \param j
    /// \param index    还需要的递归层数
    ///
    void n_queen(vector<vector<int>>& chessboard,
                 vector<vector<string>>&result, int i, int j, int index)
    {
        int n = chessboard.size();
        for(;i < n; i++)
        {
            for(; j < n; j++)
            {
                if(check(chessboard,i,j))
                {
                    chessboard[i][j] = 1;
                    if(index == 1)
                    {
                        // output result
                        vector<string> lines;
                        for(vector<int>& row:chessboard)
                        {
                            string line;
                            for(int col:row)
                            {
                                if(col == 0)
                                    line.push_back('.');
                                else
                                    line.push_back('Q');
                            }
                            lines.push_back(line);
                        }
                        result.push_back(lines);
                    }
                    else
                        n_queen(chessboard,result,i+(j+1)/n, (j+1)%n, index-1);
                    chessboard[i][j] = 0;
                }
            }
            j = 0;
        }
    }

    bool check(vector<vector<int>>& chessboard, int i, int j)
    {
        int size = chessboard.size();
        for(int iter=0;iter < size; iter++)
        {
            if(chessboard[i][iter] > 0
                    ||chessboard[iter][j]>0)
                return false;
        }
        int ii = i, jj = j;
        while(ii < size && jj < size)
        {
            if(chessboard[ii++][jj++] > 0)
                return false;
        }
        ii = i, jj = j;
        while(ii >=0 && jj >=0)
        {
            if(chessboard[ii--][jj--] >0)
                return false;
        }
        ii = i, jj = j;
        while(ii >= 0 && jj < size)
        {
            if(chessboard[ii--][jj++] > 0)
                return false;
        }
        ii = i, jj = j;
        while(ii < size && jj >=0)
        {
            if(chessboard[ii++][jj--] >0)
                return false;
        }

        return true;
    }

};

int main()
{
    Solution solution;
    auto test = [&](int n)
    {
        vector<vector<string>> result = solution.solveNQueens(n);
        for(vector<string>& res:result)
        {
            for(string& line: res)
                cout <<line<<"\n";
            cout << "\n";
        }
    };

    test(4);
    test(5);

    return 0;
}
