#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> set;

        for(int item:nums) {
            if(set.find(item) != set.end()) {
                return true;
            } else {
                set.insert(item);
            }
        }

        return false;
    }
};

int main()
{
    return 0;
}