#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;

        int length = 1;
        int none_duplicate_idx = 1;

        for (int i =1; i < nums.size(); i++)
        {
            if(nums[i] != nums[i-1])
            {
                nums[none_duplicate_idx] = nums[i];
                length++;
                none_duplicate_idx++;
            }
        }
        return length;
    }
};

int main()
{
    return 0;
}
