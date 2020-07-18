#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        if(board.size() == 0) {
            return;
        }

        int m = board.size();
        int n = board[0].size();

        vector<vector<int>> backup(m, vector<int>(n));


        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                int count = getSrounding(board, i, j, m, n);
                cout << count << " ";
                if(board[i][j] == 1) {
                    if(count < 2 || count > 3) {
                        backup[i][j] = 0;
                    } else {
                        backup[i][j] = 1;
                    } 
                }else{
                    if(count == 3) {
                        backup[i][j] = 1;
                    }else {
                        backup[i][j] = 0;
                    }
                }
            }
            cout << endl;
        }

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                board[i][j] = backup[i][j];
            }
        }

    }

    int getSrounding(vector<vector<int>>& board, int i, int j, int sizeM, int sizeN) {
        int count = 0;
        bool up = (i > 0);
        bool down = (i < sizeM-1);
        bool left  = (j > 0);
        bool right = (j < sizeN-1);

        if(up && down && left && right) {
            count += board[i-1][j-1];
            count += board[i-1][j];
            count += board[i-1][j+1];

            count += board[i][j-1];
            count += board[i][j+1];

            count += board[i+1][j-1];
            count += board[i+1][j];
            count += board[i+1][j+1];

            return count;
        }

        // 上
        if(up ) {
            count += board[i-1][j];
        }

        // 下
        if(down ) {
            count += board[i+1][j];
        }

        // 左
        if(left) {
            count += board[i][j-1];
        }

        // 右
        if(right ) {
            count += board[i][j+1];
        }

        if(up && left) {
            count += board[i-1][j-1];
        }
        if(up && right) {
            count += board[i-1][j+1];
        }
        if(down && left) {
            count += board[i+1][j-1];
        }
        if(down && right) {
            count += board[i+1][j+1];
        }
        return count;
    }
};

int main()
{
    return 0;
}