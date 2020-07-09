#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int climbStairs(int n)
    {
        vector<uint64_t> dp(3);
        int idx=3;
        dp[1] = 1;
        dp[2] = 2;
        if(n < idx)
            return dp[idx%3];
        while (idx <= n)
        {
            dp[idx%3] = dp[(idx-1)%3] + dp[(idx-2)%3];
            idx++;
        }
        idx--;
        return dp[idx%3];
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
