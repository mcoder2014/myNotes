#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
        int singleNumber(vector<int>& nums) 
    {
        if(nums.size() == 0)
            return 0;
        unordered_map<int, int> mp;
        for(int item:nums)
            mp[item] ++;
        for( auto& pa: mp)
        {
            if(pa.second == 1)
                return pa.first;
        }    
        return nums[0];
    }
    
};

int main()
{
    return 0;
}