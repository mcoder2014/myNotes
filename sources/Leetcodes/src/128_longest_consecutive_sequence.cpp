#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) 
    {
        unordered_map<int, bool> mp;
        for(int item:nums)
            mp[item] = false;
        int longest = 0;

        for(int item:nums)
        {
            int length = 1;

            // 如果是已经处理了的元素
            if(mp[item])
                continue;

            mp[item] = true;

            // 向前寻找
            for(int j = item+1; mp.find(j) != mp.end(); ++j)
            {
                mp[j] = true;
                length++;
            }
                    
            for(int j = item-1; mp.find(j) != mp.end(); --j)
            {
                mp[j] = true;
                length++;
            }
            longest = max(length, longest);
        }
        return longest;
    }
};

int main()
{
    return 0;
}