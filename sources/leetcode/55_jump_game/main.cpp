#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums)
    {

        int maxEnd = 0;
        int pos = 0;
        int len = nums.size();
        while(pos<len && pos <= maxEnd)
        {
            if(pos + nums[pos] >= maxEnd )
            {
                maxEnd = pos + nums[pos];
                if(maxEnd >= len-1)
                    return true;
            }
            pos++;
        }
        return false;
    }
};

int main()
{

    return 0;
}
