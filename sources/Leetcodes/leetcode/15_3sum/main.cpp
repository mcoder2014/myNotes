#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int size = nums.size();
        sort(nums.begin(), nums.end());

        for(int i =0; i < size; i++ )
        {
            if(nums[i] > 0)
                break;

            int target = -nums[i];
            int left = i+1, right = size-1;
            while(left < right)
            {
                int sum = nums[left] + nums[right];
                if(sum < target)
                    left ++;
                else if(sum > target)
                    right --;
                else
                {
                    // xiang deng
                    vector<int> triple(3,0);
                    triple[0] = nums[i];
                    triple[1] = nums[left];
                    triple[2] = nums[right];
                    result.push_back(triple);

                    // check if there any other possible result
                    while (left < right && nums[left] == triple[1])
                    {
                        left++;
                    }
                    while (right>left && nums[right] == triple[2])
                    {
                        right--;
                    }

                }

                // 过滤掉重复的 target
                while(i+1 < size && nums[i+1] == nums[i])
                    i++;
            }
        }


        return result;
    }
};

int main()
{
    Solution solution;

    auto test = [&](vector<int> nums)
    {
        vector<vector<int>> result = solution.threeSum(nums);
        cout << "[";
        for(vector<int>& triple:result)
        {
            cout << "[";
            for(int t:triple)
                cout << t << ' ';
            cout << "]" << endl;
        }
        cout << "]" << endl;
    };

    test({-1, 0, 1, 2, -1, -4});

    return 0;
}
