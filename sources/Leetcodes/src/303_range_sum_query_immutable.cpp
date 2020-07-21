#include <iostream>
#include <vector>

using namespace std;

class NumArray {
public:
    NumArray(vector<int>& nums)
        :sum(nums.size(), 0) {
        int64_t sumValue = 0;
        for(int i = 0; i < nums.size(); i++) {
            sumValue += nums[i];
            sum[i] = sumValue;
        }
    }
    
    int sumRange(int i, int j) {
        int64_t large = sum[j];
        int64_t small = 0;
        if(i > 0) {
            small = sum[i-1];
        }

        return large - small;
    }

    vector<int64_t> sum;

};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */

int main()
{
    return 0;
}