#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> map;
        for(int i = 0; i < strs.size(); i++)
        {
            string s = strs[i];
            sort(s.begin(), s.end());
            map[s].push_back(strs[i]);
        }
        for(pair<string, vector<string>> pa:map)
        {
            result.push_back(pa.second);
        }
        return result;
    }
};


int main()
{

    Solution solution;
    auto test = [&](vector<string> strs)
    {
        vector<vector<string>> result = solution.groupAnagrams(strs);
        for (vector<string>& line: result)
        {
            for (string & s:line ) {
                cout << s << "\t";
            }
            cout << "\n";
        }
        cout << "\n";
    };

    test({"eat", "tea", "tan", "ate", "nat", "bat"});

    return 0;
}
