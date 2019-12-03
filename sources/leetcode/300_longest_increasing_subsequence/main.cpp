#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums)
    {
        int length = nums.size();
        if(length == 0)
            return 0;
        vector<int> dp(length, 1);
        for(int i = 1; i < length; i++)
        {
            int curVal = nums[i];
            for(int j = 0; j < i; j++)
            {
                if(curVal > nums[j])
                    dp[i] = max(dp[j]+1, dp[i]);
            }
        }
        int res= dp[0];
        for(int item:dp)
            res = max(res,item);
        return res;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
