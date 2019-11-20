#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
//        vector<int> row(m,0);
//        vector<int> col(n, 0);

        int zero_i = -1;
        int zero_j = -1;
        int i= 0, j=0;
        bool find_zero =false;
        for (;i<m;i++)
        {
            for(;j<n; j++)
            {
                if(matrix[i][j] == 0)
                {
                    zero_i = i;
                    zero_j = j;
                    find_zero = true;
                    break;
                }

            }
            if(find_zero)
                break;
            j = 0;
        }

        if(zero_i == -1)
            return;

        for (i++;i<m;i++)
        {
            for(j=0;j<n; j++)
            {
                if(matrix[i][j] == 0)
                {
                    matrix[zero_i][j] = 0;
                    matrix[i][zero_j] = 0;
                }
            }
            j = 0;
        }

        // turn to zero
        // row
        for (int i = 0; i < m; i++)
        {
            if(i != zero_i && matrix[i][zero_j] == 0)
                for (int j = 0; j < n; j++)
                {
                    matrix[i][j] = 0;
                }
        }
        // col
        for (int j = 0; j < n; j++)
        {
            if(matrix[zero_i][j] == 0)
                for (int i = 0; i <m;i++)
                {
                    matrix[i][j] = 0;
                }
        }

        // row
        for(int j = 0; j < n; j++)
            matrix[zero_i][j] = 0;

    }
};

int main()
{
    Solution solution;
    auto print = [](vector<vector<int>>& matrix)
    {
        for(vector<int>& line: matrix)
        {
            for (int item:line)
            {
                cout << item <<" ";
            }
            cout << "\n";
        }
        cout << "\n";
    };

    auto test = [&](vector<vector<int>> matrix)
    {
        print(matrix);
        solution.setZeroes(matrix);
        print(matrix);
    };


    test({{0,0,0,5},{4,3,1,4},{0,1,1,4},{1,2,1,3},{0,0,1,1}});

    return 0;
}
