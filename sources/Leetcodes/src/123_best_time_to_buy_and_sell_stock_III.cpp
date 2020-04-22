#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// DP: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/135704/Detail-explanation-of-DP-solution

class Solution {
public:

// DP[k][i] = 
// case1: dp[k][i-1]
// case2: dp[k-1][j] + prices[i]-prices[j]
    int maxProfit(vector<int>& prices) 
    {
        if(prices.size() < 2)
            return 0;
        int maxBuy = 2;
        vector<vector<int> > dp(maxBuy+1, vector<int>(prices.size(), 0));

        for(int k = 1; k <= maxBuy; k++)
        {
            int minPrice = prices[0];
            for(int i=1; i < prices.size(); i++)
            {
                minPrice = min(minPrice, prices[i] - dp[k-1][i-1]);
                dp[k][i] = max(dp[k][i-1], prices[i] - minPrice);
            }
        }
        return dp[maxBuy][prices.size()-1];

    }
};

int main()
{
    return 0;
}