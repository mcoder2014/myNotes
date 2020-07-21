#include <iostream>
#include <vector>

using namespace std;

class NumMatrix {
private:
    vector<vector<int>> dp;
public:
    // 一维的时候很容易考虑，eg: sum(i,j) = dp[j]-dp[i]
    // 二维时画出二维图形容易得到， eg: sum(sx, sy, ex, ey) = dp[ex][ey]-dp[sx][sy]-(dp[ex][sy]-dp[sx][sy]+dp[sx][ey]-dp[sx][sy])
    // 可能标号差1
    
    NumMatrix(vector<vector<int>>& matrix) {
        int M = matrix.size();
        int N;
        if(M==0)  
            N = 0;
        else  
            N = matrix[0].size();
        
        dp = vector<vector<int>>(M+1, vector<int>(N+1,0));

        // dp[i][j] 表示 前i行前j列的矩形的和
        for(int i=1; i<=M; i++){
            for(int j=1; j<=N; j++){
                dp[i][j] = matrix[i-1][j-1] + dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int ans = dp[row2+1][col2+1]; 
        ans -= dp[row1][col2+1];
        ans -= dp[row2+1][col1];
        ans += dp[row1][col1];
        return ans;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

int main()
{
    return 0;
}