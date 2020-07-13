#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int, greater<int>> window;
        vector<int> result;
        for(int i = 0; i < nums.size(); i++) {
            if(window.size() >= k) {
                window.erase(window.find(nums[i-k]));
            } 
            
            window.insert(nums[i]);
            
            if(window.size() == k) {
                result.push_back(*window.begin());
            }
            
        }
        return result;
    }
};

int main()
{
    return 0;
}