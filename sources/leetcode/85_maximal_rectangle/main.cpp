#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {

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
