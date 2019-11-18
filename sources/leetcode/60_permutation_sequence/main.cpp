#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k)
    {
        vector<int> nums(n);
        for(int i = 0; i < n; i++)
        {
            nums[i] = i+1;
        }

        auto nextPermutation = [&]()
        {
            int i = n-2, j=n-1;
            while(i >= 0)
            {
                if(nums[i] < nums[i+1])
                    break;
                i--;
            }

            if(i == -1)
            {
                // end
                reverse(nums.begin(), nums.end());
            }

            while(j>i)
            {
                if(nums[j] > nums[i])
                    break;
                j--;
            }
            swap(nums[i], nums[j]);
            sort(nums.begin()+i+1, nums.end());
        };

        for (int i= 1; i<k; i++)
            nextPermutation();

        string res;
        for (int item:nums) {
            res += static_cast<char>('0'+item);
        }
        return res;
    }

};

int main()
{
    Solution solution;
    auto test = [&](int n, int k)
    {
        string res = solution.getPermutation(n, k);
        cout << res << endl;
    };

    test(9, 233794);

    return 0;
}
