#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 0) {
            return 0;
        }
        int n = prices.size();
        vector<int> sell(n, 0);
        vector<int> buy(n, 0);
        buy[0] = -prices[0];
        vector<int> cool(n, 0);

        for(int i = 1; i < n; i++) {
            sell[i] = max(buy[i-1] + prices[i], sell[i-1]);
            buy[i] = max(cool[i-1] - prices[i], buy[i-1]);
            cool[i] = max(sell[i-1], cool[i-1]);
        }

        return max(sell[n-1], cool[n-1]);
    }
};


int main()
{
    return 0;
}