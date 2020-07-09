#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current_selection;
        if(candidates.size() == 0)
            return result;

        sort(candidates.begin(), candidates.end());
        helper(current_selection, result, candidates, 0, target);
        return result;
    }

    bool helper(vector<int>& current_selection, vector<vector<int>>& result, vector<int>& candidates,  int i, int target )
    {
        if(!(i < candidates.size()) || target < 0)
            return false;
        if(target < candidates[i])
        {
            return false;
        }
        else if(target == candidates[i])
        {
            // 加入答案
            current_selection.push_back(candidates[i]);
            result.push_back(current_selection);
            current_selection.pop_back();

            return true;
        }
        else if (target > candidates[i])
        {
            // 不选择当前值
            bool flag1 = helper(current_selection, result, candidates, i+1, target);

            // 选择当前值
            current_selection.push_back(candidates[i]);
            bool flag2 = helper(current_selection, result, candidates, i, target-candidates[i]);
            current_selection.pop_back();
            return  flag1 || flag2;
        }
        return true;
    }


    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current_selection;
        if(candidates.size() == 0)
            return result;

        sort(candidates.begin(), candidates.end());
        helper2(current_selection, result, candidates, 0, target);
        return result;
    }


    bool helper2(vector<int>& current_selection, vector<vector<int>>& result, vector<int>& candidates,  int i, int target )
    {
        if(!(i < candidates.size()) || target < 0)
            return false;
        if(target < candidates[i])
        {
            return false;
        }
        else if(target == candidates[i])
        {
            // 加入答案
            current_selection.push_back(candidates[i]);
            result.push_back(current_selection);
            current_selection.pop_back();

            return true;
        }
        else if (target > candidates[i])
        {
            // 不选择当前值
            int k = i;
            while(k+1 < candidates.size() && candidates[k+1] == candidates[k])
                  k++;
            bool flag1 = helper2(current_selection, result, candidates, k+1, target);

            // 选择当前值
            current_selection.push_back(candidates[i]);
            bool flag2 = helper2(current_selection, result, candidates, i+1, target-candidates[i]);
            current_selection.pop_back();
            return  flag1 || flag2;
        }
        return true;
    }

};

int main()
{
    Solution solution;

    auto test = [&](vector<int> candidates, int target)
    {
        vector<vector<int>> result = solution.combinationSum(candidates, target);
        for (vector<int>& line:result)
        {
            for(int item:line)
                cout << item << "\t";
            cout << endl;
        }
        cout << endl;
    };


    auto test2 = [&](vector<int> candidates, int target)
    {
        vector<vector<int>> result = solution.combinationSum2(candidates, target);
        for (vector<int>& line:result)
        {
            for(int item:line)
                cout << item << "\t";
            cout << endl;
        }
        cout << endl;
    };

    test({2,3,6,7}, 7);
    test({2,3,5}, 8);

    test2({10,1,2,7,6,1,5}, 8);
    test2({2,5,2,1,2}, 5);


    return 0;
}
