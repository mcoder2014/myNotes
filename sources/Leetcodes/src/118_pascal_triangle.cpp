#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) 
    {
        vector<vector<int>> triangle(numRows);
        for(int i = 0; i < numRows; i++)
            triangle[i] = vector<int>(i+1, 1);
        for(int i = 2;i < numRows; i++)
        {
            for(int j = 1; j < i; j++)
            {
                triangle[i][j] = triangle[i-1][j-1]+triangle[i-1][j];
            }
        }
        return triangle;
    }
};

int main()
{
    return 0;
}