#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution
{
public:
    bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
    {
        multiset<int64_t> set;

        for (int i = 0; i < nums.size(); i++)
        {
            if (set.size() == k+1)
            {
                set.erase(set.find(nums[i - k-1]));
            }

            set.insert(nums[i]);

            if (helper(set, t, nums[i]))
            {
                return true;
            }
        }
        return false;
    }

    bool helper(multiset<int64_t> &set, int64_t t, int64_t value)
    {
        multiset<int64_t>::iterator iter = set.find(value);
        multiset<int64_t>::iterator iterBefore = iter;
        iterBefore--;
        multiset<int64_t>::iterator iterAfter = iter;
        iterAfter++;

        if (iter != set.begin() && *iter - *iterBefore <= t)
        {
            return true;
        }

        if (iterAfter != set.end() && *iterAfter - *iter <= t)
        {
            return true;
        }
        return false;
    }
};

int main()
{
    return 0;
}