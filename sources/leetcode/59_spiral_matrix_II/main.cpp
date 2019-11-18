#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n)
    {
        vector<vector<int>> res(n,vector<int>(n,0));
        int direction = 0;
        int top = 0, bottom = n, left = 0, right = n;
        int i=0,j=0;
        int idx = 1;
        while(i >= top && i < bottom
              && j>= left && j < right)
        {
            res[i][j] = idx++;
            if(direction%4 == 0)
            {
                if(!(++j <right))
                {
                    j--;
                    i++;
                    direction++;
                    top++;
                }
            }
            else if(direction%4 == 1)
            {
                if(!(++i<bottom))
                {
                    i--;
                    j--;
                    right--;
                    direction++;
                }
            }
            else if(direction%4 == 2)
            {
                if(!(--j >= left))
                {
                    --i;
                    j++;
                    bottom--;
                    direction++;
                }
            }
            else if(direction %4 == 3)
            {
                if(!(--i >= top))
                {
                    i++;
                    j++;
                    direction++;
                    left++;
                }
            }
        }
        return res;
    }
};

int main()
{

    return 0;
}
