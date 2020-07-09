#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target)
    {
        int n = nums.size();
        if(n == 0) return false;
        if(n==1) return nums[0] == target;
        int l = 0, r = n;
        while(l <r)
        {
            int mid = l+(r-l)/2;
            if(nums[mid] == target)
                return true;
            else if(nums[l] < nums[mid])
            {
                if(nums[l] <= target && target < nums[mid])
                    r = mid;
                else
                    l = mid + 1;
            }
            else if(nums[l] > nums[mid])
            {
                if(target <= nums[r-1] && nums[mid] < target)
                    l = mid + 1;
                else
                    r = mid;
            }
            else
                l++;
        }
        return false;
    }
};

int main()
{
    Solution solution;
    auto test = [&](vector<int> nums, int target)
    {
        bool res = solution.search(nums, target);
        cout << target << "\t" << res << "\n";
    };

    test({2,5,6,0,0,1,2}, 0);
    test({2,5,6,0,0,1,2}, 3);
    test({1,3},3);

    cout << "Hello World!" << endl;
    return 0;
}
