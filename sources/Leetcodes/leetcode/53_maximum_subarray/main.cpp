#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums)
    {

        int ans=nums[0],i,j,sum=0;
        for(i=0;i<nums.size();i++)
        {
            sum+=nums[i];
            ans=max(sum,ans);
            sum=max(sum,0);
        }
        return ans;

        return find_maximum_subarray(nums,0,nums.size()-1);
    }

    int find_max_crossing_subarray(std::vector<int> &A, int low, int mid, int high)
    {
        int left_sum = std::numeric_limits<int>::min();
        int sum = 0;
        int max_left = mid;
        for(int i = mid; i >= low; i--)
        {
            sum = sum + A[static_cast<uint>(i)];
            if(sum > left_sum)
            {
                left_sum = sum;
                max_left = i;
            }
        }

        int right_sum = std::numeric_limits<int>::min();
        int max_right = mid + 1;
        sum = 0;
        for (int j = mid + 1; j <= high; j++)
        {
            sum = sum + A[static_cast<uint>(j)];
            if(sum > right_sum)
            {
                right_sum = sum;
                max_right = j;
            }
        }
        return left_sum + right_sum;
    }

    int find_maximum_subarray(std::vector<int> &A, int low, int high)
    {

        if(low == high)
        {

            return A[low];

        }
        else
        {

            int mid = (low + high) / 2;
            int left = find_maximum_subarray(A, low, mid);
            int right = find_maximum_subarray(A, mid + 1, high);
            int cross = find_max_crossing_subarray(A, low, mid, high);

            if(left >= right && left >= cross)
            {
                return left;
            }
            else if (right >= left && right >= cross)
            {
                return right;
            }
            else
            {
                return cross;
            }
        }
    }

};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
