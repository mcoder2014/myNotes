#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        // at most one transaction
        if(prices.size() <= 1)
            return 0;
        
        int maxProfit = 0, minPrice = prices[0], size = prices.size();
        for(int i = 1; i < size; i++)
        {
            if(prices[i] > prices[i-1])
            {
                maxProfit = max(prices[i] - minPrice, maxProfit);
            }
            else
            {
                minPrice = min(prices[i], minPrice);
            }
        }
        return maxProfit;
    }
};

int main()
{
    return 0;
}