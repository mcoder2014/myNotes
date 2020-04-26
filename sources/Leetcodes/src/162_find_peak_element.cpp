#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        
        if(nums.size() == 1) {
            return 0;
        } else if (nums.size() == 2) {
            return nums[0] > nums[1]?0:1;
        }

        int left = 0;
        int right = nums.size() -1;
        int mid;
        
        while(left + 1 < right) {
            mid = left + (right - left)/2;
            if(nums[mid] > nums[mid+1] && nums[mid] > nums[mid - 1]) {
                return mid;
            } else if (nums[mid] > nums[mid-1]) {
                left = mid;
            } else {
                right = mid;
            }
        } 

        if(left + 1 == right && nums[left] > nums[right]) {
            return left;
        } else {
            return right;
        }
    }
};

int main()
{
    return 0;
}