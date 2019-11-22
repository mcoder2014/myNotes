#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums)
    {
        int n = nums.size();
        // 0,1,...,n
        vector<vector<int>> result;
        for (int i = 0; i <=n; i++)
        {
            vector<vector<int>> tmp_res = combine(nums, i);
            for(vector<int>& line: tmp_res)
            {
                result.push_back(line);
            }
        }
        return result;
    }

    vector<vector<int>> combine(vector<int>&nums, int k)
    {
        if(k == 0)
            return vector<vector<int>>(1,vector<int>());

        int n = nums.size();
        vector<int> pos(k, 0);
        vector<vector<int>> result;
        for(int i = 0; i < k; i++)
            pos[i] = i;

        while (pos[0] <= n-k)
        {
            //result
            vector<int> res;
            for(int i = 0; i < k; i++)
                res.push_back(nums[pos[i]]);
            result.push_back(res);

            // next
            int x = k-1;
            for(; x>=0; x--)
                if(pos[x]<n-k+x)
                    break;
            if(x<0)
                break;
                pos[x]++;
                for(x++; x<k; x++)
                    pos[x] = pos[x-1]+1;
        }
        return result;
    }
};

int main()
{

    return 0;
}
