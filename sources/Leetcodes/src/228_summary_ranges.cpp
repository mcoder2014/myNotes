#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        set<int> numSet;
        for(int& item:nums) {
            numSet.insert(item);
        }

        vector<string> returnValue;

        for(int& item:nums) {
            int minValue = item;
            int maxValue = item;

            if(numSet.find(item) == numSet.end()) {
                continue;
            }

            numSet.erase(numSet.find(item));

            // 向前查找
            while(numSet.find(minValue-1) != numSet.end()) {
                // 还有小的元素
                minValue--;
                numSet.erase(numSet.find(minValue));
            }

            // 向后寻找
            while(numSet.find(maxValue+1) != numSet.end()) {
                maxValue++;
                numSet.erase(numSet.find(maxValue));
            }

            if(minValue == maxValue) {
                returnValue.push_back(to_string(item));
            } else {
                returnValue.push_back(to_string(minValue) + "->" + to_string(maxValue));
            }
        }
        return returnValue;
   }
};

int main()
{
    return 0;
}