#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height)
    {
        if(height.size() <= 1)
            return 0;
        int maxLeft =0, maxRight = 0;
        int result = 0;
        int left = 0, right = height.size()-1;
        while ( left < right)
        {
            if(height[left] <= height[right])
            {
                if(height[left] > maxLeft)
                    maxLeft = height[left];
                else
                    result += maxLeft-height[left];
                left++;
            }
            else
            {
                if(height[right] >maxRight)
                    maxRight = height[right];
                else
                    result += maxRight-height[right];
                right --;
            }
        }
        return result;

    }
};

int main()
{
    Solution solut;

    auto test = [&](vector<int> height)
    {
        int res = solut.trap(height);
        cout << res << endl;
    };

    test({0,1,0,2,1,0,1,3,2,1,2,1});
    return 0;
}
