#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
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

    void solveSudoku(vector<vector<char>>& board) {

        }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
