#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        if(dungeon.size() == 0 || dungeon[0].size() ==0)
            return 1;

        int m = dungeon.size();     // 行
        int n = dungeon[0].size();  // 列
        vector<vector<int>> dp(m, vector<int>(n,0));
        dp[m-1][n-1] = max(1 - dungeon[m-1][n-1], 1);   // 初始化到达公主时的最少血量
        for(int i = m-2; i >= 0; i--) {
            dp[i][n-1] = max(1 , dp[i+1][n-1] - dungeon[i][n-1]);
        }
        for(int j = n-2; j >= 0; j--) {
            dp[m-1][j] = max(1, dp[m-1][j+1] - dungeon[m-1][j]);
        }
        for(int i = m-2; i >=0; i--) {
            for(int j = n-2; j>=0; j--) {
                int down = max(1, dp[i+1][j] -dungeon[i][j]);
                int right = max(1, dp[i][j+1] - dungeon[i][j]);
                dp[i][j] = min(down, right);
            }
        }
        return dp[0][0];
    }
};

int main()
{
    return 0;
}