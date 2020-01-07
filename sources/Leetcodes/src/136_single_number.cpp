#include <stdio.h>
#include <iostream>
#include <vector>
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

    int method2(vector<int>& nums)
    {
        int num = 0;
        for(int item:nums)
            num ^=item;
        return num;
    }
};

int main()
{
    return 0;
}