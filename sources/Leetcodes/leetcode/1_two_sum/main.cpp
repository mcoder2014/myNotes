#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> maps;
        int size = nums.size();
        for(int i = 0; i < size; ++i)
            maps[nums[i]] = i;

        for (int i = 0; i < size; ++i) {
            int left = target - nums[i];
            if(maps.count(left) > 0 && maps[left] != i)
            {
                return vector<int>({i, maps[left]});
            }
        }
        return vector<int>();
    }
};


int main()
{
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    Solution solution;
    vector<int> result = solution.twoSum(nums, target);

    for (int val:result) {
        cout << val << "\t";
    }
    cout << "\n";

    return 0;
}
