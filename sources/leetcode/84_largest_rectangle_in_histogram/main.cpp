#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights)
    {
        int n = heights.size();
        int max = 0;
        stack<int> stk;
        for(int i = 0; i <= n ; i++)
        {
            int height = (i==n)?0:heights[i];
            while(stk.size()>0 && height < heights[stk.top()])
            {
                int hh = heights[stk.top()];
                stk.pop();
                int width = stk.empty()?i:i-1-stk.top();
                max = std::max(max, hh*width);
            }
            stk.push(i);
        }
        return max;
    }
};

int main()
{
    Solution solution;
    auto test = [&](vector<int> height)
    {
        int res = solution.largestRectangleArea(height);
        cout << res << "\n";
    };


    test({2,1,5,6,2,3});
    return 0;
}
