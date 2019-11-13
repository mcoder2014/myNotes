#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <limits>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t)
    {
        unordered_map<char, int> ch_in_t;
        unordered_map<char, int> ch_in_s;
        int count = 0, l = 0, r = 0;
        for(int i = 0; i < t.size(); i++)
        {
            ch_in_t[t[i]]++;
        }

        int len_s = s.size(), len_t = t.size();
        int res = numeric_limits<int>::max();
        string ans = "";
        while(r < len_s)
        {
            while(r < len_s && count < len_t)
            {
                char ch = s[r];
                if(ch_in_t[ch] > 0)
                {
                    if(ch_in_s[ch] < ch_in_t[ch])
                        count ++;
                    ch_in_s[s[r]]++;
                }
                r++;
            }
            if(count == len_t)
            {
                while (l < r && count == len_t)
                {
                    char ch = s[l];
                    if(ch_in_t[ch]>0)
                    {
                        ch_in_s[ch]--;
                        if(ch_in_s[ch] < ch_in_t[ch])
                            count --;
                    }
                    l++;
                }
                if(r-l+1 < res)
                {
                    res = r-l+1;
                    ans = s.substr(l-1, res);
                }
            }
        }
        return ans;
    }
};


int main()
{
    Solution solution;

    auto test = [&](string s, string p)
    {
        string res = solution.minWindow(s, p);
        cout << res << endl;
    };

    test("ADOBECODEBANC", "ABC");
    return 0;
}
