#include <iostream>
#include <vector>
#include <climits>

using namespace std;

/**
 * DP 思想
 * dp[i] = max(dp[i-1], nums[i]*nums[i-1], nums[i]*nums[i-1]*nums[i-2], ... , nums[i]*...*nums[0])
 */ 
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int left = 0, right = 0;
        int length = nums.size();

        if(length == 0)
            return 0;
        else if(length == 1)
            return nums[0];

        int maxValue = INT32_MIN;       // 相当于 dp
        int curProduct = 0;
        for(int i =0; i < length; i++)
        {
            // old dp
            curProduct = 1;
            for(int j = i; j >=0; j--)
            {
                curProduct = nums[j] * curProduct;
                if(maxValue < curProduct)
                {
                    maxValue = curProduct;
                }
            }
        }
        return maxValue;
    }
};

int main()
{
    return 0;
}