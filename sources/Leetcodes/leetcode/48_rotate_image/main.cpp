#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix)
    {
        if(matrix.size() <=1)   return;
        transpose(matrix);
        flap(matrix);
    }
    void transpose(vector<vector<int>>& matrix)
    {
        int size= matrix.size();
        int tmp;
        for(int i = 0; i < size; i++)
        {
            for(int j = i+1; j < size; j++)
            {
                tmp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = tmp;
            }
        }
    }
    void flap(vector<vector<int>>& matrix)
    {
        for(vector<int>& line:matrix)
        {
            reverse(line.begin(), line.end());
        }
    }
};

int main()
{
    Solution solution;
    auto print = [&](vector<vector<int>>& matrix)
    {
        for (vector<int> line : matrix)
        {
            for(int item:line)
                cout << item << " ";
            cout << "\n";
        }
        cout << "\n";
    };
    auto test = [&](vector<vector<int>> matrix)
    {
        print(matrix);
        solution.transpose(matrix);
        print(matrix);
        solution.flap(matrix);
//        solution.rotate(matrix);
        print(matrix);
    };

    test({{1,2,3},{4,5,6},{7,8,9}});
    test({{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}});
    return 0;
}
