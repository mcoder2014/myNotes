#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), 1);

        int left = 1;
        int right = 1;

        for(int i = 0; i < nums.size(); i++) {
            
            res[i] *= left;
            left *= nums[i];

            res[nums.size()-1-i] *= right;
            right *= nums[nums.size() - 1 - i];
        }
        
        return res;
    }
};

int main()
{
    return 0;
}