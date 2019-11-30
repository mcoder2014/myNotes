#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numDecodings(string s)
    {
        int n = s.length();
        if(n==0) return 0;

        vector<int> dp(n, 1);
        dp[0] = s[0] == '0'?0:1;

        for (int i = 1; i < n; i++)
        {
            if(s[i] == '0')
                dp[i] = dp[i-1];
            else if(dp[i-1]==0)
                dp[i] = 1;
            else if(s[i] >'6')
                dp[i] = dp[i-1];
            else if(s[i-1] < '3' && s[i-1] > '0')
                dp[i] = dp[i-1] + (i>=2?dp[i-2]:1);
            else
                dp[i] = dp[i-1];
        }
        return dp[n-1];
    }
};

int main()
{
    Solution solution;
    auto test = [&](string s)
    {
        int result = solution.numDecodings(s);
        cout << result << "\n";
    };

    test("12");
    test("226");
    test("0");
    test("02026");
    return 0;
}
