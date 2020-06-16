#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        int size = nums.size();

        sort(nums.begin(), nums.end());

        for (int i =0; i < size - 3; i++)
        {
            for(int j = i+1; j < size-2; j++)
            {
                int left = j + 1;
                int right = size-1;

                int t = target - nums[i] - nums[j];

                while (left < right)
                {
                    int sum = nums[left] + nums[right];
                    if(sum < t)
                        left ++;
                    else if(sum > t)
                        right --;
                    else
                    {
                        // 记录
                        vector<int> quad{
                            nums[i], nums[j], nums[left], nums[right]};
                        result.push_back(quad);

                        while (left < right && nums[left] == quad[2])
                            left++;
                        while (left < right && nums[right] == quad[3])
                            right--;
                    }
                }
                while (j < size-2 && nums[j+1] == nums[j])
                    j++;
            }

            while (i < size-3 && nums[i+1] == nums[i])
                i++;
        }

        return result;
    }
};


int main()
{
    Solution slu;

    auto test = [&](vector<int> nums, int target)
    {
        vector<vector<int>> result = slu.fourSum(nums, target);
        cout << "[\t";
        for (vector<int> quad:result)
        {
            for(int element:quad)
                cout <<element << "\t";
            cout << endl;
        }
        cout << "]\n";
    };

    test({1, 0, -1, 0, -2, 2}, 0);

    return 0;
}
