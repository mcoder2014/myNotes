#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) 
    {
        // return helper(s,t,0,0);
        return dp(s,t);
    }

    int helper(string& s, string& t, int start, int ch_idx)
    {
        // 终止条件
        if(ch_idx == t.length())
            return 1;
        if(start >= s.length()
            || start + t.length() - ch_idx > s.length())
            return 0;

        int len1 = s.length();
        int len2 = t.length();

        int count = 0;
        for(int i = start; i < len1; i++ )
        {
            if(s[i] == t[ch_idx])
            {
                count += helper(s,t,i+1,ch_idx+1);
            }
        }

        return count;
    }

    int dp(string& s, string& t) 
    {
        int m = t.length(), n = s.length();
        vector<vector<uint64_t>> dp(m + 1, vector<uint64_t> (n + 1, 0));
        for (int j = 0; j <= n; j++) 
            dp[0][j] = 1;

        for (int j = 1; j <= n; j++)
        {
            for (int i = 1; i <= m; i++)
            {
                dp[i][j] = dp[i][j - 1] 
                    + (t[i - 1] == s[j - 1] ? dp[i - 1][j - 1] : 0);
            }
        }
        return dp[m][n];
    }
};

int main()
{

    Solution sol;
    auto test = [&](string s, string t)
    {
        int count =  sol.numDistinct(s,t);
        cout<< "count: " << count << endl;
    };

    test("rabbbit","rabbit");
    test("babgbag","bag");
    test("adbdadeecadeadeccaeaabdabdbcdabddddabcaaadbabaaedeeddeaeebcdeabcaaaeeaeeabcddcebddebeebedaecccbdcbcedbdaeaedcdebeecdaaedaacadbdccabddaddacdddc"
        ,"bcddceeeebecbc");

    return 0;
}