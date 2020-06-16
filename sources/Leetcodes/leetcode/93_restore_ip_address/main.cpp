#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s)
    {
        vector<string> result;
        vector<int> split(4,0);
        helper(s,0,split,result,0);
        return result;
    }

    int helper(string s, int idx, vector<int>& split,
               vector<string>& result, int dst)
    {
        int length = s.length();
        if(dst == 4 && idx == length)
        {
            // add into res
            string res  = s.substr(0, split[0]) + '.'
                    + s.substr(split[0], split[1]) + '.'
                    + s.substr( split[0]+split[1], split[2]) + '.'
                    + s.substr(split[0] + split[1] + split[2], split[3]);
            result.push_back(res);
            return 1;
        }
        else if(dst == 4)
        {
            return 0;
        }

        int total = 0;
        int res = 0;
        int i;
        for (i =0; i < 3 && idx + i < length; i++)
        {
            res = (s[idx+i]-'0') + res*10;
            if(res > 255 || res == 0)
            {
                break;
            }

            split[dst] = i+1;
            total += helper(s,idx+i+1,split,result,dst+1);
            split[dst] = 0;
        }

        if(res == 0 && i == 0 && idx + i < length)
        {
            // deal with zero
            split[dst] = 1;
            total += helper(s,idx+1,split,result,dst+1);
            split[dst] = 0;
        }
        return total;
    }

};


int main()
{
    Solution solution;
    auto test = [&](string s)
    {
        vector<string> result = solution.restoreIpAddresses(s);
        for (string& st:result)
        {
            cout << st << "\n";
        }
    };

    test("0000");
    test("10000");
    test("25525511135");
    test("0");
    return 0;
}
