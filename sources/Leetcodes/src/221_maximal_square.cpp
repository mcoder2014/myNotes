#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if(m < 1) {
            return 0;
        }

        int n = matrix[0].size();
        int maximum = 0;
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        /**
        dp[i][j]表示以第i行第j列为右下角所能构成的最大正方形边长, 则递推式为: 
        dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]);
        **/

        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(matrix[i-1][j-1]== '1') {
                    dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
                    maximum = max(maximum, dp[i][j]);
                }
            }
        }

        return maximum * maximum;

    }
};

int main()
{
    return 0;
}