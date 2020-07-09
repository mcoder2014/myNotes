#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        result.push_back(nums);
        while (has_next_permutation(nums))
        {
            result.push_back(next_permutation(nums));
        }
        return result;
    }
    bool has_next_permutation(vector<int> &nums)
    {
        int n = nums.size(), i;
        for(i = n-2; i >=0; i--)
        {
            if(nums[i] < nums[i+1])
                break;
        }
        return !(i<0);
    }

    vector<int> next_permutation(vector<int>& nums)
    {
        int n = nums.size(), i, j;
        for(i = n-2; i >=0; i--)
        {
            if(nums[i] < nums[i+1])
                break;
        }

        // 已经没有了
        if(i < 0)
            reverse(nums.begin(), nums.end());
        else
        {
            for(j = n-1; j > i; j--)
            {
                if(nums[j] > nums[i])
                    break;
            }
            swap(nums[i], nums[j]);
            reverse(nums.begin()+i+1, nums.end());
        }
        return nums;
    }
};

int main()
{
    Solution solution;
    auto test = [&](vector<int> nums)
    {
        vector<vector<int>> result = solution.permute(nums);
        for(vector<int> &line:result)
        {
            cout << "[ ";
            for(int item:line)
            {
                cout << item << ",";
            }
            cout << "]\n";
        }
    };

    test({1,2,3});
    return 0;
}
