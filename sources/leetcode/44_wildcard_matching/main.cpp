#include <iostream>

#include <string>
#include <vector>

using namespace std;

/*
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 */
class Solution {
public:
    bool isMatch(string s, string p)
    {
        return helper(s,p,0,0);
    }
    bool bottom_up(string s, string p)
    {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for (int i = 0;i <=m; i++)
        {
            for(int j = 1; j <=n; j++)
            {
                if(p[j-1]=='*')
                {
                    dp[i][j] = dp[i][j-1] || (i>0 ? dp[i-1][j] : false);
                }
                else
                {
                    dp[i][j] = i > 0 && dp[i-1][j-1] && (s[i-1]==p[j-1] || p[j-1]=='?');
                }
            }
        }
        return dp[m][n];
    }

    bool helper(string& s, string& p, int i, int j)
    {

        int m = s.size(), n = p.size();
        if(n == j)
        {
            return i == m;
        }

        if(p[j] != '*')
        {
            if(i < m && (s[i]==p[j]||p[j]=='?'))
            {
                bool res = helper(s,p,i+1, j+1);
                return res;
            }
        }
        else
        {
            if(helper(s,p,i,j+1))
            {
                return true;
            }
            while(i < m)
            {
                if(helper(s,p,++i,j+1))
                {
                    return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    Solution solution;
    auto test = [&](string s, string p)
    {
        bool res = solution.isMatch(s, p);
        cout << s << "\n"
             << p << "\n"
             << res << "\n\n";
    };

    test("aa","a");         // False
    test("aa","*");         // True
    test("cb","?a");        // False
    test("adceb","a*b");    // True
    test("adceb", "*a*b");  // True
    test("","*");           // True
    test("acdcb","a*c?b");  // False
    test("babaaababaabababbbbbbaabaabbabababbaababbaaabbbaaab","***bba**a*bbba**aab**b");
    test("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba","a*******b");

    return 0;
}
