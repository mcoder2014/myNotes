# include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix)
    {
        if(matrix.size() == 0) return 0;
        if(matrix[0].size() == 0) return 0;
        int m = matrix.size(), n = matrix[0].size();
        int maximum = 0;

        // 将问题转变成一个动态增长的数组中最大的矩形
        vector<int> height(n+1, 0);
        for(int i =0; i < m; i++)
        {
            stack<int> stk;
            for(int j = 0; j <= n; j++)
            {
                if(j != n)
                    height[j] = matrix[i][j] == '1'? height[j]+1:0;
                else
                    height[j] = 0;
                while(!stk.empty()&&height[j] < height[stk.top()])
                {
                    int hh = height[stk.top()];
                    stk.pop();
                    int width = stk.empty()?j:j-1-stk.top();
                    maximum = std::max(maximum, hh * width);
                }
                stk.push(j);
            }
        }
        return maximum;
    }
};

int main()
{
    Solution solution;
    auto test = [&](vector<vector<char>> matrix)
    {
        int result = solution.maximalRectangle(matrix);
        cout << result << endl;
    };

    test({{'1','0','1','0','0'},
          {'1','0','1','1','1'},
          {'1','1','1','1','1'},
          {'1','0','0','1','0'}});

    return 0;
}
