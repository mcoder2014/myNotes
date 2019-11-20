#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        if(matrix.size() == 0)
            return false;
        if(matrix[0].size()==0)
            return false;
        int m = matrix.size(), n = matrix[0].size();
        int l = 0, r = m*n-1, mid;
        while (l <r)
        {
            mid = (l+r)/2;
            if(matrix[mid/n][mid%n] == target)
                return true;
            else if(matrix[mid/n][mid%n] > target)
                r = mid-1;
            else
                l = mid +1;
        }
        return matrix[l/n][l%n]==target;
    }
};

int main()
{
    Solution solution;
    auto test = [&](vector<vector<int>> mat, int target)
    {
        bool res = solution.searchMatrix(mat, target);
        cout << res << endl;
    };

    test( {
              {1,   3,  5,  7},
              {10, 11, 16, 20},
              {23, 30, 34, 50}
          }, 3);
    test( {
              {1,   3,  5,  7},
              {10, 11, 16, 20},
              {23, 30, 34, 50}
          }, 12);
    return 0;
}
