#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        long long closet = INT_MAX;
        int size = nums.size();
        sort(nums.begin(), nums.end());

        for(int i =0; i < size; i++ )
        {

            int t = target -nums[i];
            int left = i+1, right = size-1;
            while(left < right)
            {
                int sum = nums[left] + nums[right];
                if(abs(t-sum) < abs(closet-target))
                    closet = sum + nums[i];

                if(sum < t)
                    left ++;
                else if(sum > t)
                    right --;
                else
                {
                    // 找到了相等的
                    closet = t;
                    return target;
                }

                // 过滤掉重复的 target
                while(i+1 < size && nums[i+1] == nums[i])
                    i++;
            }
        }

        return closet;
    }
};

int main()
{
    Solution solution;

    auto test = [&](vector<int> nums, int target)
    {
        int result = solution.threeSumClosest(nums, target);
        cout << result << endl;
    };

    test({-1, 2, 1, -4}, 1);
    return 0;
}
