#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board)
    {
        vector<unordered_map<char, int>> rows(9);
        vector<unordered_map<char, int>> cols(9);
        vector<unordered_map<char, int>> subs(9);
        for (int i=0; i<9; i++)
        {
            for (int j=0; j<9; j++)
            {
                // row
                char ch = board[i][j];
                if(ch != '.')
                {
                    rows[i][ch]++;
                    if(rows[i][ch] > 1)
                        return false;

                    cols[j][ch]++;
                    if(cols[j][ch] > 1)
                        return false;

                    int idx = i/3 + j-(j%3);
                    subs[idx][ch]++;
                    if(subs[idx][ch] > 1)
                        return false;
                }
            }
        }
        return true;
    }

#ifdef version_0
    bool checkInsert(vector<vector<char>>& board, int i, int j)
    {
        vector<int> row(10, 0);
        vector<int> col(10, 0);
        vector<int> sub(10, 0);

        for(int idx = 0; idx < 9; idx++)
        {
            if(board[i][idx] != '.')
            {
                row[board[i][idx]-'0']++;
                if(row[board[i][idx]-'0'] > 1)
                    return false;
            }
        }

        for(int idx = 0; idx < 9; idx++)
        {
            if(board[idx][j] != '.')
            {
                col[board[idx][j]-'0']++;
                if(col[board[idx][j]-'0'] > 1)
                    return false;
            }
        }

        int i_start = (i/3)*3;
        int j_start = (j/3)*3;

        for(int idx_i = i_start; idx_i < i_start+3; idx_i++)
        {
            for(int idx_j = j_start; idx_j < j_start+3; idx_j++)
            {
                if(board[idx_i][idx_j] !='.')
                {
                    sub[board[idx_i][idx_j]-'0']++;
                    if(sub[board[idx_i][idx_j]-'0'] > 1)
                        return false;
                }
            }
        }

        return true;

    }
#endif
#define version_1
#ifdef version_1
    vector<vector<int>> rows;
    vector<vector<int>> cols;
    vector<vector<int>> subs;

    bool checkInsert(vector<vector<char>>& board, int i, int j)
    {
        char ch = board[i][j];
        if(rows[i][ch-'0'] >1 )
            return false;
        if(cols[j][ch-'0']>1)
            return false;
        int idx = i/3 + j-(j%3);
        if(subs[idx][ch-'0']>1)
            return false;

        return true;
    }

#endif

    bool insert(vector<vector<char>>& board, int i, int j)
    {
        if(board[i][j] != '.')
        {
            int next_j = (j+1)%9;
            int next_i = i + (j+1)/9;

            if(next_i == 9)
                return true;
            if(insert(board, next_i, next_j))
            {
                return true;
            }

            return false;
        }

        for(int ch_id=1; ch_id < 10; ch_id++)
        {
            board[i][j] = ch_id+'0';
#ifdef version_1
            rows[i][ch_id]++;
            cols[j][ch_id]++;
            int idx = i/3 + j-(j%3);
            subs[idx][ch_id]++;
#endif
            if(checkInsert(board, i, j))
            {
                int next_j = (j+1)%9;
                int next_i = i + (j+1)/9;

                if(next_i == 9)
                    return true;
                if(insert(board, next_i, next_j))
                {
                    return true;
                }
            }

#ifdef version_1
            rows[i][ch_id]--;
            cols[j][ch_id]--;
            subs[idx][ch_id]--;
#endif
        }
        board[i][j] = '.';
        return false;
    }

    void solveSudoku(vector<vector<char>>& board)
    {
#ifdef version_1
        rows = vector<vector<int>>(9, vector<int>(10,0));
        cols = vector<vector<int>>(9, vector<int>(10,0));
        subs = vector<vector<int>>(9, vector<int>(10,0));

        // init
        for (int i=0; i<9; i++)
        {
            for (int j=0; j<9; j++)
            {
                // row
                char ch = board[i][j];
                if(ch != '.')
                {
                    rows[i][ch-'0']++;
                    cols[j][ch-'0']++;
                    int idx = i/3 + j-(j%3);
                    subs[idx][ch-'0']++;
                }
            }
        }
#endif

        insert(board, 0, 0);
    }
};

int main()
{

    Solution solution;
    vector<vector<char>> board({{'5','3','.','.','7','.','.','.','.'},
                                {'6','.','.','1','9','5','.','.','.'},
                                {'.','9','8','.','.','.','.','6','.'},
                                {'8','.','.','.','6','.','.','.','3'},
                                {'4','.','.','8','.','3','.','.','1'},
                                {'7','.','.','.','2','.','.','.','6'},
                                {'.','6','.','.','.','.','2','8','.'},
                                {'.','.','.','4','1','9','.','.','5'},
                                {'.','.','.','.','8','.','.','7','9'}});

    vector<vector<char>> backup({{'5','3','.','.','7','.','.','.','.'},
                                {'6','.','.','1','9','5','.','.','.'},
                                {'.','9','8','.','.','.','.','6','.'},
                                {'8','.','.','.','6','.','.','.','3'},
                                {'4','.','.','8','.','3','.','.','1'},
                                {'7','.','.','.','2','.','.','.','6'},
                                {'.','6','.','.','.','.','2','8','.'},
                                {'.','.','.','4','1','9','.','.','5'},
                                {'.','.','.','.','8','.','.','7','9'}});
    solution.solveSudoku(board);
//    bool result = solution.insert(board, 0, 0);

//    cout << result << endl;
    for (vector<char> row:board)
    {
        for(char ch:row)
            cout << ch << "\t";
        cout << endl;
    }

    return 0;
}
