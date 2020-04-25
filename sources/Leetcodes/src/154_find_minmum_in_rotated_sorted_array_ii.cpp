#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int len = nums.size();
        int left = 0 ;
        int right = len-1;
        while(left < right){
            int mid = (right + left)/2;

            if(nums[mid] < nums[right]){
                right = mid;
            }else if(nums[mid] > nums[right]){
                left = mid+1;
            }else if(nums[mid] == nums[right]){
                if(nums[right] == nums[right-1]){
                    right--;
                }else{
                    left++;
                }
            }
        }
        return nums[left];
    }
};

int main()
{
    return 0;
}