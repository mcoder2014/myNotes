#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums)
    {
        int end = 0;
        int maxPosition = 0;
        int steps = 0;
        for(int i = 0; i < nums.size()-1; i++)
        {
            maxPosition = max(maxPosition, nums[i]+i);
            if(i == end)
            {
                end = maxPosition;
                steps++;
            }
        }
        return steps;
    }

    int helper(vector<int>&notes, vector<int>& nums, int pos)
    {
        if(pos == nums.size()-1)
            return 0;
        if(notes[pos] != -1)
            return notes[pos];

        int value = nums[pos];
        int min = nums.size();
        int max = nums.size()-pos-1;
        if(value < max) max  = value ;

        if(value == 0)
            return numeric_limits<int>::max();

        for(int step = 1; step <= max; step ++)
        {
            int count = helper(notes, nums, pos+step);
            if( count < min)
                min = count ;
        }
        notes[pos] = min + 1;
        return min + 1;
    }
};

int main()
{
    Solution solution;
    auto test = [&](vector<int> nums){
        int result = solution.jump(nums);
        cout << result << endl;
    };

    test({2,1});
    test({2,3,1,1,4});      // 2
    test({5,6,4,4,6,9,4,4,7,4,4,8,2,6,8,1,5,9,6,5,2,7,9,7,9,6,9,4,1,6,8,8,4,4,2,0,3,8,5});
    test({2,3,0,1,4});      // 2
    test({1,2,3});          // 2
    

    return 0;
}
