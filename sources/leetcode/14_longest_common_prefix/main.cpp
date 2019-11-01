#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 0)
            return "";

        string result = strs[0];
        for(string comp:strs)
        {
            int size = result.size();
            if(size == 0)
                return "";

            for(int i = 0; i < size; i++)
            {
                if(result[i] != comp[i])
                {
                    result = result.substr(0,i);
                    break;
                }
            }
        }
        return result;
    }
};

int main()
{
    Solution solution;
    auto test = [&](vector<string> strs)
    {
        string pre = solution.longestCommonPrefix(strs);
        cout << pre << endl;
    };

    test({"flower", "flow", "flight"});
    test({"dog", "racecar", "car"});


    return 0;
}
