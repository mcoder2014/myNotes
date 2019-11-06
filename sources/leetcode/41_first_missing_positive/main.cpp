#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if(nums.size() == 0) return 1;
#define O_N
#ifndef O_N

        sort(nums.begin(), nums.end());
        int value = 0;
        for(int item: nums)
        {
            if(item > 0)
            {
                if(value + 1 == item)
                    value++;
                else if(value == item)
                {

                }
                else
                {
                    return value+1;
                }
            }
        }
        return value + 1;
#else
        int n = nums.size();
    for(int i=0; i < n; i++)
    {
        while(nums[i] > 0 && nums[i] != nums[nums[i] - 1] && nums[i] <= n)
        {
            int t = nums[i];
            nums[i] = nums[t - 1];
            nums[t - 1] = t;
        }

    }

    for(int i = 0; i < n; i++)
        if(nums[i] != i+1)
            return i+1;
    return n+1;
#endif
    }
};

int main()
{

    Solution solution;
    auto test = [&](vector<int> nums)
    {
        int result = solution.firstMissingPositive(nums);
        cout << result << endl;
    };

    test({1,2,0});
    test({7,8,9,11,12});
    test({3,4,-1,1});
    test({0,1,1,2,2,3,6});
    test({7,8,9,11,12});
    return 0;
}
