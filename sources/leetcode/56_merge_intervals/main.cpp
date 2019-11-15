#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        // 先排序
        sort(intervals.begin(),intervals.end(),[](vector<int>& v1, vector<int>& v2)
        { return v1[0] < v2[0]; });

        // 在合并
        for (vector<vector<int>>::iterator iter = intervals.begin();
                (iter)!=intervals.end() && (iter+1)!=intervals.end(); )
        {
            vector<int> &cur = *iter;
            vector<int> &next = *(iter+1);
            if(cur[1] >= next[0])
            {
                cur[1] = next[1] > cur[1]? next[1]:cur[1];
                intervals.erase(iter+1);
            }
            else
            {
                iter++;
            }
        }
        return intervals;
    }

};

int main()
{
    Solution solution;
    auto test = [&](vector<vector<int>> intervals)
    {
        vector<vector<int>> res = solution.merge(intervals);
        for(auto cp:res)
        {
            for(int item:cp)
            {
                cout << item << " ";
            }
            cout << "\t\t";
        }
        cout << endl;

    };

    test({{1,4},{0,4}});
    test({{1,4},{4,5}});
    test({{1,3},{2,6},{8,10},{15,18}});
    return 0;
}
