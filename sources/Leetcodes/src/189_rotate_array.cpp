#include <vector>
#include <iostream>

using namespace std;

void print(vector<int>& nums)
{
    for(int item:nums) {
        cout << item <<" ";
    }
    cout << endl;
}

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int numSize = nums.size();
        int rotatePoint = k % nums.size();
        if(rotatePoint == 0) {
            return;
        }
        rotatePoint = numSize - rotatePoint;

        // rotated
        reverse(nums, 0, rotatePoint-1);
        print(nums);
        reverse(nums, rotatePoint, numSize-1 );
        print(nums);
        reverse(nums, 0, numSize - 1);
        print(nums);
    }

    void reverse(vector<int>&nums, int left, int right) {
        while(left < right) {
            swap(nums, left, right);
            left++;
            right--;
        }
    }

    void swap(vector<int>& nums, int i ,int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
};


int main()
{
    Solution sol;
    auto test = [&](vector<int> nums, int k) {
        sol.rotate(nums, k);
        print(nums);
    };

    test({1,2,3,4,5,6,7}, 3);
    cout << endl;
    test({1,2}, 1);
    cout << endl;
    return 0;
}