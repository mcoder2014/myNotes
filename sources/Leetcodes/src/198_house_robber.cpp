#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size()== 0){
            return 0;
        }
        else if(nums.size() == 1){
            return nums[0];
        } else if(nums.size() == 2) {
            return max(nums[0], nums[1]);
        }

        int size = nums.size();
        vector<int> dp(size);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for(int i = 2; i < size; i++) {
            dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
        }
        return dp[size -1];
    }
};

int main()
{
    return 0;
}