#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> set;

        for(int i = 0; i < nums.size(); i++) {
            if(set.size() < k) {
                if(set.find(nums[i])!=set.end()) {
                    return true;
                } else {
                    set.insert(nums[i]);
                }
            } else {
                if(set.find(nums[i])!=set.end()) {
                    return true;
                } else {
                    set.insert(nums[i]);
                    set.erase(nums[i-k]);
                }
            }
        }
        return false;
    }
};

int main()
{
    return 0;
}