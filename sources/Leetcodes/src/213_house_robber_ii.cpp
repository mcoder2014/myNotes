#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return nums[0];

        vector<int> dp0 (nums.size()-1);
        vector<int> dp1 (nums.begin()+1, nums.end());


        dp0[0] = nums[0];
        dp0[1] = max(nums[0], nums[1]);
        for(int i = 2; i < nums.size() - 1; i ++) {
            dp0[i] = max(dp0[i - 1], dp0[i - 2] + nums[i]);
        }

        dp1[0] = nums[1];
        dp1[1] = max(nums[1], nums[2]);
        for(int i = 3; i < nums.size(); i++) {
            dp1[i-1] = max(dp1[i-1], dp1[i-3] + nums[i]);
        }

        return max(dp0[nums.size() - 2], dp1[nums.size() - 2]);
    }
};

int main()
{
    return 0;
}