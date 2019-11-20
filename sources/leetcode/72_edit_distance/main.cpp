#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size();
        int n = word2.size();
        if(m == 0) return n;
        if(n == 0) return m;

        vector<vector<int>> dp(m+1, vector<int>(n+1,0));
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        for(int j = 0; j <=n; j++)
            dp[0][j] = j;

        for (int i=1;i<=m;i++)
        {
            char ch1 = word1[i-1];
            for(int j = 1; j <= n; j++)
            {
                char ch2 = word2[j-1];
                int cost = (ch1 == ch2) ? 0:1;
                dp[i][j] = min(min(dp[i-1][j-1]+cost, dp[i-1][j]+1),dp[i][j-1]+1);
            }
        }
        return dp[m][n];
    }


};


int main()
{
    Solution solution;
    auto test = [&](string str1, string str2)
    {
        int res = solution.minDistance(str1, str2);
        cout << str1 << "\t" << str2 << "\t" << res << endl;
    };
    test("intention", "execution");
    test("horse","ros");

    return 0;
}
