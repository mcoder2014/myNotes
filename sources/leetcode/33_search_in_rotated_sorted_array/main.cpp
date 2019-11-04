#include <iostream>
#include <vector>

using namespace std;

/// 题目要求O(logn)
/// 因此肯定是二分法方向
/// 先求出哪个位置发生了旋转
/// 再利用二分法找到真实值

class Solution {
public:
    int search(vector<int>& nums, int target)
    {
        int idx_low = 0, idx_high = nums.size()-1;
        while (idx_low < idx_high)
        {
            int idx_mid = (idx_low+idx_high)/2;
            if(nums[idx_mid] > nums[idx_high])
            {
                idx_low = idx_mid+1;
            }
            else
            {
                idx_high = idx_mid;
            }
        }
        int round = idx_low;
        cout << "round " << idx_low << endl;
        idx_low = 0;
        idx_high = nums.size()-1;
        while(idx_low <= idx_high)
        {
            int idx_mid = (idx_low+idx_high)/2;
            if(nums[(idx_mid+round)%nums.size()] < target)
                idx_low = idx_mid+1;
            else if(nums[(idx_mid+round)%nums.size()] > target)
                idx_high = idx_mid-1;
            else
                return (idx_mid+round)%nums.size();
        }

        return -1;
    }
};

int main()
{

    Solution solution;
    auto test = [&](vector<int> nums, int target)
    {
        int idx = solution.search(nums, target);
        for (int item: nums)
            cout << item << " ";
        cout << endl;

        cout << idx << endl;
    };


    test({3, 1}, 1);
    test({4,5,6,7,0,1,2}, 0);

    return 0;
}
