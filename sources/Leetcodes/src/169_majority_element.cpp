#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;


class Solution {
public:
    int majorityElement(vector<int>& nums) {
        if(nums.size() == 1)
            return nums[0];
        unordered_map<int, int> countMap;
        for(int i : nums) {
            if(countMap.find(i) == countMap.end()) {
                countMap[i] = 1;
                continue;
            }
            countMap[i] ++;
        }

        for(pair<int, int> item:countMap) {
            if(item.second > nums.size()/2) {
                return item.first;
            }
        }
        return nums[0];
    }
};

int main()
{
    return 0;
}