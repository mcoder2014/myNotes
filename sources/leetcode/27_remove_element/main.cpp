#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(nums.size() == 0)
            return 0;

        int length = 0;
        int idx = 0;

        for (int i =0; i < nums.size(); i++)
        {
            if(nums[i] != val)
            {
                nums[idx] = nums[i];
                length++;
                idx++;
            }
        }
        return length;
    }
};


int main()
{
    return 0;
}
