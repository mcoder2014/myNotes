#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target)
    {
        int low = 0, high = nums.size() - 1;
        int pos = -1;
        while(low <= high)
        {
            int mid = (low + high)/2;
            if(nums[mid] > target)
                high = mid -1;
            else if(nums[mid] < target)
                low = mid+1;
            else
            {
                pos=mid;
                break;
            }
        }
        if(pos == -1)
            return vector<int>({-1, -1});
        else
        {
            int lower = pos;
            int upper = pos;
            while (lower >0 && nums[lower-1] == target)
            {
                lower --;
            }
            while(upper < nums.size()-1 && nums[upper+1] == target)
                upper++;
            return vector<int>({lower,upper});
        }


    }
};

int main()
{

    return 0;
}
