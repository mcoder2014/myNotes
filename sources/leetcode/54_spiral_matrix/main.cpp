#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        if(matrix.size() == 0)
            return vector<int>();

        int top = 0, bottom = matrix.size(), left=0,right = matrix[0].size();
        int i=0,j=0;
        int direction = 0;
        vector<int> result;
        while (i >= top && i< bottom && j >=left &&j < right)
        {
            result.push_back(matrix[i][j]);
            if(direction%4==0)
            {
                if(! (++j < right))
                {
                    j--;
                    i++;
                    top++;
                    direction++;
                }
            }
            else if(direction%4==1)
            {
                if(!(++i<bottom))
                {
                    i--;
                    j--;
                    right--;
                    direction++;
                }
            }
            else if(direction%4==2)
            {
                if(!(--j >= left))
                {
                    j++;
                    i--;
                    bottom--;
                    direction++;
                }
            }
            else if (direction%4==3)
            {
                if(!(--i >=top))
                {
                    i++;
                    j++;
                    left ++;
                    direction++;
                }
            }
        }
        return result;
    }

};


int main()
{
    Solution solution;
    auto test = [&](vector<vector<int>> matrix)
    {
        vector<int> res = solution.spiralOrder(matrix);
        for(int item:res)
            cout << item << " ";
        cout << endl;
    };

    test({{1,2,3,4},{5,6,7,8},{9,10,11,12}});
    test({{1}});
    test({{1,2},{3,4},{5,6}});

    return 0;
}
